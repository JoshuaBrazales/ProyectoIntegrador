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
    float montoPagado;
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

void cargarProductos() {
    FILE *archivo = fopen("productos.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %d %f", productos[numProductos].nombre, &productos[numProductos].cantidad, &productos[numProductos].precio) != EOF) {
            numProductos++;
        }
        fclose(archivo);
    }
}

void guardarProductos() {
    FILE *archivo = fopen("productos.txt", "w");
    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s %d %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
    fclose(archivo);
}

void cargarClientes() {
    FILE *archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s", clientes[numClientes].cedula, clientes[numClientes].nombre) != EOF) {
            numClientes++;
        }
        fclose(archivo);
    }
}

void guardarClientes() {
    FILE *archivo = fopen("clientes.txt", "w");
    for (int i = 0; i < numClientes; i++) {
        fprintf(archivo, "%s %s\n", clientes[i].cedula, clientes[i].nombre);
    }
    fclose(archivo);
}

void cargarFacturas() {
    FILE *archivo = fopen("facturas.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s %s %f %d", facturas[numFacturas].fecha, facturas[numFacturas].cedula, facturas[numFacturas].nombre, &facturas[numFacturas].montoPagado, &facturas[numFacturas].productosComprados) != EOF) {
            numFacturas++;
        }
        fclose(archivo);
    }
}

void guardarFacturas() {
    FILE *archivo = fopen("facturas.txt", "w");
    for (int i = 0; i < numFacturas; i++) {
        fprintf(archivo, "%s %s %s %.2f %d\n", facturas[i].fecha, facturas[i].cedula, facturas[i].nombre, facturas[i].montoPagado, facturas[i].productosComprados);
    }
    fclose(archivo);
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
    scanf("%f", &facturas[numFacturas].montoPagado);
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
               facturas[i].montoPagado, facturas[i].productosComprados);
    }
}

int m2[10];
char cedula[11];

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

        int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
        if (provincia < 1 || provincia > 24) {
            printf("Provincia no válida en la cédula.\n");
            valido = 0;
        }

        if (valido) {
            for (int i = 0; i < 10; i++) {
                m2[i] = cedula[i] - '0';
            }
            validacion(cedula);
        }
    }
}

void validacion(char *cedula) {
    int suma = 0;
    int par = 0;
    int impar = 0;
    for (int i = 0; i < 9; i += 2) {
        int d = m2[i] * 2;
        if (d > 9) {
            d -= 9;
        }
        impar += d;
    }
    for (int i = 1; i < 9; i += 2) {
        par += m2[i];
    }

    int tot = (par + impar) % 10;
    int ver = (tot != 0) ? 10 - tot : 0;

    if (ver == m2[9]) {
        printf("Cédula correcta\n");
    } else {
        printf("Cédula incorrecta\n");
    }
}

void mostrarInventario(Inventario inventario[MAX_GENEROS]) {
    printf("\nEste es el inventario actual:\n");
    for (int i = 0; i < MAX_GENEROS; i++) {
        printf("%s\n", generos[i]);
        printf("Vinilos: %d\n", inventario[i].vinilos);
        printf("CDs: %d\n", inventario[i].cds);
        printf("Cassettes: %d\n", inventario[i].cassettes);
    }
}

void ingresarInventario(Inventario inventario[MAX_GENEROS]) {
    for (int i = 0; i < MAX_GENEROS; i++) {
        printf("\nIngrese los datos de %s:\n", generos[i]);
        
        do {
            printf("Cantidad de vinilos: ");
            scanf("%d", &inventario[i].vinilos);
            if (inventario[i].vinilos < 0) {
                printf("No se debe ingresar números negativos. Intente nuevamente.\n");
            }
        } while (inventario[i].vinilos < 0);

        do {
            printf("Cantidad de CDs: ");
            scanf("%d", &inventario[i].cds);
            if (inventario[i].cds < 0) {
                printf("No se debe ingresar números negativos. Intente nuevamente.\n");
            }
        } while (inventario[i].cds < 0);

        do {
            printf("Cantidad de cassettes: ");
            scanf("%d", &inventario[i].cassettes);
            if (inventario[i].cassettes < 0) {
                printf("No se debe ingresar números negativos. Intente nuevamente.\n");
            }
        } while (inventario[i].cassettes < 0);
    }
}

void modificarInventario(Inventario inventario[MAX_GENEROS]) {
    char genero[50];
    int generoIndex = -1;

    printf("\nIngrese el nombre del género que quiere editar: ");
    scanf(" %[^\n]s", genero);

    for (int i = 0; i < MAX_GENEROS; i++) {
        if (strcmp(genero, generos[i]) == 0) {
            generoIndex = i;
            break;
        }
    }

    if (generoIndex != -1) {
        do {
            printf("\nAhora estás modificando datos para el género %s:\n", generos[generoIndex]);
            printf("Cantidad de vinilos (actual: %d): ", inventario[generoIndex].vinilos);
            scanf("%d", &inventario[generoIndex].vinilos);
            if (inventario[generoIndex].vinilos < 0) {
                printf("No se debe ingresar números negativos. Intente nuevamente.\n");
            }
        } while (inventario[generoIndex].vinilos < 0);

        do {
            printf("Cantidad de CDs (actual: %d): ", inventario[generoIndex].cds);
            scanf("%d", &inventario[generoIndex].cds);
            if (inventario[generoIndex].cds < 0) {
                printf("No se debe ingresar números negativos. Intente nuevamente.\n");
            }
        } while (inventario[generoIndex].cds < 0);

        do {
            printf("Cantidad de cassettes (actual: %d): ", inventario[generoIndex].cassettes);
            scanf("%d", &inventario[generoIndex].cassettes);
            if (inventario[generoIndex].cassettes < 0) {
                printf("No se debe ingresar números negativos. Intente nuevamente.\n");
            }
        } while (inventario[generoIndex].cassettes < 0);
    } else {
        printf("Género no válido.\n");
    }
}

int main() {
    cargarProductos();
    cargarClientes();
    cargarFacturas();

    int eleccion;

    do {
        printf("\nSistema de Inventarios\n");
        printf("1. Ingresar Producto\n");
        printf("2. Modificar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Aumentar stock de Producto\n");
        printf("5. Ingresar Cliente\n");
        printf("6. Modificar Cliente\n");
        printf("7. Ver listado de clientes\n");
        printf("8. Crear Factura\n");
        printf("9. Ver listado de facturas\n");
        printf("10. Mostrar Inventario Musical\n");
        printf("11. Ingresar Inventario Musical\n");
        printf("12. Modificar Inventario Musical\n");
        printf("0. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &eleccion);

        switch (eleccion) {
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
                mostrarInventario(inventario);
                break;
            case 11:
                ingresarInventario(inventario);
                break;
            case 12:
                modificarInventario(inventario);
                break;
            case 0:
                printf("Saliendo del sistema\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (eleccion != 0);

    return 0;
}
