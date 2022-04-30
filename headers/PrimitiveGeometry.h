#pragma once

#include <iostream>
#include "TypedefType.h"

namespace prGeom2D
{
    class vector;
    class segment;

    class abstractModel
    {
    public:
        abstractModel() noexcept = default;

        virtual ~abstractModel() = 0;
    };




    class point: public abstractModel
    {
    public:
        point(tG::CoordType aX, tG::CoordType aY): myX(aX), myY(aY) {};
        point(point&& Other) noexcept;
        point(const point& Other) noexcept;
        //point() noexcept { myX = 0; myY = 0;};
        point(): myX(0), myY(0)  {};

        tG::CoordType getX() const { return myX; } ;
        tG::CoordType getY() const { return myY; } ;
        void setX(tG::CoordType aX) { myX = aX;};
        void setY(tG::CoordType aY) { myY = aY;};

        bool operator== (const point& anOther) const noexcept;
        point& operator= (const point& anOther) noexcept;
        point operator+ (const point& anOther) const noexcept;

        vector operator- (const point& anOther) const noexcept;

    private:
        tG::CoordType myX;
        tG::CoordType myY;
    };


    class dir: public abstractModel
    {
    public:
        dir(tG::CoordType aX, tG::CoordType aY);
        dir(const point&);
        dir (const dir& anOther) noexcept;
        dir (dir&& anOther) noexcept;

        tG::CoordType getX() const { return myX; };
        tG::CoordType getY() const { return myY; };

        bool operator ==(const dir& anOther) const noexcept;
        explicit operator vector() const noexcept;
        dir& operator=(const dir& anOther) noexcept;
    private:
        tG::CoordType  myX;
        tG::CoordType  myY;
    };


    class vector: private abstractModel
    {
    public:
        vector(point&& aBegin, point&& anEnd): myBegin(std::forward<point>(aBegin)),
                                                myEnd(std::forward<point>(anEnd)) {};

        vector(const point& aBegin, const point& anEnd): myBegin(aBegin),
                                                myEnd(anEnd) {};

        vector(const point& aBegin, const dir& aDir) noexcept;
        vector (vector&& aOther) noexcept;
        vector (vector& aOther) noexcept;
        //vector(): myBegin(point(0,0)), myEnd(point(0,0)) {};

        point getBegin() const { return myBegin; };
        point getEnd() const { return myEnd; };
        void setBegin(const point& aBegin) noexcept { myBegin = aBegin; };
        void setEnd(const point& anEnd) noexcept { myEnd = anEnd; };

        bool operator== (const vector& anOther) const noexcept;
        vector& operator= (const vector& anOther) noexcept;
        explicit operator segment() const noexcept;
    private:
        point myBegin;
        point myEnd;
    };

    class segment: public abstractModel
    {
    public:
        segment(const point& aFirstPnt,const point&  aSecondPnt): myFirstPnt(aFirstPnt),
                                                     mySecondPnt(aSecondPnt) {};
        segment(segment&& aOther) noexcept;
        segment(segment& aOther) noexcept;
        //segment(): myFistPnt(point()), mySecondPnt(point()) {};

        point getBegin() const { return myFirstPnt; };
        point getEnd() const { return mySecondPnt; };
        bool operator== (const segment& anOther) const noexcept;
        segment& operator= (const segment& anOther) noexcept;
    private:
        point myFirstPnt;
        point mySecondPnt;
    };

    class line: public abstractModel
    {
    public:
        //line(point&& aBegin, dir&& aDir):  myBegin(std::move(aBegin)), myDirection(std::move(aDir)) {};
        line(const point& aBegin, const dir& aDir):  myBegin(aBegin), myDirection(aDir) {};
        line(const point &aFirstPnt, const point &aSecPnt);

        point getPointOnLine(double t) const noexcept;
        point getBegin() const noexcept { return myBegin; };
        dir getDirection() const noexcept { return myDirection; };

        bool operator== (const line& anOther) const noexcept;
        line& operator= (const line& anOther) noexcept;
    private:
        point myBegin;
        dir myDirection;
    };
}


