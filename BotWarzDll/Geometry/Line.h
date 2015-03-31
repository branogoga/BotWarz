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
        const Line& line
        );

    TESTABLE bool    areLinesParallel(
        const Line& line1, const Line& line2
        );

    TESTABLE bool    doLinesIntersect(
        const Line& line1, const Line& line2
        );

    TESTABLE double     angleInRadians(
        const Line& line1, const Line& line2
        );

    TESTABLE double     angleInDegrees(
        const Line& line1, const Line& line2
        );

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Line& line);


