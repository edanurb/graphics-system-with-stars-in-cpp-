class DispWindow;



class Point {
    public:
    explicit Point(int x=0,int y=0);
    Point& operator=(const Point &p);
    Point operator+(const Point &p);
    Point& right(int a);
    Point& left(int a);
    Point& down(int a);
    Point& up(int a);
    int x,y;

};

class allShape{
    public:
    virtual void drawAll(DispWindow* wind )  =0;

    Point n();
    Point ne();
    Point nw();
    Point s();
    Point se();
    Point sw();
    Point c();
    Point w();
    Point e();
 
    protected:
    Point N,E,W,S,NE,NW,SE,SW,C;
};



class Shape{// virtual
 public:
     virtual void  draw(const allShape& shape)=0;

    
};


class DispWindow: public Shape {//disp
     public:
        DispWindow(int x=0,int y=0);
        Point& current(const Point &p);
        Point current();
        ~DispWindow();
        void  draw(const allShape& shape);
        void show();

    char **wind;  
    Point cord;
    int x,y;
};

class Dot:public allShape{  //dot rectangle
     public:
        explicit Dot(const Point &p);
        void drawAll(DispWindow* wind) ;
       
      Point dot; 
};

class Rectangle:public allShape{
    public:
        explicit Rectangle(const Point& l, const Point&r);
        void drawAll(DispWindow* wind);

    Point rightCorner,leftCorner;
};


class Line: public allShape{
     public:
     explicit Line(const Point &p1,const Point&p2);
     void drawAll(DispWindow* wind);

    double slope;
    Point p1,p2;

};
