#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  FORWARD DECLARATIONS
// ============================================================
class User;
class MenuItem;
class Restaurant;
struct CartItem;
class Cart;
class Order;

// ============================================================
//  GLOBAL DATA
// ============================================================
vector<User>       users;
vector<Restaurant> restaurants;
vector<Order>      allOrders;
int                orderCounter = 1;

// ============================================================
//  USER CLASS
// ============================================================
class User {
public:
    string name;
    string email;
    string password;
    string role; // "customer" or "admin"

    User() {}
    User(string n, string e, string p, string r) {
        name     = n;
        email    = e;
        password = p;
        role     = r;
    }
};

// ============================================================
//  MENU ITEM CLASS
// ============================================================
class MenuItem {
public:
    int    id;
    string name;
    string description;
    double price;

    MenuItem() {}
    MenuItem(int i, string n, string d, double p) {
        id          = i;
        name        = n;
        description = d;
        price       = p;
    }

    void display() {
        cout << "  [" << id << "] " << name
             << "  -  Rs." << price << "\n"
             << "      " << description << "\n";
    }
};

// ============================================================
//  RESTAURANT CLASS
// ============================================================
class Restaurant {
public:
    int              id;
    string           name;
    string           cuisineType;
    vector<MenuItem> menu;

    Restaurant() {}
    Restaurant(int i, string n, string c) {
        id          = i;
        name        = n;
        cuisineType = c;
    }

    void addItem(MenuItem item) {
        menu.push_back(item);
    }

    void displayMenu() {
        cout << "\n🍽️  " << name << " (" << cuisineType << ")\n";
        cout << string(40, '-') << "\n";
        for (auto& item : menu) {
            item.display();
        }
    }
};

// ============================================================
//  CART ITEM STRUCT
// ============================================================
struct CartItem {
    MenuItem item;
    int      quantity;

    CartItem(MenuItem i, int q) {
        item     = i;
        quantity = q;
    }

    double subtotal() {
        return item.price * quantity;
    }

    void display() {
        cout << "  " << item.name
             << " x" << quantity
             << "  =  Rs." << subtotal() << "\n";
    }
};

// ============================================================
//  CART CLASS
// ============================================================
class Cart {
public:
    vector<CartItem> items;
    int              restaurantId;
    string           restaurantName;

    Cart() {
        restaurantId   = -1;
        restaurantName = "";
    }

    void addItem(MenuItem item, int qty, int restId, string restName) {
        if (restaurantId != -1 && restaurantId != restId) {
            cout << "⚠️  You can only order from one restaurant at a time.\n";
            cout << "    Clear your cart first to switch restaurants.\n";
            return;
        }

        restaurantId   = restId;
        restaurantName = restName;

        for (auto& ci : items) {
            if (ci.item.id == item.id) {
                ci.quantity += qty;
                cout << "✅ Updated quantity for " << item.name << "\n";
                return;
            }
        }

        items.push_back(CartItem(item, qty));
        cout << "✅ " << item.name << " added to cart!\n";
    }

    void viewCart() {
        if (items.empty()) {
            cout << "\n🛒 Your cart is empty.\n";
            return;
        }

        cout << "\n🛒 Your Cart (" << restaurantName << ")\n";
        cout << string(40, '-') << "\n";

        double total = 0;
        for (auto& ci : items) {
            ci.display();
            total += ci.subtotal();
        }

        cout << string(40, '-') << "\n";
        cout << "  Total:  Rs." << total << "\n";
    }

    double getTotal() {
        double total = 0;
        for (auto& ci : items) total += ci.subtotal();
        return total;
    }

    void clear() {
        items.clear();
        restaurantId   = -1;
        restaurantName = "";
        cout << "🗑️  Cart cleared.\n";
    }

    bool isEmpty() {
        return items.empty();
    }
};

// ============================================================
//  ORDER CLASS
// ============================================================
class Order {
public:
    int              orderId;
    string           customerName;
    string           restaurantName;
    vector<CartItem> items;
    double           total;
    string           status;

    Order(int id, string customer, string restaurant,
          vector<CartItem> cartItems, double t) {
        orderId        = id;
        customerName   = customer;
        restaurantName = restaurant;
        items          = cartItems;
        total          = t;
        status         = "Confirmed";
    }

    void display() {
        cout << "\n📦 Order #" << orderId << "\n";
        cout << "   Restaurant : " << restaurantName << "\n";
        cout << "   Customer   : " << customerName   << "\n";
        cout << "   Status     : " << status         << "\n";
        cout << string(40, '-') << "\n";
        for (auto& ci : items) ci.display();
        cout << string(40, '-') << "\n";
        cout << "   Total      : Rs." << total << "\n";
    }
};

// ============================================================
//  LOAD RESTAURANTS
// ============================================================
void loadRestaurants() {
    // 1. Pizza Palace
    Restaurant r1(1, "Pizza Palace", "Italian");
    r1.addItem(MenuItem(1, "Margherita Pizza",  "Classic tomato & cheese",        850));
    r1.addItem(MenuItem(2, "Pepperoni Pizza",   "Loaded with pepperoni",          1100));
    r1.addItem(MenuItem(3, "Garlic Bread",      "Toasted with garlic butter",     350));
    restaurants.push_back(r1);

    // 2. Burger Barn
    Restaurant r2(2, "Burger Barn", "American");
    r2.addItem(MenuItem(1, "Classic Burger",    "Beef patty with lettuce & tomato", 650));
    r2.addItem(MenuItem(2, "Cheese Burger",     "Double cheese beef burger",        750));
    r2.addItem(MenuItem(3, "Crispy Fries",      "Golden salted fries",              300));
    restaurants.push_back(r2);

    // 3. Sushi Station
    Restaurant r3(3, "Sushi Station", "Japanese");
    r3.addItem(MenuItem(1, "Salmon Roll",       "Fresh salmon with avocado",      1200));
    r3.addItem(MenuItem(2, "Tuna Nigiri",       "Premium tuna on rice",           1000));
    r3.addItem(MenuItem(3, "Miso Soup",         "Traditional Japanese soup",       400));
    restaurants.push_back(r3);

    // 4. Karahi King
    Restaurant r4(4, "Karahi King", "Pakistani");
    r4.addItem(MenuItem(1, "Chicken Karahi",    "Spicy tomato-based karahi",      1500));
    r4.addItem(MenuItem(2, "Mutton Karahi",     "Tender mutton karahi",           2200));
    r4.addItem(MenuItem(3, "Naan",              "Fresh tandoor naan",               50));
    restaurants.push_back(r4);

    // 5. Taco Town
    Restaurant r5(5, "Taco Town", "Mexican");
    r5.addItem(MenuItem(1, "Beef Taco",         "Spiced beef in crispy shell",     700));
    r5.addItem(MenuItem(2, "Chicken Burrito",   "Grilled chicken wrap",            850));
    r5.addItem(MenuItem(3, "Nachos",            "Chips with salsa & cheese",       600));
    restaurants.push_back(r5);

    // 6. Noodle Nest
    Restaurant r6(6, "Noodle Nest", "Chinese");
    r6.addItem(MenuItem(1, "Chow Mein",         "Stir-fried noodles with veggies", 650));
    r6.addItem(MenuItem(2, "Kung Pao Chicken",  "Spicy peanut chicken",            900));
    r6.addItem(MenuItem(3, "Spring Rolls",      "Crispy veggie rolls",             400));
    restaurants.push_back(r6);

    // 7. BBQ Brothers
    Restaurant r7(7, "BBQ Brothers", "BBQ");
    r7.addItem(MenuItem(1, "Chicken Tikka",     "Marinated grilled chicken",      1100));
    r7.addItem(MenuItem(2, "Seekh Kebab",       "Spiced minced meat skewers",      950));
    r7.addItem(MenuItem(3, "BBQ Platter",       "Mixed grill for two",            2500));
    restaurants.push_back(r7);

    // 8. Wrap World
    Restaurant r8(8, "Wrap World", "Fusion");
    r8.addItem(MenuItem(1, "Zinger Wrap",       "Crispy chicken with coleslaw",    700));
    r8.addItem(MenuItem(2, "Shawarma",          "Grilled meat with garlic sauce",  600));
    r8.addItem(MenuItem(3, "Club Wrap",         "Turkey, bacon & veggies",         800));
    restaurants.push_back(r8);

    // 9. Biryani Bay
    Restaurant r9(9, "Biryani Bay", "Pakistani");
    r9.addItem(MenuItem(1, "Chicken Biryani",   "Aromatic spiced rice with chicken", 550));
    r9.addItem(MenuItem(2, "Mutton Biryani",    "Slow-cooked mutton biryani",        750));
    r9.addItem(MenuItem(3, "Raita",             "Yogurt side dish",                  100));
    restaurants.push_back(r9);

    // 10. Dessert Den
    Restaurant r10(10, "Dessert Den", "Desserts");
    r10.addItem(MenuItem(1, "Chocolate Lava Cake", "Warm cake with molten center",  650));
    r10.addItem(MenuItem(2, "Mango Kulfi",          "Traditional Pakistani ice cream", 350));
    r10.addItem(MenuItem(3, "Gulab Jamun",          "Soft syrup-soaked sweets",       250));
    restaurants.push_back(r10);
}

// ============================================================
//  USER FUNCTIONS
// ============================================================
void registerUser() {
    string name, email, password;
    cout << "\nEnter Name: ";     cin >> ws; getline(cin, name);
    cout << "Enter Email: ";      getline(cin, email);
    cout << "Enter Password: ";   getline(cin, password);

    // Check if email already exists
    for (auto& u : users) {
        if (u.email == email) {
            cout << "❌ Email already registered.\n";
            return;
        }
    }

    users.push_back(User(name, email, password, "customer"));
    cout << "\n✅ Registered successfully! You can now login.\n";
}

User* loginUser() {
    string email, password;
    cout << "\nEnter Email: ";    cin >> ws; getline(cin, email);
    cout << "Enter Password: ";   getline(cin, password);

    for (auto& u : users) {
        if (u.email == email && u.password == password) {
            cout << "\n✅ Welcome, " << u.name << "!\n";
            return &u;
        }
    }
    cout << "\n❌ Invalid email or password.\n";
    return nullptr;
}

// ============================================================
//  RESTAURANT BROWSE FUNCTIONS
// ============================================================
void browseRestaurants() {
    cout << "\n===== 🏪 Restaurants =====\n";
    for (auto& r : restaurants) {
        cout << "[" << r.id << "] " << r.name
             << "  -  " << r.cuisineType << "\n";
    }
}

// ============================================================
//  ORDER FUNCTIONS
// ============================================================
void placeOrder(User* user, Cart& cart) {
    if (cart.isEmpty()) {
        cout << "\n❌ Your cart is empty! Add items first.\n";
        return;
    }

    cart.viewCart();

    cout << "\nConfirm order? (1 = Yes, 0 = No): ";
    int confirm; cin >> confirm;

    if (confirm != 1) {
        cout << "❌ Order cancelled.\n";
        return;
    }

    Order newOrder(
        orderCounter++,
        user->name,
        cart.restaurantName,
        cart.items,
        cart.getTotal()
    );

    allOrders.push_back(newOrder);
    cout << "\n🎉 Order placed successfully!\n";
    newOrder.display();

    cart.clear();
}

void viewOrderHistory(User* user) {
    cout << "\n📋 Your Order History\n";
    cout << string(40, '=') << "\n";

    bool found = false;
    for (auto& order : allOrders) {
        if (order.customerName == user->name) {
            order.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No orders yet.\n";
    }
}

void orderFromRestaurant(User* user, Cart& cart) {
    browseRestaurants();

    cout << "\nEnter Restaurant ID to order from (0 to cancel): ";
    int restId; cin >> restId;
    if (restId == 0) return;

    Restaurant* selectedRest = nullptr;
    for (auto& r : restaurants) {
        if (r.id == restId) {
            selectedRest = &r;
            break;
        }
    }

    if (!selectedRest) {
        cout << "❌ Invalid restaurant ID.\n";
        return;
    }

    selectedRest->displayMenu();

    cout << "\nEnter Item ID to add (0 to stop): ";
    int itemId;

    while (true) {
        cin >> itemId;
        if (itemId == 0) break;

        bool found = false;
        for (auto& item : selectedRest->menu) {
            if (item.id == itemId) {
                cout << "Enter quantity: ";
                int qty; cin >> qty;
                if (qty <= 0) {
                    cout << "❌ Invalid quantity.\n";
                } else {
                    cart.addItem(item, qty, selectedRest->id, selectedRest->name);
                }
                found = true;
                break;
            }
        }

        if (!found) cout << "❌ Item not found.\n";
        cout << "Enter next Item ID (0 to stop): ";
    }
}

// ============================================================
//  ADMIN FUNCTIONS
// ============================================================
void viewAllOrders() {
    if (allOrders.empty()) {
        cout << "\n📋 No orders placed yet.\n";
        return;
    }

    cout << "\n📋 All Orders\n";
    cout << string(40, '=') << "\n";
    for (auto& order : allOrders) {
        order.display();
    }
}

void viewAllRestaurants() {
    cout << "\n🏪 All Restaurants & Menus\n";
    for (auto& r : restaurants) {
        r.displayMenu();
    }
}

void addMenuItemAdmin() {
    browseRestaurants();
    cout << "\nEnter Restaurant ID: ";
    int restId; cin >> restId;

    for (auto& r : restaurants) {
        if (r.id == restId) {
            string name, desc;
            double price;
            int newId = r.menu.size() + 1;

            cout << "Item Name: ";    cin >> ws; getline(cin, name);
            cout << "Description: "; getline(cin, desc);
            cout << "Price (Rs.): "; cin >> price;

            r.addItem(MenuItem(newId, name, desc, price));
            cout << "✅ Item added to " << r.name << "\n";
            return;
        }
    }
    cout << "❌ Restaurant not found.\n";
}

void removeMenuItemAdmin() {
    browseRestaurants();
    cout << "\nEnter Restaurant ID: ";
    int restId; cin >> restId;

    for (auto& r : restaurants) {
        if (r.id == restId) {
            r.displayMenu();
            cout << "Enter Item ID to remove: ";
            int itemId; cin >> itemId;

            for (auto it = r.menu.begin(); it != r.menu.end(); ++it) {
                if (it->id == itemId) {
                    cout << "✅ Removed: " << it->name << "\n";
                    r.menu.erase(it);
                    return;
                }
            }
            cout << "❌ Item not found.\n";
            return;
        }
    }
    cout << "❌ Restaurant not found.\n";
}

// ============================================================
//  DASHBOARDS
// ============================================================
void customerDashboard(User* user, Cart& cart) {
    int choice;

    do {
        cout << "\n===== 👤 Welcome, " << user->name << " =====\n";
        cout << "1. 🏪 Browse & Order Food\n";
        cout << "2. 🛒 View Cart\n";
        cout << "3. ✅ Place Order\n";
        cout << "4. 📋 Order History\n";
        cout << "5. 🗑️  Clear Cart\n";
        cout << "0. 🚪 Logout\n";
        cout << "Choice: "; cin >> choice;

        switch (choice) {
            case 1: orderFromRestaurant(user, cart); break;
            case 2: cart.viewCart();                 break;
            case 3: placeOrder(user, cart);          break;
            case 4: viewOrderHistory(user);          break;
            case 5: cart.clear();                    break;
            case 0: cout << "👋 Logged out.\n";      break;
            default: cout << "❌ Invalid choice.\n"; break;
        }

    } while (choice != 0);
}

void adminPanel() {
    int choice;

    do {
        cout << "\n===== 🔧 Admin Panel =====\n";
        cout << "1. 📋 View All Orders\n";
        cout << "2. 🏪 View All Restaurants & Menus\n";
        cout << "3. ➕ Add Item to Restaurant\n";
        cout << "4. ❌ Remove Item from Restaurant\n";
        cout << "0. 🚪 Logout\n";
        cout << "Choice: "; cin >> choice;

        switch (choice) {
            case 1: viewAllOrders();        break;
            case 2: viewAllRestaurants();   break;
            case 3: addMenuItemAdmin();     break;
            case 4: removeMenuItemAdmin();  break;
            case 0: cout << "👋 Logged out.\n"; break;
            default: cout << "❌ Invalid choice.\n"; break;
        }

    } while (choice != 0);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    loadRestaurants();

    // Pre-load admin account
    users.push_back(User("Admin", "admin@food.com", "admin123", "admin"));

    int  choice;
    Cart cart;

    do {
        cout << "\n╔══════════════════════════╗\n";
        cout << "║   🍔 FoodExpress App 🍔   ║\n";
        cout << "╚══════════════════════════╝\n";
        cout << "1. 📝 Register\n";
        cout << "2. 🔐 Login\n";
        cout << "0. ❌ Exit\n";
        cout << "Choice: "; cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            User* loggedIn = loginUser();
            if (loggedIn != nullptr) {
                if (loggedIn->role == "admin") {
                    adminPanel();
                } else {
                    customerDashboard(loggedIn, cart);
                }
            }
        }

    } while (choice != 0);

    cout << "\n👋 Thanks for using FoodExpress! Goodbye.\n";
    return 0;
}
