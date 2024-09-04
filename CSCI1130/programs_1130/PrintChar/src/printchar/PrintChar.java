/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package printchar;
import java.io.*;

/**
 *
 * @author ASUS
 */
public class PrintChar {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception { 
        // TODO code application logic here
        PrintChar p = new PrintChar();
        throw new ArrayIndexOutOfBoundsException();
//        p.print(null);
//        p.print(new char[0][0]);
        p.print(new char[][] {{'A', 'B', 'C'}, null, {'Z'}, {}, {'P', 'q', 'R', 's'}});
    }
    
    void print(char[][] arr) {
        PrintStream s = System.out;
        
        if(arr == null) {
            s.print("null");
            return;
        }
        
        s.print("[");
        
        for(int r = 0; r < arr.length; r ++) {
            s.print(r);
            if(arr[r]==null){
                s.print("null");
                continue;
            }
            
            s.print("[");
            for(int col = 0; col<arr[r].length; col++) {
                s.print(col+"<"+arr[r][col]+">");
            }
            s.print("]");
            
        }
        s.print("]");
    
    }
    
    
    
    
}
