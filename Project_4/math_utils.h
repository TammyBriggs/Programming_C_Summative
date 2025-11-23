#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Define a function pointer type for mathematical operations
// This type represents any function that takes a float array and its size, and returns a float result.
typedef float (*MathOperation)(float*, int);

// Function Prototypes

// Memory Management & I/O
void print_data(float *data, int size);
void save_to_file(float *data, int size, const char *filename);
int load_from_file(float **data, int *size, const char *filename); // Uses double pointer to modify the array pointer itself

// Operations
float op_sum(float *data, int size);
float op_average(float *data, int size);
float op_max(float *data, int size);
float op_min(float *data, int size);

// Sorting (Void because it modifies the array in place, doesn't return a single value)
void sort_data(float *data, int size, int ascending);

int search_value(float *data, int size, float target);
void delete_element(float **data, int *size, int index);
void modify_element(float *data, int size, int index, float new_val);

#endif
