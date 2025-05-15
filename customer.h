#ifndef CUSTOMER_H
#define CUSTOMER_H

#define MAX_CUSTOMERS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Customer;

extern Customer customers[MAX_CUSTOMERS];
extern int customerCount;

void addCustomer();
void editCustomer();
void deleteCustomer();
void searchCustomer();
void displayCustomers();
void loadCustomers();
void saveCustomers();

// Hàm hỗ trợ
int findCustomerByPhone(const char* phone);
int addOrGetCustomer(const char* name, const char* phone);

#endif 