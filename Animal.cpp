#include <iostream>
using namespace std;
class Animal {
    protected:
        string name;
        int age;
        public:
        virtual void info() {
            cout << "Animal Name: " << name << ", Age: " << age << endl;
        }
};
class Zebra : public Animal {
    private:
    string origin;
    public:
    Zebra(string n, int a, string o) : origin(o) {
        name = n;
        age = a;
    }

    void info() override {
        cout << "Zebra Name: " << name << ", Age: " << age << ", Origin: " << origin << endl;
    }
};
class Dolphin : public Animal {
    private:
    string color;
    public:
    Dolphin(string n, int a, string c) : color(c) {
        name = n;
        age = a;
    }

    void info() override {
        cout << "Dolphin Name: " << name << ", Age: " << age << ", Color: " << color << endl;
    }
};
int main() {
    Animal* ptr;
    ptr = new Zebra("Zahid balti", 50, "Skardu");
    ptr->info();

    ptr = new Dolphin("Flipper", 8, "blue");
    ptr->info();

    return 0;
}