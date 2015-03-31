#include "./Line.h"
#include "./Angle.h"
#include "./Vector.h"

#include <algorithm>
#include <math.h>

namespace Geometry
{
    bool    areLinesParallel(
        const Line& line1, const Line& line2
        )
    {
        return areParallel(
            line1.direction(),
            line2.direction()
            );
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
        const Line& line1, const Line& line2
        )
    {
        return doIntersect(
            line1.from(), line1.to(),
            line2.from(), line2.to()
            );
    }

    double     angleInRadians(
        const Line& line1, const Line& line2
        )
    {
        return angleInRadians(
            line1.direction(),
            line2.direction()
            );
    }

    double     angleInDegrees(
        const Line& line1, const Line& line2
        )
    {
        return convertAngleFromRadiansToDegrees(
            angleInRadians(line1, line2)
            );
    }

    double pointToLineDistanceSquare(
        const Point& point,
        const Line& line
        )
    {
        const Point& p = point;
        const Point& v = line.from();
        const Point& w = line.to();

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
        const Line& line
        )
    {
        return sqrt(pointToLineDistanceSquare(point, line));
    }
}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Line& line)
{
    out << "from: " << line.from() << ", y: " << line.to();
    return out;
}
