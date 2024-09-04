package coffeetime;

import java.util.Random;

/**
 * CoffeeTime application for making coffee in a dialog
 * Practice: declaring a class with constructor and instance fields and methods
 * declaring and invoking methods with parameters
 * random number generation
 * looping and branching
 * user interaction with JOptionPane
 * @author ypchui
 * CSCI1130 Java Assignment 3 CoffeeTime
 *
 * Remark: Name your class, variables, methods, etc. properly. 
 * You should write comment for your work and follow good styles.
 *
 * I declare that the assignment here submitted is original except for source
 * material explicitly acknowledged, and that the same or closely related
 * material has not been previously submitted for another course. I also
 * acknowledge that I am aware of University policy and regulations on honesty
 * in academic work, and of the disciplinary guidelines and procedures
 * applicable to breaches of such policy and regulations, as contained in the
 * website.
 *
 * University Guideline on Academic Honesty:
 *     http://www.cuhk.edu.hk/policy/academichonesty
 * Faculty of Engineering Guidelines to Academic Honesty:
 *     https://www.erg.cuhk.edu.hk/erg/AcademicHonesty
 *
 * Student Name: Muquan YU
 * Student ID  : 1155191596
 * Date        : 8 Oct 2023
 */
public class CoffeeRecipe {
  
    // define and construct
    private String name = "";
    private int milkPercent;  // [0, 100]
    private static int numOfSpecialCoffee = 0;
    
    
    /**
     * 1st constructor
     */
    CoffeeRecipe() {
        this.name = "Milk";
        this.milkPercent = 100;
    }

    /**
     * 2nd constructor for 1~3
     * @param name
     * @param milkPercent 
     */
    public CoffeeRecipe(String name, int milkPercent) {
        this.name = name;
        this.milkPercent = milkPercent;
    }

    /** 
     * 3rd constructor for special coffee
     * @param namePrefix 
     */
    public CoffeeRecipe(String namePrefix) {
        this.name = namePrefix + "-" + (char)('A' + numOfSpecialCoffee);
        this.milkPercent = genRandomMilkPercent();
        numOfSpecialCoffee ++;
    }

    // return name of the coffee
    public String getName() {
        return name;
    }

    // return milk percentage
    public int getMilkPercent() {
        return milkPercent;
    }

    // print milk ratio on console
    public void printMessage() {
        System.out.println(String.format("%s has a %d:%d milk to espresso ratio.", name, milkPercent, 100 - milkPercent));
    }

    // randomly generate milk percentage
    private int genRandomMilkPercent() {
        Random rand = new Random();
        return rand.nextInt(100); // [0, 99]
    }

}
