#pragma once
namespace tG
{
    typedef double CoordType;
    typedef const double Precision;

    Precision CoordAccuracy = 0.001;
    Precision DotAccuracy = 0.00000000001;
    Precision DistAccuracy = 0.001; // DistAccuracy <= CoordAccuracy!!!
    Precision GaussAccuracy = 0.001;
}