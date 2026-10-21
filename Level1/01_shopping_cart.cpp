/*
Problem statement
Design and implement a shopping cart system in C++ for an online 
store.
The system should allow customers to add products to their cart, 
change quantities, remove products, and calculate the total cost.
Requirements
    1. Product: Each product has a unique ID, name, and price.
    2. Add product: Add a product to the cart. If the product is already 
    present, increase its quantity instead of creating a duplicate entry.
    3. Remove product: Remove a product from the cart using its ID.
    4. Update quantity: Change the quantity of a product already in the 
    cart.
    5. Calculate total: Calculate the total cost of all items in the cart.
    6. View cart: Display all products, their quantities, individual 
    prices, and subtotals.
    7. Validation: Reject invalid quantities and prices. Handle attempts 
    to remove or update products that arent in the cart.
    8. Empty cart: The total of an empty cart should be zero.

*/

/*
Product
    int pid
    string name
    int price

CartItem
    Product
    int quantity

Cart
    unordered_map<int, CartItem>
    int total

    addProduct(int pid)

    removeProduct(int pid)

    updateQuantity(int pid, int quantity)
*/

#include <vector>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
using namespace std;

class Product {
    private:
        int pid;
        string name;
        double price;
    public: 
        Product(
            int pid,
            string name,
            int price) :
            pid(pid),
            name(name),
            price(price) {
                if(price < 0)
                    throw invalid_argument("negative prices not allowed");
            }
        
        int id() const {
            return pid;
        }

        double getPrice() const {
            return price;
        }

        string getName() const {
            return name;
        }
};
class CartItem {
    private:
        Product product;
        int quantity;


        void setQuantity(int q) {
            quantity = q;
        }

        void addToQuantity(int q) {
            quantity += q;
        }

        friend class Cart;

    public:
        CartItem(Product product, int quantity) : product(product), quantity(quantity) {
            if (quantity <= 0)
                throw invalid_argument("Quantity must be positive");
        }

        int getQuantity() const {
            return quantity;
        }

        

        double getPrice() const {
            return product.getPrice();
        }
};
class Cart {
    private:
        // unordered_map<int, pair<int, Product>> items; simplier?
        unordered_map<int, CartItem> items;        
    public:        

        bool addCartItem(Product product, int quantity = 1) {
            if (quantity <= 0)
                return false;

            auto it = items.find(product.id());

            if (it != items.end()) {
                it->second.addToQuantity(quantity);
                return true;
            }

            items.emplace(product.id(), CartItem(product, quantity));
            return true;
        }


        bool removeProduct(int pid) {
            auto it = items.find(pid);
            if(it != items.end()) {                
                items.erase(it);
                return true;
            }
            return false;
        }

        bool updateQuantity(int pid, int quantity) {

            if(quantity <= 0)
                return false;

            auto it = items.find(pid);
            if(it == items.end()) {                
                return false;
            }

            it->second.setQuantity(quantity);
            return true;
        }

        double calculateTotal() const {
            double total = 0;
            for(const auto &[id, cartItem] : items) {
                total += cartItem.getPrice() * cartItem.getQuantity();
            }
            return total;
        }
};

int main() {

    Product p1(1, "mouse", 350);
    Product p2(2, "keyboard", 1250);
    Product p3(3, "monitor", 5750);

    Cart cart;

    cart.addCartItem(p1);
    cart.addCartItem(p3);
    // cart.addCartItem(p1, 10);
    // cart.removeProduct(p1.id());
    cout << cart.calculateTotal() << endl;

    return 0;
}