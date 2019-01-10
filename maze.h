// maze.h
// Specifications for Maze class
// Authors: Yusuf Pisan & Juan Arias
//
// The Maze class represents a 2D maze read from a text file which specifies
// width, height, exit row, exit location and the characters representing the
// maze. The Maze is capable of determinning whether a given location
// is a space, wall, visited or path and
// capable of marking a given location as visited or part of the path.

#ifndef MAZE_H
#define MAZE_H
#include<iostream>

class Maze {

	// Constants for locations in Maze
	enum LOCATION {

		CLEAR   = ' ',
		WALL    = 'x',
		PATH    = '*',
		VISITED = '+'
	};

	// Friend function
	// Overloaded output operator
	// Prints the maze in the format specified by its file
	friend std::ostream& operator<<(std::ostream& out, const Maze& maze); 

public:

	// Maze constructor requiring a valid file name as parameter
	explicit Maze(const std::string& fileName);

	// Copy constructor
	Maze(const Maze& other);

	// Overloaded assignment operator
	// Copies the state of parameter other,
	// returns this by reference
	Maze& operator=(const Maze& other);

	// Destroys Maze
	virtual ~Maze();

	// Returns true if the given position in the Maze is clear (space),
	// otherwise false
	bool IsClear(int row, int col) const;

	// Returns true if the given position in the Maze is wall ('x'),
	// otherwise false 
	bool IsWall(int row, int col) const;

	// Returns true if the given position in the Maze is path ('*'),
	// otherwise false 
	bool IsPath(int row, int col) const;

	// Returns true if the given position in the Maze is visited ('+'),
	// otherwise false 
	bool IsVisited(int row, int col) const;

	// Returns true if given position is exit of Maze,
	// otherwise false
	bool IsExit(int row, int col) const;

	// Marks the Maze at the given position with '*'
	void MarkAsPath(int row, int col);

	// Mark the Maze at the given position with '+'
	void MarkAsVisited(int row, int col);

private:

	// Width and height of Maze
	int width, height;

	// Row and column of exit
	int exitRow, exitCol;

	// Pointer to 2D dynamic array to represent Maze
	LOCATION **array;

	// Initalizes 2D dynamic array with
	// parameter file as the Maze's text file stream
	void initializeArray(std::ifstream& file);

	// Returns true if position is in bounds of Maze,
	// otherwise false
	bool inBounds(int row, int col) const;

	// Deallocates dynamic memory
	void clear() const;

};
#endif
