#include <iostream>
#include <string>
using namespace std;
// Класс-интерфейс IVehicle (транспортное средство)
class IVehicle {
public:
	virtual void drive(int kilometers) = 0;
	virtual void refuel() = 0;
	virtual void printStatus() = 0;
};
// Класс AbstractCar (базовый класс для автомобилей)
class AbstractCar : public IVehicle {
protected:
	int kolKM; // пробег
	double fuel; // количество топлива в баке (в литрах)
	const double kolL; // вместимость бака (в литрах)
	const double rashod; // расход топлива (литры на 100 км)
public:
	AbstractCar(double vmestimost, double consumption)
		: kolKM(0), fuel(0), kolL(vmestimost), rashod(consumption) {}
	void drive(int kilometers) override {
		double fuelNeeded = (static_cast<double>(kilometers) / 100.0) * rashod;
		if (fuel >= fuelNeeded) {
			kolKM += kilometers;
			fuel -= fuelNeeded;
			cout << "Проехали " << kilometers << " км. Осталось топлива: " << fuel << " литров." << endl;
		}
		else {
			cout << "Недостаточно топлива для поездки на " << kilometers << " км." << endl;
		}
	}
	void refuel() override {
		fuel = kolL;
		cout << "Бак заправлен до полного. Теперь у вас " << fuel << " литров топлива." << endl;
	}
	void printStatus() override {
		cout << "Пробег: " << kolKM << " км. Осталось топлива: " << fuel << " литров." << endl;
	}
};
// Класс Sedan (легковая машина)
class Sedan : public AbstractCar {
public:
	Sedan() : AbstractCar(50.0, 6.5) {} // Легковая машина, бак на 50 литров, расход 6.5 л/100 км
};
// Класс Suv (внедорожник)
class Suv : public AbstractCar {
public:
	Suv() : AbstractCar(70.0, 8.0) {} // Внедорожник, бак на 70 литров, расход 8.0 л/100 км
};
// Класс Bus (автобус)
class Bus : public AbstractCar {
public:
	Bus() : AbstractCar(200.0, 15.0) {} // Автобус, бак на 200 литров, расход 15.0 л/100 км
};
// Класс Bicycle (велосипед)
class Bicycle : public IVehicle {
private:
	int mileage; // пробег велосипеда
public:
	Bicycle() : mileage(0) {}
	void drive(int kilometers) override {
		mileage += kilometers;
		cout << "Проехали " << kilometers << " км. Пробег велосипеда: " << mileage << " км." << endl;
	}
	void refuel() override {
		// У велосипеда нет бака и топлива, поэтому этот метод не делает ничего.
		cout << "Велосипед не имеет бака для заправки." << endl;
	}
	void printStatus() override {
		cout << "Пробег велосипеда: " << mileage << " км." << endl;
	}
};
int main() {
	setlocale(LC_ALL, "ru");
	IVehicle* vehicles[4] = { new Sedan(), new Suv(), new Bus(), new Bicycle() };
	for (int i = 0; i < 4; ++i) {
		int a;
		IVehicle* vehicle = vehicles[i];
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