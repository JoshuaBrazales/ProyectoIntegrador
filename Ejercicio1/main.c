#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 100
#define MAX_INVOICES 100
#define MAX_GENEROS 5

typedef struct {
    char name[50];
    int quantity;
    float price;
} Product;

typedef struct {
    char cedula[11];
    char name[50];
} Customer;

typedef struct {
    char date[11];
    char cedula[11];
    char name[50];
    float amountPaid;
    int productsPurchased;
} Invoice;

typedef struct {
    int vinilos;
    int cds;
    int cassettes;
} Inventario;

const char* generos[MAX_GENEROS] = {"Jazz", "Funk", "Pop", "Reguetón", "Clásico"};

Product products[MAX_PRODUCTS];
int numProducts = 0;
Customer customers[MAX_CUSTOMERS];
int numCustomers = 0;
Invoice invoices[MAX_INVOICES];
int numInvoices = 0;
Inventario inventario[MAX_GENEROS] = {0};

void loadProducts() {
    FILE *file = fopen("products.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d %f", products[numProducts].name, &products[numProducts].quantity, &products[numProducts].price) != EOF) {
            numProducts++;
        }
        fclose(file);
    }
}

void saveProducts() {
    FILE *file = fopen("products.txt", "w");
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s %d %.2f\n", products[i].name, products[i].quantity, products[i].price);
    }
    fclose(file);
}

void loadCustomers() {
    FILE *file = fopen("customers.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", customers[numCustomers].cedula, customers[numCustomers].name) != EOF) {
            numCustomers++;
        }
        fclose(file);
    }
}

void saveCustomers() {
    FILE *file = fopen("customers.txt", "w");
    for (int i = 0; i < numCustomers; i++) {
        fprintf(file, "%s %s\n", customers[i].cedula, customers[i].name);
    }
    fclose(file);
}

void loadInvoices() {
    FILE *file = fopen("invoices.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s %s %f %d", invoices[numInvoices].date, invoices[numInvoices].cedula, invoices[numInvoices].name, &invoices[numInvoices].amountPaid, &invoices[numInvoices].productsPurchased) != EOF) {
            numInvoices++;
        }
        fclose(file);
    }
}

void saveInvoices() {
    FILE *file = fopen("invoices.txt", "w");
    for (int i = 0; i < numInvoices; i++) {
        fprintf(file, "%s %s %s %.2f %d\n", invoices[i].date, invoices[i].cedula, invoices[i].name, invoices[i].amountPaid, invoices[i].productsPurchased);
    }
    fclose(file);
}

void addProduct() {
    if (numProducts >= MAX_PRODUCTS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }
    printf("Ingrese el nombre del producto: ");
    scanf("%s", products[numProducts].name);
    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &products[numProducts].quantity);
    printf("Ingrese el precio del producto: ");
    scanf("%f", &products[numProducts].price);
    numProducts++;
    saveProducts();
    printf("Producto agregado exitosamente.\n");
}

void modifyProduct() {
    char name[50];
    printf("Ingrese el nombre del producto a modificar: ");
    scanf("%s", name);
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].name, name) == 0) {
            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &products[i].quantity);
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &products[i].price);
            saveProducts();
            printf("Producto modificado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void deleteProduct() {
    char name[50];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", name);
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].name, name) == 0) {
            for (int j = i; j < numProducts - 1; j++) {
                products[j] = products[j + 1];
            }
            numProducts--;
            saveProducts();
            printf("Producto eliminado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void increaseStock() {
    char name[50];
    int quantity;
    printf("Ingrese el nombre del producto: ");
    scanf("%s", name);
    printf("Ingrese la cantidad a aumentar: ");
    scanf("%d", &quantity);
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].name, name) == 0) {
            products[i].quantity += quantity;
            saveProducts();
            printf("Stock aumentado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void addCustomer() {
    if (numCustomers >= MAX_CUSTOMERS) {
        printf("No se pueden agregar más clientes.\n");
        return;
    }
    ingreso_cedula(customers[numCustomers].cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", customers[numCustomers].name);
    numCustomers++;
    saveCustomers();
    printf("Cliente agregado exitosamente.\n");
}

void modifyCustomer() {
    char cedula[11];
    printf("Ingrese la cédula del cliente a modificar: ");
    scanf("%s", cedula);
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].cedula, cedula) == 0) {
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", customers[i].name);
            saveCustomers();
            printf("Cliente modificado exitosamente.\n");
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

void listCustomers() {
    printf("\nLista de clientes:\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("Cédula: %s, Nombre: %s\n", customers[i].cedula, customers[i].name);
    }
}

void createInvoice() {
    if (numInvoices >= MAX_INVOICES) {
        printf("No se pueden crear más facturas.\n");
        return;
    }
    printf("Ingrese la fecha (dd/mm/yyyy): ");
    scanf("%s", invoices[numInvoices].date);
    ingreso_cedula(invoices[numInvoices].cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", invoices[numInvoices].name);
    printf("Ingrese el valor pagado: ");
    scanf("%f", &invoices[numInvoices].amountPaid);
    printf("Ingrese la cantidad de productos comprados: ");
    scanf("%d", &invoices[numInvoices].productsPurchased);
    numInvoices++;
    saveInvoices();
    printf("Factura creada exitosamente.\n");
}

void listInvoices() {
    printf("\nLista de facturas:\n");
    for (int i = 0; i < numInvoices; i++) {
        printf("Fecha: %s, Cédula: %s, Nombre: %s, Valor pagado: %.2f, Cantidad de productos: %d\n",
               invoices[i].date, invoices[i].cedula, invoices[i].name,
               invoices[i].amountPaid, invoices[i].productsPurchased);
    }
}

int m2[10];
char cedula[11];

void ingreso_cedula(char *cedula) {
    int valid = 0;
    while (!valid) {
        printf("Ingrese el número de cédula: ");
        scanf("%s", cedula);
        valid = 1;

        if (strlen(cedula) != 10) {
            printf("La cédula debe tener 10 dígitos.\n");
            valid = 0;
            continue;
        }

        for (int i = 0; i < 10; i++) {
            if (!isdigit(cedula[i])) {
                printf("La cédula debe contener solo dígitos.\n");
                valid = 0;
                break;
            }
        }

        int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
        if (provincia < 1 || provincia > 24) {
            printf("Provincia no válida en la cédula.\n");
            valid = 0;
        }

        if (valid) {
            for (int i = 0; i < 10; i++) {
                m2[i] = cedula[i] - '0';
            }
        }
    }
    validacion(cedula);
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
    loadProducts();
    loadCustomers();
    loadInvoices();

    int choice;

    do {
        printf("\nSistema de Inventarios\n");
        printf("1. Ingresar Producto\n");
        printf("2. Modificar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Adicionar compra Producto (aumentar stock)\n");
        printf("5. Ingresar Cliente\n");
        printf("6. Modificar Cliente\n");
        printf("7. Ver listado de clientes\n");
        printf("8. Facturar\n");
        printf("9. Ver listado de facturas\n");
        printf("10. Mostrar Inventario Musical\n");
        printf("11. Ingresar Inventario Musical\n");
        printf("12. Modificar Inventario Musical\n");
        printf("0. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                modifyProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                increaseStock();
                break;
            case 5:
                addCustomer();
                break;
            case 6:
                modifyCustomer();
                break;
            case 7:
                listCustomers();
                break;
            case 8:
                createInvoice();
                break;
            case 9:
                listInvoices();
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
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (choice != 0);

    return 0;
}
