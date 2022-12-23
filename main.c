#include "vs.h"

int main() {
    voteDatabase *database;
    database = initDatabase();

    //ENTER ELECTION CANDIDATES IN QUOTES
    char candidate1[20] = " ";
    char candidate2[20] = " ";

    setCandidates(candidate1, candidate2, database);

    mainMenu(database);

    freeDB(database);

    return 0;
}