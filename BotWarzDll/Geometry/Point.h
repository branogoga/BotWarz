#pragma once

#include "./../dll.h"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Geometry {

    class DLL_API Point
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

    DLL_API double  distanceSquare(const Point& point1, const Point& point2);
    DLL_API double  distance(const Point& point1, const Point& point2);
    DLL_API size_t  closestPointIndex(const std::vector<Point>& i_vPoints, const Point& i_point);
    DLL_API double  angleInRadians(const Point& point1, const Point& point2);
    DLL_API double  angleInDegrees(const Point& point1, const Point& point2);
    DLL_API double  convertAngleFromRadiansToDegrees(double i_dAngleInRadians);
    DLL_API double  convertAngleFromDegreesToRadians(double i_dAngleInDegrees);
    DLL_API bool    doLinesIntersect(
        const Point& startLine1, const Point& endLine1,
        const Point& startLine2, const Point& endLine2
        );

}//namespace Geometry

DLL_API std::ostream& operator << (std::ostream& out, const Geometry::Point& point);


