/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package scope;

/**
 *
 * @author ASUS
 */
public class ThisAndSuper {
    protected int n = 1;
    public void someMethod(int n) {
        System.out.println(n  + " " + this.n);
    }
    
    public static void main(String[] args) {
        ThisAndSuper tns = new ThisAndSuper();
        tns.someMethod(9);
    }
}
