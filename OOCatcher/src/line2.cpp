#include "../inlucde/line2.h"
#include "../include/line2.h"


line2::line2(point& that_p1, point& that_p2) :
    start(std::make_shared<point>(that_p1)),
    end(std::make_shared<point>(that_p2)) {}

line2::line2(std::shared_ptr<point> that_ptr1, std::shared_ptr<point> that_ptr2) :
    start(that_ptr1), end(that_ptr2) {}

double line2::get_x() const { return start->get_x(); }
double line2::get_y() const { return start->get_y(); }
double line2::end_x() const { return end->get_x(); }
double line2::end_y() const { return end->get_y(); }

double line2::length() const { return start->dist(*end); }
double line2::slope() const { return start->dir(*end); }

void line2::shift(double dx, double dy) {
    start->shift(dx, dy);
    end->shift(dx, dy);
}

void line2::rotate(double da) {
    double len = length(), ang = slope() + da;
    end->shift(
        start->get_x() + len * cos(ang) - end->get_x(),
        start->get_y() + len * sin(ang) - end->get_y()
    );
}
