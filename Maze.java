/**
 * Maze.java
 * 
 * @author Wizzol
 * 
 * Maze shits
 */
package css342;

import java.util.*;
import java.util.zip.DataFormatException;
import java.io.*;

/**
 * Maze class
 * 
 * @author Juan
 * 
 * Represents a virtual maze created from a text file
 */
public class Maze {
	
	// 2D array to store maze chars
	private MAZETXT[][] matrix;
	
	// Exit location
	private int exitRow, exitCol;
	
	/**
	 * Enum to control type safety of input chars
	 * @author Juan
	 */
	private enum MAZETXT { 
		
		// Only chars allowed in maze text file
		SPACE(' '), WALL('x'), VISITED('+'), PATH('*');
		
		// Char variable
		private char c;
		
		/**
		 * Constructs MAZETXT constant with char input
		 * @param c The char input
		 */
		private MAZETXT(char c) { this.c = c; }
		
		/**
		 * Turns MAZETXT into char
		 * @return char of MAZETXT constant
		 */
		public char toChar() { return this.c; }
		
		/**
		 * Static function to get the right MAZETXT constant from a char
		 * @param c The char input
		 * @return corresponding MAZETXT constant
		 */
		protected static MAZETXT fromChar(char c) {
			
			switch (c) {
			
			case ' ':
				
				return SPACE;
				
			case 'x':
			
				return WALL;
			
			case '+':
				
				return VISITED;
				
			case '*':
				
				return PATH;
				
			default:
				
				return null;
			}
		}
	}
	
	/**
	 * Constructs Maze with given fileName
	 * @param fileName The name of the maze file
	 * @throws FileNotFoundException
	 * @throws DataFormatException
	 */
	public Maze(String fileName) throws FileNotFoundException, DataFormatException {
		
		Scanner fileScan = new Scanner(new File(fileName));
		
		if (!fileScan.hasNextInt()) {
			
			fileScan.close();
			
			throw new DataFormatException();
		}
		
		this.initializeFields(fileScan.nextInt(), fileScan.nextInt(),
							  fileScan.nextInt(), fileScan.nextInt());
		
		fileScan.nextLine();
		
		this.extractMaze(fileScan);
		
		fileScan.close();
	}
	
	/**
	 * Determines whether a spot in the Maze is clear for moving
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if clear, false if not
	 */
	public boolean isClear(int row, int col) {
		
		return this.inBounds(row, col) && this.matrix[row][col] == MAZETXT.SPACE;
	}
	
	/**
	 * Determines whether a spot in the Maze is a wall
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if wall, false if not
	 */
	public boolean isWall(int row, int col) {
		
		return this.inBounds(row, col) && this.matrix[row][col] == MAZETXT.WALL;
	}
	
	/**
	 * Determines whether a spot in the Maze is a part of the
	 * solution path
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if path, false if not
	 */
	public boolean isPath(int row, int col) {
		
		return this.inBounds(row, col) && this.matrix[row][col] == MAZETXT.PATH;
	}
	
	/**
	 * Determines whether a spot in the Maze has been
	 * already visited
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if visited, false if not
	 */
	public boolean isVisited(int row, int col) {
		
		return this.inBounds(row, col) && this.matrix[row][col] == MAZETXT.VISITED;
	}
	
	/**
	 * Determines whether a spot in the Maze is the exit
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if exit, false if not
	 */
	public boolean isExit(int row, int col) {
		
		return this.inBounds(row, col) && (row == this.exitRow) && (col == this.exitCol);
	}
	
	/**
	 * Determines whether a spot in the Maze is a part of the
	 * solution path
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if path, false if not
	 */
	public void markAsPath(int row, int col) {
		
		this.matrix[row][col] = MAZETXT.PATH;
	}
	
	/**
	 * Determines whether a spot in the Maze has been
	 * already visited
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if visited, false if not
	 */
	public void markAsVisited(int row, int col) {
		
		this.matrix[row][col] = MAZETXT.VISITED;
	}
	
	/**
	 * Converts maze to printable string
	 * @return String representation of maze with chars
	 */
	@Override
	public String toString() {
		
		StringBuffer s = new StringBuffer();
		
		for (MAZETXT[] array : this.matrix) {
			
			for (MAZETXT constant : array) {
				
				s.append(constant.toChar());
			}
			
			s.append('\n');
		}
		
		return s.toString();
	}
	
	/**
	 * Helper method for constructor
	 * @param width The width of the maze
	 * @param height The height of the maze
	 * @param exitRow The row number of the exit
	 * @param exitCol The column number of the exit
	 */
	private void initializeFields(int width, int height, int exitRow, int exitCol) {
		
		this.matrix = new MAZETXT[height][width];
		this.exitRow = exitRow;
		this.exitCol = exitCol;
	}
	
	/**
	 * Extracts chars from text file into this maze
	 * @param fileScan The file scanner
	 */
	private void extractMaze(Scanner fileScan) {
		
		for (int row = 0; row < this.matrix.length && fileScan.hasNextLine(); ++row) {
			
			String line = fileScan.nextLine();
			
			for (int col = 0; col < this.matrix[0].length; col++) {
				
				this.matrix[row][col] = MAZETXT.fromChar(line.charAt(col));
			}
		}
	}
	
	
	/**
	 * Helper for other boolean methods to check that
	 * given spot is within boundaries
	 * @param row The row of the spot
	 * @param col The column of the spot
	 * @return boolean: true if in bounds, false if not
	 */
	private boolean inBounds(int row, int col) {
		
		return (row >= 0) && (row < this.matrix.length) && (col >= 0) &&
			   (col < this.matrix[row].length);
	}
}
