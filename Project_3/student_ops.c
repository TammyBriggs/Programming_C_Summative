#include "student.h"

// Helper: Calculate GPA
float calculate_gpa(float grades[]) {
    float sum = 0;
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        sum += grades[i];
    }
    return sum / SUBJECT_COUNT;
}

// Check if ID exists
int id_exists(Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) return 1;
    }
    return 0;
}

void add_student(Student **students, int *count) {
    // Allocate memory for one more student
    Student *temp = realloc(*students, (*count + 1) * sizeof(Student));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }
    *students = temp;

    Student new_student;
    printf("Enter ID: ");
    scanf("%d", &new_student.id);

    if (id_exists(*students, *count, new_student.id)) {
        printf("Error: Student ID %d already exists!\n", new_student.id);
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]s", new_student.name); // Regex to read string with spaces
    printf("Enter Age: ");
    scanf("%d", &new_student.age);

    if (new_student.age < 0 || new_student.age > 120) {
        printf("Error: Invalid age.\n");
        return;
    }

    printf("Enter %d Grades (0-100): ", SUBJECT_COUNT);
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        scanf("%f", &new_student.grades[i]);
    }

    new_student.gpa = calculate_gpa(new_student.grades);
    (*students)[*count] = new_student;
    (*count)++;
    printf("Student added successfully.\n");
}

void display_students(Student *students, int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\n%-5s %-20s %-5s %-6s\n", "ID", "Name", "Age", "GPA");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-5d %-6.2f\n", 
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

void update_student(Student *students, int count) {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Updating %s (Current GPA: %.2f)\n", students[i].name, students[i].gpa);
            printf("Enter New Name: ");
            scanf(" %[^\n]s", students[i].name);
            printf("Enter New Age: ");
            scanf("%d", &students[i].age);
            printf("Enter New Grades: ");
            for (int j = 0; j < SUBJECT_COUNT; j++) {
                scanf("%f", &students[i].grades[j]);
            }
            students[i].gpa = calculate_gpa(students[i].grades);
            printf("Record updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void delete_student(Student **students, int *count) {
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if ((*students)[i].id == id) {
            found = 1;
            // Shift remaining students left
            for (int j = i; j < *count - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }
            (*count)--;
            // Shrink memory (optional but good practice)
            *students = realloc(*students, *count * sizeof(Student));
            printf("Student deleted.\n");
            break;
        }
    }
    if (!found) printf("Student not found.\n");
}

void free_memory(Student *students) {
    if (students) free(students);
}

void save_to_file(Student *students, int count, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Save failed");
        return;
    }
    fprintf(f, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d\n%s\n%d\n%f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
        for (int j = 0; j < SUBJECT_COUNT; j++) fprintf(f, "%f ", students[i].grades[j]);
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Data saved to %s\n", filename);
}

void load_from_file(Student **students, int *count, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("No saved data found.\n");
        return;
    }
    
    if (*students) free(*students); // Clear current memory

    fscanf(f, "%d", count);
    *students = malloc((*count) * sizeof(Student));

    for (int i = 0; i < *count; i++) {
        fscanf(f, "%d", &(*students)[i].id);
        fscanf(f, " %[^\n]s", (*students)[i].name);
        fscanf(f, "%d", &(*students)[i].age);
        fscanf(f, "%f", &(*students)[i].gpa);
        for (int j = 0; j < SUBJECT_COUNT; j++) {
            fscanf(f, "%f", &(*students)[i].grades[j]);
        }
    }
    fclose(f);
    printf("Data loaded from %s\n", filename);
}
