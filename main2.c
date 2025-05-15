#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "invoice.h"
#include "customer.h"

// Hàm xóa dữ liệu trong file
void clearDataFiles() {
    // Xóa file products.dat
    FILE *fp = fopen("products.dat", "wb");
    if (fp) {
        fclose(fp);
        printf("Da xoa du lieu san pham!\n");
    }

    // Xóa file customers.dat
    fp = fopen("customers.dat", "wb");
    if (fp) {
        fclose(fp);
        printf("Da xoa du lieu khach hang!\n");
    }

    // Xóa file invoices.dat
    fp = fopen("invoices.dat", "wb");
    if (fp) {
        fclose(fp);
        printf("Da xoa du lieu hoa don!\n");
    }
}

// Hàm tạo dữ liệu mẫu cho sản phẩm
void createSampleProducts() {
    Product sampleProducts[] = {
        {1, "Laptop Dell XPS", 25000000, 10},
        {2, "iPhone 14 Pro", 30000000, 15},
        {3, "Samsung S23", 20000000, 20},
        {4, "Tai nghe AirPods", 5000000, 30},
        {5, "Chuot Logitech", 1000000, 50}
    };

    FILE *fp = fopen("products.dat", "wb");
    if (fp) {
        fwrite(sampleProducts, sizeof(Product), 5, fp);
        fclose(fp);
        printf("Da tao du lieu mau cho san pham!\n");
    }
}

// Hàm tạo dữ liệu mẫu cho khách hàng
void createSampleCustomers() {
    Customer sampleCustomers[] = {
        {1, "Nguyen Van A", "0123456789"},
        {2, "Tran Thi B", "0987654321"},
        {3, "Le Van C", "0123987456"},
        {4, "Pham Thi D", "0567891234"},
        {5, "Hoang Van E", "0789456123"}
    };

    FILE *fp = fopen("customers.dat", "wb");
    if (fp) {
        fwrite(sampleCustomers, sizeof(Customer), 5, fp);
        fclose(fp);
        printf("Da tao du lieu mau cho khach hang!\n");
    }
}

// Hàm tạo dữ liệu mẫu cho hóa đơn
void createSampleInvoices() {
    // Tạo hóa đơn mẫu
    Invoice inv1 = {
        .id = 1,
        .date = "2024-03-15",
        .customerId = 1,
        .itemCount = 2,
        .total = 30000000,
        .items = {
            {1, 1, 25000000},  // 1 Laptop Dell XPS
            {4, 1, 5000000}    // 1 AirPods
        }
    };

    Invoice inv2 = {
        .id = 2,
        .date = "2024-03-15",
        .customerId = 2,
        .itemCount = 1,
        .total = 30000000,
        .items = {
            {2, 1, 30000000}   // 1 iPhone 14 Pro
        }
    };

    Invoice inv3 = {
        .id = 3,
        .date = "2024-03-16",
        .customerId = 3,
        .itemCount = 3,
        .total = 26000000,
        .items = {
            {3, 1, 20000000},  // 1 Samsung S23
            {4, 1, 5000000},   // 1 AirPods
            {5, 1, 1000000}    // 1 Chuot Logitech
        }
    };

    Invoice sampleInvoices[] = {inv1, inv2, inv3};

    FILE *fp = fopen("invoices.dat", "wb");
    if (fp) {
        fwrite(sampleInvoices, sizeof(Invoice), 3, fp);
        fclose(fp);
        printf("Da tao du lieu mau cho hoa don!\n");
    }
}

void displayMenu() {
    printf("\n+===============================+\n");
    printf("|      QUAN LY DU LIEU          |\n");
    printf("+===============================+\n");
    printf("| 1. Xoa tat ca du lieu         |\n");
    printf("| 2. Tao du lieu mau            |\n");
    printf("| 3. Hien thi du lieu hien tai  |\n");
    printf("| 0. Thoat                      |\n");
    printf("+===============================+\n");
    printf("Chon chuc nang: ");

}

void displayCurrentData() {
    // Load và hiển thị dữ liệu sản phẩm
    loadProducts();
    printf("\n=== DANH SACH SAN PHAM ===\n");
    displayProducts();

    // Load và hiển thị dữ liệu khách hàng
    loadCustomers();
    printf("\n=== DANH SACH KHACH HANG ===\n");
    displayCustomers();

    // Load và hiển thị dữ liệu hóa đơn
    loadInvoices();
    printf("\n=== DANH SACH HOA DON ===\n");
    displayInvoices();
}

int main() {
    int choice;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                clearDataFiles();
                break;
            case 2:
                createSampleProducts();
                createSampleCustomers();
                createSampleInvoices(); 
                break;
            case 3:
                displayCurrentData();
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(choice != 0);

    return 0;
} 