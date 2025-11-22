#include <stdio.h>
#include "math_utils.h"

int main() {
    float *dataset = NULL;
    int size = 0;
    int choice;
    char filename[50];

    // Array of Function Pointers for operations 1-4
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
        printf("9. Save to File\n");
        printf("10. Load from File\n");
        printf("11. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Handle non-numeric input to prevent infinite loops
            while(getchar() != '\n'); 
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        // Handle Exit
        if (choice == 11) {
            if (dataset) free(dataset); // SAFETY: Free memory before exit
            printf("Exiting...\n");
            break;
        }

        // Handle Adding Data (realloc)
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

        // Handle View
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

        // Handle Sorting
        if (choice == 7 || choice == 8) {
            if (size == 0) {
                printf("Dataset is empty.\n");
                continue;
            }
            sort_data(dataset, size, (choice == 7)); // 1 for Ascending, 0 for Descending
            continue;
        }

        // Handle File I/O
        if (choice == 9) {
            printf("Enter filename to save: ");
            scanf("%s", filename);
            save_to_file(dataset, size, filename);
        } else if (choice == 10) {
            printf("Enter filename to load: ");
            scanf("%s", filename);
            load_from_file(&dataset, &size, filename);
        }
    }

    return 0;
}
