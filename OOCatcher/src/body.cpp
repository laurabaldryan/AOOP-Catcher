#include "body.h"

body::body(double neck_x, double neck_y, double seg_length) :
    neck_ptr(make_shared<point>(neck_x, neck_y)),
    back_ptr(make_shared<point>(neck_x, neck_y - seg_length)),
    engine(static_cast<mt19937::result_type>(seeder.entropy() > 0 ? seeder() : _time64(nullptr))),
    choose_seg(0, size(segs) - 1),
    choose_ang(-0.5, 0.5)  // small rotation angle
{
    segs[0] = make_unique<line1>(neck_ptr, back_ptr); // armL
    segs[1] = make_unique<line1>(neck_ptr, back_ptr); // armR

    segs[2] = make_unique<line1>(back_ptr, neck_ptr); // legL
    segs[3] = make_unique<line1>(back_ptr, neck_ptr); // legR

    segs[4] = make_unique<line2>(neck_ptr, back_ptr); // torsoD
    segs[5] = make_unique<line2>(back_ptr, neck_ptr); // torsoU

    const double PI = acos(-1);
    segs[0]->rotate(-PI / 2);       // WEST
    segs[1]->rotate( PI / 2);       // EAST
    segs[2]->rotate( 3 * PI / 4);   // SOUTH-WEST
    segs[3]->rotate(-3 * PI / 4);   // SOUTH-EAST
}

void body::seg_rotate() {
    segs[choose_seg(engine)]->rotate(choose_ang(engine));
}

void body::seg_rotate(int index) {
    segs[index]->rotate(choose_ang(engine));
}

void body::print(int highlight) {
    cout << "\n";
    for (int i = 0; i < size(segs); i++) {
        cout << format("{}[{}]: ({}, {})-({}, {})\n",
            (i == highlight ? "SEG" : "seg"), i,
            segs[i]->int_x(), segs[i]->int_y(),
            segs[i]->ent_x(), segs[i]->ent_y());
    }
}

void body::save(ofstream& file) {
    for (int i = 0; i < size(segs); i++) {
        file << segs[i]->int_x() << " "
             << segs[i]->int_y() << " "
             << segs[i]->ent_x() << " "
             << segs[i]->ent_y() << " ";
    }
    file << "\n";
}

void body::rotate(int steps, void (*method_ptr)(body*)) {
    auto rand_index = bind(choose_seg, engine);
    auto rand_angle = bind(choose_ang, engine);

    if (method_ptr == nullptr) {
        for (; steps > 0; steps--) {
            segs[rand_index()]->rotate(rand_angle());
        }
    } else {
        for (; steps > 0; steps--) {
            segs[rand_index()]->rotate(rand_angle());
            method_ptr(this);
        }
    }
}

void print(body* ptr) {
    cout << "\n";
    for (int i = 0; i < size(ptr->segs); i++) {
        cout << format("seg[{}]: ({}, {})-({}, {})\n", i,
            ptr->segs[i]->int_x(), ptr->segs[i]->int_y(),
            ptr->segs[i]->ent_x(), ptr->segs[i]->ent_y());
    }
}

void save(body* ptr) {
    ofstream file("moves.dat", ios_base::trunc);
    for (int i = 0; i < size(ptr->segs); i++) {
        file << ptr->segs[i]->int_x() << " "
             << ptr->segs[i]->int_y() << " "
             << ptr->segs[i]->ent_x() << " "
             << ptr->segs[i]->ent_y() << " ";
    }
    file << "\n";
}
