#include "./Angle.h"

#define _USE_MATH_DEFINES
#include <cmath>
#undef _USE_MATH_DEFINES

namespace Geometry
{
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
        return (i_dAngleInRadians / M_PI) * 180;
    }

    double  convertAngleFromDegreesToRadians(double i_dAngleInDegrees)
    {
        return (i_dAngleInDegrees / 180) * M_PI;
    }

}//namespace Geometry