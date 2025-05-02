#include "object.h"

object::object(double x, double y, double r) : center(x, y), radius(r) {}

bool object::is_grabbed_by(const body& b) const {
    int count = 0;
    for (const auto& seg : b.segs) {
        point a(seg->get_x(), seg->get_y());
        point b(seg->end_x(), seg->end_y());
        if (a.dist(center) <= radius) count++;
        if (b.dist(center) <= radius) count++;
    }
    return count >= 3;
}
