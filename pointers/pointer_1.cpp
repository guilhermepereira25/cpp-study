// exemplo base de como funciona um ponteiro
#include <iostream>

using namespace std;

int main() {
    int x = 10;
    int *ptr = &x; // passando o endereço de x para ptr

    cout << "Value of x " << x << endl;
    cout << "Memory address of x " << &x << endl;

    cout << "Value of ptr " << ptr << endl; // ptr armazena o endereço de x
    cout << "Memory address of ptr " << &ptr << endl; // ptr está armazenado em um endereço diferente de x
    cout << "Value of *ptr " << *ptr << endl; // ptr armazena o endereço de x, então *ptr retorna o valor de x
    return 0;
}