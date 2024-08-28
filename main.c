#include <stdio.h>
#include <stdlib.h>

#pragma region Structures

typedef struct studentSubjects{
    char *subjectName; 
    char grade;
} studentSubjects;

typedef struct students{
    unsigned short int id ;
    char *name ;
    int numOfSubjects; 
    studentSubjects *subjects ;
} students;

typedef struct Teachers{
    unsigned short int  id ;
    char *name ;
    char *subject; 
    students **st; 
} Teachers;
#pragma endregion

#pragma region Function - Clear Screen
void clearScreen() {
    #ifdef _WIN32 // check current system
        system("cls");
    #else
        system("clear");
    #endif
}
#pragma endregion

#pragma region Funtions - Add
void addStudent(){
    printf("Adding student");
}
void addTeacher(){
    printf("Adding Teacher");
}
#pragma endregion

#pragma region Functions - Find
void findAllStudentswSubject(){

}
void findStudentwId(){

}
void findTeacherwSubject(){

}
#pragma endregion

#pragma region Functions - Display

void displayTeachers(){

}
void dislpayStudents(){

}
#pragma endregion

#pragma region Function - Menu

void mainMenu(){
     // Display the menu options
    printf("\n========== Student Management System ==========\n");
    printf("1. Add a new student\n");
    printf("2. Add a new Teacher\n");
    printf("3. Find all students with certain subjects\n");
    printf("4. Find a student with ID\n");
    printf("5. Find teacher with subject\n");
    printf("6. Display  Teachers\n");
    printf("7. Display  Students\n");
    printf("8. Exit\n");
    printf("===============================================\n");
    printf("Please choose an option (1-6): ");

}
#pragma endregion


int main(void){
   

    int choice = 0;
    do{

        mainMenu(); // display Main Menu
        // Get user input and validate it
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number between 1 and 5.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        
        }
        else{
            if (choice >= 1 && choice <= 7){
                if(choice == 1){
                    addStudent();
                }else if(choice == 2){
                    addTeacher();
                }
                else if(choice == 3)
                {
                    findAllStudentswSubject();
                }
                else if(choice == 4){
                    findStudentwId();
                }
                else if(choice == 5){
                    findTeacherwSubject();
                }
                else if(choice == 6){
                    displayTeachers();
                }
                else if(choice == 7){
                    dislpayStudents(); 
                }
            }else if(choice == 8){
                printf("\nExiting the program...\n");
                break;
            }else{
                printf("\nInvalid choice. Please select a valid option (1-5).\n");
            }
                // Pause before returning to the main menu
                printf("\nPress Enter to return to the main menu...");
                while (getchar() != '\n'); // Consume newline left by scanf
                getchar(); // Wait for Enter key
                clearScreen(); // clear console screen
        }
    
    
    }while(choice != 8);
    
    return 0;
}