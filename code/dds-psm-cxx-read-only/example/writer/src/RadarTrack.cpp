#include "RadarTrack.hpp"
#include <iostream>

std::ostream&
operator << (std::ostream& os, const RadarTrack& t) {
    os << "(" << t.id() << ", " << t.x() << ", " << t.y() << ")" << std::endl;
    return os;
}

