#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "invoice.h"
#include "customer.h"

void displayMenu() {
    printf("\n+==============================+\n");
    printf("|     QUAN LY BAN HANG         |\n");
    printf("+==============================+\n");
    printf("| 1. Quan ly san pham          |\n");
    printf("| 2. Quan ly hoa don           |\n");
    printf("| 3. Thong ke                  |\n");
    printf("| 4. Quan ly khach hang        |\n");
    printf("| 0. Thoat                     |\n");
    printf("+==============================+\n");
    printf("Chon chuc nang: ");

}

void productManagement() {
    int choice;
    do {
        printf("\n+===============================+\n");
        printf("|     QUAN LY SAN PHAM          |\n");
        printf("+===============================+\n");
        printf("| 1. Them san pham              |\n");
        printf("| 2. Sua san pham               |\n");
        printf("| 3. Xoa san pham               |\n");
        printf("| 4. Tim kiem san pham          |\n");
        printf("| 5. Hien thi danh sach san pham|\n");
        printf("| 0. Quay lai                   |\n");
        printf("+===============================+\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch(choice) {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                searchProduct();
                break;
            case 5:
                displayProducts();
                break;
        }
    } while(choice != 0);

}

void invoiceManagement() {
    int choice;
    do {
        printf("\n+=============================+\n");
        printf("|      QUAN LY HOA DON        |\n");
        printf("+=============================+\n");
        printf("| 1. Tao hoa don moi          |\n");
        printf("| 2. Xem chi tiet hoa don     |\n");
        printf("| 3. Hien thi danh sach hoa don|\n");
        printf("| 0. Quay lai                 |\n");
        printf("+=============================+\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch(choice) {
            case 1:
                createInvoice();
                break;
            case 2:
                viewInvoice();
                break;
            case 3:
                displayInvoices();
                break;
        }
    } while(choice != 0);

}

void statistics() {
    int choice;
    do {
        printf("\n+=============================+\n");
        printf("|         THONG KE            |\n");
        printf("+=============================+\n");
        printf("| 1. Doanh thu theo ngay      |\n");
        printf("| 2. San pham ban chay        |\n");
        printf("| 3. Ton kho                  |\n");
        printf("| 0. Quay lai                 |\n");
        printf("+=============================+\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch(choice) {
            case 1:
                revenueByDate();
                break;
            case 2:
                bestSellingProducts();
                break;
            case 3:
                inventoryReport();
                break;
        }
    } while(choice != 0);

}

void customerManagement() {
    int choice;
    do {
        printf("\n+=============================+\n");
        printf("|     QUAN LY KHACH HANG       |\n");
        printf("+=============================+\n");
        printf("| 1. Them khach hang          |\n");
        printf("| 2. Sua khach hang           |\n");
        printf("| 3. Xoa khach hang           |\n");
        printf("| 4. Tim kiem khach hang      |\n");
        printf("| 5. Hien thi danh sach khach hang|\n");
        printf("| 0. Quay lai                 |\n");
        printf("+=============================+\n");
        printf("5. Hien thi danh sach khach hang\n");
        printf("0. Quay lai\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: addCustomer(); break;
            case 2: editCustomer(); break;
            case 3: deleteCustomer(); break;
            case 4: searchCustomer(); break;
            case 5: displayCustomers(); break;
        }
    } while(choice != 0);
}

int main() {
    int choice;
    
    // Load data from files
    loadProducts();
    loadInvoices();
    loadCustomers();

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch(choice) {
            case 1:
                productManagement();
                break;
            case 2:
                invoiceManagement();
                break;
            case 3:
                statistics();
                break;
            case 4:
                customerManagement();
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(choice != 0);

    // Save data to files before exit
    saveProducts();
    saveInvoices();
    saveCustomers();

    return 0;
} 