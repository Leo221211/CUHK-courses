/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package scope;

/**
 *
 * @author ASUS
 */
public class Scope {

    private int pri = 1;
    protected static int proStatic = 0;
    protected int proInstance = -1;
    
    public static void main(String[] args) {
        // TODO code application logic here
        Scope scope = new Scope();
        System.out.println(scope.pri);
    }
    
}
