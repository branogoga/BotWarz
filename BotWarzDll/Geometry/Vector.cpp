#include "./Vector.h"
#include "./Point.h"

#include <algorithm>
#include <math.h>

namespace Geometry
{

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Vector& vector)
{
    out << "x: " << vector.x() << ", y: " << vector.y();
    return out;
}

Geometry::Point operator+(const Geometry::Point& point, const Geometry::Vector& vector)
{
    return Geometry::Point(
        point.x() + vector.x(),
        point.y() + vector.y()
        );
}

Geometry::Vector operator-(const Geometry::Point& point1, const Geometry::Point& point2)
{
    return Geometry::Vector(
        point1.x() - point2.x(),
        point1.y() - point2.y()
        );
}


