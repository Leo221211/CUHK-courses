/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package inheritance;

/**
 *
 * @author ASUS
 */
public class Girl extends Human implements Student {
    // hide != override
    public int h = 1;
    public int priv = 3;
    private int hp = 5;
    private int hpri = 9;
    
    int xyz = 11;
    String name = "amy";

    public Integer method(int a) {
        System.out.println("I am a girl");
        return null;
    }
    
    
    @Override
    public void eat() {
        System.out.println("eat 8 tons");
    }
    
    @Override
    public void study() {
        System.out.println("girl is studying");
    }
    
    @Override
    public void run() {
//        super.run();
        System.out.println("girl is running");
    }
    
    public static void staticRun(int n) {
        Human.staticRun();
//        super.staticRun();
        System.out.println("girls is running statically");
    }
    
    public static void yima(){}
    
//    @Override
//    public String toString() {
//        return name;
//    }
}
