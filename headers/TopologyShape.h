#pragma once

#include <iostream>
#include <vector>

#include "Algorithms.h"
#include "Precision.h"
#include "PrimitiveGeometry.h"
#include "TypedefType.h"

namespace topoG
{
    class abstractShape
    {
    public:
        abstractShape() noexcept = default;

        virtual ~abstractShape() = 0;
    };

    class halfPlane: public abstractShape
    {
    public:
        halfPlane(const prGeom2D::line& aLine, const prGeom2D::dir& anOrientation): myLine(aLine),
                                                                    myOrientation(anOrientation) {};

        halfPlane(prGeom2D::line&& aLine, prGeom2D::dir&& anOrientation);

        bool operator==(const halfPlane& anOther) const noexcept;
        prGeom2D::line getLine() const noexcept {return myLine; };
        prGeom2D::dir getOrientation() const noexcept {return myOrientation; };
        bool belongTo(const prGeom2D::point& aPoint) const noexcept;
    private:
        prGeom2D::line myLine;
        prGeom2D::dir myOrientation;
    };

    class convexPolygon: public abstractShape
    {
    public:
        explicit convexPolygon(const std::vector<prGeom2D::point>& aVectorOfPnt);

        std::vector<prGeom2D::point> getLine() const noexcept {return myVectorOfPnt; };
        std::size_t getNumberOfVertex() const noexcept { return myVectorOfPnt.size(); };
        std::vector<prGeom2D::segment> getSegment() const noexcept;
    private:
        std::vector<prGeom2D::point> myVectorOfPnt{};
    };
}

