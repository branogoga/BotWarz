#pragma once

#include "./../dll.h"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Geometry {

    class Point;

    class TESTABLE Vector
    {
    public:
        Vector(double i_X = 0.0, double i_Y = 0.0)
            : m_X(i_X), m_Y(i_Y)
        {    
        }

        virtual ~Vector()
        {
        }

        double x() const
        {
            return m_X;
        }

        double y() const
        {
            return m_Y;
        }

    private:
        double m_X;
        double m_Y;
    };

    TESTABLE double lengthSquare(const Geometry::Vector& vector);
    TESTABLE double length(const Geometry::Vector& vector);
    TESTABLE Geometry::Vector normalize(const Geometry::Vector& vector);

    TESTABLE double dotProduct(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
    TESTABLE bool arePerpendicular(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
    TESTABLE bool areParallel(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
    TESTABLE double angleInRadians(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
    TESTABLE double angleInDegrees(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
    TESTABLE bool   isConvexAngle(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
    TESTABLE bool   isConcaveAngle(const Geometry::Vector& vector1, const Geometry::Vector& vector2);

    TESTABLE Geometry::Vector clockwisePerpendicular(const Geometry::Vector& vector);
    TESTABLE Geometry::Vector counterClockwisePerpendicular(const Geometry::Vector& vector);

}//namespace Geometry

TESTABLE Geometry::Point operator+(const Geometry::Point& point, const Geometry::Vector& vector);
TESTABLE Geometry::Vector operator-(const Geometry::Point& point1, const Geometry::Point& point2);

TESTABLE Geometry::Vector operator+(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
TESTABLE double operator*(const Geometry::Vector& vector1, const Geometry::Vector& vector2);
TESTABLE Geometry::Vector operator*(double scale, const Geometry::Vector& vector);
TESTABLE Geometry::Vector operator*(const Geometry::Vector& vector, double scale);
TESTABLE Geometry::Vector operator/(const Geometry::Vector& vector, double scale);

std::ostream& operator << (std::ostream& out, const Geometry::Vector& vector);


