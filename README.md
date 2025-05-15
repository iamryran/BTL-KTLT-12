# Hệ Thống Quản Lý Bán Hàng

Đây là một hệ thống quản lý bán hàng được viết bằng ngôn ngữ C, cho phép quản lý sản phẩm, khách hàng và hóa đơn.

## Cấu Trúc Dự Án

### 1. Quản Lý Sản Phẩm (product.h, product.c)
#### Cấu Trúc Dữ Liệu
```c
typedef struct {
    int id;                 // Mã sản phẩm
    char name[50];         // Tên sản phẩm
    float price;           // Giá sản phẩm
    int quantity;          // Số lượng tồn kho
} Product;
```

#### Các Phương Thức
- `addProduct()`: Thêm sản phẩm mới
- `editProduct()`: Chỉnh sửa thông tin sản phẩm
- `deleteProduct()`: Xóa sản phẩm
- `searchProduct()`: Tìm kiếm sản phẩm
- `displayProducts()`: Hiển thị danh sách sản phẩm
- `loadProducts()`: Đọc dữ liệu sản phẩm từ file
- `saveProducts()`: Lưu dữ liệu sản phẩm vào file
- `inventoryReport()`: Báo cáo tồn kho

### 2. Quản Lý Khách Hàng (customer.h, customer.c)
#### Cấu Trúc Dữ Liệu
```c
typedef struct {
    int id;                 // Mã khách hàng
    char name[50];         // Tên khách hàng
    char phone[15];        // Số điện thoại
} Customer;
```

#### Các Phương Thức
- `addCustomer()`: Thêm khách hàng mới
- `editCustomer()`: Chỉnh sửa thông tin khách hàng
- `deleteCustomer()`: Xóa khách hàng
- `searchCustomer()`: Tìm kiếm khách hàng
- `displayCustomers()`: Hiển thị danh sách khách hàng
- `loadCustomers()`: Đọc dữ liệu khách hàng từ file
- `saveCustomers()`: Lưu dữ liệu khách hàng vào file
- `findCustomerByPhone()`: Tìm khách hàng theo số điện thoại
- `addOrGetCustomer()`: Thêm hoặc lấy thông tin khách hàng

### 3. Quản Lý Hóa Đơn (invoice.h, invoice.c)
#### Cấu Trúc Dữ Liệu
```c
typedef struct {
    int productId;         // Mã sản phẩm
    int quantity;          // Số lượng
    float price;           // Đơn giá
} InvoiceItem;

typedef struct {
    int id;                // Mã hóa đơn
    char date[11];         // Ngày lập hóa đơn
    int customerId;        // Mã khách hàng
    InvoiceItem items[20]; // Danh sách sản phẩm
    int itemCount;         // Số lượng sản phẩm
    float total;           // Tổng tiền
} Invoice;
```

#### Các Phương Thức
- `createInvoice()`: Tạo hóa đơn mới
- `viewInvoice()`: Xem chi tiết hóa đơn
- `displayInvoices()`: Hiển thị danh sách hóa đơn
- `loadInvoices()`: Đọc dữ liệu hóa đơn từ file
- `saveInvoices()`: Lưu dữ liệu hóa đơn vào file
- `revenueByDate()`: Thống kê doanh thu theo ngày
- `bestSellingProducts()`: Thống kê sản phẩm bán chạy

## Cách Sử Dụng

1. **Biên Dịch Chương Trình**
   ```bash
   gcc main.c product.c customer.c invoice.c -o main
   ```

   **Biên dịch chương trình config database**
   ```bash
   gcc main2.c product.c customer.c invoice.c -o dtb
   ```

2. **Chạy Chương Trình**
   ```bash
   ./main
   ```

   **Chạy chương trình config database**
   ```bash
   ./dtb
   ```
   Chương trình dtb cho phép bạn:
   - Khởi tạo dữ liệu mẫu
   - Xóa toàn bộ dữ liệu
   - Sao lưu dữ liệu
   - Khôi phục dữ liệu từ bản sao lưu

3. **Menu Chính**
   - Quản lý sản phẩm
   - Quản lý khách hàng
   - Quản lý hóa đơn
   - Báo cáo thống kê

## Lưu ý
- Dữ liệu được lưu trong các file: products.dat, customers.dat, invoices.dat
- Mỗi loại dữ liệu có giới hạn tối đa 100 bản ghi
- Mỗi hóa đơn có thể chứa tối đa 20 sản phẩm
- Định dạng ngày tháng: YYYY-MM-DD

## Yêu Cầu Hệ Thống
- Hệ điều hành: Windows/Linux
- Trình biên dịch C (gcc)
- Bộ nhớ tối thiểu: 512MB
- Dung lượng ổ đĩa: 10MB
