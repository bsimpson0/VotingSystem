#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct candidatesStruct {
    char candidate1[20];
    char candidate2[20];
}candidates;

typedef struct personStruct {
    int id;
    char password[20];
    int vote;
}person;

typedef struct databaseStruct {
    person *peopleDB;
    candidates c;
    int size;
}voteDatabase;

voteDatabase *initDatabase();

person *initNewPerson();

void setCandidates(char *candidate1, char *candidate2, voteDatabase *database);

void mainMenu(voteDatabase *database);

void *registerToVote(voteDatabase *database);

void *vote(voteDatabase *database);

void *checkVote(voteDatabase *database);

void *checkTotal(voteDatabase *database);

void *freeDB(voteDatabase *database);