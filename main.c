#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Students;

typedef struct Teachers{
    unsigned short int  id ;
    char *name ;
    char *subject; 
    Students **st; 
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

#pragma region Utils

unsigned short int generate_Teacherid() {
    static unsigned short int current_id = 0; // Static variable to maintain state
    return ++current_id; // Increment and return the new ID
}

char *stringInput(char prompt[]){
    char temp[100];
    printf("Input %s : " , prompt);
    
        if(fgets(temp,sizeof(temp) , stdin) != NULL){
            // removing the new line character
            if(strlen(temp) > 0 && temp[strlen(temp) - 1] == '\n'){
                temp[strlen(temp) - 1] = '\0';
            }
            // Allocate the memory for result
            char *result = malloc(strlen(temp) +1);
            if(result == NULL){
                printf("Memory allocation failed to result");
                exit(1);
            }
            strncpy(result,temp,strlen(temp));
            return result;
            
        }
        else{
            printf("Error reading input\n.");
            printf("Enter Again\n.");
            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }

            return NULL;
         }
    

}

#pragma endregion

#pragma region Funtions - Add
int addTeacher(char name[] , char subject[] , Teachers **teacher){
    *teacher = malloc(sizeof(Teachers));
    if (teacher == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }
    (*teacher)->id = generate_Teacherid();

    (*teacher)->name = malloc((strlen(name) +1) * sizeof(char));
    if ((*teacher)->name == NULL) {
        printf("Memory allocation failed for teacher name!\n");
        free(teacher);
        return 0;
    }
    strncpy((*teacher)->name, name,strlen(name));

    (*teacher)->subject = malloc((strlen(subject) + 1) * sizeof(char));
    if((*teacher)->subject == NULL){
        printf("Memory allocation failed for teacher subject!\n");
        free(teacher);
        return 0;
    }
    strncpy((*teacher)->subject, subject,strlen(subject));
    return 1;
}
void addStudent(){
    printf("Adding Student");
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


void displayTeachers(Teachers **teachers , size_t size){
    clearScreen();
    for(int i = 0 ; i< size ; i++){
        printf("Teacher ID: %d \n" , teachers[i]->id);
        printf("Teacher Name: %s \n" , teachers[i]->name);
        printf("Teacher Subject: %s \n" , teachers[i]->subject);
        printf("*************************************************\n");
    }
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
    size_t numOfTeachers = 0;
    size_t numOfStudents = 0;
    Teachers **teachers = NULL;
    Students **students = NULL;


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
                if(choice == 1){ // add Student
                    if(students == NULL){ // mem not assigned , assign memory for first student

                    }
                    else{ // mem already assigned , realloc for new student

                    }
                    addStudent(); 
                }else if(choice == 2){ // Add Teacher
                    
                     if(teachers == NULL){ // mem not assigned, assign memory for first teacher
                            numOfTeachers++;
                            teachers = malloc(numOfTeachers * sizeof(Teachers *)); // assign memory of 1 teacher 
                            if(teachers == NULL){
                                printf("Memory Allocation to teachers failed");
                                return 1;
                            }
                        }
                    else{ // mem already assigned , realloc for new teacher
                            numOfTeachers++;
                            teachers = realloc(teachers , numOfTeachers * (sizeof(Teachers *)));
                            if(teachers == NULL){
                                printf("Reallocation of Memory to teachers failed while adding %zu teacher" , numOfTeachers);
                                return 1;
                            }
                    }
                    teachers[numOfTeachers - 1] = NULL;
                    while (getchar() != '\n'); // clear input
                    char *name = stringInput("name"); // get name from user
                    if(name == NULL) {
                        printf("Failed to set name");
                        return 1;
                    }
                    char *subject = stringInput("Subject"); // get subject from user
                    if(subject == NULL){
                        printf("Failed to set subject");
                        free(name);
                        return 1;
                    }

                    if(addTeacher(name , subject , &teachers[numOfTeachers - 1]) == 1){
                        printf("Teacher Added with ID: %d  ", teachers[numOfTeachers - 1]->id );
                        free(name);
                        free(subject);
                    }else{
                        printf("Failed to add teacher");
                        return 1;
                    }
                }
                else if(choice == 3) // findAllStudentswSubject
                {
                    findAllStudentswSubject();
                }
                else if(choice == 4){ // findStudentwId
                    findStudentwId();
                }
                else if(choice == 5){// findTeacherwSubject
                    findTeacherwSubject();
                }
                else if(choice == 6){// displayTeachers
                    while (getchar() != '\n'); // clear input
                    displayTeachers(teachers , numOfTeachers);
                }
                else if(choice == 7){// dislpayStudents
                    dislpayStudents(); 
                }
                }else if(choice == 8){ // Exit
                printf("\nExiting the program...\n");
                break;
                }else{
                    printf("\nInvalid choice. Please select a valid option (1-5).\n");
                }
                // Pause before returning to the main menu
                printf("\nPress Enter to return to the main menu...");
               // while (getchar() != '\n'); // Consume newline left by scanf
                getchar(); // Wait for Enter key
                clearScreen(); // clear console screen
        }
    
    
    }while(choice != 8);
    
    return 0;
}