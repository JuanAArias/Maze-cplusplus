// main.cpp
// Test functions for Maze and Creature classes
// Authors: Yusuf Pisan & Juan Arias

#include <string>
#include "creature.h"

// Global constants for easier change of file names
const char FILE1[] {"maze1.txt"};
const char FILE2[] {"maze2.txt"};

// Prints info of location of row and column in given Maze
void PrintLocationInfo(const Maze& maze, int row, int col) {

	std::cout << maze << std::endl << std::boolalpha
	<< "["  << row << ", " << col << "]"		<< std::endl
	<< "wall?    " << maze.IsWall(row, col)		<< std::endl
	<< "clear?   " << maze.IsClear(row, col)	<< std::endl
	<< "path?    " << maze.IsPath(row, col)		<< std::endl
	<< "visited? " << maze.IsVisited(row, col)  << std::endl
	<< "exit?    " << maze.IsExit(row, col)		<< std::endl << std::endl;

}

// Tests Mazes functions
void MazeTests() {

	// Construct Maze with test file
	Maze maze1(FILE1);

	// Test public functions of Maze
	PrintLocationInfo(maze1, 0, 0);
	PrintLocationInfo(maze1, 0, 13);
	PrintLocationInfo(maze1, 1, 13);
	PrintLocationInfo(maze1, 1, 14);
}

void CreatureMazeTest(Maze* const maze, Creature* const creat) {
	
	// Print the Creature to the console
	std::cout << *creat << std::endl;

	// Solve maze
	std::cout << creat->Solve(*maze) << std::endl;

	// Print maze to see visited spots and path
	std::cout << *maze << std::endl;
}

// Tests maze in test.txt file from each open area
void Maze1Test() {

	// Construct Maze with test file 1
	Maze maze1(FILE1);

	// Copy constructor
	Maze maze2(maze1), maze3(maze1);

	// Construct Creature at valid location in maze1 and test
	Creature c1(0, 13);
	CreatureMazeTest(&maze1, &c1);

	// Construct Creature at valid location in maze2 and test
	Creature c2(1, 13);
	CreatureMazeTest(&maze2, &c2);

	// Assignment operator overload
	maze1 = maze2 = maze3;

	// Construct Creature at valid location in maze1 and test
	Creature c3(3, 13);
	CreatureMazeTest(&maze1, &c3);

	// Construct Creature at valid location in maze3 and test
	Creature c4(3, 9);
	CreatureMazeTest(&maze3, &c4);

	// Get mazes blank again
	maze1 = maze3 = maze2;

	// Construct Creature at valid location in maze2 and test
	Creature c5(8, 9);
	CreatureMazeTest(&maze2, &c5);

	// Construct Creature at valid location in maze3 and test
	Creature c6(8, 6);
	CreatureMazeTest(&maze3, &c6);

	// Get mazes blank again
	maze2 = maze3 = maze1;

	// Construct Creature at valid location in maze2 and test
	Creature c7(3, 2);
	CreatureMazeTest(&maze2, &c7);

	// Construct Creature at valid location in maze1 and test
	Creature c8(5, 12);
	CreatureMazeTest(&maze1, &c8);

	// Construct Creature at valid location in maze3 and test
	Creature c9(1, 3);
	CreatureMazeTest(&maze3, &c9);
}

// Tests maze in test2.txt file from each open area
void Maze2Test() {
	
	// Construct Maze with test2 file
	Maze maze1(FILE2);

	// Copy constructor
	Maze maze2(maze1), maze3(maze1), maze4(maze1);

	// Construct Creature at valid location in maze1 and test
	Creature creat1(3, 1);
	CreatureMazeTest(&maze1, &creat1);

	// Construct Creature at valid location in maze2 and test
	Creature creat2(7, 1);
	CreatureMazeTest(&maze2, &creat2);

	// Construct Creature at valid location in maze3 and test
	Creature creat3(7, 5);
	CreatureMazeTest(&maze3, &creat3);

	// Assignment operator overload
	maze1 = maze2 = maze3 = maze4;

	// Construct Creature at valid location in maze1 and test
	Creature creat4(6, 20);
	CreatureMazeTest(&maze1, &creat4);

	// Construct Creature at valid location in maze2 and test
	Creature creat5(4, 14);
	CreatureMazeTest(&maze2, &creat5);

	// Construct Creature at valid location in maze3 and test
	Creature creat6(2, 16);
	CreatureMazeTest(&maze3, &creat6);

	// Construct Creature at valid location in maze4 and test
	Creature creat7(0, 9);
	CreatureMazeTest(&maze4, &creat7);
}

// Runs all tests for Maze and Creature classes
void AllTests() {

	MazeTests();
	Maze1Test();
	Maze2Test();
}

// Runs all tests functions
int main() {

	AllTests();
}
