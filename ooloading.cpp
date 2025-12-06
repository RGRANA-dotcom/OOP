#include <iostream>
using namespace std;
class Number{
    private:
    int number;
    public:
    void inputData(){
        cout<<"Enter an integer number:";
        cin>>number;
    }
    void outputData(){
        cout<<"The number is:"<<number<<endl;
    }
};
int main(){
    Number n1;
    n1.inputData();
    n1.outputData();
    return 0;
}
