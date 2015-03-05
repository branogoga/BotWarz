#include "./Point.h"

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
        return convertAngleFromRadiansToDegrees(
            angleInRadians(point1, point2)
            );
    }

    bool    doLinesIntersect(
        const Point& startLine1, const Point& endLine1,
        const Point& startLine2, const Point& endLine2
        )
    {
        const double dPrecision = 1E-06;
        double dIsParallel =
            (startLine1.x() - endLine1.x()) * (startLine2.y() - endLine2.y())
            - (startLine1.y() - endLine1.y()) * (startLine2.x() - endLine2.x());
        return (dIsParallel - 0.0) > dPrecision;
    }


}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Point& point)
{
    out << "x: " << point.x() << ", y: " << point.y();
    return out;
}
