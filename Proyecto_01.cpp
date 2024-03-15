#include <iostream>

using namespace std;

int cargo;
string userGER, passwordGER, userOP, passwordOP;

int main() 
{
  cout << "Cosmeticos ASD: Sistema de gestion de ventas" << endl;
  cout << "Ingrese el cargo que ocupa en la empresa" << endl;
  cout << "(1) Gerente" << endl;
  cout << "(2) Operador de sistema" << endl; 

  do {
    cout << "Opción: ";
    cin >> cargo;
  } while (cargo != 1 && cargo != 2);

  if (cargo == 1) {
  do {
      cout << "\nIngrese el usuario: ";
      cin >> userGER;
  } while (userGER != "user");

  do {
      cout << "\nIngrese la contraseña: ";
      cin >> passwordGER;
  } while (passwordGER != "123");
    
  } if(cargo == 2) {
    do {
        cout << "\nIngrese el usuario: ";
        cin >> userOP;
    } while (userOP != "user" || passwordOP != "123");
    do {
      cout << "\nIngrese la contraseña: ";
      cin >> passwordOP;
    } while (passwordOP != "123");
  }

  cout << "\nBienvenido al sistema.";


}
