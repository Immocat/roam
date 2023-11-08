#ifndef CUBICBEZIER_H
#define CUBICBEZIER_H

#include <iostream>
#include "Pinroto.h"


// CubicBezier struct declaration
struct CubicBezier
{
    // Control points
    Vector2 p0, p1, p2, p3;

    // Constructor
    CubicBezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3);

    // Sample the bezier curve at a given t value
    Vector2 Sample(Float t) const;

    // Get the first derivative of the curve at a given t value
    Vector2 Derivative(Float t) const;

    // Get the normalized tangent of the curve at a given t value
    Vector2 Tangent(Float t) const;

    // ToString equivalent in C++
    friend std::ostream& operator<<(std::ostream& os, const CubicBezier& bezier);

    // Equality operators
    bool operator==(const CubicBezier& other) const;
    bool operator!=(const CubicBezier& other) const;
};

#endif // CUBICBEZIER_H
