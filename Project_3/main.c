#include "student.h"

int main() {
    Student *students = NULL;
    int count = 0;
    int choice;
    char filename[] = "student_data.txt";

    while (1) {
        printf("\n=== STUDENT MANAGEMENT SYSTEM ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Search Student (by Name)\n");
        printf("6. Sort Students (by GPA)\n");
        printf("7. General Report (Class Avg & Top Overall)\n");
        printf("8. Find Top Student by Course\n");
        printf("9. Save Data\n");
        printf("10. Load Data\n");
        printf("11. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // clear buffer to prevent infinite loop
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: 
                add_student(&students, &count); 
                break;
            case 2: 
                display_students(students, count); 
                break;
            case 3: 
                update_student(students, count); 
                break;
            case 4: 
                delete_student(&students, &count); 
                break;
            case 5: 
                search_student(students, count); 
                break;
            case 6: 
                sort_by_gpa(students, count); 
                display_students(students, count); 
                break;
            case 7: 
                print_class_average(students, count); 
                print_top_student(students, count); 
                break;
            case 8: 
                print_top_student_by_course(students, count);
                break;
            case 9: 
                save_to_file(students, count, filename); 
                break;
            case 10: 
                load_from_file(&students, &count, filename); 
                break;
            case 11: 
                free_memory(students); 
                printf("Exiting...\n"); 
                return 0;
            default: 
                printf("Invalid choice. Please select 1-11.\n");
        }
    }
    return 0;
}
