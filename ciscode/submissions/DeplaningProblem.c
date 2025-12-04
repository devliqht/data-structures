// You are tasked to efficient deplane passengers from a plane. Given:
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PASSENGERS 3
#define MAX_ROWS 8

typedef struct {
	char passengerName[24];
} Passenger;

typedef struct {
	Passenger passengers[MAX_PASSENGERS];
	int top;
} Group;

typedef struct {
	Group ABC; // Stack v1 where A bottom and C is top
	Group DEF; // Stack v2 where F is bottom and D is top
} Row;

typedef struct {
	Row planeRows[MAX_ROWS];
} BoardingList;

