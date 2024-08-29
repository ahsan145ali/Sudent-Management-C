#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma region Structures

typedef struct studentSubjects{
    char *subjectName; 
    char grade;
} StSubjects;

typedef struct students{
    unsigned short int id ;
    char *name ;
    int numOfSubjects; 
    StSubjects **subjects ;
} Students;

typedef struct Teachers{
    unsigned short int  id ;
    char *name ;
    char *subject; 
    Students **st; 
} Teachers;
#pragma endregion

#pragma region Function - Clear Screen

/// @brief Clears the console screen based on the system beinf used
void clearScreen() {
    #ifdef _WIN32 // check current system
        system("cls"); // used for windows
    #else
        system("clear"); // used for mac and linux
    #endif
}
#pragma endregion

#pragma region Utils

/// @brief to generate auto incrementing id for teacher 
/// @return returns a unsigned short int after incrementing it which is used as an id for the teacher
unsigned short int generate_Teacherid() {
    static unsigned short int current_id = 0; // Static variable to maintain state
    return ++current_id; // Increment and return the new ID
}

/// @brief to generate auto incrementing id for student 
/// @return returns a unsigned short int after incrementing it which is used as an id for the student
unsigned short int generate_Studentid() {
    static unsigned short int current_sid = 0; // Static variable to maintain state
    return ++current_sid; // Increment and return the new ID
}

/// @brief allocates or reallocates memory to a double pointer of Teachers
/// @param teachers a pointer to a an array of pointers to Teachers Structure
/// @param size  number of Teachers pointers which points to Teachers Structure
void allocateMemoryTeacher(Teachers ***teachers , size_t* size){

    if(*teachers == NULL){ // mem not assigned, assign memory for first teacher
         *size = *size + 1; // increment size to potray number of teachers
         *teachers = malloc(*size * sizeof(Teachers *)); // assign memory of 1 teacher 
        if(*teachers == NULL){
            printf("Memory Allocation to teachers failed");
            exit(1);
            }
    }
    else{ // mem already assigned , realloc for new teacher
        *size = *size + 1; // increment size to potray number of teachers
        *teachers = realloc(*teachers , *size * (sizeof(Teachers *))); // reallocate memory to hold a new teacher
        if(*teachers == NULL){
        printf("Reallocation of Memory to teachers failed while adding %zu teacher" , *size);
        exit(1);
        }
     }
}

/// @brief allocates or reallocates memory to a double pointer of Students
/// @param students a pointer to a an array of pointers to Students Structure
/// @param size number of Teachers pointers which points to Teachers Structure
void allocateMemoryStudent(Students ***students , size_t* size){
    if(*students == NULL){ // mem not assigned, assign memory for first teacher
         *size = *size + 1; // increment size to potray number of teachers
         *students = malloc(*size * sizeof(Students *)); // assign memory of 1 teacher 
        if(*students == NULL){
            printf("Memory Allocation to teachers failed");
            exit(EXIT_FAILURE);
            }
    }
    else{ // mem already assigned , realloc for new teacher
        *size = *size + 1; // increment size to potray number of teachers
        *students = realloc(*students , *size * (sizeof(Students *))); // reallocate memory to hold a new teacher
        if(*students == NULL){
        printf("Reallocation of Memory to teachers failed while adding %zu teacher" , *size);
        exit(EXIT_FAILURE);
        }
     }
}

/// @brief gets input from user and performs validation
/// @param prompt specifies what is being asked from the user
/// @return returns a char* on success and NULL if failed
char *stringInput(char prompt[]){
    char temp[100]; // temporary char[] to get input
    printf("Input %s : " , prompt);
    
        if(fgets(temp,sizeof(temp) , stdin) != NULL){ // get input from user which does not exceed size of temp
            // removing the new line character
            if(strlen(temp) > 0 && temp[strlen(temp) - 1] == '\n'){ // check if input size is more then 0 and last character is a newline character
                temp[strlen(temp) - 1] = '\0'; // replace newline character with the Null character
            }
            // Allocate the memory for result
            char *result = malloc(strlen(temp) +1);
            if(result == NULL){
                printf("Memory allocation failed to result");
                exit(1);
            }
            strncpy(result,temp,strlen(temp)); // copy input from temp to result
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
/// @brief adds a new teacher
/// @param name accepts name for the teacher
/// @param subject  accepts subject for the teacher
/// @param teacher // a pointer to a pointer array of structure teacher
/// @return returns 0 if failed else returns 1 on Success
int addTeacher(char name[] , char subject[] , Teachers **teacher){
    *teacher = malloc(sizeof(Teachers)); // allocate memory
    if (teacher == NULL) { 
        printf("Memory allocation failed!\n");
        return 0; // failed
    }
    (*teacher)->id = generate_Teacherid(); // set id

    (*teacher)->name = malloc((strlen(name) +1) * sizeof(char)); // set size for name
    if ((*teacher)->name == NULL) {
        printf("Memory allocation failed for teacher name!\n");
        free(teacher);
        return 0; // failed
    }
    strncpy((*teacher)->name, name,strlen(name)); // copy name to structure name

    (*teacher)->subject = malloc((strlen(subject) + 1) * sizeof(char)); // allocate memory for subject
    if((*teacher)->subject == NULL){
        printf("Memory allocation failed for teacher subject!\n");
        free(teacher);
        return 0; // failed
    }
    strncpy((*teacher)->subject, subject,strlen(subject)); // copy subject to structure subject
    return 1; // Success
}

/// @brief adds a new student
/// @param name accepts name for the student
/// @param subject accepts subject for the student
/// @param student a pointer to a pointer array of structure student
/// @return returns 0 if failed else returns 1 on Success
int addStudent(char name[] , char subject[] , Students **student){
    *student = malloc(sizeof(Students)); // allocate memory
    if(student == NULL){
        printf("Memory allocation failed!\n");
        return 0;
    }
    (*student)->id = generate_Studentid(); // sert id
    (*student)->numOfSubjects = 1; // set numofsubjects


    (*student)->name = malloc((strlen(name) +1) * sizeof(char)); // set size for name
    if ((*student)->name == NULL) { 
        printf("Memory allocation failed for student name!\n");
        free(student);
        return 0;
    }
    strncpy((*student)->name, name,strlen(name)); // copy name to structre name

    int option = 1; // stores option to add another subject or exit
    do{
        if((*student)->subjects == NULL)
        { 
            (*student)->subjects = malloc((*student)->numOfSubjects * sizeof(StSubjects *)); // allocate memory for the double pointer os stSubjects structure
            if ((*student)->subjects == NULL) {
                 printf("Memory allocation failed for subjects array.\n");
                 return 0; 
            }
        }
        else{
              (*student)->numOfSubjects += 1; // increment numofSubjects
              (*student)->subjects = realloc((*student)->subjects , (*student)->numOfSubjects * (sizeof(Students *))); // re allcoate memory to the double pointer add new pointer which points to stsubjects structure to add a new subject
              if ((*student)->subjects == NULL) {
                 printf("Memory Re allocation failed for subjects array.\n");
                 return 0; 
            }
            while (getchar() != '\n'); // Clear input buffer
            subject = stringInput("subject"); // get input from user and store it in subject
        }
   
    
    (*student)->subjects[(*student)->numOfSubjects - 1] = malloc( sizeof(StSubjects)); // allocate memory
    (*student)->subjects[(*student)->numOfSubjects - 1]->subjectName= malloc((strlen(subject) +1) * sizeof(char)); // allocate memory for subject


     if ((*student)->subjects[(*student)->numOfSubjects - 1]->subjectName == NULL) { 
        printf("Memory allocation failed for student subject name!\n");
        free(student);
        return 0;
    }
    strncpy((*student)->subjects[(*student)->numOfSubjects - 1]->subjectName, subject,strlen(subject)); // copy subject name to structure subject name
    (*student)->subjects[(*student)->numOfSubjects - 1]->grade = 'B'; // set grade for subject
    printf("Press 1 to enter another subject \npress any other key to exit \n ");
    scanf("%d" , &option);
    }while(option== 1);
   
    return 1;

}
#pragma endregion

#pragma region Functions - Find


/// @brief finds all students that study a certain subject
/// @param students  a double piointer of the Students structure
/// @param  size represents the total number of students in the structure
/// @param subject the subjects that needs to be found among all students
/// @param newSize to maintain new size according to the students that are found
/// @return if found returns a pointer to a pointer array of student structure else returns Null
Students** findAllStudentswSubject(Students **students , size_t size ,char subject[] , size_t *newSize){
    Students **foundStudents = NULL; // create a new double pointer to store students with subject that is to be searched with
    for(int i =0 ;i < size ; i++){
        if(students[i]->numOfSubjects > 0){
            for(int j=0 ; j < students[i]->numOfSubjects ; j++){
                if(strcmp(students[i]->subjects[j]->subjectName, subject)== 0){ // compare current student subject with the subject that is to be found
                    allocateMemoryStudent(&foundStudents , newSize); // allocate memory to the double pointer foundStudents to add the student that is found
                    foundStudents[*newSize-1] = students[i]; // add student to foundstudent
                    break;
                }
            }
        }
    }
    if(foundStudents == NULL){
        return NULL;
    }
    return foundStudents;
}

/// @brief finds a certain student with id
/// @param students a double piointer of the Students structure
/// @param size represents the total number of students in the structure
/// @param id the id of the student which needs to be found
/// @return if found returns that student pointer to structure else returns Null
Students* findStudentwId(Students **students , size_t size ,unsigned short int id){
    clearScreen(); // Clear console screen
    if(id-1 < size){ // student exists as id is incremented automatically when a student is added
        return students[id-1]; // returns student
    }
    else{
        return NULL;
    }
    
}

/// @brief finds the teacher/teachers with a subject
/// @param teachers a double piointer of the Teachers structure
/// @param size represents the total number of Teachers in the structure
/// @param subject the subjects that needs to be found among all Teachers
/// @param newSize to maintain new size according to the teachers that are found
/// @return if found returns a pointer to a pointer array of student structure else returns Null
Teachers** findTeacherwSubject(Teachers **teachers , size_t size , char subject[] , size_t *newSize){
    Teachers **foundTeachers = NULL; // create a new double pointer to store teachers with subject that is to be searched with
    
    for(int i=0 ; i < size ; i++){
        if(strcmp(teachers[i]->subject, subject)== 0){ // compare current student subject with the subject that is to be found
            allocateMemoryTeacher(&foundTeachers , newSize); // allocate memory to the double pointer foundStudents to add the student that is found
            foundTeachers[*newSize-1] = teachers[i]; // add student to foundstudent
        }
    }
        
    if(foundTeachers == NULL){
        return NULL;
    }
    return foundTeachers;
}
#pragma endregion

#pragma region Functions - Display

/// @brief display all of the current students
/// @param teachers a double pointer to Teachers structure which holds all of the current teachers
/// @param size current number of students that have been added
void displayTeachers(Teachers **teachers , size_t size){
    clearScreen();
    for(int i = 0 ; i< size ; i++){
        printf("Teacher ID: %d \n" , teachers[i]->id);
        printf("Teacher Name: %s \n" , teachers[i]->name);
        printf("Teacher Subject: %s \n" , teachers[i]->subject);
        printf("*************************************************\n");
    }
}
/// @brief display all of the current students
/// @param students a double pointer to Students structure which holds all of the current students
/// @param size current number of students that have been added
void dislpayStudents(Students **students , size_t size){
    clearScreen();
    for(int i = 0 ; i< size ; i++){
        printf("Student ID: %d \n" , students[i]->id);
        printf("Student Name: %s \n" , students[i]->name);
        printf("Subjects studied: %d \n" , students[i]->numOfSubjects);
        if(students[i]->numOfSubjects > 0 ){
            for(int j = 0 ; j < students[i]->numOfSubjects;j++){ // print every subject for that student
                printf("\t Subject Name: %s , Grade: %c \n" , students[i]->subjects[j]->subjectName , students[i]->subjects[j]->grade );
            }
        }
        else{
            printf("No Subjects Studied\n");
        }
        printf("*************************************************\n");
    }
}
/// @brief Display a single student
/// @param student the student that is to be displayed
void displayStudentwId(Students *student){
    printf("Student Name: %s \n" , student->name);
    printf("Subjects Studied: %d \n",student->numOfSubjects);
    if(student->numOfSubjects > 0){
        for(int i=0 ; i< student->numOfSubjects ; i++)
        {
             printf("\t Subject Name: %s , Grade: %c \n" , student->subjects[i]->subjectName , student->subjects[i]->grade );
        }
    }
}
#pragma endregion

#pragma region Function - Menu

/// @brief display main menu with options
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
    printf("Please choose an option (1-7): ");

}
#pragma endregion


int main(void){

    int choice = 0; // to store option for the menu
    size_t numOfTeachers = 0; // mantains number of teachers added 
    size_t numOfStudents = 0; // mantains number of students added
    Teachers **teachers = NULL; // a pointer to pointer arrray of structure teachers
    Students **students = NULL; // a pointer to pointer array of structure students

    do{
        mainMenu(); // display Main Menu
        // Get user input and validate it
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number between 1 and 7.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        else{
            if (choice >= 1 && choice <= 7){
                if(choice == 1){ // add Student
                    allocateMemoryStudent(&students , &numOfStudents);
                    
                    students[numOfStudents - 1] = NULL;
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
                    if(addStudent(name,subject,&students[numOfStudents - 1]) == 1){
                        printf("Student Added with ID: %d  ", students[numOfStudents - 1]->id );
                        free(name);
                        free(subject);
                    } else{
                         printf("Failed to add Student");
                        return 1;
                    }
                }else if(choice == 2){ // Add Teacher
                    
                    allocateMemoryTeacher(&teachers,&numOfTeachers); // allocate memory to the pointer
                   
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
                    while (getchar() != '\n'); // Consume newline 
                    char *subject = stringInput("Subject"); // get subject from user
                    if(subject == NULL){
                        printf("Failed to set subject");
                        return 1;
                    }
                    size_t newSize = 0; // to maintain new size of the array of pointers to pointers
                    Students ** st =  findAllStudentswSubject(students , numOfStudents , subject , &newSize);
                    if(st == NULL){
                        printf("No Student Found with subject : %s " , subject );
                    }else{
                        dislpayStudents(st,newSize);
                        free(subject);
                        free(st);
                    }
                }
                else if(choice == 4){ // findStudentwId
                    while (getchar() != '\n'); // clear input
                    unsigned short int findId = 1 ;
                    printf("Enter Student Id: ");
                     if (scanf("%hd", &findId) != 1) {
                         printf("\nInvalid input. Please enter a valid number.\n");
                         while (getchar() != '\n'); // Clear input buffer
                         continue;
                    }
                    while (getchar() != '\n'); // Clear input buffer
                    Students* st =  findStudentwId(students , numOfStudents  , findId);
                    if(st == NULL)
                    {
                        printf("Invalid Id \n No Student found with the id: %d" , findId);
                    }
                    else{
                        printf("Student Found with id : %d \n" , findId);
                        displayStudentwId(st);
                        free(st);

                    }
                }
                else if(choice == 5){// findTeacherwSubject
                    while (getchar() != '\n'); // Consume newline 
                    char *subject = stringInput("Subject"); // get subject from user
                    if(subject == NULL){
                        printf("Failed to set subject");
                        return 1;
                    }
                    size_t newSize = 0; // to maintain new size of the array of pointers to pointers
                    Teachers **te = findTeacherwSubject(teachers,numOfTeachers,subject,&newSize);
                    if(te == NULL)
                    {
                        printf("No Teacher Found with the Subject");
                    }
                    else{
                        displayTeachers(te,newSize);
                        free(subject);
                        free(te);
                    }
                }
                else if(choice == 6){// displayTeachers
                    while (getchar() != '\n'); // clear input
                    displayTeachers(teachers , numOfTeachers);
                }
                else if(choice == 7){// dislpayStudents
                    while (getchar() != '\n'); // clear input
                    dislpayStudents(students,numOfStudents); 
                }
                }else if(choice == 8){ // Exit
                printf("\nExiting the program...\n");
                break;
                }else{
                    printf("\nInvalid choice. Please select a valid option (1-7).\n");
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

