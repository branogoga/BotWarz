#pragma once

#include "./../dll.h"

#include "./Point.h"
#include "./Vector.h"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Geometry {

    class TESTABLE Line
    {
    public:
        Line( const Point& ptStart, const Point& ptEnd )
        {
            m_ptStart = ptStart;
            m_ptEnd = ptEnd;
        }

        Line(const Point& ptStart, const Vector& vDirection)
        {
            m_ptStart = ptStart;
            m_ptEnd = m_ptStart + vDirection;
        }

        Point   from() const
        {
            return m_ptStart;
        }

        Point   to() const
        {
            return m_ptEnd;
        }

        Vector direction() const
        {
            return m_ptEnd - m_ptStart;
        }

        virtual ~Line()
        {
        }

    private:
        Point   m_ptStart;
        Point   m_ptEnd;
    };

    TESTABLE double  pointToLineDistance(
        const Point& point,
        const Point& line1,
        const Point& line2
        );

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

std::ostream& operator << (std::ostream& out, const Geometry::Line& line);


