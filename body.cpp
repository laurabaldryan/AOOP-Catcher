// ======================= body.cpp =======================
#include "body.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

using namespace std;

body::body(double ground_left_x, double ground_right_x, double ground_y) {
    footL = point(ground_left_x, ground_y);
    footR = point(ground_right_x, ground_y);
    hip = point((footL.get_x() + footR.get_x()) / 2, ground_y + 45.0);
    update_structure();
    update_fingers_and_toes();
    ball = point(fingers.back()->end_x(), fingers.back()->end_y() + 100);
}

void body::update_structure() {
    limbs.clear();

    double legLen = 45.0;
    double torsoLen = 35.0;
    double armLen = 30.0;
    double headRadius = 8.0;

    limbs.push_back(make_unique<line2>(footL, hip));
    limbs.push_back(make_unique<line2>(footR, hip));

    neck_base = hip;
    neck_top = point(hip.get_x(), hip.get_y() + torsoLen);
    limbs.push_back(make_unique<line2>(neck_base, neck_top));

    point left_arm_end(neck_top.get_x() - armLen, neck_top.get_y());
    point right_arm_end(neck_top.get_x() + armLen, neck_top.get_y());
    limbs.push_back(make_unique<line2>(neck_top, left_arm_end));
    limbs.push_back(make_unique<line2>(neck_top, right_arm_end));

    head_center = point(neck_top.get_x(), neck_top.get_y() + headRadius);
}

void body::update_fingers_and_toes() {
    fingers.clear();
    toes.clear();

    double finger_len = 0.6;  // Truly small fingers
    for (int i = 3; i <= 4; ++i) {
        point base = point(limbs[i]->end_x(), limbs[i]->end_y());

        for (int j = -1; j <= 0; ++j) {
            double spread = j * 0.25;
            double adjusted_angle = -PI / 2 + spread; // Always downward

            point tip(
                base.get_x() + finger_len * cos(adjusted_angle),
                base.get_y() + finger_len * sin(adjusted_angle)
            );

            fingers.push_back(make_unique<line1>(base, tip));
        }
    }

    double toe_len = 3.0;
    for (int i = 0; i <= 1; ++i) {
        auto& leg = limbs[i];
        double angle = atan2(leg->end_y() - leg->get_y(), leg->end_x() - leg->get_x());
        point base(leg->get_x(), leg->get_y());

        for (int j : {-1, 1}) {
            double offset = j * 0.5;
            double adjusted_angle = angle + offset;

            toes.push_back(make_unique<line1>(
                base,
                point(base.get_x() + toe_len * cos(adjusted_angle),
                      base.get_y() + toe_len * sin(adjusted_angle))
            ));
        }
    }
}

void body::shift_body(double dx, double dy) {
    footL.shift(dx, dy);
    footR.shift(dx, dy);
    hip.shift(dx, dy);
    neck_base.shift(dx, dy);
    neck_top.shift(dx, dy);
    head_center.shift(dx, dy);
    ball.shift(dx, dy);

    for (auto& limb : limbs) limb->shift(dx, dy);
    for (auto& f : fingers) f->shift(dx, dy);
    for (auto& t : toes) t->shift(dx, dy);
}

bool body::can_grab(const point& obj, double radius) const {
    int contact = 0;
    for (const auto& f : fingers) {
        double dx = f->end_x() - obj.get_x();
        double dy = f->end_y() - obj.get_y();
        if (sqrt(dx * dx + dy * dy) <= radius) contact++;
    }
    return contact >= 2;
}

void body::animate_throw() {
    double tx = fingers.back()->end_x();
    double ty = fingers.back()->end_y();
    double dx = tx - ball.get_x();
    double dy = ty - ball.get_y();
    ball = point(ball.get_x() + dx * 0.05, ball.get_y() + dy * 0.05);
}

void body::animate_catch() {
    double tx = fingers.back()->end_x();
    double ty = fingers.back()->end_y();
    double dx = tx - ball.get_x();
    double dy = ty - ball.get_y();
    ball = point(ball.get_x() + dx * 0.05, ball.get_y() + dy * 0.05);
}

const std::vector<std::unique_ptr<base_line>>& body::get_limbs() const { return limbs; }
const std::vector<std::unique_ptr<base_line>>& body::get_fingers() const { return fingers; }
const std::vector<std::unique_ptr<base_line>>& body::get_toes() const { return toes; }
const point& body::get_head_center() const { return head_center; }
