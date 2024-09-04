/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package newpackage;
import scope.*;

/**
 *
 * @author ASUS
 */
public class SubClass extends Scope {
        private static int itg;
        private int itgI;
    
        public static void main(String[] args) {
        System.out.println(proStatic);
        System.out.println(SubClass.itg);
//        System.out.println(this.itgI);
        
        Scope scope = new Scope();
//        System.out.println(scope.proStatic);
//        System.out.println(scope.proInstance);
        
    }
}
