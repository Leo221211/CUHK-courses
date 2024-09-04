/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package inheritance;

/**
 *
 * @author ASUS
 */
public class Human {
    public int h = 0;       // pu pu
    private int priv = 2;   // pri pu
    public int hp = 4;      // pu pri
    private int hpri = 7;   // pri pri
    
    public int xyz = 10;
    
    public Integer method(){
        System.out.println("I am a human");
        return null;
    }
    
    public void eat() {
        System.out.println("eat 10kg");
    }
    
    public void sing() {
        System.out.println("Human is singing");
    }
    
    public void run() {
        System.out.println("human is running");
    }
    
    public static void staticRun() {
        System.out.println("human statically running");
    }
    
    void teach(){};
}
