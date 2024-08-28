  if ((*student)->subjects[(*student)->numOfSubjects - 1]->subjectName == NULL) { 
        printf("Memory allocation failed for student subject name!\n");
        free(student);
        return 0;
    }
    strncpy((*student)->subjects[(*student)->numOfSubjects - 1]->subjectName, name,strlen(name));
    (*student)->subjects[(*student)->numOfSubjects - 1]->grade = 'B';
   