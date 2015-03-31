#include "./Vector.h"
#include "./Angle.h"
#include "./Point.h"

#include <algorithm>
#include <math.h>

namespace Geometry
{

    double dotProduct(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        return vector1.x()*vector2.x()
            + vector1.y()*vector2.y();
    }

    double lengthSquare(const Geometry::Vector& vector)
    {
        return pow(vector.x(), 2.0) + pow(vector.y(), 2.0);
    }

    double length(const Geometry::Vector& vector)
    {
        return sqrt(lengthSquare(vector));
    }

    Geometry::Vector normalize(const Geometry::Vector& vector)
    {
        return vector / length(vector);
    }

    bool arePerpendicular(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        const double Zero = 1E-06;
        return (vector1*vector2) < Zero;
    }

    bool areParallel(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        return arePerpendicular(
            vector1,
            clockwisePerpendicular(vector2)
            );
    }

    double angleInRadians(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        double cosAngle = (vector1*vector2) / (length(vector1)*length(vector2));
        return acos(cosAngle);
    }

    double angleInDegrees(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        return Geometry::convertAngleFromRadiansToDegrees(angleInRadians(vector1, vector2));
    }

    bool   isConvexAngle(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        return vector1*vector2 > 0.0;
    }

    bool   isConcaveAngle(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
    {
        return vector1*vector2 < 0.0;
    }

    Geometry::Vector clockwisePerpendicular(const Geometry::Vector& vector)
    {
        return Geometry::Vector(
            vector.y(),
            -vector.x()
            );
    }

    Geometry::Vector counterClockwisePerpendicular(const Geometry::Vector& vector)
    {
        return Geometry::Vector(
            -vector.y(),
            vector.x()
            );
    }

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Vector& vector)
{
    out << "x: " << vector.x() << ", y: " << vector.y();
    return out;
}

Geometry::Vector operator+(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
{
    return Geometry::Vector(
        vector1.x() + vector2.x(),
        vector1.y() + vector2.y()
        );
}

double operator*(const Geometry::Vector& vector1, const Geometry::Vector& vector2)
{
    return dotProduct(vector1, vector2);
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

Geometry::Vector operator*(double scale, const Geometry::Vector& vector)
{
    return Geometry::Vector(
        scale * vector.x(),
        scale * vector.y()
        );
}

Geometry::Vector operator*(const Geometry::Vector& vector, double scale)
{
    return scale * vector;
}

Geometry::Vector operator/(const Geometry::Vector& vector, double scale)
{
    const double Zero = 1E-06;
    if (fabs(scale) < Zero)
    {
        throw std::invalid_argument("Division by zero");
    }

    return Geometry::Vector(
        vector.x() / scale,
        vector.y() / scale
        );
}

