#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

int findCustomerByPhone(const char* phone) {
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            return i;
        }
    }
    return -1;
}

int addOrGetCustomer(const char* name, const char* phone) {
    int idx = findCustomerByPhone(phone);
    if (idx != -1) return customers[idx].id;
    if (customerCount >= MAX_CUSTOMERS) return -1;
    customers[customerCount].id = customerCount + 1;
    strncpy(customers[customerCount].name, name, MAX_NAME_LENGTH);
    strncpy(customers[customerCount].phone, phone, MAX_PHONE_LENGTH);
    customerCount++;
    return customers[customerCount-1].id;
}

void addCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Danh sach khach hang da day!\n");
        return;
    }
    Customer c;
    c.id = customerCount + 1;
    
    printf("Nhap ten khach hang: ");
    getchar();
    fgets(c.name, MAX_NAME_LENGTH, stdin);
    c.name[strcspn(c.name, "\n")] = 0;
    
    printf("Nhap so dien thoai: ");
    fgets(c.phone, MAX_PHONE_LENGTH, stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;
    
    if (findCustomerByPhone(c.phone) != -1) {
        printf("Khach hang da ton tai!\n");
        return;
    }
    customers[customerCount++] = c;
    printf("Them khach hang thanh cong!\n");
}

void editCustomer() {
    char phone[MAX_PHONE_LENGTH];
    printf("Nhap so dien thoai khach hang can sua: ");
    getchar();
    fgets(phone, MAX_PHONE_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;
    int idx = findCustomerByPhone(phone);
    if (idx == -1) {
        printf("Khong tim thay khach hang!\n");
        return;
    }
    printf("Nhap ten moi: ");
    fgets(customers[idx].name, MAX_NAME_LENGTH, stdin);
    customers[idx].name[strcspn(customers[idx].name, "\n")] = 0;
    printf("Nhap so dien thoai moi: ");
    fgets(customers[idx].phone, MAX_PHONE_LENGTH, stdin);
    customers[idx].phone[strcspn(customers[idx].phone, "\n")] = 0;
    printf("Sua thong tin thanh cong!\n");
}

void deleteCustomer() {
    char phone[MAX_PHONE_LENGTH];
    printf("Nhap so dien thoai khach hang can xoa: ");
    getchar();
    fgets(phone, MAX_PHONE_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;
    int idx = findCustomerByPhone(phone);
    if (idx == -1) {
        printf("Khong tim thay khach hang!\n");
        return;
    }
    for (int i = idx; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1];
    }
    customerCount--;
    printf("Xoa khach hang thanh cong!\n");
}

void searchCustomer() {
    char phone[MAX_PHONE_LENGTH];
    printf("Nhap so dien thoai khach hang can tim: ");
    getchar();
    fgets(phone, MAX_PHONE_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;
    int idx = findCustomerByPhone(phone);
    if (idx == -1) {
        printf("Khong tim thay khach hang!\n");
        return;
    }
    printf("ID: %d\nTen: %s\nSDT: %s\n", customers[idx].id, customers[idx].name, customers[idx].phone);
}

void displayCustomers() {
    printf("\n+----+----------------------+--------------+\n");
    printf("| %-2s | %-20s | %-12s |\n", "ID", "Ten", "SDT");
    printf("+----+----------------------+--------------+\n");
    for (int i = 0; i < customerCount; i++) {
        printf("| %-2d | %-20s | %12s |\n", customers[i].id, customers[i].name, customers[i].phone);
    }
    printf("+----+----------------------+--------------+\n");
}

void loadCustomers() {
    FILE *file = fopen("customers.dat", "rb");
    if (file == NULL) return;
    customerCount = fread(customers, sizeof(Customer), MAX_CUSTOMERS, file);
    fclose(file);
}

void saveCustomers() {
    FILE *file = fopen("customers.dat", "wb");
    if (file == NULL) return;
    fwrite(customers, sizeof(Customer), customerCount, file);
    fclose(file);
} 