#include "todo.h"

static Task *first = NULL;
static Task *last = NULL;

void add_new_item() {
    char name[20];
    printf("Enter the name of the new task: ");
    getchar();
    if (fgets(name, sizeof(name), stdin) != NULL) {
        name[strcspn(name, "\n")] = '\0';
    }

    Task *new_task = (Task *)malloc(sizeof(Task));

    strncpy(new_task->name, name, 19);
    new_task->name[19] = '\0';
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
        printf("\033[1;33mTodo list is empty!\033[0m\n");
        return;
    }

    printf("\n\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
    printf("\033[1;36m           📝 TODO LIST 📝\033[0m\n");
    printf("\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
    int number = 1;
    for (Task *index = first; index != NULL; index = index->next, number++) {
        if (index->is_done) {
            printf("\033[1;32m✓\033[0m \033[90m%d. %s\033[0m \033[1;32m[DONE]\033[0m\n", number, index->name);
        } else {
            printf("\033[1;31m○\033[0m \033[1;37m%d. %s\033[0m \033[1;33m[TODO]\033[0m\n", number, index->name);
        }
    }
    printf("\033[1;36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
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

void remove_item() {
    if (first == NULL) {
        printf("Todo list is empty!\n");
        return;
    }

    print_tasks();
    printf("Enter the number of the task to remove: ");
    int task_number;
    scanf("%d", &task_number);

    int current_number = 1;
    for (Task *index = first; index != NULL; index = index->next, current_number++) {
        if (current_number == task_number) {
            if (index->before != NULL) {
                index->before->next = index->next;
            } else {
                first = index->next;
            }
            if (index->next != NULL) {
                index->next->before = index->before;
            } else {
                last = index->before;
            }
            printf("Task '%s' removed from the list.\n", index->name);
            free(index);
            return;
        }
    }
}

void save_tasks_to_file(const char *filename) {
    printf("Saving tasks to file: %s\n", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    cJSON *json_array = cJSON_CreateArray();
    for (Task *index = first; index != NULL; index = index->next) {
        cJSON *json_task = cJSON_CreateObject();
        cJSON_AddStringToObject(json_task, "name", index->name);
        cJSON_AddBoolToObject(json_task, "is_done", index->is_done);
        cJSON_AddItemToArray(json_array, json_task);
    }
    char *json_string = cJSON_Print(json_array);
    fprintf(file, "%s", json_string);
    free(json_string);
    cJSON_Delete(json_array);
    fclose(file);
}

void load_tasks_from_file(const char *filename) {
    printf("Loading tasks from file: %s\n", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing todo list found. Starting a new one.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    cJSON *json_array = cJSON_Parse(data);
    free(data);
    if (json_array == NULL) {
        printf("Error parsing todo list file!\n");
        return;
    }

    int array_size = cJSON_GetArraySize(json_array);
    for (int i = 0; i < array_size; i++) {
        cJSON *json_task = cJSON_GetArrayItem(json_array, i);
        const char *name = cJSON_GetObjectItem(json_task, "name")->valuestring;
        cJSON_bool is_done = cJSON_GetObjectItem(json_task, "is_done")->valueint;

        Task *new_task = (Task *)malloc(sizeof(Task));
        strncpy(new_task->name, name, 20);
        new_task->is_done = is_done;
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
    cJSON_Delete(json_array);
}

int main() {
    int option;

    do {
        printf("\nTodo List Menu\n");
        printf("1. Show todo list\n");
        printf("2. Add the new item to todo list\n");
        printf("3. Remove an item from todo list\n");
        printf("4. Done an item from todo list\n");
        printf("5. Save todo list to file\n");
        printf("6. Load todo list from file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &option) != 1){
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        switch (option) {
            case 1:
                print_tasks();
                break;
            case 2:
                add_new_item();
                break;
            case 3:
                remove_item();
                break;
            case 4:
                done();
                break;
            case 5:
                {
                    char filename[50] = "todo.json";
                    printf("Enter filename or press Enter for default (todo.json): ");
                    getchar();
                    char c = getchar();
                    if (c != '\n') {
                        ungetc(c, stdin);
                        scanf("%s", filename);
                    }
                    save_tasks_to_file(filename);
                }
                break;
            case 6:
                {
                    char filename[50] = "todo.json";
                    printf("Enter filename or press Enter for default (todo.json): ");
                    getchar();
                    char c = getchar();
                    if (c != '\n') {
                        ungetc(c, stdin);
                        scanf("%s", filename);
                    }
                    load_tasks_from_file(filename);
                }
                break;
            case 0:
                if (first != NULL) {
                    printf("Do you want to save your todo list before exiting? (y/n): ");
                    char save_choice;
                    getchar();
                    scanf("%c", &save_choice);
                    if (save_choice == 'y' || save_choice == 'Y') {
                        char filename[50] = "todo.json";
                        printf("Enter filename or press Enter for default (todo.json): ");
                        getchar();
                        char c = getchar();
                        if (c != '\n') {
                            ungetc(c, stdin);
                            scanf("%s", filename);
                        }
                        save_tasks_to_file(filename);
                    }
                }
                printf("Exit\n");
                break;
            default:
                printf("Error!\n");
        }
   } while (option != 0);

   return 0;
}
v
