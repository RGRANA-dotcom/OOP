#include <iostream>
using namespace std;
class farenheit{
    private:
    float fah;
    public:
    farenheit():fah(0.0f){}
    farenheit(float f):fah(f){}
    void show(){
        cout<<"Farenheit is = "<<fah<<endl;
    }
    operator float (){
        return ((fah-32)*5)/9;
    }

};
int main()
{
    farenheit f1(98.6f);
    float celsius;
    celsius=f1;
    cout<<"Celsius is = "<<celsius<<endl;
    return 0;
}