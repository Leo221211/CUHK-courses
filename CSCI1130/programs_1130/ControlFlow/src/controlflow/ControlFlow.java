/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package controlflow;

import java.util.*;
import java.io.*;

/**
 *
 * @author ASUS
 */
public class ControlFlow {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        char c = 65;
        
        Scanner fileScan = null;
        PrintStream print = null;
        
        try {
            fileScan = new Scanner(new File("a.txt"));
            print = new PrintStream("out.txt");
            
        }
        catch (IOException e) {
            System.err.println("Exception in opening file");
            System.exit(0);
        }
        
        // read header
        c = fileScan.nextLine().charAt(0);
        switch(c) {
            case 'a': 
                System.out.println("this is a");
                break;
            case 'b':
                System.out.println("this is b");
                break;
            default:
                System.out.println("not a or b");
        }
        
        
        // read and print
        while (fileScan.hasNextLine()) {
            print.println(fileScan.nextLine());
        }
        
        
    }
    
}
