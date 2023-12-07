#include <iostream>
#include <string>

using namespace std;

int main() {
    string food = "Pizza";
    string &meal = food;

    cout << food << endl;
    cout << "Memory address of food " << &food << endl;
    cout << "Reference variable " << meal << endl;
    cout << "Memory address of meal " << &meal << endl;
    return 0;
}