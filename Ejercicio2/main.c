#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_GENEROS 5

typedef struct {
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

typedef struct {
    char cedula[11];
    char nombre[50];
} Cliente;

typedef struct {
    char fecha[11];
    char cedula[11];
    char nombre[50];
    float valorPagado;
    int productosComprados;
} Factura;

typedef struct {
    int vinilos;
    int cds;
    int cassettes;
} Inventario;

const char* generos[MAX_GENEROS] = {"Jazz", "Funk", "Pop", "Reguetón", "Clásico"};

Producto productos[MAX_PRODUCTOS];
int numProductos = 0;
Cliente clientes[MAX_CLIENTES];
int numClientes = 0;
Factura facturas[MAX_FACTURAS];
int numFacturas = 0;
Inventario inventario[MAX_GENEROS] = {0};

void cargarArchivo(const char *nombreArchivo, void (*parsearLinea)(char *)) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo != NULL) {
        char linea[256];
        while (fgets(linea, sizeof(linea), archivo)) {
            parsearLinea(linea);
        }
        fclose(archivo);
    }
}

void guardarArchivo(const char *nombreArchivo, void (*escribirDatos)(FILE *)) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo != NULL) {
        escribirDatos(archivo);
        fclose(archivo);
    }
}

void parsearLineaProducto(char *linea) {
    sscanf(linea, "%s %d %f", productos[numProductos].nombre, &productos[numProductos].cantidad, &productos[numProductos].precio);
    numProductos++;
}

void parsearLineaCliente(char *linea) {
    sscanf(linea, "%s %s", clientes[numClientes].cedula, clientes[numClientes].nombre);
    numClientes++;
}

void parsearLineaFactura(char *linea) {
    sscanf(linea, "%s %s %s %f %d", facturas[numFacturas].fecha, facturas[numFacturas].cedula, facturas[numFacturas].nombre, &facturas[numFacturas].valorPagado, &facturas[numFacturas].productosComprados);
    numFacturas++;
}

void escribirDatosProducto(FILE *archivo) {
    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s %d %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
}

void escribirDatosCliente(FILE *archivo) {
    for (int i = 0; i < numClientes; i++) {
        fprintf(archivo, "%s %s\n", clientes[i].cedula, clientes[i].nombre);
    }
}

void escribirDatosFactura(FILE *archivo) {
    for (int i = 0; i < numFacturas; i++) {
        fprintf(archivo, "%s %s %s %.2f %d\n", facturas[i].fecha, facturas[i].cedula, facturas[i].nombre, facturas[i].valorPagado, facturas[i].productosComprados);
    }
}

void cargarProductos() {
    cargarArchivo("productos.txt", parsearLineaProducto);
}

void guardarProductos() {
    guardarArchivo("productos.txt", escribirDatosProducto);
}

void cargarClientes() {
    cargarArchivo("clientes.txt", parsearLineaCliente);
}

void guardarClientes() {
    guardarArchivo("clientes.txt", escribirDatosCliente);
}

void cargarFacturas() {
    cargarArchivo("facturas.txt", parsearLineaFactura);
}

void guardarFacturas() {
    guardarArchivo("facturas.txt", escribirDatosFactura);
}

void agregarProducto() {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }
    printf("Ingrese el nombre del producto: ");
    scanf("%s", productos[numProductos].nombre);
    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &productos[numProductos].cantidad);
    printf("Ingrese el precio del producto: ");
    scanf("%f", &productos[numProductos].precio);
    numProductos++;
    guardarProductos();
    printf("Producto agregado exitosamente.\n");
}

void modificarProducto() {
    char nombre[50];
    printf("Ingrese el nombre del producto a modificar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &productos[i].cantidad);
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &productos[i].precio);
            guardarProductos();
            printf("Producto modificado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    char nombre[50];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            for (int j = i; j < numProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }
            numProductos--;
            guardarProductos();
            printf("Producto eliminado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void aumentarStock() {
    char nombre[50];
    int cantidad;
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
    printf("Ingrese la cantidad a aumentar: ");
    scanf("%d", &cantidad);
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            productos[i].cantidad += cantidad;
            guardarProductos();
            printf("Stock aumentado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void agregarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("No se pueden agregar más clientes.\n");
        return;
    }
    ingresoCedula(clientes[numClientes].cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", clientes[numClientes].nombre);
    numClientes++;
    guardarClientes();
    printf("Cliente agregado exitosamente.\n");
}

void modificarCliente() {
    char cedula[11];
    printf("Ingrese la cédula del cliente a modificar: ");
    scanf("%s", cedula);
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", clientes[i].nombre);
            guardarClientes();
            printf("Cliente modificado exitosamente.\n");
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

void listarClientes() {
    printf("\nLista de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Cédula: %s, Nombre: %s\n", clientes[i].cedula, clientes[i].nombre);
    }
}

void crearFactura() {
    if (numFacturas >= MAX_FACTURAS) {
        printf("No se pueden crear más facturas.\n");
        return;
    }
    printf("Ingrese la fecha (dd/mm/yyyy): ");
    scanf("%s", facturas[numFacturas].fecha);
    ingresoCedula(facturas[numFacturas].cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", facturas[numFacturas].nombre);
    printf("Ingrese el valor pagado: ");
    scanf("%f", &facturas[numFacturas].valorPagado);
    printf("Ingrese la cantidad de productos comprados: ");
    scanf("%d", &facturas[numFacturas].productosComprados);
    numFacturas++;
    guardarFacturas();
    printf("Factura creada exitosamente.\n");
}

void listarFacturas() {
    printf("\nLista de facturas:\n");
    for (int i = 0; i < numFacturas; i++) {
        printf("Fecha: %s, Cédula: %s, Nombre: %s, Valor pagado: %.2f, Cantidad de productos: %d\n",
               facturas[i].fecha, facturas[i].cedula, facturas[i].nombre,
               facturas[i].valorPagado, facturas[i].productosComprados);
    }
}

int m2[10];

void ingresoCedula(char *cedula) {
    int valido = 0;
    while (!valido) {
        printf("Ingrese el número de cédula: ");
        scanf("%s", cedula);
        valido = 1;

        if (strlen(cedula) != 10) {
            printf("La cédula debe tener 10 dígitos.\n");
            valido = 0;
            continue;
        }

        for (int i = 0; i < 10; i++) {
            if (!isdigit(cedula[i])) {
                printf("La cédula debe contener solo dígitos.\n");
                valido = 0;
                break;
            }
        }

        if (!valido) {
            continue;
        }

        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                m2[i] = cedula[i] * 2;
                if (m2[i] >= 10) {
                    m2[i] -= 9;
                }
            } else {
                m2[i] = cedula[i];
            }
        }

        int suma = 0;
        for (int i = 0; i < 9; i++) {
            suma += m2[i];
        }

        int verificador = (suma / 10 + 1) * 10 - suma;
        if (verificador == 10) {
            verificador = 0;
        }

        if (verificador != cedula[9] - '0') {
            printf("Dígito verificador no válido.\n");
            valido = 0;
        }
    }
}

int main() {
    cargarProductos();
    cargarClientes();
    cargarFacturas();

    int opcion;
    do {
        printf("\n1. Agregar producto\n");
        printf("2. Modificar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Aumentar stock\n");
        printf("5. Agregar cliente\n");
        printf("6. Modificar cliente\n");
        printf("7. Listar clientes\n");
        printf("8. Crear factura\n");
        printf("9. Listar facturas\n");
        printf("10. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                modificarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                aumentarStock();
                break;
            case 5:
                agregarCliente();
                break;
            case 6:
                modificarCliente();
                break;
            case 7:
                listarClientes();
                break;
            case 8:
                crearFactura();
                break;
            case 9:
                listarFacturas();
                break;
            case 10:
                printf("Saliendo del programa\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 10);

    return 0;
}
