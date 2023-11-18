#include "GanttFunctions.h"

/*This function prints the gantt chart. It takes in:
-> The struct array variable
-> The number of tasks*/
void PRINT_GANTT(USER_GANTT task[], int numTasks)
{
    printf("==========================================================================================================================================================================================================\n");
    printf("                         |  JANUARY   |  FEBRUARY  |    MARCH   |    APRIL   |    MAY     |   JUNE     |    JULY    |   AUGUST   |  SEPTEMBER  |  OCTOBER  |  NOVEMBER  |  DECEMBER  |   DEPENDENCIES\n");
    printf("==========================================================================================================================================================================================================\n");
    int i, j;
    //printing blocks depending on the start and end month
    for(i = 0; i < numTasks; i++)
    {
        printf("%-25s|", task[i].taskName);
        for(j = 1; j < task[i].startMonth; j++)
        {
            printf("            |");
        }

        for(j = task[i].startMonth; j <= task[i].endMonth; j++)
        {
            printf("    XXX     |");
        }

        for(j = task[i].endMonth; j < 12; j++)
        {
            printf("            |");
        }

        printf(" ");

        //printing dependencies
        for(j = 0; j < task[i].num_of_depend; j++)
        {
            printf("%d ", task[i].depend[j]);
        }

        printf("\n");
        printf("==========================================================================================================================================================================================================\n");

    }



}
/*
This function creates the user's gantt chart. It takes in
-> the struct array variable
-> the iteration of i to know where to store the user's input in the struct array variable
-> an integer to change the print statement*/
void MAKE_GANTT(USER_GANTT task[], int i, int ifEdit)
{
    char tempTaskName[MAX_STR_LEN];
    int j, k;

    //change print statement if task is being edited or not
    if(ifEdit == 0)
        printf("Please enter the task name\n");

    else if (ifEdit == 1)
        printf("Please enter the new task name or its old name\n");

    taskname:
    REMOVENL(tempTaskName);
    strcpy(task[i].taskName, tempTaskName);

    //comparing the task names to ensure no task name is inputted twice
    if(i > 0)
    {
        for(k = 0; k < i; k++)
            if(strcmp(task[i].taskName, task[k].taskName) == 0)
            {
                printf("This is already a task name!\nPlease enter a unique task name\n");
                goto taskname;
            }
    }

    months:
    printf("Start month(1-12):\n");
    scanf("%d", &task[i].startMonth);

    printf("End month(1-12):\n");
    scanf("%d", &task[i].endMonth);

    if(task[i].endMonth < task[i].startMonth)
    {
        printf("End month is before start month!\nPlease enter a valid start and end month\n");
        goto months;
    }

    if(task[i].startMonth < 1 || task[i].startMonth > 12 || task[i].endMonth < 1 || task[i].endMonth > 12)
    {
        ERROR();
        goto months;
    }

    printf("Enter how many dependencies this task has\n");
    scanf("%d", &task[i].num_of_depend);
    getchar();
    if(task[i].num_of_depend > 0)
    {
        for(j = 0;j<task[i].num_of_depend;j++)
        {
            dependencies:
            printf("Enter dependant task\n");
            scanf("%d", &task[i].depend[j]);
            getchar();

            if(task[i].depend[j] == i+1)
            {
                printf("Task cannot depend on itself\n");
                goto dependencies;
            }
        }
    }

}

//This function prints an error message
void ERROR(void)
{
    printf("Please enter a valid option\n");
}


/*THis function checks if a task has a circular dependency. It takes in:
-> The struct array variable
-> The int specifying which task is being checked
*/
int CHECK_IF_CIRCULAR(USER_GANTT task[], int taskID)
{
    int flag = 0;
    for(int i = 0; i < task[taskID].num_of_depend; i++)
    {
        int dependencyID = task[taskID].depend[i];

        for (int j = 0; j < task[dependencyID - 1].num_of_depend; j++)
        {
            // Check if there is tasks depend on each other
            if(task[dependencyID - 1].depend[j] == taskID + 1)
            {
                printf("CIRCULAR DEPENDENCY FOUND!\nTask %d: %s depends on task %d: %s and vice versa!\n", taskID + 1, task[taskID].taskName, dependencyID, task[dependencyID - 1].taskName);
                flag = 1;
            }
        }
    }

    if(flag == 0)
        printf("No circular dependency found\n");

    return 0;
}

/*This functions removes the newline char after calling fgets. It takes in:
-> The array where the string is to be stored
*/
void REMOVENL(char tempTaskName[])
{
    fgets(tempTaskName, MAX_STR_LEN, stdin);
    int length = strlen(tempTaskName);
    tempTaskName[length - 1] = '\0';

}

//This function creates the example gantt chart. It takes in the struct array variable
void EXAMPLE_GANTT(USER_GANTT tasks[])
{
    strcpy(tasks[0].taskName, "clean up writing space");
    tasks[0].startMonth = 1;
    tasks[0]. endMonth = 1;
    tasks[0].num_of_depend = 0;

    strcpy(tasks[1].taskName, "create general plot");
    tasks[1].startMonth = 2;
    tasks[1]. endMonth = 2;
    tasks[1].num_of_depend = 0;

    strcpy(tasks[2].taskName, "detail plot outline");
    tasks[2].startMonth = 3;
    tasks[2]. endMonth = 3;
    tasks[2].num_of_depend = 1;
    tasks[2].depend[0] = 2;

    strcpy(tasks[3].taskName, "research");
    tasks[3].startMonth = 3;
    tasks[3]. endMonth = 3;
    tasks[3].num_of_depend = 0;

    strcpy(tasks[4].taskName, "first draft");
    tasks[4].startMonth = 4;
    tasks[4]. endMonth = 6;
    tasks[4].num_of_depend = 2;
    tasks[4].depend[0] = 2;
    tasks[4].depend[1] = 3;

    strcpy(tasks[5].taskName, "editor review");
    tasks[5].startMonth = 6;
    tasks[5]. endMonth = 6;
    tasks[5].num_of_depend = 1;
    tasks[5].depend[0] = 5;

    strcpy(tasks[6].taskName, "second draft");
    tasks[6].startMonth = 7;
    tasks[6]. endMonth = 9;
    tasks[6].num_of_depend = 1;
    tasks[6].depend[0] = 6;

    strcpy(tasks[7].taskName, "find illustrator");
    tasks[7].startMonth = 9;
    tasks[7]. endMonth = 10;
    tasks[7].num_of_depend = 0;

    strcpy(tasks[8].taskName, "final revisions");
    tasks[8].startMonth = 10;
    tasks[8]. endMonth = 11;
    tasks[8].num_of_depend = 1;
    tasks[8].depend[0] = 7;

    strcpy(tasks[9].taskName, "negotiate with publisher");
    tasks[9].startMonth = 12;
    tasks[9]. endMonth = 12;
    tasks[9].num_of_depend = 0;

}



//This functions prints a thank-you message and art
void ASCII_ART(void)
{
    printf("\nThank you for using our Gantt generator!\n");
    printf("              _         _ \n");
    printf("  __   ___.--'_`.     .'_`--.___   __ \n");
    printf(" ( _`.'. -   'o` )   ( 'o`   - .`.'_ ) \n");
    printf(" _\\\\.'_'      _.-'     `-._      `_`./_ \n");
    printf("( \\`. )    //\\\\`         '/\\\\\\\\    ( .'/ ) \n");
    printf(" \\\\_`-'`---'\\\\\\\\__,       ,__//`---'`-'_/ \n");
    printf("  \\\\\\`        `-\\         /-'        '/ \n");
    printf("   `                               '   \n");
}

