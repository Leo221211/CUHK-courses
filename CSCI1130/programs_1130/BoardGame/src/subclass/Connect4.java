/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package subclass;
import boardgame.*;
/**
 *
 * @author ASUS
 */
public class Connect4 extends BoardGame{
    protected int[] columnHeight;
    public Connect4() {
        super(6,7);
        String[] players = new String[] {"R", "Y"};
        setPlayers(players);
        
        for(int r = 0; r < height; r ++) {
            for(int c = 0; c < width; c ++) {
                board[r][c] = BLANK;
            }
        }
        
        columnHeight = new int[7];
        displayBoard();
    }
    
    public void move() {
        int inputCol = input.nextInt();
        
        // check if col is full
        if(columnHeight[inputCol] == height) {
            System.out.println("Invalid move");
            return;
        }
        
        board[columnHeight[inputCol]][inputCol] = getPlayer();
        columnHeight[inputCol]++;
        super.move();
        displayBoard();
    }
    
    
}
