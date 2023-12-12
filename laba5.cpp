#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

class IVehicle
{
public:
    virtual bool drive(int kilometres) = 0;
    virtual void refuel() = 0;
    virtual void printstatus() = 0;

    virtual ~IVehicle() = default;
};


class AbctractCar : public IVehicle
{
private:
    double bak;
    double rashod;
    int zapashoda;
    int probeg;
    double maxBak;
    int maxZapashoda;
    int i = 0;
    bool hasdriven = false;

public:

    AbctractCar(double maxBak, int maxZapashoda, double rashod) : probeg(0), bak(maxBak), maxBak(maxBak), maxZapashoda(maxZapashoda), rashod(rashod) {}


    bool drive(int kilometres) override
    {
        if (zapashoda >= kilometres)
        {
            probeg += kilometres;
            bak -= (kilometres / 100.0) * rashod;
            zapashoda -= kilometres;
            hasdriven = true;
            cout << "Вы проехали : " << kilometres << "км" << endl;
            return true;
        }
        else
        {
            cout << "Не хватает топлива для поездки!" << endl;
            return false;
        }
    }


    void refuel()
    {
        double needFuel = maxBak - bak;
        bak += needFuel;
        zapashoda = maxZapashoda;
        cout << "Вы заправились!" << endl;
    }


    void printstatus()
    {
        if (hasdriven)
        {
            i += 1;
            cout << setw(10) << i << " Поездка" << endl;
            cout << "Пробег: " << probeg << " км" << endl;
            cout << "Оставшееся топливо: " << bak << " литров" << endl;
            cout << "Запас хода: " << zapashoda << " км" << endl;
            cout << endl;
            if (i == 4)
            {
                cout << endl;
            }
        }
    }


    ~AbctractCar()
    {
    }
};


class Bicycle : public IVehicle
{
private:
    int probeg;

public:

    Bicycle() : probeg(0) {}


    bool drive(int kilometres) override
    {
        probeg += kilometres;
        return true;
    }

    void refuel() override
    {
    }


    void printstatus() override
    {
        cout << "Вы проехали " << probeg << " км на велосипеде." << endl;
    }
};


class Sedan : public AbctractCar
{
public:

    Sedan() : AbctractCar(43.0, 614, 7.0) {}

};


class Suv : public AbctractCar
{
public:

    Suv() : AbctractCar(70.0, 280, 25.0) {}

};


class Bus : public AbctractCar
{
public:

    Bus() : AbctractCar(120.0, 600, 20.0) {}


};


struct RoutePoint
{
public:
    int xKm;
    int yKm;
    string nameRoutePoint;


    RoutePoint() : xKm(0), yKm(0), nameRoutePoint("Default") {}


    RoutePoint(int xKm, int yKm, string name) : xKm(xKm), yKm(yKm), nameRoutePoint(name) {}


};


class Route : public RoutePoint
{
private:
    vector<RoutePoint> routePoints;
    double gipotenuza;

public:

    Route() {}

    void addPoint(const RoutePoint& point)
    {
        routePoints.push_back(point);
    }

    void run(IVehicle* vehicle)
    {

        if (routePoints.size() < 2)
        {
            cout << "Нужно 2 точки" << endl;

        }
        for (int i = 1; i < routePoints.size() - 1; i++)
        {



            int XKm = routePoints[i + 1].xKm - routePoints[i].xKm;
            int YKm = routePoints[i + 1].yKm - routePoints[i].yKm;
            cout << "Текущая точка маршрута: " << "(" << XKm << "," << YKm << ") " << routePoints[i].nameRoutePoint << endl;
            double gipotenuza = sqrt(pow(XKm, 2) + pow(YKm, 2));

            if (!vehicle->drive(gipotenuza))
            {
                vehicle->refuel();
                cout << "Дозаправка" << endl;
                if (!vehicle->drive(gipotenuza))
                {
                    cout << "Не удалось проехать по маршруту" << endl;
                    return;
                }


            }


        }
    }


};
string zizy()
{
    return "Неверное имя файла";
}

int main(int argc, char* argv[])
{

    setlocale(LC_ALL, "Russian");
    string line;
    {

        if (argc != 2)
        {
            cout << "Путь к файлу: " << argv[0] << " <route>\n";
            cout << zizy() << endl;
            return 1;

        }
    }

    string dorogi = argv[1];

    ifstream routeFile(dorogi);

    if (!routeFile.is_open())
    {
        cout << "File  not found: " << dorogi << "\n";
        return 1;
    }
    Route route;
    int xKm, yKm;
    string nameRoutePoint;
    while (routeFile >> xKm >> yKm >> nameRoutePoint)
    {
        route.addPoint(RoutePoint(xKm, yKm, nameRoutePoint));
    }


    if (routeFile.fail() && !routeFile.eof())
    {
        cout << "Error\n";
        return 1;
    }

    IVehicle* vehicles[4] = { new Sedan, new Suv, new Bus, new Bicycle };
    for (int i = 0; i < 4; i++)
    {
        IVehicle* vehicle = vehicles[i];
        cout << "Vehicle: ";
        if (dynamic_cast<Sedan*>(vehicle) != nullptr) cout << "Sedan" << endl;
        else if (dynamic_cast<Suv*>(vehicle) != nullptr) cout << "Bezdorozhnik" << endl;
        else if (dynamic_cast<Bus*>(vehicle) != nullptr) cout << "Babas" << endl;
        else if (dynamic_cast<Bicycle*>(vehicle) != nullptr) cout << "Bicukle" << endl;
        route.run(vehicle);
        delete vehicle;
        cout << endl;

    }
    routeFile.close();
    return 0;
}
