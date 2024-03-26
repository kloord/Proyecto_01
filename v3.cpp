#include <iostream>
#include <fstream> // Para trabajar con archivos
#include <iomanip> // Para el formateo de la salida
#include <limits>  // Para limpiar el buffer de entrada
#include <vector>  // Para usar vectores de la STL

using namespace std;

// Variables globales
int M, N;
vector<vector<double>> monto;

// Función para guardar los datos en un archivo .txt
void guardarDatosEnArchivo() {
    ofstream archivo("datos.txt");
    if (archivo.is_open()) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                archivo << monto[i][j] << " ";
            }
            archivo << endl;
        }
        archivo.close();
        cout << "Datos guardados en el archivo 'datos.txt'." << endl;
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
    }
}

// Función para mostrar los datos desde el archivo en forma de matriz
void mostrarDatosDesdeArchivo() {
    ifstream archivo("datos.txt");
    if (archivo.is_open()) {
        cout << "Matriz de montos vendidos:" << endl;
        cout << setw(12) << "Sucursales";

        // Leer y mostrar los nombres de los meses
        for (int i = 1; i <= M; ++i) {
            cout << setw(10) << "Mes " << i;
        }
        cout << endl;

        // Leer y mostrar los datos de montos vendidos
        for (int j = 0; j < N; ++j) {
            cout << setw(12) << "Sucursal " << j + 1;
            for (int i = 0; i < M; ++i) {
                double valor;
                archivo >> valor;
                cout << setw(10) << valor;
            }
            cout << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para cargar los datos." << endl;
    }
}

// Función para ingresar los montos vendidos por el Operador de sistema
void ingresarMontos() {
    cout << "Ingreso de montos vendidos:" << endl;
    monto.resize(M, vector<double>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Monto vendido en el mes " << i + 1 << " en la sucursal " << j + 1 << ": ";
            cin >> monto[i][j];
        }
    }
    // Luego de ingresar los datos, los guardamos en el archivo
    guardarDatosEnArchivo();
}

// Función para autenticar al usuario (Gerente u Operador de sistema)
bool autenticarUsuario(const string& usuario, const string& contrasena, bool esGerente) {
    if (esGerente && usuario == "user" && contrasena == "123") {
        return true;
    } else if (!esGerente && usuario == "user" && contrasena == "123") {
        return true;
    }
    return false;
}

// Función principal
int main() {
    int cargo;
    bool autenticado = false;
    string usuario, contrasena;

    cout << "Cosmeticos ASD: Sistema de gestion de ventas" << endl;
    cout << "Ingrese el cargo que ocupa en la empresa" << endl;
    cout << "(1) Gerente" << endl;
    cout << "(2) Operador de sistema" << endl;

    do {
        cout << "Opción: ";
        cin >> cargo;
        if (cin.fail() || (cargo != 1 && cargo != 2)) {
            cin.clear(); // Restaurar el estado del flujo
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
            cout << "Opción inválida. Por favor, ingrese 1 para Gerente o 2 para Operador de sistema." << endl;
        } else {
            break;
        }
    } while (true);

    do {
        cout << "\nIngrese el usuario: ";
        cin >> usuario;
        cout << "\nIngrese la contraseña: ";
        cin >> contrasena;

        autenticado = autenticarUsuario(usuario, contrasena, cargo == 1);

        if (!autenticado) {
            cout << "\nUsuario o contraseña incorrectos. Inténtelo nuevamente." << endl;
        }
    } while (!autenticado);

    if (cargo == 1) {
        // Si el cargo es Gerente, mostramos los datos almacenados en forma de matriz
        mostrarDatosDesdeArchivo();
    } else if (cargo == 2) {
        // Solicitamos el número de meses y sucursales al Operador de sistema
        do {
            cout << "Ingrese el número de meses (máximo 12): ";
            cin >> M;
            if (cin.fail() || M < 1 || M > 12) {
                cin.clear(); // Restaurar el estado del flujo
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                cout << "Número de meses inválido. Ingrese un número entre 1 y 12." << endl;
            } else {
                break;
            }
        } while (true);

        do {
            cout << "Ingrese el número de sucursales (máximo 15): ";
            cin >> N;
            if (cin.fail() || N < 1 || N > 15) {
                cin.clear(); // Restaurar el estado del flujo
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                cout << "Número de sucursales inválido. Ingrese un número entre 1 y 15." << endl;
            } else {
                break;
            }
        } while (true);

        // Permitimos al Operador de sistema ingresar los montos vendidos
        ingresarMontos();
    }

    return 0;
}
