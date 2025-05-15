#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Product;

// Global variables
extern Product products[MAX_PRODUCTS];
extern int productCount;

// Function declarations
void addProduct();
void editProduct();
void deleteProduct();
void searchProduct();
void displayProducts();
void loadProducts();
void saveProducts();
void inventoryReport();

#endif 