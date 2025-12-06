#include<iostream>
using namespace std;
class Teacher{
    private : 
    double salary;
    public:
    Teacher(string n,string d,string s, double sal){
        name= n;
        dept = d;
        subject =s;
        salary = sal;
    }
    string name;
    string dept;
    string subject;
    Teacher(){
        dept = "computer science";
    }
    void changeDept(string newDept){
        dept = newDept;
    }
    void getinfo(){
        cout<<"name is"<< " "<<name<<endl;
        cout<<"subject is"<< " " <<subject<<endl;
    }
};
int main(){
 Teacher t1("iqbal","CS","OOP",25000);
 t1.getinfo();
    
    return 0;
}