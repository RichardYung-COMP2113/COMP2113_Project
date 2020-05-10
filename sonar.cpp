#include <iostream>
#include <ctime>
#include <cstdlib>
#include "sonar.h"

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

// the main function
int main() {

	int height, width, number_of_crates, remaining_number_of_crates, number_of_sonars, signal;

	cout << "Please insert the height and width of the grid: ";
	cin >> height >> width;
	char ** grid = createGrid(height, width);
	int ** crates;

	do{
		cout << "Please insert the number of the sonars: ";
		cin >> number_of_sonars; 
	}while(number_of_sonars <= 0);

	int number_of_moves = number_of_sonars;
	
	do{
		cout << "Please insert the number of the crates: ";
		cin >> number_of_crates; 
	}while(number_of_crates <= 0);

	remaining_number_of_crates = number_of_crates;
	crates = createCrates(number_of_crates, height, width);
	printGrid(grid, height, width, 1);

	while (1) {
		while (number_of_sonars > 0 && remaining_number_of_crates > 0) {
			printGrid(grid, height, width, signal);
			signal = 0;
			cout << "You have " << number_of_sonars << " sonars";
			cout << " and there are " << remaining_number_of_crates << " hidden treasure crates."  << endl;

			placeSonar(grid, height, width, crates, number_of_crates, remaining_number_of_crates, number_of_sonars, signal);
			
		}
		if (number_of_sonars == 0 && remaining_number_of_crates > 0){
			printGrid(grid, height, width, signal);
			cout << "Sorry, you used up all your sonars. There are still treasure crates remain under the sea." << endl;
			cout << "GAME OVER" << endl;
			exitGame(grid, width, crates);
		}
		else if (remaining_number_of_crates == 0) {
			printGrid(grid, height, width, signal);
			cout << "You have found all the treasure crates. Congratulations!" << endl;
			cout << "YOU WIN" << endl;
			exitGame(grid, width, crates);
		}

		break;

	}
	
	exitGame(grid, height, crates);

	return 0;
}

// create a 2D dynamic array to store the grids
// take two integer, h and w, as the height and width of the grids
// return a pointer to pointer to char
char ** createGrid(int h, int w) {
	char ** grid = 0;
	grid = new char * [h];

	for (int i = 0; i < h; ++i) {
		grid[i] = new char[w];
		for (int j = 0; j < w; ++j) {
			grid[i][j] = '~';
		}
	}

	return grid;
}

// create a N * 2 dynamic array to store the x y coordinates of the hidden crates.
// the x y coordinates are created randomly.x
// take integer n, h, and w as the number of crates, the height and the width of the grids
// return a pointer to pointer to int
int ** createCrates(int n, int h, int w) {

	int ** crates = new int * [n];

	srand(time(NULL));

	for (int i = 0; i < n; ++i) {
		crates[i] = new int[2];

		crates[i][0] = rand() % h;
		crates[i][1] = rand() % w;
	}

	return crates;
}

// print the 2d grid
// receive the grid and its height and width as parameters, 
// the signal parameter is used as a means to communicate with other functions
// special messages are displayed with different signal
void printGrid(char **grid, int h, int w, int signal) {
	system("clear");
	// print the tens digit before the numeric header row
	cout << "    ";
	for (int i = 0; i < w; ++i) {
		if (i % 10 == 0 && i != 0) {
			cout << i / 10 << " ";
		}
		else {
			cout << "  ";
		}
	}
	cout << endl;

	// print the numeric header row
	cout << "    ";
	for (int i = 0; i < w; ++i) {
		cout << i % 10 << " " ;
	}
	cout << endl;
	for (int i = 0; i < w * 2 + 3; ++i) {
		cout << "=";
	}
	cout << endl;

	// print the grid
	for (int i = 0; i < h; ++i) {
		if (i < 10)
			cout << " " << i << "║ ";
		else 
			cout << i << "║ ";
		for (int j = 0; j < w; ++j) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	
	if (signal == 1) {
		cout << "Treasure crates are out of range." << endl;
	}
	else if (signal == 2)  {
		cout << "You found a crate. Good job." << endl;
	}
	else if (signal == -1)  {
		cout << "Invalid values." << endl;
	}
}

// This is a temporary function simply for debugging
// show the crates on the grid
void showCratesOnGrid(char **grid, int **crates, int n) {
	for (int i = 0; i < n; i++) {
		int x = crates[i][1];
		int y = crates[i][0];
		grid[x][y] = 'C';
	}
		
}

// validate the input of x y coordinates are within range
// return true if yes, false if no
bool isValidMove(int x, int y, int h, int w) {

	if (x >= 0 && x < w && y >= 0 && y < h )
		return true;
	else
		return false;
}

// free the memory from the dynamic arrays created
// receive the grid and its width, as well as the crates
// grid and crates are the dynamic arrays.
void exitGame(char ** grid, int w, int ** crates){
	// cleanup
	// the grid
	for (int i = 0; i < w; ++i){
		delete[] grid[i];
	}
	delete[] grid;
	// the array that stores the x y coordinates of the crates.
	for (int i = 0; i < 2; ++i) {
		delete[] crates[i];
	}
	delete[] crates;

	exit(0);
}

// ask for x y coordinates of sonars and then place them on the grid
// receive several parameters such as the grid and its height and width;
// crates and its number. 
// I used the pass by reference for the parameters "remaining_crates" and "remaining_sonars" because I need to modify their values.
// the "signal" variable is used to indicate what kind of message that the printGrid function needs to display
void placeSonar(char ** grid, int h, int w, int ** crates, int number_of_crates, int &remaining_crates, int &remaining_sonars, int &signal) {
	int x, y, distance;
	cout << "Please enter the x y coordinates of your next sonar: (enter -1 to quit)" << endl; 

	cin >> x;

	if (x == -1) {
		cout << "Thank you for playing. Bye Bye.";
		exitGame(grid, w, crates);
	}

	cin >> y;

	if (y == -1) {
		cout << "Thank you for playing. Bye Bye.";
		exitGame(grid, w, crates);
	}

	if (isValidMove(x, y, h, w)) {
		// if the sonar "hit" the crate
		if (distance_between_sonar_and_crates(grid, crates, number_of_crates, x, y) == 0) {
			grid[y][x] = 'X';
			remaining_sonars--;
			remaining_crates--;
			updateGrid(grid, h, w, crates, number_of_crates);
			signal = 2;
		}
		// if the crate is out of range of the sonar
		else if (distance_between_sonar_and_crates(grid, crates, number_of_crates, x, y) < 10) {
			grid[y][x] = distance_between_sonar_and_crates(grid, crates, number_of_crates, x, y) + '0';
			remaining_sonars--;
		}
		else{
			// if the distance is equal to or larger than 10
			grid[y][x] = 'o';
			remaining_sonars--;
			signal = 1;
		}
	}

	else {
		signal = -1;
	}

}

// calculate the distance between a sonar and any crates nearby.
// receive 2D arrays: grid and crates, also their numbers and the x y coordinates
// output the distance between the sonar and the crates
int distance_between_sonar_and_crates(char ** grid, int ** crates, int n, int x, int y) {
	int distance;
	int minDistance = 999;
	// go through every crate stored in the crates array.
	for (int i = 0; i < n; ++i) {
		// ignore the arrays with negative values.
		if (crates[i][0] < 0 && crates[i][1] < 0) {
			continue;
		}
		// calculate the absolute distance between x y coordinates.
		int x_distance = abs(crates[i][1] - x);
		int y_distance = abs(crates[i][0] - y);
		if (x_distance > y_distance) {
			distance = x_distance;
		}
		else {
			distance = y_distance;
		}

		if (distance < minDistance) {
			minDistance = distance;
		}

		if (minDistance == 0) {
			// change the values of the array to negative numbers 
			// so that the next time the function will ignore this element.
			crates[i][0] = -1;
			crates[i][1] = -1;
			return minDistance;
		}
	}
	return minDistance;
}

// update the grid whenever a crate is found.
// all the distances of the existing sonars needs to re-calculate
// receive the grid and its height and width as inputs
// also the crates and its number
void updateGrid(char ** grid, int h, int w, int ** crates, int crates_number) {
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			// Only the active sonars, i.e. the number shown on the grid.
			if (grid[i][j] != '~' && grid[i][j] != 'o' && grid[i][j] != 'X' ) {
				int distance = distance_between_sonar_and_crates(grid, crates, crates_number, j, i);
				if (distance >= 10) {
					grid[i][j] = 'o';
				}
				else{
					grid[i][j] = distance + '0' ;
				}
			}
		}

	}

}
