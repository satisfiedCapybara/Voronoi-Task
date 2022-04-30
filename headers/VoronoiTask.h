#pragma once
#include <iostream>
#include "Exception.h"
#include "PrimitiveGeometry.h"
#include "Algorithms.h"

inline std::vector<topoG::convexPolygon> VoronoiTask(const std::vector<prGeom2D::point>& aVecOfPnt)
{
        std::size_t theNumberOfPnt = aVecOfPnt.size();


        std::vector<double> theVecX;
        std::vector<double> theVecY;
        for (std::size_t i = 0; i < theNumberOfPnt; ++i) {
            theVecX.push_back(aVecOfPnt[i].getX());
            theVecY.push_back(aVecOfPnt[i].getY());
        }
        double  maxX = 800,
                minX = 0,
                maxY = 600,
                minY = 0;

        std::vector<topoG::convexPolygon> theResult;
        for (std::size_t i = 0; i < theNumberOfPnt; ++i) {
            std::vector<topoG::halfPlane> theVecOfHalfPlane;

            for (std::size_t j = 0; j < theNumberOfPnt; ++j) {
                if (i == j) continue;
                prGeom2D::dir theDirToPnt = algG::normalization({aVecOfPnt[j], aVecOfPnt[i]});

                double theX = (aVecOfPnt[i].getX() + aVecOfPnt[j].getX()) / 2;
                double theY = (aVecOfPnt[i].getY() + aVecOfPnt[j].getY()) / 2;

                prGeom2D::line theLine = {{theX, theY},
                                          prGeom2D::dir{theDirToPnt.getY(), -theDirToPnt.getX()}};
                theVecOfHalfPlane.emplace_back(topoG::halfPlane(theLine, theDirToPnt));
            }

            prGeom2D::line theUp = {prGeom2D::point{minX, maxY} , prGeom2D::point{maxX, maxY}},
                    theBottom = {prGeom2D::point{minX, minY} , prGeom2D::point{maxX, minY}},
                    theLeft = {prGeom2D::point{minX, minY} , prGeom2D::point{minX, maxY}},
                    theRight = {prGeom2D::point{maxX, minY} , prGeom2D::point{maxX, maxY}};
            prGeom2D::dir theDUp = {{0, -1}},
                    theDBottom = {{0, 1}},
                    theDRight = {{-1, 0}},
                    theDLeft = {{1, 0}};

            theVecOfHalfPlane.emplace_back(topoG::halfPlane(theUp, theDUp));
            theVecOfHalfPlane.emplace_back(topoG::halfPlane(theBottom, theDBottom));
            theVecOfHalfPlane.emplace_back(topoG::halfPlane(theRight, theDRight));
            theVecOfHalfPlane.emplace_back(topoG::halfPlane(theLeft, theDLeft));

            std::size_t theNumberOfHalfPl = theVecOfHalfPlane.size();
            std::vector<prGeom2D::point> theIntersectionPoint;
            for (std::size_t k = 0; k < theNumberOfHalfPl; ++k)
            {
                for (std::size_t t = 0; t < theNumberOfHalfPl; ++t)
                {
                    if (algG::isIntersection(theVecOfHalfPlane[k].getLine(), theVecOfHalfPlane[t].getLine())) {
                        prGeom2D::point theInterPoint = algG::intersection(theVecOfHalfPlane[k].getLine(),
                                                                           theVecOfHalfPlane[t].getLine());
                        if(!std::count(std::begin(theIntersectionPoint), std::end(theIntersectionPoint), theInterPoint))
                            theIntersectionPoint.emplace_back(theInterPoint);
                    }
                }
            }


            std::vector<prGeom2D::point> theForResult;
            bool theNotBelong = false;
            std::size_t theNumberOfIntP = theIntersectionPoint.size();
            for (std::size_t k = 0; k < theNumberOfIntP; ++k)
            {

                for (std::size_t t = 0; t < theNumberOfHalfPl; ++t)
                {
                    if(!theVecOfHalfPlane[t].belongTo(theIntersectionPoint[k]))
                        theNotBelong = true;
                }
                if (!theNotBelong)
                {
                    theForResult.emplace_back(theIntersectionPoint[k]);
                }
                theNotBelong = false;
            }
            theResult.emplace_back(theForResult);
        }
        return theResult;
}
