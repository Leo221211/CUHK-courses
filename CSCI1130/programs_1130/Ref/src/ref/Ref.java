/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package ref;

/**
 *
 * @author ASUS
 */

class SomeClass {
    public static int i = 0;
}


public class Ref {


    public static void main(String[] args) {
        // TODO code application logic here
        int n = 0;
        method(n);
        System.out.println(n);
        
        SomeClass sc =  new SomeClass();
        method2(sc);
        System.out.println(sc.i);
        
    }
    
    public static void method(int n) {
        // int n = 
        n = n+1;
    }
    
    public static void method2(SomeClass sc) {
        sc.i ++;
    }
    
}
