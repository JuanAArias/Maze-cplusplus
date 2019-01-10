// maze.cpp
// Implementations for Maze class
// Author: Juan Arias
//
// The Maze class represents a 2D maze read from a text file which specifies
// width, height, exit row, exit location and the characters representing the
// maze. The Maze is capable of determinning whether a given location
// is a space, wall, visited or path and
// capable of marking a given location as visited or part of the path.

#include "maze.h"
#include <fstream>
#include <string>
#include <iomanip>

// Friend function
// Overloaded output operator
// Prints the maze in the format specified by the its file
std::ostream& operator<<(std::ostream& out, const Maze& maze) {
	
	out << std::left << std::setw(5) << maze.width << maze.height
		<< std::endl
		<< std::left << std::setw(5) << maze.exitRow << maze.exitCol
		<< std::endl;

	for (int i(0); i < maze.height; ++i) {

		for (int j(0); j < maze.width; ++j) {
		
			out << maze.array[i][j];
		
		}

		out << std::endl;

	}
	
	return out;
}

// Maze constructor requiring a valid file name as parameter
// Initalizes fields then calls helper method initializeArray
Maze::Maze(const std::string& fileName) :array(nullptr) {

	std::ifstream file(fileName);

	if (!file.is_open()) {

		std::cout << "Error in filename" << std::endl;

		throw 99;
	}

	file >> this->width;
	file >> this->height;
	file >> this->exitRow;
	file >> this->exitCol;
	file.ignore();

	this->initializeArray(file);

	file.close();
}

// Copy constructor
// Initializes array to nullptr,
// uses overloaded assignment operator to
// copy state of parameter other
Maze::Maze(const Maze& other) :array(nullptr) {

	*this = other;
}

// Overloaded assignment operator
// Copies the state of parameter other,
// checks for self assignment and uninitialized pointer,
// returns *this by reference
Maze& Maze::operator=(const Maze& other) {

	if (this != &other) {

		if (this->array != nullptr) {

			this->clear();
		}

		this->width   = other.width;
		this->height  = other.height;
		this->exitRow = other.exitRow;
		this->exitCol = other.exitCol;

		this->array = new LOCATION*[height];

		for (int i(0); i < this->height; ++i) {

			this->array[i] = new LOCATION[this->width];

			for (int j(0); j < this->width; ++j) {

				this->array[i][j] = other.array[i][j];
			}
		}
	}

	return *this;
}

// Destroys Maze
// Deallocates all dynamic memory
Maze::~Maze() {

	this->clear();
}

// Returns true if the given position in the Maze is clear (space),
// otherwise false
bool Maze::IsClear(int row, int col) const {
	
	return (this->inBounds(row, col)) && (this->array[row][col] == CLEAR);

}

// Returns true if the given position in the Maze is wall ('x'),
// otherwise false 
bool Maze::IsWall(int row, int col) const {

	return (this->inBounds(row, col)) && (this->array[row][col] == WALL);

}

// Returns true if the given position in the Maze is path ('*'),
// otherwise false 
bool Maze::IsPath(int row, int col) const {

	return (this->inBounds(row, col)) && (array[row][col] == PATH);

}

// Returns true if the given position in the Maze is visited ('+'),
// otherwise false 
bool Maze::IsVisited(int row, int col) const {

	return (this->inBounds(row, col)) && (array[row][col] == VISITED);

}

// Returns true if given position is exit of Maze,
// otherwise false
bool Maze::IsExit(int row, int col) const {

	return (row == this->exitRow) && (col == this->exitCol);

}

// Marks the Maze at the given position with *
void Maze::MarkAsPath(int row, int col) {

	this->array[row][col] = PATH;
}

// Mark the Maze at the given position with +
void Maze::MarkAsVisited(int row, int col) {

	this->array[row][col] = VISITED;
}

// Initalizes 2D dynamic array with
// parameter file as the Maze's text file stream
void Maze::initializeArray(std::ifstream& file) {

	std::string line;

	this->array = new LOCATION*[height];

	for (int i(0); i < this->height; ++i) {

		std::getline(file, line);

		this->array[i] = new LOCATION[width];
		
		for (int j(0); j < this->width; ++j) {

			this->array[i][j] = static_cast<LOCATION>(line[j]);
		}
	}
}

// Returns true if position is in bounds of Maze,
// otherwise false
bool Maze::inBounds(int row, int col) const {

	return (0 <= row) && (row <= this->height) && (0 <= col) &&
		   (col <= this->width);

}

// Deallocates dynamic memory
void Maze::clear() const {

	for (int i(0); i < this->height; ++i) {

		delete[] this->array[i];
	}

	delete[] this->array;
}
