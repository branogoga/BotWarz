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

}//namespace Geometry

TESTABLE Geometry::Point operator+(const Geometry::Point& point, const Geometry::Vector& vector);
TESTABLE Geometry::Vector operator-(const Geometry::Point& point1, const Geometry::Point& point2);

std::ostream& operator << (std::ostream& out, const Geometry::Vector& vector);


