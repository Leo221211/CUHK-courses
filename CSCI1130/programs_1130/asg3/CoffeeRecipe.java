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
 * Student Name: xxx <fill in yourself>
 * Student ID  : xxx <fill in yourself>
 * Date        : xxx <fill in yourself>
 */
public class CoffeeRecipe {

  // Do not MODIFY the two give private fields
  private String name = "";
  private int milkPercent;
  
  // Define more date fields as needed
  
  // Do not MODIFY the default constructor which is for the example run
  CoffeeRecipe() {
      this.name = "Milk";
      this.milkPercent = 100;
  }
  
  // STUDENT WORK HERE to modify and add related methods
  
  // Do not MODIFY the method signature which is for CoffeeMaker to call
  public String getName() {
    return "Milk";  // TODO: update the method body as the value returned is Hardcoded now
  }
  
  // Do not MODIFY the method signature which is for CoffeeMaker to call
  public int getMilkPercent() {
    return 100;  // TODO: update the method body as the value returned is Hardcoded now
  }

  // Do not MODIFY the method signature which is for CoffeeMaker to call
  public void printMessage() {
      System.out.println("...");   // TODO: update the method body as needed
  }

  // STUDENT may define extra helper methods here
  

}
