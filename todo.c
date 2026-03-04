#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define FILENAME "tasks.txt"

typedef struct {
    char *description;
    int completed;
} Task;

typedef struct {
    Task *tasks;
    int size;
    int capacity;
} TodoList;

/* ---------- Function Prototypes ---------- */
void initList(TodoList *list);
void freeList(TodoList *list);
void resizeList(TodoList *list);
void addTask(TodoList *list, const char *desc);
void deleteTask(TodoList *list, int index);
void markComplete(TodoList *list, int index);
void printTasks(const TodoList *list);
void saveToFile(const TodoList *list);
void loadFromFile(TodoList *list);
void menu();

/* ---------- Implementation ---------- */

void initList(TodoList *list) {
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->tasks = malloc(sizeof(Task) * list->capacity);
    if (!list->tasks) {
        perror("Memory allocation failed");
        exit(1);
    }
}

void resizeList(TodoList *list) {
    list->capacity *= 2;
    Task *newTasks = realloc(list->tasks, sizeof(Task) * list->capacity);
    if (!newTasks) {
        perror("Reallocation failed");
        exit(1);
    }
    list->tasks = newTasks;
}

void addTask(TodoList *list, const char *desc) {
    if (list->size >= list->capacity) {
        resizeList(list);
    }

    list->tasks[list->size].description = malloc(strlen(desc) + 1);
    if (!list->tasks[list->size].description) {
        perror("Memory allocation failed");
        exit(1);
    }

    strcpy(list->tasks[list->size].description, desc);
    list->tasks[list->size].completed = 0;
    list->size++;
}

void deleteTask(TodoList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid task number.\n");
        return;
    }

    free(list->tasks[index].description);

    for (int i = index; i < list->size - 1; i++) {
        list->tasks[i] = list->tasks[i + 1];
    }

    list->size--;
}

void markComplete(TodoList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid task number.\n");
        return;
    }
    list->tasks[index].completed = 1;
}

void printTasks(const TodoList *list) {
    if (list->size == 0) {
        printf("No tasks found.\n");
        return;
    }

    for (int i = 0; i < list->size; i++) {
        printf("%d. [%c] %s\n",
               i + 1,
               list->tasks[i].completed ? 'X' : ' ',
               list->tasks[i].description);
    }
}

void saveToFile(const TodoList *list) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        perror("Could not open file for saving");
        return;
    }

    for (int i = 0; i < list->size; i++) {
        fprintf(file, "%d|%s\n",
                list->tasks[i].completed,
                list->tasks[i].description);
    }

    fclose(file);
}

void loadFromFile(TodoList *list) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;  // No file yet

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        char *newline = strchr(buffer, '\n');
        if (newline) *newline = '\0';

        char *token = strtok(buffer, "|");
        int completed = atoi(token);

        token = strtok(NULL, "|");
        if (token) {
            addTask(list, token);
            list->tasks[list->size - 1].completed = completed;
        }
    }

    fclose(file);
}

void freeList(TodoList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->tasks[i].description);
    }
    free(list->tasks);
}

void menu() {
    printf("\n--- TODO APP ---\n");
    printf("1. Add Task\n");
    printf("2. Delete Task\n");
    printf("3. Mark Complete\n");
    printf("4. Show Tasks\n");
    printf("5. Exit\n");
    printf("Choose: ");
}

int main() {
    TodoList list;
    initList(&list);
    loadFromFile(&list);

    int choice;
    char buffer[1024];

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                addTask(&list, buffer);
                break;

            case 2:
                printTasks(&list);
                printf("Task number to delete: ");
                scanf("%d", &choice);
                getchar();
                deleteTask(&list, choice - 1);
                break;

            case 3:
                printTasks(&list);
                printf("Task number to mark complete: ");
                scanf("%d", &choice);
                getchar();
                markComplete(&list, choice - 1);
                break;

            case 4:
                printTasks(&list);
                break;

            case 5:
                saveToFile(&list);
                freeList(&list);
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
