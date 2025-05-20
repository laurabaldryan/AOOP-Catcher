#pragma once

#include <vector>
#include <memory>
#include "point.h"
#include "base_line.h"
#include "line1.h"
#include "line2.h"

class body {
public:
    body(double ground_left_x, double ground_right_x, double ground_y);

    void update_structure();
    void update_fingers_and_toes();
    void shift_body(double dx, double dy);
    bool can_grab(const point& obj, double radius) const;
    void animate_throw();
    void animate_catch();

    point ball;

    const std::vector<std::unique_ptr<base_line>>& get_limbs() const;
    const std::vector<std::unique_ptr<base_line>>& get_fingers() const;
    const std::vector<std::unique_ptr<base_line>>& get_toes() const;
    const point& get_head_center() const;

private:
    point footL, footR, hip;
    point neck_base, neck_top, head_center;

    std::vector<std::unique_ptr<base_line>> limbs;
    std::vector<std::unique_ptr<base_line>> fingers;
    std::vector<std::unique_ptr<base_line>> toes;
};
