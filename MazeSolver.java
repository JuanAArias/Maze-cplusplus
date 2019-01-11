/**
 * MazeSolver.java
 * 
 * @author Wizzollz
 * 
 */
package css342;

/**
 * This mfin interface specifies the behavior to
 * solve a Maze object
 * 
 * @author Juan
 *
 */
public interface MazeSolver {
	/**
	 * Solves the given Maze and returns the directional solution path
	 * @param maze The Maze to solve
	 * @return the directional solution path as a String
	 */
	String solve(Maze maze);
	
	/*
	 * Enum for directional chars to enforce type safety
	 */
	public enum DIRECTION {
		
		
		
		// Constants for each direction in Maze
		NORTH('N'), SOUTH('S'), EAST('E'), WEST('W'), NONE('X');
		
		/**
		 * Converts char to DIRECTION
		 * @param c The char to convert
		 * @return the corresponding DIRECTION
		 */
		public static DIRECTION fromChar(char c) {
			
			switch (c) {
			
			case 'N':
				
				return NORTH;
				
			case 'S':
				
				return SOUTH;
				
			case 'E':
				
				return EAST;
				
			case 'W':
				
				return WEST;
				
			default:
				
				return NONE;
			}
		}
		
		// Actually char data
		private char c;
		
		/**
		 * Simple constructor to initialize constant
		 * @param  c The char direction
		 */
		private DIRECTION(char c) {
		
			this.c = c;
		}
		

		
		/**
		 * DIRECTION to char
		 * @return the char that this DIRECTION holds
		 */
		public char toChar() {
			
			return this.c;
		}
		
		/**
		 * DIRECTION to String
		 * @return String of the char that this DIRECTION holds
		 */
		@Override
		public String toString() {
		
			return Character.toString(this.c);
		}
	}
}
