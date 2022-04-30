#pragma once

#include <cmath>
#include "Precision.h"
#include "PrimitiveGeometry.h"
#include "Exception.h"
#include "TypedefType.h"
#include "TopologyShape.h"


#include<vector>
#include<algorithm>
#include<iostream>


namespace algG
{
    double dotProduct(const prGeom2D::dir& aFirstVec, const prGeom2D::dir& aSecVec);

    double distance(const prGeom2D::point& aFirstPnt, const prGeom2D::point& aSecPnt);

    bool isParallelLine(const prGeom2D::line& aFirst, const prGeom2D::line& aSecond);

    bool isPerpendicularLine(const prGeom2D::line& aFirst, const prGeom2D::line& aSecond);

    bool isParallelVec(const prGeom2D::vector& aFirst, const prGeom2D::vector& aSecond);

    bool isPerpendicularVec(const prGeom2D::vector& aFirst, const prGeom2D::vector& aSecond);

    bool isPntAffiliation(const prGeom2D::line& aLine, const prGeom2D::point& aPnt);

    bool isPntAffiliationSeg(const prGeom2D::segment& aSegment, const prGeom2D::point& aPnt);

    prGeom2D::dir normalization(const prGeom2D::vector& aCandidate);

    prGeom2D::point intersection(const prGeom2D::line& aFirst, const prGeom2D::line& aSecond);

    prGeom2D::point intersectionSegments(const prGeom2D::segment& aFirst, const prGeom2D::segment& aSecond);

    bool  isIntersection(const prGeom2D::line& aFirst, const prGeom2D::line& aSecond);

    bool  isIntersectionSegments(const prGeom2D::segment& aFirst, const prGeom2D::segment& aSecond);
}