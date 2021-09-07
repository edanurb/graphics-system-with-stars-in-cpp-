#include <iostream>
#include <math.h>  
#include "library.h"

#include <typeinfo>
using namespace std;

Point ::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point &Point::operator=(const Point &p)
{
    x = p.x;
    y = p.y;
    return *this;
}

Point Point::operator+(const Point &p)
{
    Point temp;
    temp.x = x + p.x;
    temp.y = y + p.y;

    return temp;
}

Point &Point::right(int a)
{
    x += a;
    return *this;
}

Point &Point::left(int a)
{
    x -= a;
    return *this;
}

Point &Point::down(int a)
{
    y += a;
    return *this;
}

Point &Point::up(int a)
{
    y -= a;
    return *this;
}

void DispWindow ::draw(const allShape &shape)
{

    allShape &ptr = const_cast<allShape &>(shape);
    ptr.drawAll(this);
}

DispWindow::DispWindow(int x, int y) : cord(0, 0), x(x), y(y)
{
    wind = new char *[y];

    for (int i = 0; i < y; i++)
    {
        wind[i] = new char[x];
    }

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            wind[i][j] = ' ';
        }
    }
}

DispWindow::~DispWindow()
{
    for (int i = 0; i < y; i++)
        delete[] wind[y];
    delete[] wind;
}

Point DispWindow::current()
{
    return cord;
}

Point &DispWindow::current(const Point &p)
{
    if (p.x < x && p.y < y)
        cord = p;
    return cord;
}

void DispWindow::show()
{

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            cout << wind[i][j];
        }
        cout << endl;
    }
}

Dot::Dot(const Point &p) : dot(p)
{
    N = E = W = S = NE = NW = SE = SW = C = p;
}

void Dot ::drawAll(DispWindow *wind)
{
    if (dot.x < wind->x && dot.y < wind->y)
        wind->wind[dot.y][dot.x] = '*';

    wind->current(dot);    
}

Rectangle::Rectangle(const Point &l, const Point &r)
{
    SE = rightCorner = r;
    NW = leftCorner = l;

    N.y = NE.y = NW.y;
    SW.x = W.x = NW.x;
    SW.y = S.y = SE.y;
    NE.x = E.x = SE.x;

    S.x = N.x = C.x = ((SE.x - NW.x) % 2 == 1 ? ((SE.x - NW.x) + 1) / 2 : (SE.x - NW.x) / 2) + NW.x;
    W.y = C.y = E.y = ((SE.y - NW.y) % 2 == 1 ? ((SE.y - NW.y) + 1) / 2 : (SE.y - NW.y) / 2) + NW.y;
}

void Rectangle::drawAll(DispWindow *wind)
{
    wind->current(rightCorner);
    for (int i = leftCorner.x; i <= rightCorner.x; i++)
    {
        if (leftCorner.y < wind->y && i < wind->x)
            wind->wind[leftCorner.y][i] = '*';

        if (rightCorner.y < wind->y && i < wind->x)
            wind->wind[rightCorner.y][i] = '*';
    }
    for (int i = leftCorner.y; i <= rightCorner.y; i++)
    {
        if (leftCorner.x < wind->x && i < wind->y)
            wind->wind[i][leftCorner.x] = '*';

        if (leftCorner.x < wind->x && i < wind->y)
            wind->wind[i][rightCorner.x] = '*';
    }
}

Line::Line(const Point &p1, const Point &p2) : p1(p1), p2(p2)
{

    N = NE = NW = p1.y <= p2.y ? p1 : p2;
    S = SE = SW = p1.y <= p2.y ? p2 : p1;

    C.x = ((N.x - S.x) / 2) + S.x;
    C.y = ((N.y - S.y) / 2) + S.y;
    if (S.x != N.x)
    {
        slope = (S.y - N.y);
        slope /= (S.x - N.x);
    }
    else
        slope = 0;
}

void Line ::drawAll(DispWindow *wind)
{
    wind->current(p2);

    if (N.x == S.x)
    {
        for (int i = N.y; i <= S.y; i++)
        {

            if (i < wind->y && i >= 0 && S.x < wind->x && S.x >= 0)
                wind->wind[i][S.x] = '*';
        }
    }

    else if (N.y == S.y)
    {

        int start = N.x < S.x ? N.x : S.x;
        int finish = N.x < S.x ? S.x : N.x;

        for (int i = start; i <= finish; i++)
        {
            if (i < wind->x && N.y < wind->y)
                wind->wind[N.y][i] = '*';
            
        }
    }

    else if (slope > 0)
    {

        slope /= 100;
        int k = 1;
        
        for (double i = N.x, j = N.y; j <= S.y; k++)
        {
           

            if (i < wind->x && j < wind->y)
                wind->wind[(int)(j)][(int)(i)] = '*';

             i =N.x+  (0.01)*k ;
            j =N.y+ (slope)*k;
         
        }
    }

    else if (slope < 0)
    {

        slope /= -100;
        int k = 1;
      
        for (double i = N.x, j = N.y; j <= S.y; k++)
        {
            
            if (i < wind->x && j < wind->y)
                 wind->wind[(int)(j)][(int)(ceil(i))] = '*';

            i = N.x - (0.01) * k;
            j = N.y + (slope)*k;
        }
    }
}

Point allShape::n()
{
    return N;
}

Point allShape::ne()
{
    return NE;
}

Point allShape::nw()
{
    return NW;
}

Point allShape::s()
{
    return S;
}

Point allShape::se()
{
    return SE;
}

Point allShape::sw()
{
    return SW;
}

Point allShape::c()
{
    return C;
}

Point allShape::w()
{
    return W;
}

Point allShape::e()
{
    return E;
}
