/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package classobj;

/**
 *
 * @author ASUS
 */
public class ClassObj {

    /**
     * @param args the command line arguments
     */
    public static final double PI = 3.14;
    
    public static void print2Pi(double pi){
        System.out.println(pi * 2);
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        ClassObj math = new ClassObj();
        math.print2Pi(math.PI);
    }
    
}
