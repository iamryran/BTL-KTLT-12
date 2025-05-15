#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "invoice.h"
#include "customer.h"

static Invoice invoices[MAX_INVOICES];
static int invoiceCount = 0;

// Helper function to find product by ID
static Product* findProduct(int id) {
    extern Product products[MAX_PRODUCTS];
    extern int productCount;
    
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            return &products[i];
        }
    }
    return NULL;
}

void createInvoice() {
    if (invoiceCount >= MAX_INVOICES) {
        printf("Danh sach hoa don da day!\n");
        return;
    }

    Invoice inv;
    inv.id = invoiceCount + 1;
    inv.itemCount = 0;
    inv.total = 0;

    // Get current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(inv.date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    // Nhập thông tin khách hàng
    char phone[MAX_PHONE_LENGTH];
    char name[MAX_NAME_LENGTH];
    printf("Nhap so dien thoai khach hang: \n");
    fgets(phone, MAX_PHONE_LENGTH, stdin);
    phone[strcspn(phone, "\n")] = 0;

    int customerIdx = findCustomerByPhone(phone);
    if (customerIdx != -1) {
        // Khách hàng đã tồn tại
        inv.customerId = customers[customerIdx].id;
        printf("Tim thay khach hang: %s\n", customers[customerIdx].name);
    } else {
        // Khách hàng mới
        printf("Khach hang moi. Vui long nhap ten: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = 0;
        
        int newCustomerId = addOrGetCustomer(name, phone);
        if (newCustomerId == -1) {
            printf("Khong the them khach hang moi!\n");
            return;
        }
        inv.customerId = newCustomerId;
        printf("Da them khach hang moi: %s\n", name);
    }

    printf("\nTao hoa don moi (ID: %d, Ngay: %s)\n", inv.id, inv.date);
    
    while (1) {
        if (inv.itemCount >= MAX_ITEMS) {
            printf("Hoa don da day!\n");
            break;
        }

        // Hiển thị danh sách sản phẩm hiện có (format đẹp)
        printf("\n+----+----------------------+------------+-----------+\n");
        printf("| %-2s | %-20s | %-10s | %-9s |\n", "ID", "Ten", "Gia", "So luong");
        printf("+----+----------------------+------------+-----------+\n");
        for (int i = 0; i < productCount; i++) {
            printf("| %-2d | %-20s | %10.2f | %9d |\n", 
                products[i].id, 
                products[i].name, 
                products[i].price, 
                products[i].quantity);
        }
        printf("+----+----------------------+------------+-----------+\n");


        int productId;
        printf("\nNhap ID san pham (0 de ket thuc): ");
        scanf("%d", &productId);
        getchar(); // Clear buffer
        if (productId == 0) break;

        Product* product = findProduct(productId);
        if (product == NULL) {
            printf("Khong tim thay san pham!\n");
            continue;
        }

        int quantity;
        printf("Nhap so luong: ");
        scanf("%d", &quantity);
        getchar(); // Clear buffer
        if (quantity <= 0 || quantity > product->quantity) {
            printf("So luong khong hop le!\n");
            continue;
        }

        // Add item to invoice
        inv.items[inv.itemCount].productId = productId;
        inv.items[inv.itemCount].quantity = quantity;
        inv.items[inv.itemCount].price = product->price;
        inv.total += product->price * quantity;
        inv.itemCount++;

        // Update product quantity
        product->quantity -= quantity;
        printf("Da them san pham vao hoa don!\n");
    }

    if (inv.itemCount > 0) {
        invoices[invoiceCount++] = inv;
        printf("\nHoa don da duoc tao thanh cong!\n");
        printf("Tong tien: %.2f\n", inv.total);
        // Lưu hóa đơn vào file ngay sau khi tạo
        saveInvoices();
    } else {
        printf("Hoa don khong co san pham nao!\n");
    }
}

void viewInvoice() {
    int id;
    printf("Nhap ID hoa don can xem: ");
    scanf("%d", &id);

    for (int i = 0; i < invoiceCount; i++) {
        if (invoices[i].id == id) {
            // Lấy thông tin khách hàng
            int cid = invoices[i].customerId;
            Customer* c = NULL;
            for (int k = 0; k < customerCount; k++) {
                if (customers[k].id == cid) {
                    c = &customers[k];
                    break;
                }
            }
           printf("\n+------------------------------------------------------------+\n");
            printf("| HOA DON #%-5d                                Ngay: %-10s |\n", invoices[i].id, invoices[i].date);
            printf("+------------------------------------------------------------+\n");
            if (c) {
                printf("| Khach hang: %-30s SDT: %-12s |\n", c->name, c->phone);
            } else {
                printf("| Khach hang: %-44s |\n", "[Khong tim thay]");
            }
            printf("+----+-------+----------------------+----------+-----------+------------+\n");
            printf("| %-2s | %-5s | %-20s | %-8s | %-9s | %-10s |\n", 
                "STT", "ID", "Ten", "So luong", "Don gia", "Thanh tien");
            printf("+----+-------+----------------------+----------+-----------+------------+\n");

            for (int j = 0; j < invoices[i].itemCount; j++) {
                Product* product = findProduct(invoices[i].items[j].productId);
                printf("| %-2d | %-5d | %-20s | %8d | %9.2f | %10.2f |\n",
                    j + 1,
                    product ? product->id : 0,
                    product ? product->name : "[Da xoa]",
                    invoices[i].items[j].quantity,
                    invoices[i].items[j].price,
                    invoices[i].items[j].price * invoices[i].items[j].quantity);
            }

            printf("+----+-------+----------------------+----------+-----------+------------+\n");
            printf("| %-55s | %10.2f |\n", "TONG TIEN:", invoices[i].total);
            printf("+------------------------------------------------------------+------------+\n");

            return;
        }
    }
    printf("Khong tim thay hoa don!\n");
}

void displayInvoices() {
    if (invoiceCount == 0) {
        printf("Danh sach hoa don trong!\n");
        return;
    }

    printf("\n+----+------------+----------------------+------------+\n");
    printf("| %-2s | %-10s | %-20s | %-10s |\n", "ID", "Ngay", "Khach hang", "Tong tien");
    printf("+----+------------+----------------------+------------+\n");
    for (int i = 0; i < invoiceCount; i++) {
        Customer* c = NULL;
        for (int k = 0; k < customerCount; k++) {
            if (customers[k].id == invoices[i].customerId) {
                c = &customers[k];
                break;
            }
        }
        printf("| %-2d | %-10s | %-20s | %10.2f |\n",
            invoices[i].id,
            invoices[i].date,
            c ? c->name : "[Khong tim thay]",
            invoices[i].total);
    }
    printf("+----+------------+----------------------+------------+\n");
}

void loadInvoices() {
    FILE *file = fopen("invoices.dat", "rb");
    if (file == NULL) {
        printf("Khong tim thay file du lieu hoa don!\n");
        return;
    }

    invoiceCount = fread(invoices, sizeof(Invoice), MAX_INVOICES, file);
    fclose(file);
    printf("Da tai %d hoa don tu file!\n", invoiceCount);
}

void saveInvoices() {
    FILE *file = fopen("invoices.dat", "wb");
    if (file == NULL) {
        printf("Loi khi luu file hoa don!\n");
        return;
    }

    fwrite(invoices, sizeof(Invoice), invoiceCount, file);
    fclose(file);
    printf("Da luu %d hoa don vao file!\n", invoiceCount);
}

void revenueByDate() {
    char date[11];
    float total = 0;
    printf("Nhap ngay can thong ke (YYYY-MM-DD): ");
    scanf("%10s", date);
    int found = 0;
    printf("\n+----+------------+\n");
    printf("| %-2s | %-10s |\n", "ID", "Tong tien");
    printf("+----+------------+\n");
    for (int i = 0; i < invoiceCount; i++) {
        if (strcmp(invoices[i].date, date) == 0) {
            printf("| %-2d | %10.2f |\n", invoices[i].id, invoices[i].total);
            total += invoices[i].total;
            found = 1;
        }
    }
    printf("+----+------------+\n");
    if (!found) {
        printf("Khong co hoa don nao trong ngay nay!\n");
    } else {
        printf("Tong doanh thu: %.2f\n", total);
    }
}

void bestSellingProducts() {
    int sold[MAX_PRODUCTS] = {0};
    for (int i = 0; i < invoiceCount; i++) {
        for (int j = 0; j < invoices[i].itemCount; j++) {
            int pid = invoices[i].items[j].productId;
            for (int k = 0; k < productCount; k++) {
                if (products[k].id == pid) {
                    sold[k] += invoices[i].items[j].quantity;
                    break;
                }
            }
        }
    }
    printf("\n+----+----------------------+--------------+\n");
    printf("| %-2s | %-20s | %-12s |\n", "ID", "Ten", "So luong ban");
    printf("+----+----------------------+--------------+\n");
    for (int i = 0; i < productCount; i++) {
        if (sold[i] > 0) {
            printf("| %-2d | %-20s | %12d |\n", 
                products[i].id, 
                products[i].name, 
                sold[i]);
        }
    }
    printf("+----+----------------------+--------------+\n");

} 