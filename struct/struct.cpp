#include <iostream>
#include <string>
using namespace std;

struct {
    int num;
    string name;
} myStructure;

struct {
    string brand;
    string model;
    int year;
} car;

void setMyStructure(int num, string name) {
    myStructure.num = num;
    myStructure.name = name;
}

void setCar(char brand[], string model, int year) {
    car.brand = brand;
    car.model = model;
    car.year = year;
}

int main() {
    setMyStructure(1, "John");

    cout << "Number: " << myStructure.num << endl;
    cout << "Name: " << myStructure.name << endl;

    char brand[] = "Ford";
    setCar(brand, "Mustang", 1969);
    cout << "Brand: " << car.brand << endl;
    cout << "Model: " << car.model << endl;
    cout << "Year: " << car.year << endl;

    return 0;
}