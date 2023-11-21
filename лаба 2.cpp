#include <iostream>
#include <string>
using namespace std;
class Vehicle {
protected:
    int kolKM;         // пробег
    double fuel;         // количество топлива в баке (в литрах)
    const double kolL; // вместимость бака (в литрах)
    const double rashod; // расход топлива (литры на 100 км)
public:
    Vehicle(double volume, double consumption)
        : kolKM(0), fuel(0), kolL(volume), rashod(consumption) {}
    void drive(int kilometers) {
        double fuelNeeded = (static_cast<double>(kilometers) / 100.0) * rashod;
        if (fuel >= fuelNeeded) {
            kolKM += kilometers;
            fuel -= fuelNeeded;
            cout << "Пройдено расстояние: " << kilometers << " км. Осталось топлива: " << fuel << " литров." << endl;
        }
        else {
            cout << "Недостаточно топлива для поездки на расстояние " << kilometers << " км." << endl;
        }
    }
    void refuel() {
        fuel = kolL;
        cout << "Заправка прошла успешно. В баке " << fuel << " литров топлива." << endl;
    }
    void printStatus() {
        cout << "Пробег: " << kolKM << " км. Осталось топлива: " << fuel << " литров." << endl;
    }
};
class Sedan : public Vehicle {
public:
    Sedan() : Vehicle(43.0, 7.0) {} // Легковая машина, бак на 43 литров, расход 7.0 л/100 км
};
class Suv : public Vehicle {
public:
    Suv() : Vehicle(80.0, 10.0) {} // Внедорожник, бак на 80 литров, расход 10.0 л/100 км
};
class Bus : public Vehicle {
public:
    Bus() : Vehicle(200.0, 15.0) {} // Автобус, бак на 200 литров, расход 15.0 л/100 км
};
int main() {
    setlocale(LC_ALL, "Russian");
    Vehicle* vehicles[3] = { new Sedan(), new Suv(), new Bus() };
    for (int i = 0; i < 3; ++i) {
        int a;
        Vehicle* vehicle = vehicles[i];
        vehicle->refuel();
        vehicle->printStatus();
        cout << "Введите количество километров: " << endl;
        cin >> a;
        vehicle->drive(a);
        vehicle->printStatus();
        cout << "Введите количество километров: " << endl;
        cin >> a;
        vehicle->drive(a);
        vehicle->printStatus();
        cout << "Введите количество километров: " << endl;
        cin >> a;
        vehicle->drive(a);
        vehicle->printStatus();
        vehicle->refuel();
        cout << "Введите количество километров: " << endl;
        cin >> a;
        vehicle->drive(a);
        vehicle->printStatus();
        delete vehicle;
        cout << endl;
    }
    return 0;
}