#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define LEN 30
#define MAXINV 20

typedef struct {
    char name[LEN];
    int price;
    int stock;
} Product;

typedef struct {
    char name[LEN];
    int qty;
} Item;

/* function prototypes */
void loadProducts(int store, Product p[]);
void saveProducts(int store, Product p[]);
void showProducts(Product p[]);
void buyProduct(Product p[], Item inv[], int *invCount, int *money, char storeName[]);
void showInventory(Item inv[], int invCount, int money);
int findItem(Item inv[], int invCount, char name[]);
void saveReceipt(char storeName[], char item[], int qty, int price, int total, int money);

int main() {
    Product p[N];
    Item inv[MAXINV];
    int invCount = 0;
    int money = 500;
    int store, choice;

    char storeName[LEN];

    while (1) {
        invCount = 0;
        money = 500;

        printf("                      ====================\n");
        printf("                      II CANTEEN STORE II\n");
        printf("                      ====================\n");
        printf("Choose store:\n");
        printf("1. Alven's Store\n");
        printf("2. Mae's Store\n");
        printf("3. Camille's Store\n");
        printf("4. Lowie's Store\n");
        printf("5. Exit\n");
        printf("Enter: ");
        scanf("%d", &store);

        if (store == 5) {
            break;
        }

        if (store == 1) strcpy(storeName, "Alven_Store");
        else if (store == 2) strcpy(storeName, "Mae_Store");
        else if (store == 3) strcpy(storeName, "Camille_Store");
        else if (store == 4) strcpy(storeName, "Lowie's_Store");
        else {
            printf("Invalid store.\n");
            continue;
        }

        loadProducts(store, p);

        while (1) {
            printf("\n1. View products\n");
            printf("2. Buy\n");
            printf("3. View inventory\n");
            printf("4. Back to store selection\n");
            printf("Enter: ");
            scanf("%d", &choice);

            if (choice == 1) {
                showProducts(p);
            } else if (choice == 2) {
                buyProduct(p, inv, &invCount, &money, storeName);
                saveProducts(store, p);
            } else if (choice == 3) {
                showInventory(inv, invCount, money);
            } else if (choice == 4) {
                saveProducts(store, p);
                break;
            } else {
                printf("Invalid choice.\n");
            }
        }
    }

    return 0;
}

void loadProducts(int store, Product p[]) {
    FILE *fp;
    int i;

    if (store == 1) fp = fopen("alven_stock.txt", "r");
    else if (store == 2) fp = fopen("mae_stock.txt", "r");
    else if (store == 3) fp = fopen("camille_stock.txt", "r");
    else fp = fopen("lowie_stock.txt", "r");

    if (fp == NULL) {
        if (store == 1) {
            strcpy(p[0].name, "Water");   p[0].price = 20; p[0].stock = 10;
            strcpy(p[1].name, "Juice");   p[1].price = 30; p[1].stock = 8;
            strcpy(p[2].name, "Chips");   p[2].price = 25; p[2].stock = 12;
            strcpy(p[3].name, "Bread");   p[3].price = 15; p[3].stock = 20;
            strcpy(p[4].name, "Candy");   p[4].price = 10; p[4].stock = 25;
        } else if (store == 2) {
            strcpy(p[0].name, "Burger");   p[0].price = 60; p[0].stock = 10;
            strcpy(p[1].name, "Fries");    p[1].price = 35; p[1].stock = 15;
            strcpy(p[2].name, "Soda");     p[2].price = 25; p[2].stock = 20;
            strcpy(p[3].name, "Hotdog");   p[3].price = 40; p[3].stock = 12;
            strcpy(p[4].name, "IceCream"); p[4].price = 45; p[4].stock = 8;
        } else if (store == 3) {
            strcpy(p[0].name, "RiceMeal"); p[0].price = 70; p[0].stock = 8;
            strcpy(p[1].name, "Pasta");    p[1].price = 55; p[1].stock = 10;
            strcpy(p[2].name, "MilkTea");  p[2].price = 45; p[2].stock = 15;
            strcpy(p[3].name, "Cookies");  p[3].price = 20; p[3].stock = 18;
            strcpy(p[4].name, "Sandwich"); p[4].price = 50; p[4].stock = 10;
        } else {
            strcpy(p[0].name, "Notebook"); p[0].price = 25; p[0].stock = 15;
            strcpy(p[1].name, "Pen");       p[1].price = 10; p[1].stock = 30;
            strcpy(p[2].name, "Pencil");    p[2].price = 8;  p[2].stock = 40;
            strcpy(p[3].name, "Eraser");    p[3].price = 5;  p[3].stock = 25;
            strcpy(p[4].name, "Ruler");     p[4].price = 12; p[4].stock = 20;
        }
        return;
    }

    for (i = 0; i < N; i++) {
        fscanf(fp, "%s %d %d", p[i].name, &p[i].price, &p[i].stock);
    }
    fclose(fp);
}

void saveProducts(int store, Product p[]) {
    FILE *fp;
    int i;

    if (store == 1) fp = fopen("alven_stock.txt", "w");
    else if (store == 2) fp = fopen("mae_stock.txt", "w");
    else if (store == 3) fp = fopen("camille_stock.txt", "w");
    else fp = fopen("lowie_stock.txt", "w");

    if (fp == NULL) return;

    for (i = 0; i < N; i++) {
        fprintf(fp, "%s %d %d\n", p[i].name, p[i].price, p[i].stock);
    }
    fclose(fp);
}

void showProducts(Product p[]) {
    int i;
    printf("\nAVAILABLE PRODUCTS:\n");
    for (i = 0; i < N; i++) {
        printf("%d. %s - Price: %d - Stock: %d\n", i + 1, p[i].name, p[i].price, p[i].stock);
    }
}

void buyProduct(Product p[], Item inv[], int *invCount, int *money, char storeName[]) {
    int choice, qty, total, index, i;
    char print;

    showProducts(p);

    printf("Choose product number: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > N) {
        printf("Invalid product.\n");
        return;
    }

    index = choice - 1;

    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    if (qty > p[index].stock) {
        printf("Not enough stock.\n");
        return;
    }

    total = p[index].price * qty;

    if (total > *money) {
        printf("Not enough money.\n");
        return;
    }

    p[index].stock -= qty;
    *money -= total;

    i = findItem(inv, *invCount, p[index].name);
    if (i == -1) {
        if (*invCount < MAXINV) {
            strcpy(inv[*invCount].name, p[index].name);
            inv[*invCount].qty = qty;
            (*invCount)++;
        } else {
            printf("Inventory full.\n");
        }
    } else {
        inv[i].qty += qty;
    }

    printf("Bought %d %s.\n", qty, p[index].name);
    printf("Remaining balance: %d\n", *money);

    printf("Print receipt? (Y/N): ");
    scanf(" %c", &print);

    if (print == 'Y' || print == 'y') {
        saveReceipt(storeName, p[index].name, qty, p[index].price, total, *money);
    }
}

int findItem(Item inv[], int invCount, char name[]) {
    int i;
    for (i = 0; i < invCount; i++) {
        if (strcmp(inv[i].name, name) == 0) return i;
    }
    return -1;
}

void showInventory(Item inv[], int invCount, int money) {
    int i;
    printf("\nYOUR INVENTORY:\n");
    for (i = 0; i < invCount; i++) {
        printf("%s - Qty: %d\n", inv[i].name, inv[i].qty);
    }
    printf("Remaining balance: %d\n", money);
}

void saveReceipt(char storeName[], char item[], int qty, int price, int total, int money) {
    FILE *fp = fopen("receipt.txt", "a");
    if (fp == NULL) return;

    fprintf(fp, "STORE: %s\n", storeName);
    fprintf(fp, "ITEM: %s\n", item);
    fprintf(fp, "QTY: %d\n", qty);
    fprintf(fp, "PRICE: %d\n", price);
    fprintf(fp, "TOTAL: %d\n", total);
    fprintf(fp, "BALANCE: %d\n", money);
    fprintf(fp, "----------------------\n");

    fclose(fp);
}
