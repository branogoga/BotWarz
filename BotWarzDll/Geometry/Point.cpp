#include "./Point.h"

#include <algorithm>
#include <math.h>

namespace Geometry
{
    double  distanceSquare(const Point& point1, const Point& point2)
    {
        return pow(point2.x() - point1.x(), 2.0) + pow(point2.y() - point1.y(), 2.0);
    }

    double  distance(const Point& point1, const Point& point2)
    {
        return sqrt(distanceSquare(point1, point2));
    }

    size_t  closestPointIndex(const std::vector<Point>& i_vPoints, const Point& i_point)
    {
        if (i_vPoints.empty())
        {
            throw std::invalid_argument("Cannot find closest point from empty point array.");
        }

        double      dMinDistance = DBL_MAX;
        unsigned    nPointWithMinDistanceIndex = INT_MAX;

        unsigned    nCurrentPointIndex = 0;
        for each(auto currentPoint in i_vPoints)
        {
            double dCurrentDistance = distance(currentPoint, i_point);
            if (dCurrentDistance < dMinDistance)
            {
                dMinDistance = dCurrentDistance;
                nPointWithMinDistanceIndex = nCurrentPointIndex;
            }
            nCurrentPointIndex++;
        }

        return nPointWithMinDistanceIndex;
    }

    double dotProduct(const Point& point1, const Point& point2)
    {
        return (point1.x()*point2.x()) + (point1.y()*point2.y());
    }

    double dotProductWithPerpendicularVector(const Point& point1, const Point& point2)
    {
        return (point1.y()*point2.x()) - (point1.x()*point2.y());
    }

    double determinant(const Point& point1, const Point& point2)
    {
        return (point1.x()*point2.y()) - (point1.y()*point2.x());
    }

    double  angleInRadians(const Point& point1, const Point& point2)
    {
        return atan2(
            point2.y() - point1.y(),
            point2.x() - point1.x()
            );
    }

    double  normalizeAngleInDegrees(const double i_dAngleInDegrees)
    {
        double dAngle = i_dAngleInDegrees;

        while (dAngle < 180.0)
        {
            dAngle += 360.0;
        }

        while (dAngle > 180.0)
        {
            dAngle -= 360.0;
        }

        return dAngle;
    }


    double  convertAngleFromRadiansToDegrees(double i_dAngleInRadians)
    {
        const double Pi = 3.14159265358979323846;
        return (i_dAngleInRadians / Pi) * 180;
    }

    double  convertAngleFromDegreesToRadians(double i_dAngleInDegrees)
    {
        const double Pi = 3.14159265358979323846;
        return (i_dAngleInDegrees / 180) * Pi;
    }

    double  angleInDegrees(const Point& point1, const Point& point2)
    {
        return normalizeAngleInDegrees(
                convertAngleFromRadiansToDegrees(
                    angleInRadians(point1, point2)
                    )
                );
    }

    bool    areLinesParallel(
        const Point& startLine1, const Point& endLine1,
        const Point& startLine2, const Point& endLine2
        )
    {
        const double dPrecision = 1E-06;
        double dIsParallel =
            (startLine1.x() - endLine1.x()) * (startLine2.y() - endLine2.y())
            - (startLine1.y() - endLine1.y()) * (startLine2.x() - endLine2.x());
        return (dIsParallel < dPrecision);
    }

    namespace {

        //http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
        // Given three colinear points p, q, r, the function checks if
        // point q lies on line segment 'pr'
        bool onSegment(const Point& p, const Point& q, const Point& r)
        {
            if (q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x()) &&
                q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y()))
                return true;

            return false;
        }

        // To find orientation of ordered triplet (p, q, r).
        // The function returns following values
        // 0 --> p, q and r are colinear
        // 1 --> Clockwise
        // 2 --> Counterclockwise
        typedef enum LineOrientation
        {
            Colinear = 0,
            Clockwise = 1,
            Counterclockwise = 2
        };

        int orientation(const Point& p, const Point& q, const Point& r)
        {
            // See 10th slides from following link for derivation of the formula
            // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
            double val = (q.y() - p.y()) * (r.x() - q.x()) -
                (q.x() - p.x()) * (r.y() - q.y());

            if (val < 1E-06)
            {
                return LineOrientation::Colinear;  // colinear
            }

            return (val > 0) ? LineOrientation::Clockwise : LineOrientation::Counterclockwise; // clock or counterclock wise
        }

        // The main function that returns true if line segment 'p1q1'
        // and 'p2q2' intersect.
        bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2)
        {
            // Find the four orientations needed for general and
            // special cases
            int o1 = orientation(p1, q1, p2);
            int o2 = orientation(p1, q1, q2);
            int o3 = orientation(p2, q2, p1);
            int o4 = orientation(p2, q2, q1);

            // General case
            if (o1 != o2 && o3 != o4)
                return true;

            // Special Cases
            // p1, q1 and p2 are colinear and p2 lies on segment p1q1
            if (o1 == LineOrientation::Colinear && onSegment(p1, p2, q1)) return true;

            // p1, q1 and p2 are colinear and q2 lies on segment p1q1
            if (o2 == LineOrientation::Colinear && onSegment(p1, q2, q1)) return true;

            // p2, q2 and p1 are colinear and p1 lies on segment p2q2
            if (o3 == LineOrientation::Colinear && onSegment(p2, p1, q2)) return true;

            // p2, q2 and q1 are colinear and q1 lies on segment p2q2
            if (o4 == LineOrientation::Colinear && onSegment(p2, q1, q2)) return true;

            return false; // Doesn't fall in any of the above cases
        }
    }

    bool    doLinesIntersect(
        const Point& startLine1, const Point& endLine1,
        const Point& startLine2, const Point& endLine2
        )
    {
        return doIntersect(
            startLine1, endLine1,
            startLine2, endLine2
            );
    }

    double     lineAngleInRadians(
        const Point& line1_start, const Point& line1_end,
        const Point& line2_start, const Point& line2_end
        )
    {
        double dx21 = line1_end.x() - line1_start.x();
        double dy21 = line1_end.y() - line1_start.y();
        double dx31 = line2_end.x() - line2_start.x();
        double dy31 = line2_end.y() - line2_start.y();
        double m12 = sqrt(dx21*dx21 + dy21*dy21);
        double m13 = sqrt(dx31*dx31 + dy31*dy31);
        double theta = acos((dx21*dx31 + dy21*dy31) / (m12 * m13));
        return theta;
    }

    double     lineAngleInDegrees(
        const Point& line1_start, const Point& line1_end,
        const Point& line2_start, const Point& line2_end
        )
    {
        return convertAngleFromRadiansToDegrees(
            lineAngleInRadians(line1_start, line1_end, line2_start, line2_end)
            );
    }

    double pointToLineDistanceSquare(
        const Point& point,
        const Point& line1,
        const Point& line2
        )
    {
        const Point& p = point;
        const Point& v = line1;
        const Point& w = line2;

        double l2 = distanceSquare(v, w);
        if (l2 == 0)
        {
            return distanceSquare(p, v);
        }

        double t = ((p.x() - v.x()) * (w.x() - v.x()) + (p.y() - v.y()) * (w.y() - v.y())) / l2;
        if (t < 0)
        {
            return distanceSquare(p, v);
        }

        if (t > 1)
        {
            return distanceSquare(p, w);
        }

        Point pt(
            v.x() + t * (w.x() - v.x()),
            v.y() + t * (w.y() - v.y())
            );

        return distanceSquare(p, pt);
    }

    double  pointToLineDistance(
        const Point& point,
        const Point& line1,
        const Point& line2
        )
    {
        return sqrt(pointToLineDistanceSquare(point, line1, line2));
    }

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Point& point)
{
    out << "x: " << point.x() << ", y: " << point.y();
    return out;
}
