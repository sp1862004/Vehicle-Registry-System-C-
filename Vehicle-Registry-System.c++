#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;

    static int totalVehicles; 

public:
    Vehicle() : vehicleID(0), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }

    Vehicle(int id, const string& mfg, const string& mdl, int yr)
        : vehicleID(id), manufacturer(mfg), model(mdl), year(yr) {
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    void setVehicleID(int id) { vehicleID = id; }
    int getVehicleID() const { return vehicleID; }

    void setManufacturer(const string& mfg) { manufacturer = mfg; }
    string getManufacturer() const { return manufacturer; }

    void setModel(const string& mdl) { model = mdl; }
    string getModel() const { return model; }

    void setYear(int yr) { year = yr; }
    int getYear() const { return year; }

    static int getTotalVehicles() { return totalVehicles; }

    virtual void displayDetails() const {
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

class Car : virtual public Vehicle {
protected:
    string fuelType;

public:
    Car() : Vehicle(), fuelType("") {}
    Car(int id, const string& mfg, const string& mdl, int yr, const string& fuel)
        : Vehicle(id, mfg, mdl, yr), fuelType(fuel) {}

    void setFuelType(const string& fuel) { fuelType = fuel; }
    string getFuelType() const { return fuelType; }

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

class ElectricCar : public Car {
private:
    int batteryCapacity;

public:
    ElectricCar() : Car(), batteryCapacity(0) {}
    ElectricCar(int id, const string& mfg, const string& mdl, int yr, const string& fuel, int capacity)
        : Car(id, mfg, mdl, yr, fuel), batteryCapacity(capacity) {}

    void setBatteryCapacity(int capacity) { batteryCapacity = capacity; }
    int getBatteryCapacity() const { return batteryCapacity; }

    void displayDetails() const override {
        Car::displayDetails();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

class Aircraft : virtual public Vehicle {
protected:
    int flightRange;

public:
    Aircraft() : Vehicle(), flightRange(0) {}
    Aircraft(int id, const string& mfg, const string& mdl, int yr, int range)
        : Vehicle(id, mfg, mdl, yr), flightRange(range) {}

    void setFlightRange(int range) { flightRange = range; }
    int getFlightRange() const { return flightRange; }

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}
    FlyingCar(int id, const string& mfg, const string& mdl, int yr, const string& fuel, int range)
        : Vehicle(id, mfg, mdl, yr), Car(id, mfg, mdl, yr, fuel), Aircraft(id, mfg, mdl, yr, range) {}

    void displayDetails() const override {
        Car::displayDetails();
        cout << "Flight Range: " << Aircraft::flightRange << " km" << endl;
    }
};

class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar() : ElectricCar(), topSpeed(0) {}
    SportsCar(int id, const string& mfg, const string& mdl, int yr, const string& fuel, int capacity, int speed)
        : ElectricCar(id, mfg, mdl, yr, fuel, capacity), topSpeed(speed) {}

    void setTopSpeed(int speed) { topSpeed = speed; }
    int getTopSpeed() const { return topSpeed; }

    void displayDetails() const override {
        ElectricCar::displayDetails();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car {
public:
    Sedan() : Car() {}
    Sedan(int id, const string& mfg, const string& mdl, int yr, const string& fuel)
        : Car(id, mfg, mdl, yr, fuel) {}

    void displayDetails() const override {
        cout << "Sedan Details:" << endl;
        Car::displayDetails();
    }
};

class SUV : public Car {
public:
    SUV() : Car() {}
    SUV(int id, const string& mfg, const string& mdl, int yr, const string& fuel)
        : Car(id, mfg, mdl, yr, fuel) {}

    void displayDetails() const override {
        cout << "SUV Details:" << endl;
        Car::displayDetails();
    }
};

class VehicleRegistry {
private:
    Vehicle* vehicles[100];
    int totalVehicles;

public:
    VehicleRegistry() : totalVehicles(0) {}

    ~VehicleRegistry() {
        for (int i = 0; i < totalVehicles; i++) {
            delete vehicles[i];
        }
    }

    void addVehicle(Vehicle* v) {
        if (totalVehicles < 100) {
            vehicles[totalVehicles++] = v;
            cout << "Vehicle added successfully!\n";
        } else {
            cout << "Vehicle registry is full!\n";
        }
    }

    void displayAllVehicles() const {
        if (totalVehicles == 0) {
            cout << "No vehicles in the registry.\n";
        } else {
            for (int i = 0; i < totalVehicles; i++) {
                cout << "Vehicle " << i + 1 << " Details:\n";
                vehicles[i]->displayDetails();
                cout << "-------------------------\n";
            }
        }
    }

    void searchVehicleByID(int id) const {
        for (int i = 0; i < totalVehicles; i++) {
            if (vehicles[i]->getVehicleID() == id) {
                cout << "Vehicle Found:\n";
                vehicles[i]->displayDetails();
                return;
            }
        }
        cout << "Vehicle with ID " << id << " not found.\n";
    }
};

int main() {
    VehicleRegistry registry;

    int choice;
    do {
        cout << "\n--- Vehicle Registry Menu ---\n";
        cout << "1. Add a Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. Search Vehicle by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int type, id, year, range, capacity, speed;
            string mfg, mdl, fuel;

            cout << "Select Vehicle Type:\n";
            cout << "1. Sedan\n";
            cout << "2. SUV\n";
            cout << "3. SportsCar\n";
            cout << "4. FlyingCar\n";
            cin >> type;

            cout << "Enter Vehicle ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Manufacturer: ";
            getline(cin, mfg);
            cout << "Enter Model: ";
            getline(cin, mdl);
            cout << "Enter Year: ";
            cin >> year;

            if (type == 1 || type == 2) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                if (type == 1) {
                    registry.addVehicle(new Sedan(id, mfg, mdl, year, fuel));
                } else {
                    registry.addVehicle(new SUV(id, mfg, mdl, year, fuel));
                }
            } else if (type == 3) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity (kWh): ";
                cin >> capacity;
                cout << "Enter Top Speed (km/h): ";
                cin >> speed;
                registry.addVehicle(new SportsCar(id, mfg, mdl, year, fuel, capacity, speed));
            } else if (type == 4) {
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Flight Range (km): ";
                cin >> range;
                registry.addVehicle(new FlyingCar(id, mfg, mdl, year, fuel, range));
            } else {
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 2:
            registry.displayAllVehicles();
            break;
        case 3: {
            int searchID;
            cout << "Enter Vehicle ID to search: ";
            cin >> searchID;
            registry.searchVehicleByID(searchID);
            break;
        }
        case 4:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
