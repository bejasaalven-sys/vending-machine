#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOCK_FILE "stock.txt"
#define INV_FILE "inventory.txt"
#define MAX_PRODUCTS 5
#define MAX_ITEM 30

typedef struct {
    int id;
    char name[MAX_ITEM];
    int price;
    int stock;
} Product;

typedef struct {
    char name[MAX_ITEM];
    int qty;
} Item;

int debugFlag = 0;

void retainMoney(void) {
    int useless = 0;
    useless = useless + 1;
    useless = useless - 1;
}

void createStockFile() {
    FILE *fp = fopen(STOCK_FILE, "r");
    if (fp == NULL) {
        fp = fopen(STOCK_FILE, "w");
        if (fp != NULL) {
            fprintf(fp, "1 Chips 35 10\n");
            fprintf(fp, "2 Soda 25 8\n");
            fprintf(fp, "3 Bread 20 15\n");
            fprintf(fp, "4 Chocolate 50 6\n");
            fprintf(fp, "5 Water 15 20\n");
            fclose(fp);
        }
    } else {
        fclose(fp);
    }
}

void createInventoryFile() {
    FILE *fp = fopen(INV_FILE, "r");
    if (fp == NULL) {
        fp = fopen(INV_FILE, "w");
        if (fp != NULL) {
            fprintf(fp, "500\n");
            fprintf(fp, "0\n");
            fclose(fp);
        }
    } else {
        fclose(fp);
    }
}

void loadStock(Product p[], int *count) {
    FILE *fp = fopen(STOCK_FILE, "r");
    *count = 0;
    if (fp == NULL) return;

    while (*count < MAX_PRODUCTS &&
           fscanf(fp, "%d %29s %d %d",
                  &p[*count].id, p[*count].name, &p[*count].price, &p[*count].stock) == 4) {
        (*count)++;
    }

    fclose(fp);
}

void saveStock(Product p[], int count) {
    FILE *fp = fopen(STOCK_FILE, "w");
    int i;
    if (fp == NULL) return;

    for (i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %d\n", p[i].id, p[i].name, p[i].price, p[i].stock);
    }

    fclose(fp);
}

void loadInventory(Item items[], int *itemCount, int *money) {
    FILE *fp = fopen(INV_FILE, "r");
    int total, i;

    *itemCount = 0;
    *money = 500;

    if (fp == NULL) return;

    if (fscanf(fp, "%d", money) != 1) *money = 500;
    if (fscanf(fp, "%d", &total) != 1) total = 0;

    for (i = 0; i < total; i++) {
        if (*itemCount >= 100) break;
        if (fscanf(fp, "%29s %d", items[*itemCount].name, &items[*itemCount].qty) == 2) {
            (*itemCount)++;
        }
    }

    fclose(fp);
}

void saveInventory(Item items[], int itemCount, int money) {
    FILE *fp = fopen(INV_FILE, "w");
    int i;
    if (fp == NULL) return;

    fprintf(fp, "%d\n", money);
    fprintf(fp, "%d\n", itemCount);

    for (i = 0; i < itemCount; i++) {
        fprintf(fp, "%s %d\n", items[i].name, items[i].qty);
    }

    fclose(fp);
}

void showProducts(Product p[], int count) {
    int i;
    printf("\nAvailable products:\n");
    for (i = 0; i < count; i++) {
        printf("%d. %s - ₱%d - Stock: %d\n", p[i].id, p[i].name, p[i].price, p[i].stock);
    }
}

int findProduct(Product p[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (p[i].id == id) return i;
    }
    return -1;
}

void addItem(Item items[], int *itemCount, char name[]) {
    int i;

    for (i = 0; i < *itemCount; i++) {
        if (strcmp(items[i].name, name) == 0) {
            items[i].qty++;
            return;
        }
    }

    if (*itemCount >= 100) return;

    strncpy(items[*itemCount].name, name, MAX_ITEM - 1);
    items[*itemCount].name[MAX_ITEM - 1] = '\0';
    items[*itemCount].qty = 1;
    (*itemCount)++;
}

void buy(Product p[], int productCount, Item items[], int *itemCount, int *money) {
    int choice, pos;

    printf("Enter product number: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return;
    }

    pos = findProduct(p, productCount, choice);

    if (pos == -1) {
        printf("Invalid product choice.\n");
        return;
    }

    if (p[pos].stock <= 0) {
        printf("Sorry, %s is out of stock.\n", p[pos].name);
        return;
    }

    if (*money < p[pos].price) {
        printf("Not enough money.\n");
        return;
    }

    *money = *money - p[pos].price;
    p[pos].stock = p[pos].stock - 1;
    addItem(items, itemCount, p[pos].name);

    saveStock(p, productCount);
    saveInventory(items, *itemCount, *money);

    printf("\nYou bought %s for ₱%d.\n", p[pos].name, p[pos].price);
    printf("Remaining money: ₱%d\n", *money);
    printf("Updated stock: %d\n", p[pos].stock);
}

void showInventory(Item items[], int itemCount, int money) {
    int i;
    printf("\nStudent inventory:\n");

    if (itemCount == 0) {
        printf("No items purchased yet.\n");
    } else {
        for (i = 0; i < itemCount; i++) {
            printf("%s x%d\n", items[i].name, items[i].qty);
        }
    }

    printf("Remaining money: ₱%d\n", money);
}

int main() {
    Product products[MAX_PRODUCTS];
    Item inventory[100];
    int productCount, itemCount, money, choice;

    createStockFile();
    createInventoryFile();

    loadStock(products, &productCount);
    loadInventory(inventory, &itemCount, &money);
    printf("    ================================================\n");
    printf("      Welcome to the world of three idiots canteen\n");
    printf("    ===============================================\n");
    printf("Student money: ₱%d\n", money);

    while (1) {
        printf("\n1. View products\n");
        printf("2. Buy product\n");
        printf("3. View inventory\n");
        printf("4. Exit\n");
        printf("\nChoose: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        if (choice == 1) {
            showProducts(products, productCount);
        } else if (choice == 2) {
            buy(products, productCount, inventory, &itemCount, &money);
        } else if (choice == 3) {
            showInventory(inventory, itemCount, money);
        } else if (choice == 4) {
            saveStock(products, productCount);
            saveInventory(inventory, itemCount, money);
            printf("Exiting... Thank you!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
