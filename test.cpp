#include <iostream>
#include <string>
#include <list>
#include <limits>

using namespace std;

class Car {
public:
    string color;
    int wheelsNo;
    Car(string c, int w);
};

Car::Car(string c, int w) {
    color = c;
    wheelsNo = w;
}


int main()
{

    // list<Car> ls;
    // list<Car> ls2;

    // Car c11("red", 4);
    // Car c12("blue", 4);
    // Car c13("brown", 4);

    // ls.push_back(c11);
    // ls.push_back(c12);
    // ls.push_back(c13);

    // Car c21("purple", 4);
    // Car c22("yellow", 4);
    // Car c23("green", 4);

    // ls2.push_back(c21);
    // ls2.push_back(c22);
    // ls2.push_back(c23);

    // ls.splice(ls.end(), ls2);

    // ls.pop_back();

    // for (auto const& entry : ls) {
    //     cout << entry.color << "\n";
    // }
    double a = numeric_limits<double>::infinity();
    
    // cout << (3 < a);
    cout << (a == numeric_limits<double>::infinity());

    return 0;
}
