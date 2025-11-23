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
    char course[MAX_NAME]; // NEW: Course added
    int age;
    float grades[SUBJECT_COUNT];
    float gpa;
} Student;

// Operations
void add_student(Student **students, int *count);
void display_students(Student *students, int count);
void update_student(Student *students, int count);
void delete_student(Student **students, int *count);
void free_memory(Student *students);
void save_to_file(Student *students, int count, const char *filename);
void load_from_file(Student **students, int *count, const char *filename);

// Analytics
void sort_by_gpa(Student *students, int count);
void search_student(Student *students, int count);
void print_top_student(Student *students, int count);
void print_class_average(Student *students, int count);
void print_top_student_by_course(Student *students, int count); // NEW

float calculate_gpa(float grades[]);

#endif
