#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define SUBJECT_COUNT 5

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    float grades[SUBJECT_COUNT];
    float gpa;
} Student;

// === CRUD Operations (student_ops.c) ===
void add_student(Student **students, int *count);
void display_students(Student *students, int count);
void update_student(Student *students, int count);
void delete_student(Student **students, int *count);
void free_memory(Student *students);

// === File I/O (student_ops.c) ===
void save_to_file(Student *students, int count, const char *filename);
void load_from_file(Student **students, int *count, const char *filename);

// === Analytics & Algorithms (analytics.c) ===
void sort_by_gpa(Student *students, int count);
void search_student(Student *students, int count); // Linear Search
void print_top_student(Student *students, int count);
void print_class_average(Student *students, int count);

// Helper
float calculate_gpa(float grades[]);

#endif
