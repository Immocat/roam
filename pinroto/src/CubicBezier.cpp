#include "CubicBezier.h"

// Constructor definition
CubicBezier::CubicBezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3)
    : p0(p0), p1(p1), p2(p2), p3(p3) {}

// Sample function definition
Vector2 CubicBezier::Sample(Float t) const
{
    Float ti = 1 - t;
    Float t0 = ti * ti * ti;
    Float t1 = 3 * ti * ti * t;
    Float t2 = 3 * ti * t * t;
    Float t3 = t * t * t;
    return t0 * p0 + t1 * p1 + t2 * p2 + t3 * p3;
}

// Derivative function definition
Vector2 CubicBezier::Derivative(Float t) const
{
    Float ti = 1 - t;
    Float tp0 = 3 * ti * ti;
    Float tp1 = 6 * ti * t;
    Float tp2 = 3 * t * t;
    return tp0 * (p1 - p0) + tp1 * (p2 - p1) + tp2 * (p3 - p2);
}

// Tangent function definition
Vector2 CubicBezier::Tangent(Float t) const
{
    Vector2 derivative = Derivative(t);
    return derivative.normalized();
}

// operator<< function definition
std::ostream& operator<<(std::ostream& os, const CubicBezier& bezier)
{
    os << "CubicBezier: (<" << bezier.p0.x() << ", " << bezier.p0.y() << "> <"
       << bezier.p1.x() << ", " << bezier.p1.y() << "> <"
       << bezier.p2.x() << ", " << bezier.p2.y() << "> <"
       << bezier.p3.x() << ", " << bezier.p3.y() << ">)";
    return os;
}

// Equality operators definition
bool CubicBezier::operator==(const CubicBezier& other) const
{
    return p0 == other.p0 && p1 == other.p1 && p2 == other.p2 && p3 == other.p3;
}

bool CubicBezier::operator!=(const CubicBezier& other) const
{
    return !(*this == other);
}

// Hash function for CubicBezier, if needed, can also be placed in a separate .cpp file
namespace std
{
    template <>
    struct hash<CubicBezier>
    {
        std::size_t operator()(const CubicBezier& bezier) const
        {
            std::size_t seed = 0;
            auto hash_combine = [&seed](std::size_t h) {
                seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            };

            hash_combine(std::hash<Float>()(bezier.p0.x()));
            hash_combine(std::hash<Float>()(bezier.p0.y()));
            hash_combine(std::hash<Float>()(bezier.p1.x()));
            hash_combine(std::hash<Float>()(bezier.p1.y()));
            hash_combine(std::hash<Float>()(bezier.p2.x()));
            hash_combine(std::hash<Float>()(bezier.p2.y()));
            hash_combine(std::hash<Float>()(bezier.p3.x()));
            hash_combine(std::hash<Float>()(bezier.p3.y()));

            return seed;
        }
    };
}
