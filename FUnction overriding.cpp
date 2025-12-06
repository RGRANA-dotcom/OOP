#include <iostream>
using namespace std;
class Animal{
    public:
    virtual void sound(){
        cout<<"Animal sound"<<endl;
    }
};
class Cat: public Animal{
    public:
    void sound() {
        cout<<"Meow Meow"<<endl;
    }
};
int main(){
    Animal* ptr;
    ptr = new Cat();
    ptr -> sound();
    return 0;
}
    