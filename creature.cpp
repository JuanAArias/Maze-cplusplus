// creature.cpp
// Implementations for Creature class
// Author: Juan Arias
//
// The Creature class represents something that can move through the Maze
// class, marking locations as visited or part of the path to the exit, and
// returns a string indicating its path in North West South East.

#include "creature.h"

// Friend function
// Overloaded output operator
// Prints the position of the Creature in the format: C(x, y)
std::ostream& operator<<(std::ostream& out, const Creature& creat) {

	out << "C(" << creat.row << ", " << creat.col << ')';

	return out;
}

// Constructs Creature at position in Maze,
// assumes position is valid open space
// Initialies mazePtr to nullptr, row to parameter startRow &
// col to parameter startCol
Creature::Creature(int startRow, int startCol)

	:mazePtr(nullptr), row(startRow), col(startCol) {}

// Destroys Creature
Creature::~Creature() {}

// Returns a string in the form of NNEEN
// (where N means North, E means East, etc)
// that will let the creature get to the exit
// if creature cannot get to the exit, returns "X"
// if constructed at exit, returns ""
// Assumes maze has not been marked
std::string Creature::Solve(Maze& maze) {

	if (maze.IsExit(row, col)) {
		
		maze.MarkAsPath(row, col);
		return "";

	}

	mazePtr = &maze;

	std::string path(goNorth());
	
	path = (path[0] == NO_PATH) ? goWest()  : path;
	path = (path[0] == NO_PATH) ? goEast()  : path;
	path = (path[0] == NO_PATH) ? goSouth() : path;

	if (path[0] == NO_PATH) {

		maze.MarkAsVisited(row, col);
	}

	return path;
}

// Attempts to go North in Maze, updates position &
// returns NORTH if successful, otherwise returns NO_PATH
std::string Creature::goNorth() {

	if (mazePtr->IsClear(row - 1, col)) {
		
		mazePtr->MarkAsPath(row--, col);

		if (mazePtr->IsExit(row, col)) {
		
			mazePtr->MarkAsPath(row, col);

			return std::string(1, NORTH);
		}
		
		std::string newPath(goNorth());

		newPath = (newPath[0] == NO_PATH) ? goWest() : newPath;
		newPath = (newPath[0] == NO_PATH) ? goEast() : newPath;

		if (newPath[0] == NO_PATH) {

			mazePtr->MarkAsVisited(row++, col);
			return newPath;
		}

		return newPath.insert(0, 1, NORTH);
	}

	return std::string(1, NO_PATH);
}

// Attempts to go South in Maze, updates position &
// returns SOUTH if successful, otherwise NO_PATH
std::string Creature::goSouth() {

	if (mazePtr->IsClear(row + 1, col)) {
	
		mazePtr->MarkAsPath(row++, col);

		if (mazePtr->IsExit(row, col)) {
		
			mazePtr->MarkAsPath(row, col);

			return std::string(1, SOUTH);
		
		}

		std::string newPath(goSouth());

		newPath = (newPath[0] == NO_PATH) ? goWest() : newPath;
		newPath = (newPath[0] == NO_PATH) ? goEast() : newPath;

		if (newPath[0] == NO_PATH) {

			mazePtr->MarkAsVisited(row--, col);
			return newPath;

		}

		return newPath.insert(0, 1, SOUTH);
	
	}
	return std::string(1, NO_PATH);

}

// Attempts to go East in Maze, updates position &
// returns EAST if successful, otherwise returns NO_PATH
std::string Creature::goEast() {

	if (mazePtr->IsClear(row, col + 1)) {
	
		mazePtr->MarkAsPath(row, col++);

		if (mazePtr->IsExit(row, col)) {
		
			mazePtr->MarkAsPath(row, col);

			return std::string(1, EAST);
		
		}

		std::string newPath(goEast());

		newPath = (newPath[0] == NO_PATH) ? goNorth() : newPath;
		newPath = (newPath[0] == NO_PATH) ? goSouth() : newPath;

		if (newPath[0] == NO_PATH) {

			mazePtr->MarkAsVisited(row, col--);
			return newPath;

		}

		return newPath.insert(0, 1, EAST);
	}

	return std::string(1, NO_PATH);

}

// Attempts to go West in Maze, updates position &
// returns WEST if successful, otherwise returns NO_PATH
std::string Creature::goWest() {

	if (mazePtr->IsClear(row, col - 1)) {
	
		mazePtr->MarkAsPath(row, col--);

		if (mazePtr->IsExit(row, col)) {
		
			mazePtr->MarkAsPath(row, col);

			return std::string (1, WEST);

		}

		std::string newPath(goWest());

		newPath = (newPath[0] == NO_PATH) ? goNorth() : newPath;
		newPath = (newPath[0] == NO_PATH) ? goSouth() : newPath;

		if (newPath[0] == NO_PATH) {

			mazePtr->MarkAsVisited(row, col++);
			return newPath;

		}

		return newPath.insert(0, 1, WEST);
	
	}

	return std::string(1, NO_PATH);

}
