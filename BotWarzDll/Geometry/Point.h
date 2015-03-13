#pragma once

#include "./../dll.h"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Geometry {

    class TESTABLE Point
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

    double dotProduct(const Point& point1, const Point& point2);
    double dotProductWithPerpendicularVector(const Point& point1, const Point& point2);
    TESTABLE double  distanceSquare(const Point& point1, const Point& point2);
    TESTABLE double  distance(const Point& point1, const Point& point2);
    TESTABLE double  pointToLineDistance(
        const Point& point,
        const Point& line1,
        const Point& line2
        );
    TESTABLE size_t  closestPointIndex(const std::vector<Point>& i_vPoints, const Point& i_point);
    TESTABLE double  angleInRadians(const Point& point1, const Point& point2);
    TESTABLE double  angleInDegrees(const Point& point1, const Point& point2);
    TESTABLE double  normalizeAngleInDegrees(const double i_dAngleInDegrees);
    TESTABLE double  convertAngleFromRadiansToDegrees(double i_dAngleInRadians);
    TESTABLE double  convertAngleFromDegreesToRadians(double i_dAngleInDegrees);
    TESTABLE bool    areLinesParallel(
        const Point& startLine1, const Point& endLine1,
        const Point& startLine2, const Point& endLine2
        );

    TESTABLE bool    doLinesIntersect(
        const Point& startLine1, const Point& endLine1,
        const Point& startLine2, const Point& endLine2
        );

    TESTABLE double     lineAngleInRadians(
        const Point& line1_start, const Point& line1_end,
        const Point& line2_start, const Point& line2_end
        );

    TESTABLE double     lineAngleInDegrees(
        const Point& line1_start, const Point& line1_end,
        const Point& line2_start, const Point& line2_end
        );

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Point& point);


