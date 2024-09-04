package coffeetime;

// imports for JOptionPane, Random, etc.
import javax.swing.JOptionPane;
//import java.util.Random;

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
public class CoffeeTime {

  private static String[] coffeeNames;
  private static int[] coffeeMilkPercents;
  private static CoffeeMaker coffeeMaker;

  /**
   * Show a menu of choices and get user's input, given method
   * @return a String of user input: "1","2",…,"4", null means Cancel/Close
   */
   public static String showCoffeeMenu() {
   /*** student's work to display coffee menu items ***/
      return JOptionPane.showInputDialog("... " );
   }

  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) {

    // Example use of CoffeeMaker with a CoffeeRecipe, you should replace them with your own logic
    //*
    coffeeMaker = new CoffeeMaker();
   
    for(int i=0; i<4; i++) {
        CoffeeRecipe coffee = new CoffeeRecipe();
        coffeeMaker.makeCoffee(coffee);
    }
    //coffeeMaker.makeCoffee(new CoffeeRecipe("Cortado", 50));  // this fails initially
    //*/
    // End of the exmample
    
    // initialize coffee names & milk percent
    coffeeNames = new String[]{"Noir", "Cortado", "Latte", "Special"};
    coffeeMilkPercents = new int[]{0, 50, 75, -1};

    /*** student's work here to initialize values, call getChoiceFromCoffeeMenu()of the CoffeeTimeHelper class,            where Number-Format Exceptions are handled for you.
       Modify the following sample code fragment to start processing user requests in a loop ***/
    int coffeeMenuChoice = CoffeeMaker.getChoiceFromCoffeeMenu();
    if (coffeeMenuChoice == -1) {
        System.out.println("User closed or cancelled dialog box");
        System.exit(0);
    }
    else if (coffeeMenuChoice == 1) {
        //System.out.println("User picked 1"); // optionally printed for debugging purposes
        
        // STUDENT WORK HERE
        
    }
                
    // STUDENT WORK HERE

            
  }
}
