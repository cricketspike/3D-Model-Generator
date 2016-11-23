#include "color.h"

Color::Color() {
    r = g = b = 0;
    a = 1;
}

Color::Color(double r, double g, double b, double a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
