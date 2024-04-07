#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int M, N;

class empleado {
private:
    string nombre;
    string apellido;
    string cargo;

public:
    empleado() : nombre("Nan"), apellido("Nan"), cargo(" "){};

    empleado(string n, string a, string cargo, string con)
        : nombre(n), apellido(a), cargo(cargo){};

    void mostrarDatosEmpleado() {
        cout << setw(13) << "Nombre:" << nombre << endl
             << setw(15) << "Apellido:" << apellido << endl
             << setw(12) << "Cargo:" << cargo << endl;
    }

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
            sort(datos.begin(), datos.end(),
                 [](const pair<vector<double>, int> &a,
                    const pair<vector<double>, int> &b) {
                     return a.second < b.second;
                 });

            int num_sucursales = datos.front().first.size();

            cout << setw(10) << " ";
            for (int i = 1; i <= num_sucursales; ++i) {
                cout << setw(10) << "Sucursal " << i;
            }
            cout << endl;

            for (const auto &par : datos) {
                cout << setw(10) << "Mes " << par.second << ":";
                for (double valor : par.first) {
                    cout << setw(9) << valor;
                }
                cout << endl;
            }
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo 'datos.txt' para leer los datos."
                 << endl;
        }
    }

    bool autenticarUsuario(const string &usuario, const string &contrasena,
                           bool esGerente) {
        if (esGerente && usuario == "user" && contrasena == "123") {
            return true;
        } else if (!esGerente && usuario == "user" && contrasena == "123") {
            return true;
        }
        return false;
    }

    void mesConMayorPromedioVentas() {
        ifstream archivo("datos.txt");
        if (archivo.is_open()) {
            vector<pair<vector<double>, int>> datos;
            string line;
            while (getline(archivo, line)) {
                vector<double> fila;
                double valor;
                stringstream ss(line);
                while (ss >> valor) {
                    fila.push_back(valor);
                }
                datos.push_back(make_pair(fila, datos.size() + 1));
            }
            archivo.close();

            int mesMayorPromedio = -1;
            double mayorPromedio = 0.0;

            for (const auto &par : datos) {
                double promedio = 0.0;
                for (double valor : par.first) {
                    promedio += valor;
                }
                promedio /= par.first.size();

                if (promedio > mayorPromedio) {
                    mayorPromedio = promedio;
                    mesMayorPromedio = par.second;
                }
            }
            cout << mesMayorPromedio << endl; // Mostrar el mes con mayor promedio
        } else {
            cout << "No se pudo abrir el archivo 'datos.txt' para leer los datos."
                 << endl;
        }
    }

    void promedioVentasPorMes() {
        ifstream archivo("datos.txt");
        if (archivo.is_open()) {
            vector<pair<vector<double>, int>> datos;
            string line;
            while (getline(archivo, line)) {
                vector<double> fila;
                double valor;
                stringstream ss(line);
                while (ss >> valor) {
                    fila.push_back(valor);
                }
                datos.push_back(make_pair(fila, datos.size() + 1));
            }
            archivo.close();

            cout << "Promedio de ventas por mes:" << endl;
            for (const auto &par : datos) {
                double totalVentas = 0.0;
                for (double valor : par.first) {
                    totalVentas += valor;
                }
                double promedio = totalVentas / par.first.size();
                cout << "Mes " << par.second << ": " << promedio << endl;
            }
        } else {
            cout << "No se pudo abrir el archivo 'datos.txt' para leer los datos."
                 << endl;
        }
    }

    void montoVentasPorSucursal() {
        ifstream archivo("datos.txt");
        if (archivo.is_open()) {
            vector<pair<vector<double>, int>> datos;
            string line;
            while (getline(archivo, line)) {
                vector<double> fila;
                double valor;
                stringstream ss(line);
                while (ss >> valor) {
                    fila.push_back(valor);
                }
                datos.push_back(make_pair(fila, datos.size() + 1));
            }
            archivo.close();

            cout << "Monto de ventas por sucursal:" << endl;
            int num_sucursal = 1;
            for (const auto &par : datos) {
                double totalVentas = 0.0;
                for (double valor : par.first) {
                    totalVentas += valor;
                }
                cout << "Sucursal " << num_sucursal << ": " << totalVentas << endl;
                num_sucursal++;
            }
        } else {
            cout << "No se pudo abrir el archivo 'datos.txt' para leer los datos."
                 << endl;
        }
    }

    void sucursalMasVendioEnMeses() {
        ifstream archivo("datos.txt");
        if (archivo.is_open()) {
            vector<vector<double>> datos(M, vector<double>(N, 0.0)); // Inicializar vector con ceros
            string line;
            int mes = 0;
            while (getline(archivo, line) && mes < M) {
                stringstream ss(line);
                for (int i = 0; i < N; ++i) {
                    ss >> datos[mes][i];
                }
                mes++;
            }
            archivo.close();

            vector<double> totalVentasPorSucursal(N, 0.0);
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    totalVentasPorSucursal[j] += datos[i][j];
                }
            }

            double maxVentas = -1.0;
            int sucursalMaxVentas = -1;
            for (int i = 0; i < N; ++i) {
                if (totalVentasPorSucursal[i] > maxVentas) {
                    maxVentas = totalVentasPorSucursal[i];
                    sucursalMaxVentas = i + 1;
                }
            }

            if (sucursalMaxVentas != -1) {
                cout << "La sucursal que más ha vendido en los últimos " << M << " meses es la sucursal " << sucursalMaxVentas << endl;
            } else {
                cout << "No hay datos suficientes para determinar la sucursal que más ha vendido en los últimos " << M << " meses." << endl;
            }
        } else {
            cout << "No se pudo abrir el archivo 'datos.txt' para leer los datos."
                 << endl;
        }
    }
};

int main() {
    int cargo;
    bool autenticado = false;
    string usuario, contrasena;

    cout << "Cosmeticos ASD: Sistema de gestion de ventas" << endl;
    cout << "Ingrese el cargo que ocupa en la empresa" << endl;
    cout << "(1) Gerente" << endl;
    cout << "(2) Operador de sistema" << endl;

    empleado empleado1("Ismael", "Moreno", "Gerente", "123"); // Cambiado el cargo a string
    empleado empleado2("Antonio", "Gomez", "Operador", "098"); // Cambiado el cargo a string

    do {
        cout << "Opción: ";
        cin >> cargo;
        if (cin.fail() || (cargo != 1 && cargo != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción inválida. Por favor, ingrese 1 para Gerente o 2 para "
                    "Operador de sistema."
                 << endl;
        } else {
            break;
        }
    } while (true);

    do {
        cout << "\nIngrese el usuario: ";
        cin >> usuario;
        cout << "\nIngrese la contraseña: ";
        cin >> contrasena;

        autenticado = empleado1.autenticarUsuario(usuario, contrasena, cargo == 1);

        if (!autenticado) {
            cout << "\nUsuario o contraseña incorrectos. Inténtelo nuevamente."
                 << endl;
        }
    } while (!autenticado);

    if (cargo == 1) {
        cout << "\nBienvenido Gerente." << endl;
        empleado1.mostrarDatosEmpleado();
        empleado1.mostrarDatosGerenteArchivo();
      cout <<"--------------------------------" << endl;
        cout << "Mes con mayor promedio de ventas: ";
        empleado1.mesConMayorPromedioVentas();// Mostrar el mes con mayor promedio
      cout <<"--------------------------------" << endl;
        empleado1.promedioVentasPorMes(); // Mostrar el promedio de ventas por mes
      cout <<"--------------------------------" << endl;
        empleado1.montoVentasPorSucursal(); // Mostrar el monto de ventas por sucursal
      cout <<"--------------------------------" << endl;
        empleado1.sucursalMasVendioEnMeses(); // Mostrar la sucursal que más ha vendido en los últimos M meses
    } else if (cargo == 2) {
        do {
            cout << "Ingrese el número de meses (máximo 12): ";
            cin >> M;
            if (cin.fail() || M < 1 || M > 12) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Número de meses inválido. Ingrese un número entre 1 y 12."
                     << endl;
            } else {
                break;
            }
        } while (true);

        do {
            cout << "Ingrese el número de sucursales (máximo 15): ";
            cin >> N;
            if (cin.fail() || N < 1 || N > 15) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Número de sucursales inválido. Ingrese un número entre 1 y 15."
                     << endl;
            } else {
                break;
            }
        } while (true);

        // No es necesario que el operador ingrese los montos, ya que se leerán del archivo "datos.txt"
    }

    return 0;
}
