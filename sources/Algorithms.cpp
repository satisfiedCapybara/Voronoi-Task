#include "headers/Algorithms.h"



double algG::distance(const prGeom2D::point& aFirstPnt, const prGeom2D::point& aSecPnt)
{
    return sqrt(pow(aFirstPnt.getX() - aSecPnt.getX(),2) +
                pow(aFirstPnt.getY() - aSecPnt.getY(),2));
}

double algG::dotProduct(const prGeom2D::dir &aFirstDir, const prGeom2D::dir &aSecDir)
{
    return aFirstDir.getX()* aSecDir.getX() + aFirstDir.getY()* aSecDir.getY();
}

bool algG::isParallelLine(const prGeom2D::line& aFirst, const prGeom2D::line& aSecond)
{
    return precisionG::DotPrecision(fabs(dotProduct(aFirst.getDirection(),
                                                    aSecond.getDirection())) - 1, tG::DotAccuracy);
}

bool algG::isPerpendicularLine(const prGeom2D::line &aFirst, const prGeom2D::line &aSecond)
{
    return precisionG::DotPrecision(dotProduct(aFirst.getDirection(),
                                                    aSecond.getDirection()),tG::DotAccuracy);
}

prGeom2D::dir algG::normalization(const prGeom2D::vector &aCandidate)
{

    double theLength = algG::distance(aCandidate.getBegin(), aCandidate.getEnd());
    if(precisionG::DistPrecision(theLength,tG::DistAccuracy))
    {
        throw exceptionG::geomException("Расстояние незначительное",0 );
    }
    tG::CoordType theX = (aCandidate.getEnd().getX() - aCandidate.getBegin().getX()) / theLength;
    tG::CoordType theY = (aCandidate.getEnd().getY() - aCandidate.getBegin().getY()) / theLength;

    return {theX, theY};
}

bool algG::isParallelVec(const prGeom2D::vector& aFirst, const prGeom2D::vector& aSecond)
{
    prGeom2D::dir theDirFirst = algG::normalization(aFirst);
    prGeom2D::dir theDirSecond = algG::normalization(aSecond);

    return precisionG::DotPrecision(std::fabs(dotProduct(theDirFirst, theDirSecond))- 1, tG::DotAccuracy);
}

bool algG::isPerpendicularVec(const prGeom2D::vector &aFirst, const prGeom2D::vector &aSecond)
{
    prGeom2D::dir theDirFirst = algG::normalization(aFirst);
    prGeom2D::dir theDirSecond = algG::normalization(aSecond);

    return precisionG::DotPrecision(dotProduct(theDirFirst, theDirSecond), tG::DotAccuracy);
}

bool algG::isPntAffiliation(const prGeom2D::line &aLine, const prGeom2D::point &aPnt)
{
    if (aLine.getBegin() == aPnt) return true;
    return algG::isParallelVec((prGeom2D::vector)aLine.getDirection(),
                               {aLine.getBegin(), aPnt});
}

prGeom2D::point algG::intersection(const prGeom2D::line &aFirst, const prGeom2D::line &aSecond)
{
    //ax=b
    if (isParallelLine(aFirst, aSecond))
    {
        throw exceptionG::geomException("Параллельны", 0);
    }

    prGeom2D::dir aFirstDirection = aFirst.getDirection();
    prGeom2D::dir aSecondDirection = aSecond.getDirection();

    std::vector<std::vector<double>> AMatrix =
            {{aSecondDirection.getX(), - aFirstDirection.getX()}, { aSecondDirection.getY(), - aFirstDirection.getY()}};
    std::vector<double> bVector = {aFirst.getBegin().getX() - aSecond.getBegin().getX(),
                                   aFirst.getBegin().getY() - aSecond.getBegin().getY()};


    double detA =  AMatrix[0][0]*AMatrix[1][1] - AMatrix[1][0]*AMatrix[0][1];
    double detAb0 = bVector[0]*AMatrix[1][1] - bVector[1]*AMatrix[0][1];
    double detAb1 = AMatrix[0][0]*bVector[1] - AMatrix[1][0]*bVector[0];
    std::vector<double> xVector = {detAb1 / detA, detAb0/ detA};

    return {aFirst.getBegin().getX() + xVector[0]* aFirstDirection.getX(),
            aFirst.getBegin().getY() + xVector[0]* aFirstDirection.getY()};
}

bool algG::isIntersection(const prGeom2D::line &aFirst, const prGeom2D::line &aSecond)
{
    return !isParallelLine(aFirst, aSecond);
}

bool algG::isPntAffiliationSeg(const prGeom2D::segment &aSegment, const prGeom2D::point &aPnt)
{
    prGeom2D::line theLine(aSegment.getBegin(), aSegment.getEnd());

    if (!algG::isPntAffiliation(theLine,aPnt)) return false;

    double theT = (aPnt.getX() - aSegment.getBegin().getX())/ theLine.getDirection().getX();
    double theTEnd = (aSegment.getEnd().getX() - theLine.getBegin().getX())/ theLine.getDirection().getX();
    return theT < theTEnd && theT >= 0;
}

prGeom2D::point algG::intersectionSegments(const prGeom2D::segment &aFirst, const prGeom2D::segment &aSecond)
{
    prGeom2D::line theLineF(aFirst.getBegin(), aFirst.getEnd());
    prGeom2D::line theLineS(aSecond.getBegin(), aSecond.getEnd());

    prGeom2D::point theIntersection = algG::intersection(theLineF, theLineS);
    if (!algG::isPntAffiliationSeg(aFirst, theIntersection))
    {
        throw exceptionG::geomException("Не в сегменте",0);
    }
    return theIntersection;
}

bool algG::isIntersectionSegments(const prGeom2D::segment &aFirst, const prGeom2D::segment &aSecond)
{
    prGeom2D::line theLineF(aFirst.getBegin(), aFirst.getEnd());
    prGeom2D::line theLineS(aSecond.getBegin(), aSecond.getEnd());

    if (isIntersection(theLineS, theLineF))
    {
        return isPntAffiliationSeg(aFirst, algG::intersection(theLineF, theLineS));
    }
    return false;
}

