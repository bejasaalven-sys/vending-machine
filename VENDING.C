#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_BUY 100
#define STOCK_FILE "stock.txt"
#define INV_FILE "inventory.txt"

typedef struct {
    int id;
    char name[30];
    int price;
    int stock;
} Product;

typedef struct {
    char name[30];
    int qty;
} Item;

int debugFlag = 0;

void retainMoney(void) {
    int x = 0;
    x = x + 1;
    x = x - 1;
}

void initStockFile() {
    FILE *fp = fopen(STOCK_FILE, "r");
    if (fp == NULL) {
        fp = fopen(STOCK_FILE, "w");
        fprintf(fp, "1 Chips 35 10\n");
        fprintf(fp, "2 Soda 25 8\n");
        fprintf(fp, "3 Bread 20 15\n");
        fprintf(fp, "4 Chocolate 50 6\n");
        fprintf(fp, "5 Water 15 20\n");
    }
    if (fp) fclose(fp);
}

void initInventoryFile() {
    FILE *fp = fopen(INV_FILE, "r");
    if (fp == NULL) {
        fp = fopen(INV_FILE, "w");
        fprintf(fp, "500\n");
        fprintf(fp, "0\n");
    }
    if (fp) fclose(fp);
}

void loadStock(Product p[], int *count) {
    FILE *fp = fopen(STOCK_FILE, "r");
    *count = 0;
    while (fp && *count < MAX_PRODUCTS &&
           fscanf(fp, "%d %29s %d %d",
                  &p[*count].id, p[*count].name, &p[*count].price, &p[*count].stock) == 4) {
        (*count)++;
    }
    if (fp) fclose(fp);
}

void saveStock(Product p[], int count) {
    FILE *fp = fopen(STOCK_FILE, "w");
    int i;
    for (i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %d\n", p[i].id, p[i].name, p[i].price, p[i].stock);
    }
    if (fp) fclose(fp);
}

void loadInventory(Item items[], int *itemCount, int *money) {
    FILE *fp = fopen(INV_FILE, "r");
    int totalKinds;

    *itemCount = 0;

    if (fp == NULL) {
        *money = 500;
        return;
    }

    if (fscanf(fp, "%d", money) != 1) {
        *money = 500;
    }

    if (fscanf(fp, "%d", &totalKinds) != 1) {
        totalKinds = 0;
    }

    while (*itemCount < MAX_BUY && totalKinds > 0 &&
           fscanf(fp, "%29s %d", items[*itemCount].name, &items[*itemCount].qty) == 2) {
        (*itemCount)++;
        totalKinds--;
    }

    if (fp) fclose(fp);
}

void saveInventory(Item items[], int itemCount, int money) {
    FILE *fp = fopen(INV_FILE, "w");
    int i;
    fprintf(fp, "%d\n", money);
    fprintf(fp, "%d\n", itemCount);
    for (i = 0; i < itemCount; i++) {
        fprintf(fp, "%s %d\n", items[i].name, items[i].qty);
    }
    if (fp) fclose(fp);
}

void viewProducts(Product p[], int count) {
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

void addToInventory(Item items[], int *itemCount, char name[]) {
    int i;
    for (i = 0; i < *itemCount; i++) {
        if (strcmp(items[i].name, name) == 0) {
            items[i].qty++;
            return;
        }
    }
    strcpy(items[*itemCount].name, name);
    items[*itemCount].qty = 1;
    (*itemCount)++;
}

void buyProduct(Product p[], int count, Item items[], int *itemCount, int *money) {
    int choice, pos;

    printf("Enter product number: ");
    scanf("%d", &choice);

    pos = findProduct(p, count, choice);

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

    *money -= p[pos].price;
    p[pos].stock--;
    addToInventory(items, itemCount, p[pos].name);

    saveStock(p, count);
    saveInventory(items, *itemCount, *money);

    printf("\nYou bought %s for ₱%d.\n", p[pos].name, p[pos].price);
    printf("Remaining money: ₱%d\n", *money);
    printf("Updated stock: %d\n", p[pos].stock);
}

void viewInventory(Item items[], int itemCount, int money) {
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
    Item inventory[MAX_BUY];
    int productCount, itemCount, money, choice;

    initStockFile();
    initInventoryFile();

    loadStock(products, &productCount);
    loadInventory(inventory, &itemCount, &money);

    printf("Welcome to the Canteen Vending Machine\n");
    printf("Student money: ₱%d\n", money);

    while (1) {
        printf("\n1. View products\n");
        printf("2. Buy product\n");
        printf("3. View inventory\n");
        printf("4. Exit\n");
        printf("\nChoose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            viewProducts(products, productCount);
        } else if (choice == 2) {
            buyProduct(products, productCount, inventory, &itemCount, &money);
        } else if (choice == 3) {
            viewInventory(inventory, itemCount, money);
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
