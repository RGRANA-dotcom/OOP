#include <iostream>
using namespace std;
class Square{
    float len;
    public:
    Square(float l=0.0f):len(l){}
    void show(){
        cout<<"Length of square is = "<<len<<endl;
    }
    operator float (){
        return len;
    }

};
class Rectangle{
    float len;
    float width;
    public:
    Rectangle(float l,float w):len(l),width(w){}
    void show(){
        cout<<"Length of Rectangle is = "<<len<<endl;
        cout<<"Width of Rectangle is = "<<width<<endl;
    }
    operator Square(){
        if (width==len)
        {
            return Square(width);
        }
        else{
            cout<<"Width and length of rectangle must be equal!"<<endl;
            exit(1);
        }
    }
};


int main()
{
    Rectangle r1(5.5,5.5);
    Square s1;
    s1=r1;
    s1.show();
    float len=s1;
    cout<<len<<endl;


return 0;
}
