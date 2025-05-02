#pragma once
#include "point.h"
#include "body.h"

class object {
public:
    point center;
    double radius;

    object(double x, double y, double r);
    bool is_grabbed_by(const body& b) const;
};
