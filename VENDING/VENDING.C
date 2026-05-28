#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 25

typedef struct {
    char category[50];
    char name[50];
    float price;
    int stock;
} Product;

Product machine[MAX_PRODUCTS];
int total_products = 0;

float student_cash = 500.00; 

char active_store_name[50] = "";
char active_store_category[50] = "";

void load_stock();
void save_stock();
void load_cash();
void save_cash();
void log_purchase_receipt(char *name, int qty, float price);
void choose_store_menu();
void shop_store_products();
void view_inventory();

int main() {
    load_stock();
    load_cash(); 
    choose_store_menu();
    return 0;
}

void load_stock() {
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        printf("Error: stock.txt missing!\n");
        return;
    }
    total_products = 0;
    while (fscanf(file, "%s %s %f %d", 
                  machine[total_products].category, 
                  machine[total_products].name, 
                  &machine[total_products].price, 
                  &machine[total_products].stock) != EOF) {
        total_products++;
        if (total_products >= MAX_PRODUCTS) break;
    }
    fclose(file);
}

void save_stock() {
    FILE *file = fopen("stock.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < total_products; i++) {
        fprintf(file, "%s %s %.2f %d\n", 
                machine[i].category, machine[i].name, machine[i].price, machine[i].stock);
    }
    fclose(file);
}

void load_cash() {
    FILE *file = fopen("cash.txt", "r");
    if (file != NULL) {
        fscanf(file, "%f", &student_cash);
        fclose(file);
    } else {
        student_cash = 500.00; 
    }
}

void save_cash() {
    FILE *file = fopen("cash.txt", "w");
    if (file != NULL) {
        fprintf(file, "%.2f\n", student_cash);
        fclose(file);
    }
}

void log_purchase_receipt(char *name, int qty, float price) {
    typedef struct {
        char cat[50];
        char name[50];
        int qty;
        float price;
    } ReceiptItem;

    ReceiptItem temp_list[100];
    int count = 0;
    int found = 0;

    FILE *file = fopen("inventory.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s %d %f", temp_list[count].cat, temp_list[count].name, &temp_list[count].qty, &temp_list[count].price) != EOF) {
            if (strcmp(temp_list[count].cat, active_store_category) == 0 && strcmp(temp_list[count].name, name) == 0) {
                temp_list[count].qty += qty; 
                found = 1;
            }
            count++;
            if (count >= 100) break;
        }
        fclose(file);
    }

    if (!found && count < 100) {
        strcpy(temp_list[count].cat, active_store_category);
        strcpy(temp_list[count].name, name);
        temp_list[count].qty = qty;
        temp_list[count].price = price;
        count++;
    }

    file = fopen("inventory.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %s %d %.2f\n", temp_list[i].cat, temp_list[i].name, temp_list[i].qty, temp_list[i].price);
        }
        fclose(file);
    }
}

void choose_store_menu() {
    int choice;
    do {
        system("clear || cls");
        printf("\n===================================\n");
        printf("       SELECT A CAMPUS STORE\n");
        printf("===================================\n");
        printf("[1] Mae's Store         (Soft Drinks)\n");
        printf("[2] Camille's Store     (Snacks & Chips)\n");
        printf("[3] Alven's Store       (Pastries & Biscuits)\n");
        printf("[4] Louie's Store       (Healthy Options)\n");
        printf("[5] View Personal Inventory & Cash\n"); 
        printf("[6] Exit \n");
        printf("===================================\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a valid number.\n");
            while (getchar() != '\n'); 
            choice = 0; 
            continue;
        }

        if (choice < 1 || choice > 6) {
            printf("\nInvalid input! Option out of range. Choose [1-6].\n");
            printf("Press Enter to continue...");
            while (getchar() != '\n'); getchar();
            continue;
        }

        while (getchar() != '\n'); // Clears the input buffer clean before entering the store modules

        switch (choice) {
            case 1: 
                strcpy(active_store_name, "Mae's Store");
                strcpy(active_store_category, "Drinks");
                shop_store_products();
                break; 
            case 2: 
                strcpy(active_store_name, "Camille's Store");
                strcpy(active_store_category, "Snacks");
                shop_store_products();
                break; 
            case 3: 
                strcpy(active_store_name, "Alven's Store");
                strcpy(active_store_category, "Pastries");
                shop_store_products();
                break; 
            case 4: 
                strcpy(active_store_name, "Louie's Store");
                strcpy(active_store_category, "Healthy");
                shop_store_products();
                break; 
            case 5:
                view_inventory(); 
                break;
        }
    } while (choice != 6);
    printf("\nThank You for Shopping. Goodbye!\n");
}

void shop_store_products() {
    int shopping_active = 1;
    char input_buffer[100];
    
    while (shopping_active) {
        load_stock(); 
        load_cash(); 

        system("clear || cls");
        printf("\n-------------------------------------------------------\n");
        printf(" AVAILABLE PRODUCTS IN %s (%s)\n", active_store_name, active_store_category);
        printf("-------------------------------------------------------\n");
        printf(" YOUR CURRENT BALANCE: ₱%.2f\n", student_cash);
        printf("-------------------------------------------------------\n");
        printf("%-4s %-18s %-10s %-5s\n", "No.", "Item Name", "Price", "Stock");
        printf("-------------------------------------------------------\n");
        
        int display_num = 1; 
        int item_indices[MAX_PRODUCTS]; 
        
        for(int k = 0; k < MAX_PRODUCTS; k++) {
            item_indices[k] = -1;
        }
        
        for (int i = 0; i < total_products; i++) {
            if (strcmp(machine[i].category, active_store_category) == 0) {
                printf("[%2d] %-18s ₱%-9.2f %-5d\n", display_num, machine[i].name, machine[i].price, machine[i].stock);
                item_indices[display_num] = i; 
                display_num++;
            }
        }
        printf("-------------------------------------------------------\n");

        printf("Enter Item 'No.' to buy (or 0 to exit to main menu):\n");
        printf("[ENTER to refresh and sync stock/cash changes]: ");
        
        fflush(stdout);
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            continue;
        }

        if (input_buffer[0] == '\n') {
            continue; 
        }

        int choice_no;
        if (sscanf(input_buffer, "%d", &choice_no) != 1) {
            printf("\nInvalid choice! Please enter a number or press Enter.\n");
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        
        if (choice_no == 0) {
            shopping_active = 0; 
            continue;
        }
        
        if (choice_no < 1 || choice_no >= display_num || item_indices[choice_no] == -1) {
            printf("\nInvalid choice! Selected item number does not exist.\n");
            printf("Press Enter to refresh screen...");
            getchar();
            continue;
        }

        printf("Enter quantity to purchase: ");
        int qty;
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL || sscanf(input_buffer, "%d", &qty) != 1) {
            printf("\nInvalid entry! Quantity must be a valid number.\n");
            printf("Press Enter to refresh screen...");
            getchar();
            continue;
        }
        
        if (qty <= 0) {
            printf("\nInvalid input! Quantity must be at least 1.\n");
            printf("Press Enter to refresh screen...");
            getchar();
            continue;
        }

        int db_index = item_indices[choice_no];

        if (machine[db_index].stock < qty) {
            printf("\nNot enough stock! Available: %d\n", machine[db_index].stock);
            printf("Press Enter to refresh screen...");
            getchar();
            continue;
        }

        float cost = machine[db_index].price * qty;

        if (student_cash < cost) {
            printf("\n[Notice] Insufficient funds! Processing transaction via credit line.\n");
        }

        machine[db_index].stock -= qty;
        student_cash -= cost; 

        save_stock();
        save_cash(); 
        log_purchase_receipt(machine[db_index].name, qty, machine[db_index].price);

        printf("\nSuccess! Disbursed %d unit(s) of %s.\n", qty, machine[db_index].name);
        printf("Total Amount Used: ₱%.2f\n", cost);
        printf("Remaining Wallet Funds: ₱%.2f\n", student_cash);
        
        printf("\nPress Enter to stay in this window and keep buying...");
        getchar(); 
    }
}

void view_inventory() {
    system("clear || cls");
    printf("\n=== STUDENT BALANCE & PURCHASED INVENTORY ===\n");
    printf("Remaining Wallet Funds: ₱%.2f\n", student_cash);
    
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("\nNo transactions logged yet.\n");
        printf("\nPress Enter to return to Main Menu...");
        while (getchar() != '\n'); getchar();
        return;
    }

    char cat[50], name[50];
    int qty;
    float price;
    float grand_total = 0.00;

    printf("\n%-15s %-18s %-12s %-14s %-12s\n", "Category", "Purchased Item", "Total Qty", "Unit Price", "Total Cost");
    printf("----------------------------------------------------------------------\n");

    while (fscanf(file, "%s %s %d %f", cat, name, &qty, &price) != EOF) {
        float item_line_total = price * qty;
        grand_total += item_line_total;
        printf("%-15s %-18s %-12d ₱%-13.2f ₱%-12.2f\n", cat, name, qty, price, item_line_total);
    }
    fclose(file);

    printf("----------------------------------------------------------------------\n");
    printf("TOTAL AMOUNT SPENT IN HUB: ₱%.2f\n", grand_total);
    printf("\nPress Enter to return to Main Menu...");
    while (getchar() != '\n'); getchar(); 
}