// Written by Rebecca Stolper (z3378134) 
// on 27 June 2022
//
// Interactive program to scan in and display the details of students in a
// class.

#include <stdio.h>

#define MAX_CLASS_SIZE 20
#define MAX_EXAM_MARK 40
#define MAX_ASSIGMENTS_MARK 60

// UNSW COMPSCI major codes
enum major {
    COMPA1,
    COMPD1,
    COMPE1,
    COMPI1,
    COMPJ1,
    COMPN1,
    COMPS1,
    COMPY1,
    NONE
};

// Struct representing a UNSW COMPSCI student
struct student {
    int z_id;
    enum major major;
    double assignments_mark;
    double exam_mark;
    double course_grade;
};

// function to write major from its identifier code
void write_major(enum major major) {
        
    if (major == COMPA1) {
        printf("Computer Science\n");
    } else if (major == COMPD1) {
        printf("Database Systems\n");
    } else if (major == COMPE1) {
        printf("eCommerce Systems\n");
    } else if (major == COMPI1) {
        printf("Artificial Intelligence\n");
    } else if (major == COMPJ1) {
        printf("Programming Languages\n");
    } else if (major == COMPN1) {
        printf("Computer Networks\n");
    } else if (major == COMPS1) {
        printf("Embedded Systems\n");
    } else if (major == COMPY1) {
        printf("Security Engineering\n");
    } else {
        printf("None\n");
    }

}

// function to create a set of structs of type 'student' called 'new_student'
struct student scan_student_details(void) {

    struct student new_student;
      
    printf("Enter zID: ");
    scanf("%d", &new_student.z_id);

    printf("Select Major: \n");
    enum major major = COMPA1;
    while (major <= NONE) {
        printf("%d: ", major);
        write_major(major);
        major++;
    }
    printf(": ");
    int scanned_major;
    scanf("%d", &scanned_major);
    major = NONE;
    if (scanned_major >= COMPA1 && scanned_major < NONE) {
        major = scanned_major;
    }

    new_student.major = major;

    printf("Enter Assignments mark (out of %d): ", MAX_ASSIGMENTS_MARK);
    scanf("%lf", &new_student.assignments_mark);

    printf("Enter exam mark (out of %d): ", MAX_EXAM_MARK);
    scanf("%lf", &new_student.exam_mark);

    new_student.course_grade = new_student.exam_mark 
                             + new_student.assignments_mark;

    return new_student;
}

// function to print details of all new_student structs from class
void print_class(struct student student) {

    printf("z%07d: {\n", student.z_id);

    printf("\tMajor: ");
    write_major(student.major);

    printf("\tAssignments Mark: %3.02lf/%d\n", student.assignments_mark, 
           MAX_ASSIGMENTS_MARK);
    printf("\tExam Mark: %3.02lf/%d\n", student.exam_mark, MAX_EXAM_MARK);
    printf("\tCourse Grade: %3.02lf/%d\n", student.course_grade, 
           MAX_ASSIGMENTS_MARK + MAX_EXAM_MARK);
    printf("}\n");

}

int main(void) {
    int class_size;
    printf("Enter Class Size: ");
    scanf("%d", &class_size);

    if (class_size <= 0 || class_size > MAX_CLASS_SIZE) {
        printf("Class Size must be between 1 and %d\n", MAX_CLASS_SIZE);
        // Exit the program early
        return 0;
    }

    struct student class[MAX_CLASS_SIZE]; 
    
    int i = 0;
    while (i < class_size) {
        printf("Student %d: \n", i + 1);
        class[i] = scan_student_details();
        i++;
    }

    printf("Students: \n");
    i = 0;
    while (i < class_size) {
        print_class(class[i]);
        i++;
    }

    return 0;
    
}
