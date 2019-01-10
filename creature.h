// creature.h
// Specifications for Creature class
// Authors: Yusuf Pisan & Juan Arias
//
// The Creature class represents something that can move through the Maze
// class, marking locations as visited or part of the path to the exit, and
// returns a string indicating its path in North West South East.

#ifndef CREATURE_H
#define CREATURE_H

#include "maze.h"

class Creature {

	// Constants for directions
	enum DIRECTION {

		NORTH   = 'N',
		SOUTH   = 'S',
		EAST    = 'E',
		WEST    = 'W',
		NO_PATH = 'X'
	};
	
	
	// Friend function
	// Overloaded output operator
	// Prints the position of the Creature in the format: C(x, y)
	friend std::ostream& operator<<(std::ostream& out, const Creature& creat);

public:

	// Constructs Creature at position in Maze,
	// assumes position is valid open space
	Creature(int startRow, int startCol);

	// Destroys creature
	virtual ~Creature();

	// Returns a string in the form of NNEEN
	// (where N means North, E means East, etc)
	// that will let the creature get to the exit
	// if creature cannot get to the exit, returns "X"
	// if constructed at exit, returns ""
	// Assumes maze has not been marked
	std::string Solve(Maze &maze);

private:

	// Pointer to current Maze
	Maze* mazePtr;

	// Position of Creature in Maze
	int row, col;

	// Attempts to go North in Maze, updates position &
	// returns "N" if successful, otherwise returns empty string
	std::string goNorth();

	// Attempts to go South in Maze, updates position &
	// returns "S" if successful, otherwise returns empty string
	std::string goSouth();

	// Attempts to go East in Maze, updates position &
	// returns "E" if successful, otherwise returns empty string
	std::string goEast();

	// Attempts to go West in Maze, updates position &
	// returns "W" if successful, otherwise returns empty string
	std::string goWest();

};
#endif
