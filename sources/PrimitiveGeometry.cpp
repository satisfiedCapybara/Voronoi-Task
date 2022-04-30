#include <cmath>

#include "headers/Precision.h"
#include "headers/Exception.h"
#include "headers/TypedefType.h"
#include "headers/PrimitiveGeometry.h"
#include "headers/Algorithms.h"

prGeom2D::abstractModel::~abstractModel() {};


prGeom2D::point::point(const prGeom2D::point &aOther) noexcept
{
    myX = aOther.myX;
    myY = aOther.myY;
}

prGeom2D::point::point(prGeom2D::point &&aOther) noexcept
{
    myX = aOther.myX;
    myY = aOther.myY;
}

prGeom2D::point &prGeom2D::point::operator=(const prGeom2D::point &aOther) noexcept
{
    myX = aOther.myX;
    myY = aOther.myY;
    return *this;
}

prGeom2D::point prGeom2D::point::operator+(const prGeom2D::point &anOther)const noexcept
{
    return {myX + anOther.myX, myY + anOther.myY};
}

prGeom2D::vector prGeom2D::point::operator-(const prGeom2D::point &anOther) const noexcept
{
    return {*this, anOther};
}

bool prGeom2D::point::operator==(const prGeom2D::point &anOther) const noexcept
{
    return precisionG::CoordPrecision(algG::distance(*this, anOther), tG::CoordAccuracy);
}


prGeom2D::dir::dir(tG::CoordType aX, tG::CoordType aY)
{
    if (precisionG::DistPrecision(sqrt(pow(aX,2) + pow(aY,2)) - 1, tG::DistAccuracy))
    {
        myX = aX;
        myY = aY;
    }
    else
    {
        throw exceptionG::geomException("Плохая точность",0);
    }
}

prGeom2D::dir::dir(prGeom2D::dir &&aOther)  noexcept
{
    myX = aOther.myX;
    myY = aOther.myY;
}

prGeom2D::dir::dir(const prGeom2D::dir &aOther) noexcept
{
    myX = aOther.myX;
    myY = aOther.myY;
}

prGeom2D::dir::dir(const prGeom2D::point &aPnt)
{
    if (precisionG::DistPrecision(sqrt(pow(aPnt.getX(),2) + pow(aPnt.getY(),2)) - 1,
                                   tG::DistAccuracy))
    {
        myX = aPnt.getX();
        myY = aPnt.getY();
    }
    else
    {
        throw exceptionG::geomException("Плохая точность",0);
    }
}

prGeom2D::dir &prGeom2D::dir::operator=(const prGeom2D::dir &other) noexcept
{
    myY = other.myY;
    myX = other.myX;
    return *this;
}

prGeom2D::dir::operator prGeom2D::vector() const noexcept
{
    return {{0,0}, {myX, myY}};
}

bool prGeom2D::dir::operator==(const prGeom2D::dir &anOther) const noexcept
{
    return precisionG::DotPrecision(algG::dotProduct(*this, anOther) - 1, tG::DotAccuracy);
}


prGeom2D::vector::vector(const point& aBegin, const dir& aDir) noexcept
{
    myBegin = aBegin;
    myEnd = point(aBegin.getX() + aDir.getX(), aBegin.getY() + aDir.getY());
}

prGeom2D::vector::vector(prGeom2D::vector &&anOther) noexcept
{
    myBegin = anOther.myBegin;
    myEnd = anOther.myEnd;
}

prGeom2D::vector::vector(prGeom2D::vector &anOther) noexcept
{
    myBegin = anOther.myBegin;
    myEnd = anOther.myEnd;
}

prGeom2D::vector &prGeom2D::vector::operator=(const prGeom2D::vector &anOther) noexcept
{
    myBegin = anOther.myBegin;
    myEnd = anOther.myEnd;
    return *this;
}




prGeom2D::vector::operator prGeom2D::segment() const noexcept
{
    return prGeom2D::segment(myBegin, myEnd);
}

bool prGeom2D::vector::operator==(const prGeom2D::vector &anOther) const noexcept
{
    return (anOther.myBegin == myBegin) && (precisionG::DotPrecision(algG::isParallelVec(*this,
                                                                                            anOther), tG::DotAccuracy));
}

prGeom2D::segment::segment(prGeom2D::segment &&anOther) noexcept
{
    myFirstPnt = anOther.myFirstPnt;
    mySecondPnt = anOther.mySecondPnt;
}

prGeom2D::segment::segment(prGeom2D::segment &anOther) noexcept
{
    myFirstPnt = anOther.myFirstPnt;
    mySecondPnt = anOther.mySecondPnt;
}

prGeom2D::segment &prGeom2D::segment::operator=(const prGeom2D::segment &anOther) noexcept
{
    myFirstPnt = anOther.myFirstPnt;
    mySecondPnt = anOther.mySecondPnt;
    return *this;
}

bool prGeom2D::segment::operator==(const prGeom2D::segment &anOther) const noexcept
{
    return (mySecondPnt == anOther.mySecondPnt) && (myFirstPnt == anOther.myFirstPnt);
    //Сравнивается по точкам, потому что длина сегмента будет не очень большой. В случае векторов и прямых полагаем, что
    // нам придётся работать с очень большими числами
}


prGeom2D::point prGeom2D::line::getPointOnLine(double t) const noexcept
{
    return {myBegin.getX() + t*myDirection.getX(), myBegin.getY() + t*myDirection.getX()};
}

prGeom2D::line::line(const prGeom2D::point &aFirstPnt, const prGeom2D::point &aSecPnt):
                            myDirection(algG::normalization({aFirstPnt, aSecPnt})),
                            myBegin(aFirstPnt) {}

bool prGeom2D::line::operator==(const prGeom2D::line &anOther) const noexcept
{
    return (myBegin == anOther.myBegin) && (myDirection == anOther.myDirection);
}

prGeom2D::line &prGeom2D::line::operator=(const prGeom2D::line &anOther) noexcept
{
    myBegin = anOther.myBegin;
    myDirection = anOther.myDirection;
    return *this;
};



