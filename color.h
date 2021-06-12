#pragma once

// #include "vect3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color[0]) << ' '
        << static_cast<int>(255.999 * pixel_color[1]) << ' '
        << static_cast<int>(255.999 * pixel_color[2]) << '\n';
}