#include "GanttFunctions.h"
int main()
{
    int userChoice, numTasks;
    int i, ifEdit;
    char tempTaskName[MAX_STR_LEN];
    char GanttName[MAX_STR_LEN];

    printf("Welcome to the Gantt Chart Generator\n");
    beginning:
    printf("Would you like to see an example or create your own Gantt chart from scratch?\nEnter 1 for example or enter 2 to create your own\n");
    scanf("%d", &userChoice);
    getchar();

    // test example
    if(userChoice == 1)
    {
        USER_GANTT tasks[10];
        EXAMPLE_GANTT(tasks);
        printf("\nWrite and Publish a Book\n");
        PRINT_GANTT(tasks, 10);
        goto beginning;
    }

    //user's gantt
    else if(userChoice == 2)
    {
        printf("What is the overall goal of your Gantt Chart?\n");
        REMOVENL(GanttName);

        number_of_tasks:
        printf("How many tasks would you like to add? (1 - 10)\n");
        scanf("%d", &numTasks);
        getchar();

        if(numTasks > 10 || numTasks < 1 )
        {
            ERROR();
            goto number_of_tasks;
        }

        //creating gantt
        USER_GANTT user[numTasks];
        for(i = 0;i < numTasks;i++)
        {
            ifEdit = 0;
            MAKE_GANTT(user, i, ifEdit);
        }
        
        printf("\n%s\n", GanttName);
        PRINT_GANTT(user, numTasks);

        char choice[MAX_STR_LEN], newTask[MAX_STR_LEN];
        edit_test_quit:
        printf("If you wish to edit the Gantt please type ''edit''  /  If you wish to run a test, type ''test''  /  exit, type ''quit'' and then press enter to execute your option.\n");
        scanf("%s", &choice);
        getchar();

        if((strcmp(choice, "edit") == 0))
        {
            printf("Enter 1 if you would like to add another task or\nEnter 2 to edit an existing task?\n");
            scanf("%d", &userChoice);
            getchar();
            if(userChoice == 1)
            {
                if(numTasks != 10)
                {
                    ifEdit = 0;
                    MAKE_GANTT(user, i, ifEdit);
                    i++;
                    numTasks++;
                    goto print;
                }
                
                else
                    printf("You already have ten tasks");

                goto edit_test_quit;
            }
            
            else if(userChoice == 2) {
                changingTask:
                printf("Please enter the task name you wish to change exactly\n");
                REMOVENL(tempTaskName);
                strcpy(newTask, tempTaskName);

                //comparing user input to task names
                for (int y = 0; y < numTasks; y++) {
                    if (strcmp(newTask, user[y].taskName) == 0) {
                        ifEdit = 1;
                        MAKE_GANTT(user, y, ifEdit);
                        break;
                    }

                    if (y == numTasks - 1 && strcmp(newTask, user[y].taskName) != 0)
                        printf("This task does not exist\n");

                }
                
                errorTask:
                printf("Change another task?\n");
                printf("Enter 1 for yes and 2 for no\n");
                scanf("%d", &userChoice);
                getchar();

                if (userChoice == 1)
                    goto changingTask;
                
                else if (userChoice == 2) {
                    print:
                    system(SCREEN_CLEAR);
                    printf("\n%s\n", GanttName);
                    PRINT_GANTT(user, numTasks);
                } else {
                    ERROR();
                    goto errorTask;
                }

            }

            else
                ERROR();

        }

        else if((strcmp(choice, "test") == 0))
        {
            printf("Enter the name of the task you want to test\n");
            REMOVENL(tempTaskName);
            strcpy(newTask, tempTaskName);

            for(int y = 0; y < numTasks; y++)
            {
                //comparing user input to task names
                if(strcmp(newTask, user[y].taskName) == 0)
                {
                    CHECK_IF_CIRCULAR(user, y);
                    break;
                }


                if(y == numTasks - 1 && strcmp(newTask, user[y].taskName) != 0)
                    printf("This task does not exist\n");

            }

        }

        else if((strcmp(choice, "quit") == 0))
        {
            ASCII_ART();
            return 0;
        }

        else
            ERROR();

        goto edit_test_quit;
    }

    else
    {
        ERROR();
        goto beginning;
    }

}

