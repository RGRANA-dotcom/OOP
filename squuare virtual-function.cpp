#include <iostream>
using namespace std;
class Shape{
    public:
    virtual void area(){
        cout<<"Area of shape"<<endl;
    }
    ~Shape(){
    
        cout<<"Shape Destructor called"<<endl;
    }
};
class Square:public Shape{
    private:
    float side;
    public:
    Square(float s):side(s){}
    void area() {
        cout<<"Area of Square is = "<<side*side<<endl;
    }
    ~Square(){
        cout<<"Square Destructor called"<<endl;
    }
};
class Triangle:public Shape{
    private:
    float base;
    float height;
    public:
    Triangle(float b,float h):base(b),height(h){}
    void area() {
        cout<<"Area of Triangle is = "<<0.5*base*height<<endl;
    }
    ~Triangle(){
        cout<<"Triangle Destructor called"<<endl;
    }
};
int main(){
    Shape* ptr;
    Square s1 (5.5f);
    Triangle t1 (4.0f, 6.0f);
    ptr = &s1;
    ptr -> area();
    ptr = &t1;
    ptr -> area();
    delete ptr;

    return 0;
}
