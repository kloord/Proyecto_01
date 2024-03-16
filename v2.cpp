#include <iostream>
using namespace std;

int cargo, M, N;
string userGER, passwordGER, userOP, passwordOP;

double monto[12][15];

// Declaración de la función sucursales
void sucursales(int M, int N) {
  cout << "Cosméticos ACME: Sistema de ventas." << endl;

  while (true) {
    cout << "\nIngrese el número de sucursales (máximo 15): ";
    cin >> N;
    if (N >= 1 && N <= 15) {
      break;
    } else {
      cout << "Número de sucursales inválido. Ingrese un número entre 1 y 15."
           << endl;
    }
  }

  while (true) {
    cout << "Ingrese el número de meses (máximo 12): ";
    cin >> M;
    if (M >= 1 && M <= 12) {
      break;
    } else {
      cout << "Número de meses inválido. Ingrese un número entre 1 y 12."
           << endl;
    }
  }
  // Inicialización de la matriz monto
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        monto[i][j] = 0; // Inicializamos todos los montos en 0
      }
    }

    // Entrada de montos vendidos
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        cout << "Monto vendido en el mes " << i + 1 << " en la sucursal " << j + 1 << ": ";
        cin >> monto[i][j];
      }
    }

    /* Impresión de montos vendidos
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        cout << "Mes " << i + 1 << ", Sucursal " << j + 1 << ": $" << monto[i][j] << std::endl;
      }*/
    }
  


int main() {
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

  } else if (cargo == 2) {
    do {
      cout << "\nIngrese el usuario: ";
      cin >> userOP;
    } while (userOP != "user");

    do {
      cout << "\nIngrese la contraseña: ";
      cin >> passwordOP;
    } while (passwordOP != "123");
  }

  cout << "\nBienvenido al sistema.";

  // Llama la función sucursales sólo si el cargo que ocupa la persona es operador de sistema. 
  if(cargo==2){
  sucursales(M, N);
  }
  return 0;
}
