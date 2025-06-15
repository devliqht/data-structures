#include "../globals.h"

// As an example for ADT Lists, we define structure with an array
// that contains names of people.

typedef struct ADT_ListV1 {
    char *names[MAX_AMT];  // Array of string pointers
    int count;
} ADT_ListV1;

status_t initialize(ADT_ListV1* list);
status_t insertFirst(ADT_ListV1* list, char* val);
status_t insertLast(ADT_ListV1* list, char* val);
status_t removeFirst(ADT_ListV1* list);
status_t removeLast(ADT_ListV1* list);
status_t search(ADT_ListV1* list, char* name);
status_t searchAndRemove(ADT_ListV1* list, char* name);
status_t insertSorted(ADT_ListV1* list, char* val);
status_t printNames(ADT_ListV1 list);

int main(void) {
    ADT_ListV1 list;
    initialize(&list);
    printf("Enter 5 names: \n");
    for (int i = 0; i < 5; i++) {
        char* name = malloc(sizeof(char) * MAX_STR_LEN); // str length of 50
        scanf(" %[^\n]s", name);
        insertFirst(&list, name);
        free(name);
    }
    printNames(list);
    insertLast(&list, "bayot");
    printNames(list);


    return 0;
}

status_t initialize(ADT_ListV1* list) {
    list->count = 0;

    for (int i = 0; i < MAX_AMT; i++) {
        list->names[i] = (char*)malloc(sizeof(char) * MAX_STR_LEN);
    }

    return INITIALIZE_SUCCESS;
}

status_t printNames(ADT_ListV1 list) {
    if (list.count == 0 || list.count > MAX_AMT) return PRINT_ERROR;

    printf("\nNAMES:\n");
    for (int i = 0; i < list.count; i++) {
        printf("%s -> ", list.names[i]);
    }
    printf("NULL\n");
    return PRINT_SUCCESS;
}

status_t insertFirst(ADT_ListV1* list, char* val) {
    if (list->count >= MAX_AMT) {
        return INSERT_ERROR;
    }

    for (int i = list->count; i >= 0; i--) {
        strcpy(list->names[i+1], list->names[i]);
    }

    strcpy(list->names[0], val);
    list->count++;

    return INSERT_SUCCESS;
}


status_t insertLast(ADT_ListV1* list, char* val) {
    if (list->count >= MAX_AMT) {
        return INSERT_ERROR;
    }

    strcpy(list->names[list->count++], val);
    return INSERT_SUCCESS;
}