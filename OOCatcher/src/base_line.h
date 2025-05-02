#pragma once

class base_line {
public:
    virtual double get_x() const = 0;
    virtual double get_y() const = 0;
    virtual double end_x() const = 0;
    virtual double end_y() const = 0;

    virtual int int_x() const final { return static_cast<int>(get_x() + 0.5); }
    virtual int int_y() const final { return static_cast<int>(get_y() + 0.5); }
    virtual int ent_x() const final { return static_cast<int>(end_x() + 0.5); }
    virtual int ent_y() const final { return static_cast<int>(end_y() + 0.5); }

    virtual double length() const = 0;
    virtual double slope() const = 0;

    virtual void shift(double dx, double dy) = 0;
    virtual void rotate(double da) = 0;

    virtual ~base_line() = default;
};
