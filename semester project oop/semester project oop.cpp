#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SkincareProduct {
private:
    string name;
    double price;
    int quantity;

public:
    SkincareProduct() : name("\0"), price(0.0), quantity(0) {}

    SkincareProduct(const string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    void decreaseQuantity() {
        if (quantity > 0) {
            quantity--;
        }
    }
};

class CartItem {
private:
    SkincareProduct product;
    int quantity;

public:
    CartItem() {}
    CartItem(const SkincareProduct& product, int quantity = 1)
        : product(product), quantity(quantity) {}

    SkincareProduct getProduct() const {
        return product;
    }

    int getQuantity() const {
        return quantity;
    }

    void increaseQuantity() {
        quantity++;
    }
};

class SkincareStore {
private:
    SkincareProduct products[10];
    CartItem cart[22];
    int cartSize;

public:
    SkincareStore() : cartSize(0) {
        // Add some sample products
        products[0] = SkincareProduct("Cleanser", 1500, 40);
        products[1] = SkincareProduct("Moisturizer", 1500, 30);
        products[2] = SkincareProduct("Face wash", 1000, 20);
        products[3] = SkincareProduct("Sunscreen", 1200, 40);
        products[4] = SkincareProduct("Lip balm", 600, 19);
        products[5] = SkincareProduct("Vitamin C serum", 1600, 20);
        products[6] = SkincareProduct("Vitamin B-3 serum", 1600, 20);
        products[7] = SkincareProduct("Lip oil", 400, 20);
    }

    void displayMenu() const {
        cout << "Skincare Product Menu:\n";
        cout << "======================\n";
        cout << endl;
        for (int i = 0; i < 8; ++i) {
            cout << i + 1 << ". " << products[i].getName() << " - Rs" << products[i].getPrice() << " (Quantity: " << products[i].getQuantity() << ")" << endl;
        }
        cout << endl;
        cout << "======================\n";
    }

 
    void addToCart(int choice) {
        if (choice > 0 && choice <= 8) {
            SkincareProduct selectedProduct = products[choice - 1];
            if (selectedProduct.getQuantity() > 0) {
                bool found = false;
                for (int i = 0; i < cartSize; ++i) {
                    if (cart[i].getProduct().getName() == selectedProduct.getName()) {
                        cart[i].increaseQuantity();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cart[cartSize++] = CartItem(selectedProduct);
                }
                selectedProduct.decreaseQuantity();
                cout << "Added to cart: " << selectedProduct.getName() << endl;
            }
            else {
                cout << "Sorry, the selected product is out of stock." << endl;
            }
        }
        else {
   
            cout << "Invalid choice. Please try again." << endl;
            displayMenu();
            int newChoice;
            cout << "please enter again" << endl;
            cin >> newChoice;
            addToCart(newChoice);
        }
    }

    void displayCart() const {
        cout << "Cart:\n";
        cout << "======================\n";
        for (int i = 0; i < cartSize; ++i) {
            CartItem cartItem = cart[i];
            SkincareProduct product = cartItem.getProduct();
            cout << product.getName() << " - Rs" << product.getPrice() << " (Quantity: " << cartItem.getQuantity() << ")" << endl;
        }
        cout << "======================\n";
    }

    double calculateTotalBill() const {
        double total = 0.0;
        for (int i = 0; i < cartSize; ++i) {
            CartItem cartItem = cart[i];
            SkincareProduct product = cartItem.getProduct();
            total += product.getPrice() * cartItem.getQuantity();
        }
        return total;
    }
};

class Customer {
private:
    string name;
    string address;
    string contact;

public:
    Customer(const string& name, const string& address, const string& contact)
        : name(name), address(address), contact(contact) {}

    string getName() const {
        return name;
    }

    string getAddress() const {
        return address;
    }

    string getContact() const {
        return contact;
    }
};

class Order : public Customer {
private:
    double totalBill;

public:
    Order(const Customer& customer, double totalBill)
        : Customer(customer), totalBill(totalBill) {}

    double getTotalBill() const {
        return totalBill;
    }
    void saveToFile() const {
        ofstream file;
        file.open("E:order.txt", ios::app);
        if (file.is_open()) {
            file << "Name: " << getName() << endl;
            file << "Address: " << getAddress() << endl;
            file << "Contact Number: " << getContact() << endl;
            file << "Total Bill: Rs" << getTotalBill() << endl;
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }

};

int main() {
    SkincareStore store;
    int choice;
    char continueShopping;
    cout << "\t" << "\t" << "\t" << "\t" << "\t""*****************************" << endl;
    cout << "\t" << "\t" << "\t" << "\t" << "\t"" Welcome to the AK skinStore!\n";
    cout << "\t" << "\t" << "\t" << "\t" << "\t""*****************************" << endl;
    cout << endl;
    do {
        system("cls");
        store.displayMenu();
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        store.addToCart(choice);

        cout << "Do you want to continue shopping? (y/n): ";
        cin >> continueShopping;
    } while (continueShopping == 'y' || continueShopping == 'Y');

    store.displayCart();

    // Get customer information
    string name, address, contact;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your address: ";
    getline(cin, address);
    cin.ignore();
    cout << "Enter your contact number: ";
    getline(cin, contact);
    cin.ignore();
    Customer customer(name, address, contact);
    double totalBill = store.calculateTotalBill();

    Order order(customer, totalBill);

    cout << "----------------------\n";
    cout << "Name: " << order.getName() << endl;
    cout << "Address: " << order.getAddress() << endl;
    cout << "Contact Number: " << order.getContact() << endl;
    cout << "Total Bill: Rs" << order.getTotalBill() << endl;
    order.saveToFile();
    return 0;
}
