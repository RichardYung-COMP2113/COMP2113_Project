#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//function declaration
char ** createGrid(int h, int w) ;
int ** createCrates(int n, int h, int w) ;
void printGrid(char **grid, int h, int w, int signal) ;
void showCratesOnGrid(char **grid, int **crates, int n);
bool isValidMove(int x, int y, int h, int w) ;
int distance_between_sonar_and_crates(char ** grid, int ** crates, int n, int x, int y);
void placeSonar(char ** grid, int h, int w, int ** crates, int number_of_crates, int &remaining_crates, int &remaining_sonars, int &signal) ;
void exitGame(char ** grid, int w, int ** crates);
void updateGrid(char ** grid, int h, int w, int ** crates, int crates_number);
