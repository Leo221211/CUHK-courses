/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package staticinstance;

/**
 *
 * @author ASUS
 */
public class StaticInstance {
    
    public static void staticMethod(){
        System.out.println("static");
    }
    
    public void instanceMethod(){
        System.out.println("isntance");
    }
    
    public void instanceMethodM(){
        instanceMethod();
        staticMethod();
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        StaticInstance obj = new StaticInstance();
        
        staticMethod();     // can 
//        instanceMethod();   // cannot
        obj.instanceMethodM();
   }
    
}
