package coffeetime;

// imports for JOptionPane, Random, etc.
import javax.swing.JOptionPane;

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

public class CoffeeTime {

    private static String[] coffeeNames;
    private static int[] coffeeMilkPercents;
    private static CoffeeMaker coffeeMaker;

    /**
     * Show a menu of choices and get user's input, given method
     * @return a String of user input: "1","2",…,"4", null means Cancel/Close
     */
    public static String showCoffeeMenu() {
      return JOptionPane.showInputDialog("Make Coffee: Input your choice\n1. Noir\n2. Cortado\n3. Latte\n4. Special",
                                         "<type [1-4] here>");
   }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // init coffee maker object
        coffeeMaker = new CoffeeMaker();

        // initialize coffee names & milk percent
        coffeeNames = new String[]{"Noir", "Cortado", "Latte", "Special"};
        coffeeMilkPercents = new int[]{0, 50, 75, -1};

        while(true) {
            // get choice, return -1 or -2
            int coffeeMenuChoice = CoffeeMaker.getChoiceFromCoffeeMenu();

            // check if exception
            if (coffeeMenuChoice == -1) {
                JOptionPane.showMessageDialog(null, "Hope to serve you again");
                System.out.println("User closed or cancelled dialog box\nBye!");
                System.exit(0);
            }
            else if (coffeeMenuChoice == -2) {
                JOptionPane.showMessageDialog(null, "Invalid input");
                continue;
            }
            
            // generate coffee recipe 
            CoffeeRecipe coffee;
            if (coffeeMenuChoice == 4){  // special coffee
                coffee = new CoffeeRecipe(coffeeNames[coffeeMenuChoice - 1]);
            } 
            else {  // normal coffee
                coffee = new CoffeeRecipe(coffeeNames[coffeeMenuChoice - 1], coffeeMilkPercents[coffeeMenuChoice - 1]);
            }

            // draw coffee and output ready, if out of beans, quit
            if(coffeeMaker.makeCoffee(coffee) == -1) { // out of beans
                JOptionPane.showMessageDialog(null, "Hope to serve you again");
                System.out.println("User closed or cancelled dialog box\nBye!");
                System.exit(0);
            }
            JOptionPane.showMessageDialog(null, String.format("Your %s is ready!", coffee.getName()));
        }
    }
}
