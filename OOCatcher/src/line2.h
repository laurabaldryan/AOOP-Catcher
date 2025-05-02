#pragma once
#include "base_line.h"
#include "point.h"
#include <memory>

class line2 : public base_line {
public:
    line2(point& that_p1, point& that_p2);
    line2(std::shared_ptr<point> that_ptr1, std::shared_ptr<point> that_ptr2);

    double get_x() const override;
    double get_y() const override;
    double end_x() const override;
    double end_y() const override;

    double length() const override;
    double slope()  const override;

    void shift(double dx, double dy) override;
    void rotate(double da) override;

private:
    std::shared_ptr<point> start;
    std::shared_ptr<point> end;
};
