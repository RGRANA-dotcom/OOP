#include <iostream>
using namespace std;

class Fahrenheit; // Forward declaration

class Celsius {
    float c;
public:
    Celsius(float temp = 0.0f) : c(temp) {}

    void show() {
        cout << "Temperature in Celsius = " << c << "°C" << endl;
    }

    operator float() {
        return c;
    }

    // Convert Celsius → Fahrenheit
    operator Fahrenheit();
};

class Fahrenheit {
    float f;
public:
    Fahrenheit(float temp = 0.0f) : f(temp) {}

    void show() {
        cout << "Temperature in Fahrenheit = " << f << "°F" << endl;
    }

    // Convert Fahrenheit → Celsius
    operator Celsius() {
        float c = (f - 32) * 5.0 / 9.0;
        return Celsius(c);
    }

    operator float() {
        return f;
    }
};

// Define conversion outside class (Celsius → Fahrenheit)
Celsius::operator Fahrenheit() {
    float f = (c * 9.0 / 5.0) + 32;
    return Fahrenheit(f);
}

int main() {
    Celsius c1(37.0);
    Fahrenheit f1;

    f1 = c1;      // Celsius → Fahrenheit
    f1.show();

    c1 = f1;      // Fahrenheit → Celsius
    c1.show();

    float temp = f1;   // Convert Fahrenheit to float
    cout << "As float value: " << temp << "°F" << endl;

    return 0;
}
