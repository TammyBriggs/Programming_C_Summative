#include "math_utils.h"

// === MEMORY & I/O UTILS ===

void print_data(float *data, int size) {
    if (size == 0) {
        printf("Dataset is empty.\n");
        return;
    }
    printf("Current Dataset: [ ");
    for (int i = 0; i < size; i++) {
        printf("%.2f ", data[i]);
    }
    printf("]\n");
}

void save_to_file(float *data, int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }
    // Write size first, then data
    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%f\n", data[i]);
    }
    fclose(file);
    printf("Data saved to %s successfully.\n", filename);
}

int load_from_file(float **data, int *size, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return 0; // Failure
    }

    int new_size;
    if (fscanf(file, "%d", &new_size) != 1) {
        printf("Error reading file format.\n");
        fclose(file);
        return 0;
    }

    // Free old data if it exists
    if (*data != NULL) {
        free(*data);
    }

    // Allocate new memory based on file content
    *data = (float *)malloc(new_size * sizeof(float));
    if (*data == NULL) {
        printf("Memory allocation failed during load.\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < new_size; i++) {
        fscanf(file, "%f", &(*data)[i]);
    }

    *size = new_size;
    fclose(file);
    printf("Data loaded successfully. New size: %d\n", *size);
    return 1; // Success
}

// === MATHEMATICAL OPERATIONS ===

float op_sum(float *data, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) sum += data[i];
    return sum;
}

float op_average(float *data, int size) {
    if (size == 0) return 0.0;
    return op_sum(data, size) / size;
}

float op_max(float *data, int size) {
    if (size == 0) return 0.0;
    float max = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] > max) max = data[i];
    }
    return max;
}

float op_min(float *data, int size) {
    if (size == 0) return 0.0;
    float min = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] < min) min = data[i];
    }
    return min;
}

// Simple Bubble Sort
void sort_data(float *data, int size, int ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            int condition = ascending ? (data[j] > data[j+1]) : (data[j] < data[j+1]);
            if (condition) {
                float temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
    printf("Data sorted %s.\n", ascending ? "Ascending" : "Descending");
}
