#include <iostream>
using namespace std;
class Shape {
public:
    virtual void area() {
        cout << "Area of shape " << endl;
    }
    virtual ~Shape() {
        cout << "Shape Destructor called" << endl;
    }
};
class Square : public Shape {
private:
    float side;
public:
    Square(float s) : side(s) {}
    void area()  {
        cout << "Area of Square is = " << side * side << endl;
    }
    ~Square()  {
        cout << "Square Destructor called" << endl;
    }
    
    float getSide() const {
        return side;
    }
    void setSide(float s) {
        side = s;
    }
};
class Triangle : public Shape {
private:
    float base;
    float height;
public:
    Triangle(float b, float h) : base(b), height(h) {}
    void area()  {
        cout << "Area of Triangle is = " << 0.5 * base * height << endl;
    }
    ~Triangle()  {
        cout << "Triangle Destructor called" << endl;
    }
    float getBase() const {
        return base;
    }
    void setBase(float b) {
        base = b;
    }
    float getHeight() const {
        return height;
    }
    void setHeight(float h) {
        height = h;
    }
};
int main() {
    Shape* ptr;
    ptr = new Square(5.5f);
    ptr->area();
    delete ptr;

    ptr = new Triangle(4.0f, 6.0f);
    ptr->area();
    delete ptr;

    return 0;
}
