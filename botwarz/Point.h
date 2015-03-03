#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Geometry {

    class Point
    {
    public:
        Point(double i_X = 0.0, double i_Y = 0.0)
            : m_X(i_X), m_Y(i_Y)
        {    
        }

        virtual ~Point()
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

    double  distanceSquare(const Point& point1, const Point& point2);
    double  distance(const Point& point1, const Point& point2);
    size_t  closestPointIndex(const std::vector<Point>& i_vPoints, const Point& i_point);
    double  angle(const Point& point1, const Point& point2);

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Point& point);


