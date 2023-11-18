#ifndef BD_ASSIGNMENT_2_GANTTFUNCTIONS_H
#define BD_ASSIGNMENT_2_GANTTFUNCTIONS_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//changing system command depending on OS type
#ifdef _WIN32
#define SCREEN_CLEAR "cls"
#else
#define SCREEN_CLEAR "clear"
#endif
#define MAX_STR_LEN 30


typedef struct
{
    char taskName[MAX_STR_LEN];
    int startMonth;
    int endMonth;
    int num_of_depend;
    int depend[12];

}USER_GANTT;

void PRINT_GANTT(USER_GANTT task[], int numTasks);
void MAKE_GANTT(USER_GANTT task[], int i, int ifEdit);
void EXAMPLE_GANTT(USER_GANTT tasks[]);
int CHECK_IF_CIRCULAR(USER_GANTT task[], int dependentTaskID);
void ASCII_ART(void);
void REMOVENL(char tempTaskName[]);
void ERROR(void);

#endif //BD_ASSIGNMENT_2_GANTTFUNCTIONS_H
