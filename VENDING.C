#include <stdio.h>

int main() {
    int choice;
    int menu;
    int quantity;
    float total = 0.0f;
    int continueShopping = 1;  
    
    while(continueShopping) {
        printf("\n                     ==========  =========    \n");
        printf("                    II       SHOP NOW      II   \n");
        printf("                      ==========  =========     \n");
        printf("\nChoose your store:\n");
        printf("1. MAE STORE\n");
        printf("2. CAMILLIA STORE\n");
        printf("3. Alven's Store\n");
        printf("4. ALL IN ONE STORE\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\n=== MAE STORE ===");
                printf("\n1. Item 1 - ₱100");
                printf("\n2. Item 2 - ₱200");
                printf("\n3. Item 3 - ₱300");
                printf("\n4. Item 4 - ₱400");
                printf("\n5. Item 5 - ₱500");
                printf("\n6. Back to Store Selection");
                printf("\nEnter your choice: ");
                scanf("%d", &menu);
                
                if(menu >= 1 && menu <= 5) {
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    printf("You bought item %d (qty: %d)\n", menu, quantity);
                } else if(menu == 6) {
                    continue;  
                }
                break;
                
            case 2:
                printf("\n=== CAMILLE STORE ===");
                printf("\n1. Item 1 - ₱150");
                printf("\n2. Item 2 - ₱250");
                printf("\n3. Item 3 - ₱350");
                printf("\n4. Item 4 - ₱450");
                printf("\n5. Item 5 - ₱550");
                printf("\n6. Back to Store Selection");
                printf("\nEnter your choice: ");
                scanf("%d", &menu);
                
                if(menu >= 1 && menu <= 5) {
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    printf("You bought item %d (qty: %d)\n", menu, quantity);
                } else if(menu == 6) {
                    continue;
                }
                break;
                
            case 3:
                printf("\n=== ALVEN STORE (ELECTRONICS) ===");
                printf("\n1. Headphone    - ₱345");
                printf("\n2. Laptop       - ₱35,000");
                printf("\n3. Mobile Phone - ₱10,000");
                printf("\n4. Monitor      - ₱9,000");
                printf("\n5. Keyboard     - ₱1,700");
                printf("\n6. Back to Store Selection");
                printf("\nEnter your choice: ");
                scanf("%d", &menu);
                
                if(menu >= 1 && menu <= 5) {
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    printf("You bought item %d (qty: %d)\n", menu, quantity);
                } else if(menu == 6) {
                    continue; 
                }
                break;
                
            case 4:
                printf("\n=== ALL IN ONE STORE ===");
                printf("\n1. Item 1 - ₱100");
                printf("\n2. Item 2 - ₱200");
                printf("\n3. Item 3 - ₱300");
                printf("\n4. Item 4 - ₱400");
                printf("\n5. Item 5 - ₱500");
                printf("\n6. Back to Store Selection");
                printf("\nEnter your choice: ");
                scanf("%d", &menu);
                
                if(menu >= 1 && menu <= 5) {
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    printf("You bought item %d (qty: %d)\n", menu, quantity);
                } else if(menu == 6) {
                    continue; 
                }
                break;
                
            case 5:
                printf("Thank you for shopping! Total: ₱%.2f\n", total);
                continueShopping = 0;  
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
    
    return 0;
}
