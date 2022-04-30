#include "headers/Precision.h"

#include <cmath>

bool precisionG::CoordPrecision(tG::CoordType aInAccuracy, tG::Precision aPrecision)
{
        return std::fabs(aInAccuracy) <= aPrecision;
}

bool precisionG::DotPrecision(double aDotProduct, tG::Precision aPrecision)
{
    return std::fabs(aDotProduct) <= aPrecision;
}

bool precisionG::DistPrecision(double aDistance, tG::Precision aPrecision)
{
    return std::fabs(aDistance) <= aPrecision;
}
