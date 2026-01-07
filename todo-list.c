#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Task
{
    char name[20];
    bool is_done;
    struct Task *next;
    struct Task *before;
} Task;

static Task *first = NULL;
static Task *last = NULL;

void add_new_item() {
    char name[20];
    printf("Enter the name of the new task: ");
    scanf("%s", name);

    Task *new_task = (Task *)malloc(sizeof(Task));

    strncpy(new_task->name, name, 20);
    new_task->is_done = false;
    new_task->next = NULL;

    if (first == NULL) {
        first = new_task;
        last = new_task;
        new_task->before = NULL;
    } else {
        last->next = new_task;
        new_task->before = last;
        last = new_task;
    }
}

void print_tasks() {
    if (first == NULL) {
        printf("Todo list is empty!\n");
        return;
    }

    printf("\nTodo list:\n");
    int number = 1;
    for (Task *index = first; index != NULL; index = index->next, number++) {
        if (index->is_done) {
            printf("%d. name: %s, status: done\n", number , index->name);
        } else {
            printf("%d. name: %s, status: not done\n", number , index->name);
        }
    }
}

void done() {
    if (first == NULL) {
        printf("Todo list is empty!\n");
        return;
    }

    print_tasks();
    printf("Enter the number of the task to mark as done: ");
    int task_number;
    scanf("%d", &task_number);

    int current_number = 1;
    for (Task *index = first; index != NULL; index = index->next, current_number++) {
        if (current_number == task_number) {
            index->is_done = true;
            printf("Task '%s' marked as done.\n", index->name);
            return;
        }
    }
}

int main() {
    int option;

    do {
        printf("\nTodo List Menu\n");
        printf("1. Show todo list\n");
        printf("2. Add the new item to todo list\n");
        printf("3. Done an item from todo list\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &option) != 1){
            printf("Invalid input! Please enter a number.\n");
            break;
        }

        switch (option) {
            case 1:
                print_tasks();
                break;
            case 2:
                add_new_item();
                break;
            case 3:
                done();
                break;
            case 0:
                printf("Exit\n");
                break;
            default:
                printf("Error!\n");
        }
   } while (option != 0);

   return 0;
}
