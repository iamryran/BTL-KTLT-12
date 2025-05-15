#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Danh sach san pham da day!\n");
        return;
    }

    Product p;
    printf("Nhap thong tin san pham:\n");
    printf("ID: ");
    scanf("%d", &p.id);
    getchar();
    // Check if ID already exists
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == p.id) {
            printf("ID da ton tai!\n");
            return;
        }
    }

    printf("Ten san pham: ");
    fgets(p.name, MAX_NAME_LENGTH, stdin);
    p.name[strcspn(p.name, "\n")] = 0; // Remove newline

    printf("Gia: ");
    scanf("%f", &p.price);
    getchar(); // Clear buffer

    printf("So luong: ");
    scanf("%d", &p.quantity);
    getchar(); // Clear buffer

    products[productCount++] = p;
    printf("Them san pham thanh cong!\n");
}

void editProduct() {
    int id;
    printf("Nhap ID san pham can sua: ");
    scanf("%d", &id);
    getchar(); // Clear buffer

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("Nhap thong tin moi:\n");
            printf("Ten san pham: ");
            fgets(products[i].name, MAX_NAME_LENGTH, stdin);
            products[i].name[strcspn(products[i].name, "\n")] = 0;

            printf("Gia: ");
            scanf("%f", &products[i].price);

            printf("So luong: ");
            scanf("%d", &products[i].quantity);

            printf("Sua san pham thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay san pham!\n");
}

void deleteProduct() {
    int id;
    printf("Nhap ID san pham can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            // Shift remaining products
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            printf("Xoa san pham thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay san pham!\n");
}

void searchProduct() {
    int id;
    printf("Nhap ID san pham can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("\n+---------------------------+\n");
            printf("|    THONG TIN SAN PHAM     |\n");
            printf("+---------------------------+\n");
            printf("| %-12s: %-10d |\n", "ID", products[i].id);
            printf("| %-12s: %-10s |\n", "Ten", products[i].name);
            printf("| %-12s: %-10.2f |\n", "Gia", products[i].price);
            printf("| %-12s: %-10d |\n", "So luong", products[i].quantity);
            printf("+---------------------------+\n");
            return;
        }
    }
    printf("Khong tim thay san pham!\n");
}

void displayProducts() {
    if (productCount == 0) {
        printf("Danh sach san pham trong!\n");
        return;
    }

    printf("\n+----+----------------------+--------------+\n");
    printf("| %-2s | %-20s | %-12s |\n", "ID", "Ten", "So luong");
    printf("+----+----------------------+--------------+\n");
    for (int i = 0; i < productCount; i++) {
        printf("| %-2d | %-20s | %12d |\n", 
            products[i].id, 
            products[i].name, 
            products[i].quantity);
    }
    printf("+----+----------------------+--------------+\n");
}

void loadProducts() {
    FILE *file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("Khong tim thay file du lieu san pham!\n");
        return;
    }

    productCount = fread(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    printf("Da tai %d san pham tu file!\n", productCount);
}

void saveProducts() {
    FILE *file = fopen("products.dat", "wb");
    if (file == NULL) {
        printf("Loi khi luu file san pham!\n");
        return;
    }

    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
    printf("Da luu %d san pham vao file!\n", productCount);
}

void inventoryReport() {
    printf("\n+----+----------------------+--------------+\n");
    printf("| %-2s | %-20s | %-12s |\n", "ID", "Ten", "So luong con lai");
    printf("+----+----------------------+--------------+\n");
    for (int i = 0; i < productCount; i++) {
        printf("| %-2d | %-20s | %12d |\n", 
            products[i].id, 
            products[i].name, 
            products[i].quantity);
    }
    printf("+----+----------------------+--------------+\n");
} 