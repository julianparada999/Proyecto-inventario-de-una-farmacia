#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip> // Para la función setprecision

using namespace std;

// Clase para generar un identificador único para cada producto
class GeneradorCodigo {
private:
    static int contador;
public:
    static int generarCodigo() {
        return ++contador;
    }
};

int GeneradorCodigo::contador = 0;

// Definición de la estructura de Producto
struct Producto {
    int codigoInterno; // Identificador único interno del producto
    string codigoExterno; // Código que el usuario asigna al producto
    string nombre;
    int cantidad;
    double precio;
};

// Mapa para almacenar el inventario de productos
map<string, Producto> inventario;

// Vector para almacenar el historial de ventas
vector<pair<string, double>> historialVentas;

// Función para registrar un nuevo producto en el inventario
void registroProducto() {
    string nombre, codigoExterno;
    int cantidad;
    double precio;

    cout << "Ingrese el nombre del producto: ";
    getline(cin >> ws, nombre);
    cout << "Ingrese el código del producto: ";
    getline(cin, codigoExterno);
    cout << "Ingrese la cantidad del producto: ";
    cin >> cantidad;
    cout << "Ingrese el precio del producto: ";
    cin >> precio;

    // Generar el código interno único para el producto
    int codigoInterno = GeneradorCodigo::generarCodigo();

    // Agregar el producto al inventario
    Producto nuevoProducto = {codigoInterno, codigoExterno, nombre, cantidad, precio};
    inventario[codigoExterno] = nuevoProducto;

    cout << "Producto registrado exitosamente." << endl;
}

// Función para mostrar el inventario completo
void mostrarInventario() {
    if (inventario.empty()) {
        cout << "Aún no tienes productos en el inventario." << endl;
    } else {
        cout << "Inventario de productos:" << endl;
        for (const auto& par : inventario) {
            const Producto& producto = par.second;
            cout << "Código interno: " << producto.codigoInterno << ", Código externo: " << producto.codigoExterno
                << ", Nombre: " << producto.nombre << ", Cantidad: " << producto.cantidad << ", Precio: " << producto.precio << endl;
        }
    }
}

// Función para editar el inventario
void editarInventario() {
    string codigoExterno;
    char opcion;

    cout << "Ingrese el código del producto que desea editar: ";
    cin >> codigoExterno;

    if (inventario.find(codigoExterno) != inventario.end()) {
        Producto& producto = inventario[codigoExterno];

        do {
            cout << "Seleccione el dato que desea cambiar:" << endl;
            cout << "  1. Nombre: " << producto.nombre << endl;
            cout << "  2. Código externo: " << producto.codigoExterno << endl;
            cout << "  3. Cantidad: " << producto.cantidad << endl;
            cout << "  4. Precio: " << producto.precio << endl;
            cout << "  5. Finalizar edición" << endl;
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case '1':
                    cout << "Nuevo nombre: ";
                    cin >> ws;
                    getline(cin, producto.nombre);
                    break;
                case '2': {
                    string nuevoCodigoExterno;
                    cout << "Nuevo código externo: ";
                    cin >> ws;
                    getline(cin, nuevoCodigoExterno);
                    producto.codigoExterno = nuevoCodigoExterno; // Actualizar el código externo del producto
                    break;
                }
                case '3':
                    cout << "Nueva cantidad: ";
                    cin >> producto.cantidad;
                    break;
                case '4':
                    cout << "Nuevo precio: ";
                    cin >> producto.precio;
                    break;
                case '5':
                    cout << "Finalizando edición." << endl;
                    break;
                default:
                    cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
            }
        } while (opcion != '5');
    } else {
        cout << "El producto no se encuentra en el inventario." << endl;
    }
}

// Función para realizar una nueva venta
void nuevaVenta() {
    string codigoExterno;
    int cantidad;

    cout << "Ingrese el código del producto a vender: ";
    cin >> codigoExterno;

    // Buscar el producto con el código externo actualizado
    for (auto& par : inventario) {
        if (par.second.codigoExterno == codigoExterno) {
            Producto& producto = par.second;
            
            cout << "Ingrese la cantidad a vender: ";
            cin >> cantidad;

            if (producto.cantidad >= cantidad) {
                // Realizar la venta
                double precioVenta = cantidad * producto.precio;
                producto.cantidad -= cantidad;
                historialVentas.push_back(make_pair(producto.nombre, precioVenta));
                cout << "Venta realizada exitosamente. Precio total: $" << fixed << setprecision(2) << precioVenta << endl;
                return;
            } else {
                cout << "No hay suficiente cantidad en el inventario." << endl;
                return;
            }
        }
    }

    // Si no se encuentra el producto
    cout << "El producto no se encuentra en el inventario." << endl;
}

// Función para mostrar el registro de ventas
void mostrarRegistroVentas() {
    if (historialVentas.empty()) {
        cout << "Aún no se han realizado ventas." << endl;
    } else {
        cout << "Registro de ventas:" << endl;
        for (const auto& venta : historialVentas) {
            cout << "Producto: " << venta.first << ", Precio: $" << fixed << setprecision(2) << venta.second << endl;
        }
    }
}

// Función principal
int main() {
    char opcion;

    do {
        cout << "          MENU PRINCIPAL" << endl;
        cout << "Seleccione una opción:" << endl;
        cout << "  1. Inventario" << endl;
        cout << "  2. Ventas" << endl;
        cout << "  3. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case '1': {
                char subopcion;
                do {
                    cout << "          INVENTARIO" << endl;
                    mostrarInventario();
                    cout << "Opciones:" << endl;
                    cout << "  1. Ingresar producto" << endl;
                    cout << "  2. Editar producto" << endl;
                    cout << "  3. Volver al menú principal" << endl;
                    cout << "Opción: ";
                    cin >> subopcion;
                    cout << endl;

                    switch (subopcion) {
                        case '1':
                            registroProducto();
                            break;
                        case '2':
                            editarInventario();
                            break;
                        case '3':
                            cout << "Volviendo al menú principal." << endl;
                            break;
                        default:
                            cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
                    }
                } while (subopcion != '3');
                break;
            }
            case '2': {
                char subopcionVenta;
                do {
                    cout << "          VENTAS" << endl;
                    cout << "Seleccione una opción:" << endl;
                    cout << "  1. Nueva venta" << endl;
                    cout << "  2. Registro de ventas" << endl;
                    cout << "  3. Volver al menú principal" << endl;
                    cout << "Opción: ";
                    cin >> subopcionVenta;
                    cout << endl;

                    switch (subopcionVenta) {
                        case '1':
                            nuevaVenta();
                            break;
                        case '2':
                            mostrarRegistroVentas();
                            break;
                        case '3':
                            cout << "Volviendo al menú principal." << endl;
                            break;
                        default:
                            cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
                    }
                } while (subopcionVenta != '3');
                break;
            }
            case '3':
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
        }
        cout << endl;
    } while (opcion != '3');

    return 0;
}