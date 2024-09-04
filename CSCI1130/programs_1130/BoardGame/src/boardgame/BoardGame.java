package boardgame;
import java.util.Scanner;

import subclass.*;


public class BoardGame {
    protected int height, width, currentPlayerIndex, roundNumber;
    protected String[][] board;
    protected String[] players = {"Foo", "Bar"};
    protected final String BLANK = " ";
    protected Scanner input;

    // Constructor of BoardGame with given height x width
    public BoardGame(int gameBoardHeight, int gameBoardWidth){
        height = gameBoardHeight;
        width = gameBoardWidth;
        board = new String[height][width];
        currentPlayerIndex = 0;
        roundNumber = 1;
        input = new Scanner(System.in);
    }
    
    public void setPlayers(String[] gamePlayers) {
        if (gamePlayers != null && gamePlayers.length>0) { 
            players = gamePlayers;
        }
            currentPlayerIndex = 0;
    }
    
    public int getRound() {return roundNumber;} 
    public int nextRound() {return ++roundNumber;}
    public int getNumberOfPlayers() {return players.length; }
    public String getPlayer() {return players[currentPlayerIndex];}

    public String nextPlayer() {
        currentPlayerIndex =(currentPlayerIndex + 1) % getNumberOfPlayers();
        return players[currentPlayerIndex];
    }
    
    public void displayBoard() {
        for (int row = 0; row < height; row++, System.out.println()) 
            for (int col = 0; col < width; col++) 
                System.out.print(board[row][col] +".");
            
    }
    
    public void move() {
        System.out.println("Round "+getRound()+": "+getPlayer()+" made a move");
        System.out.println(nextPlayer() + "'s turn in Round "+ nextRound());
    }
    
    public static void main(String[] args) {
        Connect4 con = new Connect4();
        while(true) {
            con.move();
        }
        
    }
}