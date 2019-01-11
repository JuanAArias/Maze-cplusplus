/**
 * Creature.java
 * 
 * @author Wizzollz
 * 
 * Solves maze
 */
package css342;

/**
 * Creature mfin class
 * 
 * @author Juan
 * 
 * These objects use exhaustive recursion to solve Maze class objects
 * 		
 * 	  ***************************************************************
 *    *ASSUMES that (0,0) is a valid starting location in given Maze*
 *    ***************************************************************
 */
public class Creature implements MazeSolver {
	
	// Reference to Maze to solve
	private Maze maze;
	
	// Buffer to build solution path String
	private StringBuilder solPath = new StringBuilder();
	
	// Current location of Creature
	private int row = 0, col = 0, solPathIndex = 0;
	
	/**
	 * Solves the given Maze and returns the directional solution path
	 * @param maze The Maze to solve
	 * @return the directional solution path as a String
	 */
	public String solve(Maze maze) {
		
		if (maze.isExit(this.row, this.col)) {
			
			maze.markAsPath(this.row, this.col);
			
			return DIRECTION.NONE.toString();
		}
		
		this.maze = maze;
		
		if (!this.north()) {
			
			if (!this.east()) {
				
				if (!this.west()) {
					
					this.south();
				}
			}
		}
		
		return this.formatPath();
	}
	
	/**
	 * String representation of this hoe
	 * @return String mfin format
	 */
	public String toString() {
		
		return String.format("C(%d, %d)", this.row, this.col);
	}
	
	/**
	 * Recursive function for Creature to go North in Maze,
	 * edits maze and solPath on the way
	 */
	private boolean north() {
		
		boolean rightPath = false;
		
		if (this.maze.isClear(this.row - 1, this.col) ) {
			
			this.maze.markAsPath(this.row--, this.col);
			
			this.addToPath(DIRECTION.NORTH);
			
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.north();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.east();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.west();
			
			if (rightPath) {
				
				this.maze.markAsPath(this.row, this.col);
				
			} else {
				
				--this.solPathIndex;
				this.maze.markAsVisited(this.row++, this.col);
			}
		}
		
		return rightPath;
	}
	
	/**
	 * Recursive function for Creature to go South in Maze,
	 * edits maze and solPath on the way
	 */
	private boolean south() {
		
		boolean rightPath = false;
		
		if (this.maze.isClear(this.row + 1, this.col) ) {
			
			this.maze.markAsPath(this.row++, this.col);
			
			this.addToPath(DIRECTION.SOUTH);
			
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.south();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.east();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.west();
			
			if (rightPath) {
				
				this.maze.markAsPath(this.row, this.col);
				
			} else {

				--this.solPathIndex;
				this.maze.markAsVisited(this.row--, this.col);
			}
		}
		
		return rightPath;
	}
	
	/**
	 * Recursive function for Creature to go East in Maze,
	 * edits maze and solPath on the way
	 */
	private boolean east() {
		
		boolean rightPath = false;
		
		if (this.maze.isClear(this.row, this.col + 1) ) {
			
			this.maze.markAsPath(this.row, this.col++);
			
			this.addToPath(DIRECTION.EAST);
			
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.east();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.north();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.south();
			
			if (rightPath) {
				
				this.maze.markAsPath(this.row, this.col);
				
			} else {
			
				--this.solPathIndex;
				this.maze.markAsVisited(this.row, this.col--);
			}
		}
		
		return rightPath;
	}
	
	/**
	 * Recursive function for Creature to go West in Maze,
	 * edits maze and solPath on the way
	 */
	private boolean west() {
		
		boolean rightPath = false;
		
		if (this.maze.isClear(this.row, this.col - 1) ) {
			
			this.maze.markAsPath(this.row, this.col--);
			
			this.addToPath(DIRECTION.WEST);
			
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.west();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.north();
			rightPath = (this.maze.isExit(this.row, this.col)) ? true : this.south();
			
			if (rightPath) {
				
				this.maze.markAsPath(this.row, this.col);
				
			} else {
				
				--this.solPathIndex;
				this.maze.markAsVisited(this.row, this.col++);
			}
		}
		
		return rightPath;
	}
	
	/**
	 * Uses most efficient method for building solPath
	 * @param dir The DIRECTION to add in the path
	 */
	private void addToPath(DIRECTION dir) {
		
		if (this.solPathIndex < this.solPath.length()) {
			
			this.solPath.setCharAt(this.solPathIndex++, dir.toChar());
			
		} else {
			
			++this.solPathIndex;
			this.solPath.append(dir.toChar());
		}
	}
	
	/**
	 * Returns path String in nice ass format
	 * @return formatted path String
	 */
	private String formatPath() {
		
		StringBuilder formatted = new StringBuilder();
		
		for (int i = 0; i < this.solPathIndex; ++i) {
			
			DIRECTION dir = DIRECTION.fromChar(this.solPath.charAt(i));
			
			int dirSteps = 1;
			
			while ((i < this.solPathIndex) && (dir.toChar() == this.solPath.charAt(i + 1))) {
				
				++i;
				++dirSteps;
			}
			
			formatted.append(dir.toChar());
			
			if (dirSteps > 1) {
				
				formatted.append('x');
				formatted.append(dirSteps);
			}
			
			if (i < this.solPathIndex - 1) {
				
				formatted.append('-');
			}
		}
		
		return formatted.toString();
	}
}
