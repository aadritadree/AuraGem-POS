#include <stdio.h>
int main()
{
    // Maximum Customer/Product array capacity is 100
    int customerBills[100];
    int soldProducts[100];
    int totalCustomers = 0;
    int grandTotalRevenue = 0;
    int totalProductsSold = 0;
    // Array to track quantities sold for each item type (Index 0: Ring, 1: Earrings, 2: Pendant, 3: Bangle)
    int productQuantities[4] = {0, 0, 0, 0};
    char choice;
    printf("JEWELLERY SHOP SYSTEM\n");
    do
    {
        if (totalCustomers >= 100)
        {
            printf("\nMaximum customer limit reached for today!\n");
            break;
        }
        totalCustomers++;
        int totalBill = 0;
        int customerType;

        printf("\nCUSTOMER No.%d\n", totalCustomers);
        printf("Enter Customer Type (1 for Regular, 2 for New): ");
        scanf("%d", &customerType);

        printf("\nPRODUCT MENU\n");
        printf("1. Ring- 500 Tk\n");
        printf("2. Earrings- 300 Tk\n");
        printf("3. Pendant- 450 Tk\n");
        printf("4. Bangle- 150 Tk\n");

        int numberOfTypes;
        printf("\nHow many different types of products do you want to buy? ");
        scanf("%d", &numberOfTypes);

        for (int i = 1; i <= numberOfTypes; i++)
        {
            int productChoice;
            int quantity;

            printf("\nItem Type %d of %d\n", i, numberOfTypes);
            printf("Select Product Type (1-4): ");
            scanf("%d", &productChoice);

            printf("How many units of Product %d do you want? ", productChoice);
            scanf("%d", &quantity);

            int pricePerUnit = 0;
            if (productChoice == 1) {
                pricePerUnit = 500; // Ring
            }
            else if (productChoice == 2) {
                pricePerUnit = 300; // Earrings
            }
            else if (productChoice == 3) {
                pricePerUnit = 450; // Pendant
            }
            else if (productChoice == 4) {
                pricePerUnit = 150; // Bangle
            }
            else
            {
                printf("Invalid product choice! Skipping this item.\n");
                continue;
            }

            // Track total units sold per product type
            productQuantities[productChoice - 1] += quantity;

            int itemTotalCost = pricePerUnit * quantity;
            totalBill += itemTotalCost;

            // Track sold products for Linear Search later
            for (int k = 0; k < quantity; k++)
            {
                if (totalProductsSold < 100)
                {
                    soldProducts[totalProductsSold] = productChoice;
                    totalProductsSold++;
                }
                else
                {
                    printf("Warning: Reached max product tracking limit (100 units).\n");
                    break;
                }
            }
        }

        // Apply discount for Regular Customers (10% OFF)
        if (customerType == 1)
        {
            printf("\nRegular Customer Discount Applied: 10%% OFF\n");
            totalBill = totalBill - (totalBill * 10 / 100);
        }
        else
        {
            printf("\n Welcome New Customer!\n");
        }

        printf("Final Bill for Customer %d: %d Tk\n", totalCustomers, totalBill);
        printf("Thank you for shopping with us!\n");
        printf("Please visit our shop again!   \n");
        // Save bill to history
        customerBills[totalCustomers - 1] = totalBill;
        grandTotalRevenue += totalBill;

        printf("\nIs there another customer? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\n END OF DAY REPORT\n");
    printf("Total Customers Visited : %d\n", totalCustomers);
    printf("Total Products Sold     : %d\n", totalProductsSold);
    printf("Total Revenue Generated : %d Tk\n", grandTotalRevenue);

    // Find Maximum Units Sold
    int maxQuantity = productQuantities[0];
    for (int i = 1; i < 4; i++)
    {
        if (productQuantities[i] > maxQuantity)
        {
            maxQuantity = productQuantities[i];
        }
    }

    char *productNames[] = {"Ring", "Earrings", "Pendant", "Bangle"};

    // Display top selling product
    if (maxQuantity > 0)
    {
        printf("Highest Selling Product(s) (%d units sold):\n", maxQuantity);
        for (int i = 0; i < 4; i++)
        {
            if (productQuantities[i] == maxQuantity)
            {
                printf(" %s\n", productNames[i]);
            }
        }
    }
    else
    {
        printf("Highest Selling Product : None sold today\n");
    }

    // Sort customer bills in ascending order (Selection Sort)
    for (int i = 0; i < totalCustomers - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < totalCustomers; j++)
        {
            if (customerBills[j] < customerBills[minIndex])
            {
                minIndex = j;
            }
        }
        // Swap values
        int temp = customerBills[i];
        customerBills[i] = customerBills[minIndex];
        customerBills[minIndex] = temp;
    }

    printf("\nCustomer Bills Sorted (Ascending): ");
    for (int i = 0; i < totalCustomers; i++)
    {
        printf("%d Tk  ", customerBills[i]);
    }
    printf("\n");

    // Check if a specific product was sold today (Linear search)
    int searchKey;
    int found = 0;
    printf("\nEnter Product Number to Search if Sold Today (1-4): ");
    scanf("%d", &searchKey);

    for (int i = 0; i < totalProductsSold; i++)
    {
        if (soldProducts[i] == searchKey)
        {
            found = 1;
            break; // Stop searching once found
        }
    }

    if (found == 1)
    {
        printf("Result: YES! Product %d was sold today.\n", searchKey);
    }
    else
    {
        printf("Result: NO! Product %d was not sold today.\n", searchKey);
    }

    return 0;
}
