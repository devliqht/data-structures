// You are tasked to find and delete the guest from the tableList if they exist.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TABLES 9

typedef struct {
	int guestID;
	char guestName[16];
} Guest;

// I have renamed this from tableNode into guestNode since from the original problem it was tableNode.
// That is partially incorrect since each TABLE has GUESTS, so the nodes of the Table are
// guests, not Tables themselves.
typedef struct guestNode {
	Guest g;
	struct guestNode* next;
} guestNode, *guestList;

// Each table is a LINKED LIST of Guests. This structure contains a pointer to the first guest and a pointer to the last guest.
typedef struct {
	guestList front;
	guestList end;
} Table;

// There are in total 9 TABLES, with each table being a LINKED LIST of GUESTS.
typedef struct {
	Table tableRows[MAX_TABLES];
} TableArrangement;

// Given Functions
void initTableArrangement(TableArrangement*);
void addGuest(TableArrangement*, int, int, char*);
void displayTables(TableArrangement);

// Feel free to add any helper function.

void deleteGuests(int listOfIDs[], int toRemoveCount, TableArrangement* tables) {
   
}

int main(void) {
 	TableArrangement arrangement;
    initTableArrangement(&arrangement);

    addGuest(&arrangement, 0, 11, "Alice");
    addGuest(&arrangement, 0, 12, "Aaron");

    addGuest(&arrangement, 1, 19, "Bob");
    addGuest(&arrangement, 1, 21, "Bella");
    addGuest(&arrangement, 1, 43, "Ben");

    addGuest(&arrangement, 2, 9, "Charlie K.");
    addGuest(&arrangement, 2, 9, "Donald");

    addGuest(&arrangement, 3, 5, "Diana");
    addGuest(&arrangement, 3, 1, "David");

    addGuest(&arrangement, 5, 3, "Frank");

    addGuest(&arrangement, 7, 23, "Hannah");
    addGuest(&arrangement, 7, 15, "Harry");
    
    addGuest(&arrangement, 4, 76, "Discaya");
    addGuest(&arrangement, 4, 2, "Romualdez");
    addGuest(&arrangement, 4, 31, "Bongbong");

    displayTables(arrangement);
    int toRemove[3];
    for (int idx = 0; idx < 3; idx++) {
	    printf("Enter the ID you want to remove: ");
	    scanf("%d", &toRemove[idx]);
    }
    
    deleteGuests(toRemove, 3, &arrangement);
    
    displayTables(arrangement);
    
    
    return 0;
}

// Initialize an empty TableArrangement
void initTableArrangement(TableArrangement *arr) {
    for (int i = 0; i < MAX_TABLES; i++) {
        arr->tableRows[i].front = NULL;
        arr->tableRows[i].end = NULL;
    }
}

// Add a guest to a specific table
void addGuest(TableArrangement *arr, int tableIndex, int id, char *name) {
    if (tableIndex < 0 || tableIndex >= MAX_TABLES) return;

    guestNode *newNode = (guestNode *)malloc(sizeof(guestNode));
    newNode->g.guestID = id;
    strcpy(newNode->g.guestName, name);
    newNode->next = NULL;

    if (arr->tableRows[tableIndex].front == NULL) {
        arr->tableRows[tableIndex].front = newNode;
        arr->tableRows[tableIndex].end = newNode;
    } else {
        arr->tableRows[tableIndex].end->next = newNode;
        arr->tableRows[tableIndex].end = newNode;
    }
}

// Display all tables and guests
void displayTables(TableArrangement arr) {
    for (int i = 0; i < MAX_TABLES; i++) {
        printf("Table %d:", i + 1);
        guestList trav = arr.tableRows[i].front;
        if (trav == NULL) {
            printf("  [Empty]\n");
        }
        while (trav != NULL) {
            printf(" [%d] %s %s", trav->g.guestID, trav->g.guestName, ((trav->next != NULL) ? "->" : "\n"));
            trav = trav->next;
        }
    }
}