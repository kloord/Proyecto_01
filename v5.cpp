#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>  
#include <string> 
#include <algorithm>

using namespace std;

int M, N;
vector<vector<double>> monto;

void mostrarDatosGerenteArchivo() {
    ifstream archivo("datos.txt");
    if (archivo.is_open()) {
        cout << "\nDatos de ventas:" << endl;
        vector<pair<vector<double>, int>> datos;
        string line;
        int num_mes = 1;
        while (getline(archivo, line)) {
            vector<double> fila;
            double valor;
            stringstream ss(line);
            while (ss >> valor) {
                fila.push_back(valor);
            }
            datos.push_back(make_pair(fila, num_mes));
            num_mes++;
        }
        sort(datos.begin(), datos.end(), [](const pair<vector<double>, int>& a, const pair<vector<double>, int>& b) {
            return a.second < b.second;
        });

        // Obtener el número total de sucursales
        int num_sucursales = datos.front().first.size();

        // Mostrar encabezado con nombres de sucursales
        cout << setw(10) << " ";
        for (int i = 1; i <= num_sucursales; ++i) {
            cout << setw(10) << "Sucursal " << i;
        }
        cout << endl;

        // Mostrar datos organizados
        for (const auto& par : datos) {
            cout << setw(10) << "Mes " << par.second << ":";
            for (double valor : par.first) {
                cout << setw(9) << valor;
            }
            cout << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo 'datos.txt' para leer los datos." << endl;
    }
}


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

void ingresarMontos() {
    cout << "Ingreso de montos vendidos:" << endl;
    monto.resize(M, vector<double>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Monto vendido en el mes " << i + 1 << " en la sucursal " << j + 1 << ": ";
            cin >> monto[i][j];
        }
    }
    guardarDatosEnArchivo();
}

bool autenticarUsuario(const string& usuario, const string& contrasena, bool esGerente) {
    if (esGerente && usuario == "user" && contrasena == "123") {
        return true;
    } else if (!esGerente && usuario == "user" && contrasena == "123") {
        return true;
    }
    return false;
}

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
            cin.clear(); 
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
        cout << "\nBienvenido Gerente." << endl;
     mostrarDatosGerenteArchivo();


    } else if (cargo == 2) {
        do {
            cout << "Ingrese el número de meses (máximo 12): ";
            cin >> M;
            if (cin.fail() || M < 1 || M > 12) {
                cin.clear(); 
                cout << "Número de meses inválido. Ingrese un número entre 1 y 12." << endl;
            } else {
                break;
            }
        } while (true);

        do {
            cout << "Ingrese el número de sucursales (máximo 15): ";
            cin >> N;
            if (cin.fail() || N < 1 || N > 15) {
                cin.clear(); 
                cout << "Número de sucursales inválido. Ingrese un número entre 1 y 15." << endl;
            } else {
                break;
            }
        } while (true);

        ingresarMontos();
    }

    return 0;
}
