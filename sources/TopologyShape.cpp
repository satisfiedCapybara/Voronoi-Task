#include <vector>

#include "headers/TopologyShape.h"
#include "headers/Algorithms.h"


topoG::abstractShape::~abstractShape() {}

topoG::halfPlane::halfPlane(prGeom2D::line &&aLine, prGeom2D::dir &&anOrientation) :
                                        myLine(std::forward<prGeom2D::line>(aLine)),
                                        myOrientation(std::forward<prGeom2D::dir>(anOrientation)) {}

bool topoG::halfPlane::operator==(const halfPlane& anOther) const noexcept
{
    return myOrientation == anOther.myOrientation && myLine == anOther.myLine;
}

bool topoG::halfPlane::belongTo(const prGeom2D::point &aPoint) const noexcept
{
    if (algG::isPntAffiliation(myLine, aPoint)) return true;
    prGeom2D::line theLine = {aPoint, myOrientation};
    prGeom2D::point theIntPoint = algG::intersection(theLine, myLine);
    prGeom2D::dir theCandidate = algG::normalization({theIntPoint, aPoint});

    if (theCandidate == myOrientation) return true;
    return false;
};

topoG::convexPolygon::convexPolygon(const std::vector <prGeom2D::point> &aVectorOfPnt) {myVectorOfPnt = aVectorOfPnt;}


std::vector<prGeom2D::segment> topoG::convexPolygon::getSegment() const noexcept
{
    std::size_t theSize = myVectorOfPnt.size();
    std::vector<prGeom2D::segment> theSegment;
    std::vector<prGeom2D::point> theVectorOfPnt = myVectorOfPnt;

    //theStart, theCurrentPnt, theCurrentDir, theCandidate, theCandidateDir, theMaxDot
    prGeom2D::point theStart = theVectorOfPnt[0];
    theVectorOfPnt.erase(std::find(std::begin(theVectorOfPnt), std::end(theVectorOfPnt), theStart));
    prGeom2D::point theCurrentPnt;

    bool theIntersection = false;
    for(auto &&elem: theVectorOfPnt) {
        for (auto &&theBegin: theVectorOfPnt) {
            for (auto &&theEnd: theVectorOfPnt) {
                if ((theBegin == theEnd) || (theBegin == elem) || (theEnd == elem)) continue;
                if (algG::isIntersectionSegments({theStart, elem}, {theBegin, theEnd})) {
                    theIntersection = true;
                    break;
                }
            }
            if (theIntersection) break;
        }
        if(!theIntersection) {
            theCurrentPnt = elem;
            break;
        }
        theIntersection = false;
    }
    prGeom2D::dir theCurrentDir = {algG::normalization({{theStart},{theCurrentPnt}})};
    theVectorOfPnt.erase(std::find(std::begin(theVectorOfPnt), std::end(theVectorOfPnt), theCurrentPnt));
    theSegment.push_back({theStart, theCurrentPnt});

    while(!theVectorOfPnt.empty())
    {
        double theMaxDot = -1;
        prGeom2D::point theCandidate;

        for(auto&& elem: theVectorOfPnt)
        {

            prGeom2D::dir theDirElem = algG::normalization({{theCurrentPnt}, {elem}});
            double theCurDot = algG::dotProduct(theCurrentDir, theDirElem);

            if (theCurDot > theMaxDot)
            {
                theMaxDot = theCurDot;

                theCandidate = elem;
            }
        }
        prGeom2D::dir theCandidateDir = algG::normalization({{theCurrentPnt}, {theCandidate}});

        theVectorOfPnt.erase(std::find(std::begin(theVectorOfPnt), std::end(theVectorOfPnt), theCandidate));
        theSegment.push_back({theCurrentPnt, theCandidate});
        theCurrentDir = theCandidateDir;
        theCurrentPnt = theCandidate;
    }
    theSegment.push_back({theCurrentPnt, theStart});

    return theSegment;
}
