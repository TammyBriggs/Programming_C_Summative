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

void print_top_student_by_course(Student *students, int count) {
    char target_course[MAX_NAME];
    printf("Enter Course Name to analyze: ");
    scanf(" %[^\n]s", target_course);

    int best_index = -1;
    float max_gpa = -1.0;

    for (int i = 0; i < count; i++) {
        // Compare strings
        if (strcmp(students[i].course, target_course) == 0) {
            if (students[i].gpa > max_gpa) {
                max_gpa = students[i].gpa;
                best_index = i;
            }
        }
    }

    if (best_index != -1) {
        printf("Top Student in %s: %s (GPA: %.2f)\n", 
               target_course, students[best_index].name, students[best_index].gpa);
    } else {
        printf("No students found in course: %s\n", target_course);
    }
}
