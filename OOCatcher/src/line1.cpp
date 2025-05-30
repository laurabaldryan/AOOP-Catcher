#include "line1.h"

line1::line1(point& that_p1, point& that_p2) :
    start(std::make_shared<point>(that_p1)),
    len(that_p1.dist(that_p2)),
    ang(that_p1.dir(that_p2)) {}

line1::line1(std::shared_ptr<point> that_ptr1, std::shared_ptr<point> that_ptr2) :
    start(that_ptr1),
    len(that_ptr1->dist(*that_ptr2)),
    ang(that_ptr1->dir(*that_ptr2)) {}

double line1::get_x() const { return start->get_x(); }
double line1::get_y() const { return start->get_y(); }
double line1::end_x() const { return get_x() + len * cos(ang); }
double line1::end_y() const { return get_y() + len * sin(ang); }

double line1::length() const { return len; }
double line1::slope() const { return ang; }

void line1::shift(double dx, double dy) { start->shift(dx, dy); }
void line1::rotate(double da) { ang += da; }
