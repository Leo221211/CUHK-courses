/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package pp2;
import java.util.Scanner;
import java.lang.Math;

/**
 *
 * @author ASUS
 */
public class Pp2 {

    /**
     * @param args the command line arguments
     * 
     * 1. multiple strings need to be specially handle using \ or +
     * 2. + sign has 2 meanings in java, from left to right, it depends on if there is a string or not
     * 3. how to scan
     * 4. Math: a function always needs a class name before it. 
     * 5. Use tool method from another class
     */
    public static void main(String[] args) {
        // TODO code application logic here 
        
        // 1
        System.out.println("To be or not to be, that\n" +
                           "is the question.");
        
        //2
        System.out.println("50 plus 25 is " + 50 + 25);
        System.out.println("50 plus 25 is " + (50 + 25));
        
        // 3
        Scanner scanner = new Scanner(System.in);
//        double db = scanner.nextDouble();
        
        // 4
        System.out.println(Math.sin(1));
        
        // 5
        System.out.println(KmToMile.kmToMile(500));
    }
    
}
