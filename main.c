#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ============================================================
//  CONSTANTS
// ============================================================
#define MAX_USERS        50
#define MAX_RESTAURANTS  10
#define MAX_MENU_ITEMS   10
#define MAX_CART_ITEMS   20
#define MAX_ORDERS       100
#define MAX_ORDER_ITEMS  20

// ============================================================
//  STRUCTS
// ============================================================

typedef struct {
    int    id;
    char   name[50];
    char   description[100];
    double price;
} MenuItem;

typedef struct {
    int      id;
    char     name[50];
    char     cuisine[30];
    MenuItem menu[MAX_MENU_ITEMS];
    int      menuCount;
} Restaurant;

typedef struct {
    char name[50];
    char email[50];
    char password[30];
    char role[10];
} User;

typedef struct {
    MenuItem item;
    int      quantity;
} CartItem;

typedef struct {
    CartItem items[MAX_CART_ITEMS];
    int      itemCount;
    int      restaurantId;
    char     restaurantName[50];
} Cart;

typedef struct {
    int      orderId;
    char     customerName[50];
    char     restaurantName[50];
    CartItem items[MAX_ORDER_ITEMS];
    int      itemCount;
    double   total;
    char     status[20];
} Order;

// ============================================================
//  GLOBAL DATA
// ============================================================
User       users[MAX_USERS];
int        userCount      = 0;

Restaurant restaurants[MAX_RESTAURANTS];
int        restCount      = 0;

Order      allOrders[MAX_ORDERS];
int        orderCount     = 0;
int        orderIdCounter = 1;

Cart       cart;

// ============================================================
//  HELPER FUNCTIONS
// ============================================================
void printLine() {
    printf("----------------------------------------\n");
}

// ============================================================
//  LOAD RESTAURANTS
// ============================================================
void addMenuItem(int restIndex, int id, char* name, char* desc, double price) {
    int m = restaurants[restIndex].menuCount;
    restaurants[restIndex].menu[m].id = id;
    strcpy(restaurants[restIndex].menu[m].name,        name);
    strcpy(restaurants[restIndex].menu[m].description, desc);
    restaurants[restIndex].menu[m].price = price;
    restaurants[restIndex].menuCount++;
}

void loadRestaurants() {
    // 1. Pizza Palace
    restaurants[0].id = 1;
    strcpy(restaurants[0].name,    "Pizza Palace");
    strcpy(restaurants[0].cuisine, "Italian");
    restaurants[0].menuCount = 0;
    addMenuItem(0, 1, "Margherita Pizza",  "Classic tomato & cheese",    850);
    addMenuItem(0, 2, "Pepperoni Pizza",   "Loaded with pepperoni",      1100);
    addMenuItem(0, 3, "Garlic Bread",      "Toasted with garlic butter", 350);

    // 2. Burger Barn
    restaurants[1].id = 2;
    strcpy(restaurants[1].name,    "Burger Barn");
    strcpy(restaurants[1].cuisine, "American");
    restaurants[1].menuCount = 0;
    addMenuItem(1, 1, "Classic Burger", "Beef patty with lettuce",   650);
    addMenuItem(1, 2, "Cheese Burger",  "Double cheese beef burger", 750);
    addMenuItem(1, 3, "Crispy Fries",   "Golden salted fries",       300);

    // 3. Sushi Station
    restaurants[2].id = 3;
    strcpy(restaurants[2].name,    "Sushi Station");
    strcpy(restaurants[2].cuisine, "Japanese");
    restaurants[2].menuCount = 0;
    addMenuItem(2, 1, "Salmon Roll", "Fresh salmon with avocado", 1200);
    addMenuItem(2, 2, "Tuna Nigiri", "Premium tuna on rice",      1000);
    addMenuItem(2, 3, "Miso Soup",   "Traditional Japanese soup",  400);

    // 4. Karahi King
    restaurants[3].id = 4;
    strcpy(restaurants[3].name,    "Karahi King");
    strcpy(restaurants[3].cuisine, "Pakistani");
    restaurants[3].menuCount = 0;
    addMenuItem(3, 1, "Chicken Karahi", "Spicy tomato-based karahi", 1500);
    addMenuItem(3, 2, "Mutton Karahi",  "Tender mutton karahi",      2200);
    addMenuItem(3, 3, "Naan",           "Fresh tandoor naan",           50);

    // 5. Taco Town
    restaurants[4].id = 5;
    strcpy(restaurants[4].name,    "Taco Town");
    strcpy(restaurants[4].cuisine, "Mexican");
    restaurants[4].menuCount = 0;
    addMenuItem(4, 1, "Beef Taco",       "Spiced beef in crispy shell", 700);
    addMenuItem(4, 2, "Chicken Burrito", "Grilled chicken wrap",        850);
    addMenuItem(4, 3, "Nachos",          "Chips with salsa & cheese",   600);

    // 6. Noodle Nest
    restaurants[5].id = 6;
    strcpy(restaurants[5].name,    "Noodle Nest");
    strcpy(restaurants[5].cuisine, "Chinese");
    restaurants[5].menuCount = 0;
    addMenuItem(5, 1, "Chow Mein",        "Stir-fried noodles with veggies", 650);
    addMenuItem(5, 2, "Kung Pao Chicken", "Spicy peanut chicken",            900);
    addMenuItem(5, 3, "Spring Rolls",     "Crispy veggie rolls",             400);

    // 7. BBQ Brothers
    restaurants[6].id = 7;
    strcpy(restaurants[6].name,    "BBQ Brothers");
    strcpy(restaurants[6].cuisine, "BBQ");
    restaurants[6].menuCount = 0;
    addMenuItem(6, 1, "Chicken Tikka", "Marinated grilled chicken",  1100);
    addMenuItem(6, 2, "Seekh Kebab",   "Spiced minced meat skewers",  950);
    addMenuItem(6, 3, "BBQ Platter",   "Mixed grill for two",        2500);

    // 8. Wrap World
    restaurants[7].id = 8;
    strcpy(restaurants[7].name,    "Wrap World");
    strcpy(restaurants[7].cuisine, "Fusion");
    restaurants[7].menuCount = 0;
    addMenuItem(7, 1, "Zinger Wrap", "Crispy chicken with coleslaw",   700);
    addMenuItem(7, 2, "Shawarma",    "Grilled meat with garlic sauce",  600);
    addMenuItem(7, 3, "Club Wrap",   "Turkey, bacon & veggies",         800);

    // 9. Biryani Bay
    restaurants[8].id = 9;
    strcpy(restaurants[8].name,    "Biryani Bay");
    strcpy(restaurants[8].cuisine, "Pakistani");
    restaurants[8].menuCount = 0;
    addMenuItem(8, 1, "Chicken Biryani", "Aromatic spiced rice with chicken", 550);
    addMenuItem(8, 2, "Mutton Biryani",  "Slow-cooked mutton biryani",        750);
    addMenuItem(8, 3, "Raita",           "Yogurt side dish",                  100);

    // 10. Dessert Den
    restaurants[9].id = 10;
    strcpy(restaurants[9].name,    "Dessert Den");
    strcpy(restaurants[9].cuisine, "Desserts");
    restaurants[9].menuCount = 0;
    addMenuItem(9, 1, "Chocolate Lava Cake", "Warm cake with molten center",       650);
    addMenuItem(9, 2, "Mango Kulfi",         "Traditional Pakistani ice cream",    350);
    addMenuItem(9, 3, "Gulab Jamun",         "Soft syrup-soaked sweets",           250);

    restCount = 10;
}

// ============================================================
//  USER FUNCTIONS
// ============================================================
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("System full. Cannot register more users.\n");
        return;
    }

    User newUser;
    printf("\n--- Register ---\n");
    printf("Name     : "); scanf(" %[^\n]", newUser.name);
    printf("Email    : "); scanf(" %[^\n]", newUser.email);
    printf("Password : "); scanf(" %[^\n]", newUser.password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, newUser.email) == 0) {
            printf("Email already registered.\n");
            return;
        }
    }

    strcpy(newUser.role, "customer");
    users[userCount++] = newUser;
    printf("Registered successfully! You can now login.\n");
}

int loginUser() {
    char email[50], password[30];
    printf("\n--- Login ---\n");
    printf("Email    : "); scanf(" %[^\n]", email);
    printf("Password : "); scanf(" %[^\n]", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email,    email)    == 0 &&
            strcmp(users[i].password, password) == 0) {
            printf("Welcome, %s!\n", users[i].name);
            return i;
        }
    }
    printf("Invalid email or password.\n");
    return -1;
}

// ============================================================
//  CART FUNCTIONS
// ============================================================
void initCart() {
    cart.itemCount    = 0;
    cart.restaurantId = -1;
    strcpy(cart.restaurantName, "");
}

void addToCart(MenuItem item, int qty, int restId, char* restName) {
    if (cart.restaurantId != -1 && cart.restaurantId != restId) {
        printf("You can only order from one restaurant at a time.\n");
        printf("Clear your cart first to switch restaurants.\n");
        return;
    }

    cart.restaurantId = restId;
    strcpy(cart.restaurantName, restName);

    for (int i = 0; i < cart.itemCount; i++) {
        if (cart.items[i].item.id == item.id) {
            cart.items[i].quantity += qty;
            printf("Updated quantity for %s\n", item.name);
            return;
        }
    }

    if (cart.itemCount >= MAX_CART_ITEMS) {
        printf("Cart is full.\n");
        return;
    }

    cart.items[cart.itemCount].item     = item;
    cart.items[cart.itemCount].quantity = qty;
    cart.itemCount++;
    printf("%s added to cart!\n", item.name);
}

void viewCart() {
    if (cart.itemCount == 0) {
        printf("\nYour cart is empty.\n");
        return;
    }

    printf("\n--- Your Cart (%s) ---\n", cart.restaurantName);
    printLine();

    double total = 0;
    for (int i = 0; i < cart.itemCount; i++) {
        double sub = cart.items[i].item.price * cart.items[i].quantity;
        printf("  %-25s x%d  =  Rs.%.0f\n",
               cart.items[i].item.name,
               cart.items[i].quantity,
               sub);
        total += sub;
    }

    printLine();
    printf("  Total : Rs.%.0f\n", total);
}

double getCartTotal() {
    double total = 0;
    for (int i = 0; i < cart.itemCount; i++) {
        total += cart.items[i].item.price * cart.items[i].quantity;
    }
    return total;
}

void clearCart() {
    initCart();
    printf("Cart cleared.\n");
}

// ============================================================
//  RESTAURANT BROWSE & MENU
// ============================================================
void browseRestaurants() {
    printf("\n========== RESTAURANTS ==========\n");
    for (int i = 0; i < restCount; i++) {
        printf("  [%2d] %-20s  (%s)\n",
               restaurants[i].id,
               restaurants[i].name,
               restaurants[i].cuisine);
    }
    printLine();
}

void displayMenu(int restIndex) {
    printf("\n--- %s Menu (%s) ---\n",
           restaurants[restIndex].name,
           restaurants[restIndex].cuisine);
    printLine();
    for (int i = 0; i < restaurants[restIndex].menuCount; i++) {
        printf("  [%d] %-25s  Rs.%.0f\n      %s\n",
               restaurants[restIndex].menu[i].id,
               restaurants[restIndex].menu[i].name,
               restaurants[restIndex].menu[i].price,
               restaurants[restIndex].menu[i].description);
    }
    printLine();
}

void orderFromRestaurant(int userIndex) {
    browseRestaurants();

    printf("Enter Restaurant ID (0 to cancel): ");
    int restId; scanf("%d", &restId);
    if (restId == 0) return;

    int restIndex = -1;
    for (int i = 0; i < restCount; i++) {
        if (restaurants[i].id == restId) {
            restIndex = i;
            break;
        }
    }

    if (restIndex == -1) {
        printf("Invalid restaurant ID.\n");
        return;
    }

    displayMenu(restIndex);

    int itemId;
    printf("Enter Item ID to add (0 to stop): ");

    while (1) {
        scanf("%d", &itemId);
        if (itemId == 0) break;

        int found = 0;
        for (int i = 0; i < restaurants[restIndex].menuCount; i++) {
            if (restaurants[restIndex].menu[i].id == itemId) {
                int qty;
                printf("Enter quantity: ");
                scanf("%d", &qty);
                if (qty <= 0) {
                    printf("Invalid quantity.\n");
                } else {
                    addToCart(restaurants[restIndex].menu[i],
                              qty,
                              restaurants[restIndex].id,
                              restaurants[restIndex].name);
                }
                found = 1;
                break;
            }
        }

        if (!found) printf("Item not found.\n");
        printf("Enter next Item ID (0 to stop): ");
    }
}

// ============================================================
//  ORDER FUNCTIONS
// ============================================================
void placeOrder(int userIndex) {
    if (cart.itemCount == 0) {
        printf("\nYour cart is empty! Add items first.\n");
        return;
    }

    viewCart();

    printf("\nConfirm order? (1 = Yes, 0 = No): ");
    int confirm; scanf("%d", &confirm);

    if (confirm != 1) {
        printf("Order cancelled.\n");
        return;
    }

    if (orderCount >= MAX_ORDERS) {
        printf("Order limit reached.\n");
        return;
    }

    Order newOrder;
    newOrder.orderId   = orderIdCounter++;
    strcpy(newOrder.customerName,   users[userIndex].name);
    strcpy(newOrder.restaurantName, cart.restaurantName);
    newOrder.itemCount = cart.itemCount;
    newOrder.total     = getCartTotal();
    strcpy(newOrder.status, "Confirmed");

    for (int i = 0; i < cart.itemCount; i++) {
        newOrder.items[i] = cart.items[i];
    }

    allOrders[orderCount++] = newOrder;

    printf("\n*** Order Placed Successfully! ***\n");
    printLine();
    printf("  Order ID   : #%d\n",      newOrder.orderId);
    printf("  Restaurant : %s\n",       newOrder.restaurantName);
    printf("  Customer   : %s\n",       newOrder.customerName);
    printf("  Total      : Rs.%.0f\n",  newOrder.total);
    printf("  Status     : %s\n",       newOrder.status);
    printLine();

    clearCart();
}

void viewOrderHistory(int userIndex) {
    printf("\n--- Your Order History ---\n");
    printLine();

    int found = 0;
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(allOrders[i].customerName, users[userIndex].name) == 0) {
            printf("  Order #%d  |  %s  |  Rs.%.0f  |  %s\n",
                   allOrders[i].orderId,
                   allOrders[i].restaurantName,
                   allOrders[i].total,
                   allOrders[i].status);
            for (int j = 0; j < allOrders[i].itemCount; j++) {
                printf("    - %-20s x%d\n",
                       allOrders[i].items[j].item.name,
                       allOrders[i].items[j].quantity);
            }
            printLine();
            found = 1;
        }
    }

    if (!found) printf("No orders yet.\n");
}

// ============================================================
//  ADMIN FUNCTIONS
// ============================================================
void viewAllOrders() {
    if (orderCount == 0) {
        printf("\nNo orders placed yet.\n");
        return;
    }

    printf("\n--- All Orders ---\n");
    for (int i = 0; i < orderCount; i++) {
        printf("\n  Order #%d\n",           allOrders[i].orderId);
        printf("  Customer   : %s\n",      allOrders[i].customerName);
        printf("  Restaurant : %s\n",      allOrders[i].restaurantName);
        printf("  Total      : Rs.%.0f\n", allOrders[i].total);
        printf("  Status     : %s\n",      allOrders[i].status);
        printLine();
    }
}

void addMenuItemAdmin() {
    browseRestaurants();
    printf("Enter Restaurant ID: ");
    int restId; scanf("%d", &restId);

    for (int i = 0; i < restCount; i++) {
        if (restaurants[i].id == restId) {
            int m = restaurants[i].menuCount;
            if (m >= MAX_MENU_ITEMS) {
                printf("Menu is full for this restaurant.\n");
                return;
            }
            char name[50], desc[100];
            double price;
            int newId = m + 1;

            printf("Item Name   : "); scanf(" %[^\n]", name);
            printf("Description : "); scanf(" %[^\n]", desc);
            printf("Price (Rs.) : "); scanf("%lf", &price);

            addMenuItem(i, newId, name, desc, price);
            printf("Item added to %s\n", restaurants[i].name);
            return;
        }
    }
    printf("Restaurant not found.\n");
}

void removeMenuItemAdmin() {
    browseRestaurants();
    printf("Enter Restaurant ID: ");
    int restId; scanf("%d", &restId);

    for (int i = 0; i < restCount; i++) {
        if (restaurants[i].id == restId) {
            displayMenu(i);
            printf("Enter Item ID to remove: ");
            int itemId; scanf("%d", &itemId);

            for (int j = 0; j < restaurants[i].menuCount; j++) {
                if (restaurants[i].menu[j].id == itemId) {
                    printf("Removed: %s\n", restaurants[i].menu[j].name);
                    for (int k = j; k < restaurants[i].menuCount - 1; k++) {
                        restaurants[i].menu[k] = restaurants[i].menu[k + 1];
                    }
                    restaurants[i].menuCount--;
                    return;
                }
            }
            printf("Item not found.\n");
            return;
        }
    }
    printf("Restaurant not found.\n");
}

// ============================================================
//  DASHBOARDS
// ============================================================
void customerDashboard(int userIndex) {
    int choice;

    do {
        printf("\n========== CUSTOMER MENU ==========\n");
        printf("  Welcome, %s\n", users[userIndex].name);
        printLine();
        printf("  1. Browse & Order Food\n");
        printf("  2. View Cart\n");
        printf("  3. Place Order\n");
        printf("  4. Order History\n");
        printf("  5. Clear Cart\n");
        printf("  0. Logout\n");
        printLine();
        printf("  Choice: "); scanf("%d", &choice);

        switch (choice) {
            case 1: orderFromRestaurant(userIndex); break;
            case 2: viewCart();                     break;
            case 3: placeOrder(userIndex);          break;
            case 4: viewOrderHistory(userIndex);    break;
            case 5: clearCart();                    break;
            case 0: printf("Logged out.\n");        break;
            default: printf("Invalid choice.\n");   break;
        }

    } while (choice != 0);
}

void adminPanel() {
    int choice;

    do {
        printf("\n========== ADMIN PANEL ==========\n");
        printLine();
        printf("  1. View All Orders\n");
        printf("  2. View All Restaurants & Menus\n");
        printf("  3. Add Item to Restaurant\n");
        printf("  4. Remove Item from Restaurant\n");
        printf("  0. Logout\n");
        printLine();
        printf("  Choice: "); scanf("%d", &choice);

        switch (choice) {
            case 1: viewAllOrders(); break;
            case 2:
                for (int i = 0; i < restCount; i++)
                    displayMenu(i);
                break;
            case 3: addMenuItemAdmin();    break;
            case 4: removeMenuItemAdmin(); break;
            case 0: printf("Logged out.\n"); break;
            default: printf("Invalid choice.\n"); break;
        }

    } while (choice != 0);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    loadRestaurants();
    initCart();

    // Pre-load admin account
    strcpy(users[0].name,     "Admin");
    strcpy(users[0].email,    "admin@food.com");
    strcpy(users[0].password, "admin123");
    strcpy(users[0].role,     "admin");
    userCount = 1;

    int choice;

    do {
        printf("\n====================================\n");
        printf("        FOODEXPRESS APP             \n");
        printf("====================================\n");
        printf("  1. Register\n");
        printf("  2. Login\n");
        printf("  0. Exit\n");
        printf("------------------------------------\n");
        printf("  Choice: "); scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            int index = loginUser();
            if (index != -1) {
                if (strcmp(users[index].role, "admin") == 0) {
                    adminPanel();
                } else {
                    customerDashboard(index);
                }
            }
        }

    } while (choice != 0);

    printf("\nThanks for using FoodExpress! Goodbye.\n");
    return 0;
}
