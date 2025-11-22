#include "student.h"

// Manual Bubble Sort by GPA (Descending)
void sort_by_gpa(Student *students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Sorted by GPA (Highest to Lowest).\n");
}

// Linear Search by Name
void search_student(Student *students, int count) {
    char search_name[MAX_NAME];
    printf("Enter Name to search: ");
    scanf(" %[^\n]s", search_name);

    int found = 0;
    printf("\nSearch Results:\n");
    for (int i = 0; i < count; i++) {
        // strstr finds a substring, useful for partial matches
        if (strstr(students[i].name, search_name) != NULL) {
            printf("ID: %d | Name: %s | GPA: %.2f\n", 
                   students[i].id, students[i].name, students[i].gpa);
            found = 1;
        }
    }
    if (!found) printf("No matching student found.\n");
}

// Statistical Report: Class Average
void print_class_average(Student *students, int count) {
    if (count == 0) return;
    float total_gpa = 0;
    for (int i = 0; i < count; i++) {
        total_gpa += students[i].gpa;
    }
    printf("Class Average GPA: %.2f\n", total_gpa / count);
}

// Statistical Report: Top Student
void print_top_student(Student *students, int count) {
    if (count == 0) return;
    int top_index = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].gpa > students[top_index].gpa) {
            top_index = i;
        }
    }
    printf("Top Performer: %s (GPA: %.2f)\n", students[top_index].name, students[top_index].gpa);
}
