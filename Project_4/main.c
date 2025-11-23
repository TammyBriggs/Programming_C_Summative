#include <stdio.h>
#include "math_utils.h"

int main() {
    float *dataset = NULL;
    int size = 0;
    int choice;
    char filename[50];

    // Array of Function Pointers for operations 1-4 (Sum, Avg, Max, Min)
    // This satisfies the "Dynamic Function Dispatch" requirement
    MathOperation operations[] = {op_sum, op_average, op_max, op_min};
    const char *op_names[] = {"Sum", "Average", "Max", "Min"};

    while (1) {
        printf("\n=== DYNAMIC MATH ENGINE ===\n");
        printf("1. Add Number to Dataset\n");
        printf("2. View Dataset\n");
        printf("3. Compute Sum\n");
        printf("4. Compute Average\n");
        printf("5. Find Max\n");
        printf("6. Find Min\n");
        printf("7. Sort Data (Ascending)\n");
        printf("8. Sort Data (Descending)\n");
        printf("9. Search for Value\n");       // NEW
        printf("10. Delete Value by Index\n"); // NEW
        printf("11. Modify Value by Index\n"); // NEW
        printf("12. Save to File\n");
        printf("13. Load from File\n");
        printf("14. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Handle non-numeric input to prevent infinite loops
            while(getchar() != '\n'); 
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        // Handle Adding Data (Option 1)
        if (choice == 1) {
            float val;
            printf("Enter value: ");
            scanf("%f", &val);
            
            // Dynamic Memory Allocation Logic
            float *temp = (float *)realloc(dataset, (size + 1) * sizeof(float));
            if (temp == NULL) {
                printf("Memory allocation failed!\n");
            } else {
                dataset = temp;
                dataset[size] = val;
                size++;
                printf("Value added.\n");
            }
            continue;
        }

        // Handle View (Option 2)
        if (choice == 2) {
            print_data(dataset, size);
            continue;
        }

        // Handle Math Operations (3, 4, 5, 6) using Function Pointers
        if (choice >= 3 && choice <= 6) {
            if (size == 0) {
                printf("Dataset is empty.\n");
                continue;
            }
            // Adjust index: choice 3 maps to index 0, etc.
            int op_index = choice - 3;
            
            // EXECUTE FUNCTION VIA POINTER
            float result = operations[op_index](dataset, size);
            
            printf("Result (%s): %.2f\n", op_names[op_index], result);
            continue;
        }

        // Handle Sorting (Option 7 & 8)
        if (choice == 7 || choice == 8) {
            if (size == 0) {
                printf("Dataset is empty.\n");
                continue;
            }
            sort_data(dataset, size, (choice == 7)); // 1 for Ascending, 0 for Descending
            continue;
        }

        // Handle Search (Option 9)
        if (choice == 9) {
            if (size == 0) { printf("Dataset is empty.\n"); continue; }
            float target;
            printf("Enter value to search: ");
            scanf("%f", &target);
            int idx = search_value(dataset, size, target);
            if (idx != -1) printf("Value %.2f found at index %d.\n", target, idx);
            else printf("Value %.2f not found in dataset.\n", target);
            continue;
        }

        // Handle Delete (Option 10)
        if (choice == 10) {
            if (size == 0) { printf("Dataset is empty.\n"); continue; }
            int idx;
            printf("Enter index to delete (0 to %d): ", size - 1);
            scanf("%d", &idx);
            delete_element(&dataset, &size, idx);
            continue;
        }

        // Handle Modify (Option 11)
        if (choice == 11) {
            if (size == 0) { printf("Dataset is empty.\n"); continue; }
            int idx;
            float val;
            printf("Enter index to modify (0 to %d): ", size - 1);
            scanf("%d", &idx);
            printf("Enter new value: ");
            scanf("%f", &val);
            modify_element(dataset, size, idx, val);
            continue;
        }

        // Handle File I/O (Option 12 & 13)
        if (choice == 12) {
            printf("Enter filename to save: ");
            scanf("%s", filename);
            save_to_file(dataset, size, filename);
        } else if (choice == 13) {
            printf("Enter filename to load: ");
            scanf("%s", filename);
            load_from_file(&dataset, &size, filename);
        }

        // Handle Exit (Option 14)
        if (choice == 14) {
            if (dataset) free(dataset); // SAFETY: Free memory before exit
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}
