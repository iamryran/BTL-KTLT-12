#ifndef INVOICE_H
#define INVOICE_H

#include "product.h"

#define MAX_INVOICES 100
#define MAX_ITEMS 20

typedef struct {
    int productId;
    int quantity;
    float price;
} InvoiceItem;

typedef struct {
    int id;
    char date[11]; // Format: YYYY-MM-DD
    int customerId;
    InvoiceItem items[MAX_ITEMS];
    int itemCount;
    float total;
} Invoice;

// Function declarations
void createInvoice();
void viewInvoice();
void displayInvoices();
void loadInvoices();
void saveInvoices();
void revenueByDate();
void bestSellingProducts();

#endif 