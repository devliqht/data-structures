#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define PERSONS 3

typedef struct {
    int id;
    char name[100];
    int earnings; // in millions
    float rating;
} Movie;

typedef struct {
    char name[30];
    int favorites[SIZE]; // 0 - didn't like the movie, 1 - liked the movie
} Person;

// Function prototypes
void displayMovies(Movie movies[]);
void displayFriendsSummary(Person f);
void displaySet(int set[], Movie movies[]);
void unionSet(int A[], int B[], int C[]);
void intersectionSet(int A[], int B[], int C[]);
void differenceSet(int A[], int B[], int C[]);
void analysis(Movie movies[], Person friends[]);
void preferences(Movie movies[], Person friends[]);

int main(void) {
    Movie movies[SIZE] = {
        {0, "Rogue One: A Star Wars Story", 1057, 7.6},
        {1, "The Amazing Spider-Man", 758, 6.3},
        {2, "Pirates of the Caribbean: The Curse of the Black Pearl", 654, 7.2},
        {3, "Avatar: The Way of Water", 2343, 8.1},
        {4, "Justice League", 661, 6.7},
        {5, "Furious 7", 1515, 7.5},
        {6, "Wicked", 752, 8.7},
        {7, "Beauty and the Beast", 1266, 8.2},
        {8, "The Lord of the Rings: The Two Towers", 938, 9.1},
        {9, "Kung Fu Panda 2", 665, 7.9},
        {10, "The Twilight Saga: New Moon", 711, 6.0},
        {11, "Ant-Man and the Wasp", 622, 7.2},
        {12, "Forrest Gump", 678, 9.8},
        {13, "Dune: Part Two", 714, 9.3},
        {14, "2012", 791, 7.6},
        {15, "Barbie", 1447, 8.0},
        {16, "Oppenheimer", 975, 9.1},
        {17, "The Hunger Games: Mockingjay - Part 1", 758, 7.6},
        {18, "Mission: Impossible - Fallout", 824, 7.5},
        {19, "Frozen", 1286, 7.2}
    };

    Person A = {"Hank Garrison",
        {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0}};
    Person B = {"Helen Bernard",
        {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1}};
    Person C = {"Lee Potter",
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0}};

    Person friends[PERSONS] = {A, B, C};

    printf("=== MY FRIENDS' FAVORITE FILMS! ===\n\n");
    displayMovies(movies);
    printf("\n");

    for (int i = 0; i < PERSONS; i++)
        displayFriendsSummary(friends[i]);

    printf("\n[WHAT DID THEY LIKE?]\n");
    preferences(movies, friends);

    printf("\n\n[FILM PREFERENCE ANALYSIS]\n");
    analysis(movies, friends);
}

// Function stubs (unchanged)
void displayMovies(Movie movies[]) {
    printf("ID | Movie Title | Earnings (M) | Rating\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d | %-55s | %4d | %.1f\n",
               movies[i].id,
               movies[i].name,
               movies[i].earnings,
               movies[i].rating);
    }
}

void displayFriendsSummary(Person f) {
    printf("Name: %s\n", f.name);
    printf("Favorites: { ");
    for (int i = 0; i < SIZE; i++)
        if (f.favorites[i] == 1)
            printf("%d ", i);
    printf("}\n");
}

void displaySet(int set[], Movie movies[]) {
    for (int i = 0; i < SIZE; i++) {
        if (set[i] == 1)
            printf("> %s\n", movies[i].name);
    }
    printf("\n");
}

void unionSet(int A[], int B[], int C[]) {
    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] | B[i];
    }
}

void intersectionSet(int A[], int B[], int C[]) {
    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] & B[i];
    }
}

void differenceSet(int A[], int B[], int C[]) {
    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] & ~B[i];
    }
}

void preferences(Movie movies[], Person friends[]) {
    printf("\nMovies at least one of them liked:\n");
    // Movies atleast one of them liked.
    // High-level logic: Check every movie to see their friends status if it's 1. 1 means liked.
    // If a movie already has 1, break the loop. No need to continue.
    for (int idx = 0; idx < SIZE; idx++) {
    	int movieLiked = 0;
    	for (int jdx = 0; jdx < PERSONS && movieLiked == 0; jdx++) { // Traverse the friends to see their prefeference to the movie.
     		// If atleast one of them is already 1, then that means the movie is liked atleast once.
     		if (friends[jdx].favorites[idx]) {
    			movieLiked = 1;
       		}
     	}
     	if (movieLiked >= 1) printf("> %s\n", movies[idx].name);
    }

    printf("\n\nMovies they all liked: \n");
    for (int idx = 0; idx < SIZE; idx++) {
    	int movieLiked = 0;
    	for (int jdx = 0; jdx < PERSONS; jdx++) { // Traverse the friends to see their prefeference to the movie.
     		// Increment movieLiked by 1 if their preference is 1.
     		if (friends[jdx].favorites[idx]) {
    			movieLiked += 1;
       		}
     	}
     	if (movieLiked == 3) printf("> %s\n", movies[idx].name); // All movies are liked.
    }

    printf("\n\nMovies at least two of them liked: \n");
    for (int idx = 0; idx < SIZE; idx++) {
    	int movieLiked = 0;
    	for (int jdx = 0; jdx < PERSONS; jdx++) { // Traverse the friends to see their prefeference to the movie.
     		// When movieLiked is 1 and the current person also likes the movie, the inner loop will stop. 
     		if (friends[jdx].favorites[idx]) {
    			movieLiked += 1;
       		}
     	}
     	if (movieLiked == 2) printf("> %s\n", movies[idx].name);
    }

    printf("\n\nMovies only one of them liked:\n");
    for (int idx = 0; idx < SIZE; idx++) {
    	int movieLiked = 0;
    	for (int jdx = 0; jdx < PERSONS; jdx++) { // Traverse the friends to see their prefeference to the movie.
     		// When movieLiked is 1 and the current person also likes the movie, the inner loop will stop. 
     		if (friends[jdx].favorites[idx]) {
    			movieLiked += 1;
       		}
     	}
     	if (movieLiked == 1) printf("> %s\n", movies[idx].name);
    }
}

void analysis(Movie movies[], Person friends[]) {

    // ---- Certified Fan Favorites ----
    printf("\n------ CERTIFIED FAN FAVORITES ------\n");
    printf("(At least 2 liked it, rating > 7, earnings > 800M)\n");

    for (int idx = 0; idx < SIZE; idx++) {
    	int fanFavorite = 0;
    	for (int jdx = 0; jdx < PERSONS; jdx++) { 
     		if (friends[jdx].favorites[idx]) {
    			fanFavorite += 1;
       		}
     	}
     	if (fanFavorite >= 2) {
      		if (movies[idx].rating > 7 && movies[idx].earnings > 800) {
        		printf("> %s\n", movies[idx].name);
        	}
      	}
    }

    // ---- Underrated Gems ----
    printf("\n------ UNDERRATED GEMS ------\n");
    printf("(At most 2 liked it, rating > 8.5, earnings < 750M)\n");

    for (int idx = 0; idx < SIZE; idx++) {
    	int underratedGem = 0;
    	for (int jdx = 0; jdx < PERSONS; jdx++) { 
     		if (friends[jdx].favorites[idx]) {
    			underratedGem += 1;
       		}
     	}
     	if (underratedGem <= 2) {
      		if (movies[idx].rating > 8.5 && movies[idx].earnings < 750) {
        		printf("> %s\n", movies[idx].name);
        	}
      	}
    }

}
