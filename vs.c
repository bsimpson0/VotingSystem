#include "vs.h"

voteDatabase *initDatabase() {
    voteDatabase *database;
    database = malloc(sizeof(voteDatabase));
    if(!database) {
        puts("error: couldn't allocate memory initDatabase() 1");
        return NULL;
    }

    database->peopleDB = malloc(sizeof(person));
    if(!database->peopleDB) {
        puts("error: couldn't allocate memory initDatabase() 2");
    }
    database->size = 0;
    return database;    
}

person *initNewPerson() {
    person *newPerson = NULL;
    newPerson = malloc(sizeof(person));
    if(!newPerson) {
        //malloc fail check
        puts("error: couldn't allocate memory initNewPerson()");
        return NULL;
    }
    newPerson->id = 0;
    newPerson->vote = 0;
    return newPerson;
}

void setCandidates(char *candidate1, char *candidate2, voteDatabase *database) {
    strcpy(database->c.candidate1, candidate1);
    strcpy(database->c.candidate2, candidate2);
}

void *updateDatabase(voteDatabase *database, person *newPerson) {
    database->peopleDB[database->size] = *newPerson;
    database->size++;
    return NULL;
}

void mainMenu(voteDatabase *database) {
    puts("\n*** VOTE MACHINE MAIN MENU ***");
    puts("Hello, what would you like to do?");
    puts("0.) Exit Program");
    puts("1.) Register to Vote");
    puts("2.) Vote in the Election");
    puts("3.) Check Your Vote");
    puts("4.) Check Total Votes");
    int s1 = -1;
    fflush(stdin);
    scanf("%d", &s1);
    fflush(stdin);
    if(s1 == 0) {
        puts("\nExiting Program");
        return;
    }
    if(s1 == 1) {
        registerToVote(database);
    }
    else if(s1 == 2) {
        vote(database);
    }
    else if(s1 == 3) {
        checkVote(database);
    }
    else if(s1 == 4) {
        checkTotal(database);
    }
    else {
        puts("\n");
        mainMenu(database);
    }
}

void *registerToVote(voteDatabase *database) {
    person *newPerson = NULL;
    newPerson = initNewPerson();
    int newID;
    char newPass[20];

    puts("\n*** REGISTER TO VOTE MENU ***");
    puts("Enter ID");
    scanf("%d", &newID);
    fflush(stdin); //clears stdin
    puts("Enter Password:");
    fgets(newPass, 20, stdin); //20 character password limit
    fflush(stdin);

    newPerson->id = newID;
    strcpy(newPerson->password, newPass);

    updateDatabase(database, newPerson);

    puts("\nCongrats, You're Now Registerd to Vote\n");
    mainMenu(database);
    return NULL;
}

void *vote(voteDatabase *database) {
    puts("\n*** VOTE SCREEN ***");
    int id;
    char pass[20];

    puts("Enter ID:");
    scanf("%d", &id);
    for(int i = 0; i < database->size; i++) {
        if(id == database->peopleDB[i].id) {
            puts("Enter Password:");
            fflush(stdin);
            fgets(pass, 20, stdin);
            if(strcmp(pass, database->peopleDB[i].password) == 0) {
                int vote;
                puts("\n*** CANDIDATES ***");
                puts("0.) Go Back To Main Menu");
                //puts("1.) Blake Simpson");
                printf("1.) %s\n", database->c.candidate1);
                //puts("2.) Joe Linville");
                printf("2.) %s\n", database->c.candidate2);
                fflush(stdin);
                scanf("%d", &vote);
                if(vote == 0) {
                    mainMenu(database);
                }
                else if(vote == 1) {
                    database->peopleDB[i].vote = 1;
                    printf("\nCongrats, You Voted For %s", database->c.candidate1);
                }
                else if(vote == 2) {
                    database->peopleDB[i].vote = 2;
                    printf("\nCongrats, You Voted For %s", database->c.candidate2);
                }
                else {
                    puts("error: couldn't save vote");
                }
            }
            else {
                puts("error: incorrect password");
                mainMenu(database);
            }
        }
    }

    fflush(stdin);
    mainMenu(database);
    return NULL;
}

void *checkVote(voteDatabase *database) {
    int id;
    char pass[20];
    puts("Enter ID#:");
    fflush(stdin);
    scanf("%d", &id);
    for(int i = 0; i < database->size; i++) {
        if(id == database->peopleDB[i].id) {
            puts("Enter Password:");
            fflush(stdin);
            fgets(pass, 20, stdin);
            if(strcmp(pass, database->peopleDB[i].password) == 0) {
                if(database->peopleDB[i].vote == 1) {
                    printf("\nYou Voted For: %s\n", database->c.candidate1);
                }
                else if(database->peopleDB[i].vote == 2) {
                    printf("\nYou Voted For: %s\n", database->c.candidate2);
                }
                else {
                    puts("\nYou Haven't Voted Yet!\n");
                }
            }
        }
    }
    mainMenu(database);
    return NULL;
}

void *checkTotal(voteDatabase *database) {
    int c1 = 0;
    int c2 = 0;
    
    for(int i = 0; i < database->size; i++) {
        if(database->peopleDB[i].vote == 1) {
            c1++;
        }
        else if(database->peopleDB[i].vote == 2) {
            c2++;
        }
        else {
            continue;
        }
    }
    puts("\n*** TOTAL VOTES ***");
    printf("%s: %d\n", database->c.candidate1, c1);
    printf("%s: %d\n", database->c.candidate2, c2);

    mainMenu(database);
    return NULL;
}

void *freeDB(voteDatabase *database) {
    free(database->peopleDB);
    free(database);
    return NULL;
}