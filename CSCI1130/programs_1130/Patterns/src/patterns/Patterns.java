/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package patterns;

import java.io.*;

/**
 *
 * @author ASUS
 */
public class Patterns {

    /**
     * @param args the command line arguments
     */
    public void printPattern(String filename, int N) {
        if (N % 2 == 0 || N <= 0) {
            return;
        }
        
        PrintStream file = null;
        try {
            file = new PrintStream(filename);
        }
        catch (IOException e) {
        }
        
        // 0th
        for(int i = 0; i < N + 2; i ++)
            file.print("X");
        file.println();
        
        for (int r = 1; r <= N; r ++) {
            if(r == (N+1)/2) {
                file.print("X");
                for(int i = 0; i < N; i ++)
                    file.print("#");
                file.print("X\n");
                continue;                
            }
           
            int starCnt;
            if(r < (N+1)/2)
                starCnt = r *2 -1;
            else
                starCnt = (N-r+1)*2-1;
            int xCnt = (N+2) - 2 - starCnt;
            
            for(int i = 0; i < xCnt/2; i ++) {
                file.print("X");
            }
            
            if(r < (N+1)/2)
                file.print("/");
            else
                file.print("\\");
           
            
            for(int i = 0; i < starCnt; i ++) {
                file.print("*");
            }
            
            if(r < (N+1)/2)
                file.print("\\");
            else
                file.print("/");
            
            
            for(int i = 0; i < xCnt / 2; i ++) 
                file.print("X");
            
            file.println();
            
        }
        
        for(int i = 0; i < N + 2; i ++) {
            file.print("X");
        

        }
    } 
    
    public static void main(String[] args) {
        // TODO code application logic here
        Patterns p = new Patterns();
        p.printPattern("out.txt", 31);
        
        char j = 'B';
        do {
            j--;
            System.out.println(j);
            continue;
        } while(j >= 'A');
    }
    
}
