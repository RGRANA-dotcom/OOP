#include <iostream>
using namespace std;
/// const and Classes
/// const Member Functions

class Distance
{
    private:
            int feets;
            float inches;
    public:
        Distance(): feets(0),inches(0.0f)
        {}
        Distance(int ft, float inc): feets(ft),inches(inc)
        {}
        void getdist()
        {
            cout<<"Enter Feets ";
            cin>>feets;
            cout<<"Enter Inches ";
            cin>>inches;
        }
        void setdist(int f, float inc)
        {
            feets = f;
            inches = inc;
        }
        void showdist() const
        {
            cout<<"\nDistance is "<<feets<<'\''<<','<<inches<<'\"'<<endl;
        }

        Distance Adddist(Distance& dd2) const
        {
            Distance temp;
            temp.feets = feets + dd2.feets;
            temp.inches = inches + dd2.inches;

            while(temp.inches >= 12.0f)
            {
                temp.inches -= 12.0f;
                temp.feets = temp.feets + 1;
            }
            return temp;
        }
        ~Distance()
        {

        }
};
int main()
{
    Distance d1, d2(4,11.7f);
    d1.getdist();               ///2' 2.2"

    Distance d3 = d1.Adddist(d2);     /// Default copy Constructor

    d1.showdist();
    d2.showdist();
    cout<<"Sum of two Distance is"<<endl;
    d3.showdist();

    return 0;
}
