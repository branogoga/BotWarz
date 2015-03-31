#include "./Line.h"

#include <algorithm>
#include <math.h>

namespace Geometry
{

}//namespace Geometry

std::ostream& operator << (std::ostream& out, const Geometry::Line& line)
{
    out << "from: " << line.from() << ", y: " << line.to();
    return out;
}
