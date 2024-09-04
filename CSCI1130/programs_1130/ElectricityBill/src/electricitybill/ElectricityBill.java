/**
 * CSCI1130 Java Assignment 2 ElectricityBill
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
 * http://www.cuhk.edu.hk/policy/academichonesty
 * Faculty of Engineering Guidelines to Academic Honesty:
 * https://www.erg.cuhk.edu.hk/erg/AcademicHonesty
 *
 * Student Name: Muquan YU
 * Student ID : 1155191596@link.cuhk.edu.hk
 * Date : 26 September 2023
 */ 

// package declaration
package electricitybill;
import java.util.Scanner;

// class declaration    
public class ElectricityBill {
    // starting point of the program
    public static void main(String[] args) {
        // initialize
        // create an array to store monthly fuel clause charge data 
        double [] fcc = {82.5, 82.5, 86.4, 90.6, 91.7, 85.7, 77.3, 69.7, 62.4};
        // create a new Scanner object, named keyboard 
        Scanner keyboard = new Scanner(System.in);

        // input and validate
        // create input variables
        int totalUnits, month;
        
        // input units
        // total units should be non negative 
        System.out.print("Total Electricity Consumption (units): ");
        totalUnits = keyboard.nextInt();
        if(totalUnits < 0){
            System.out.println("Invalid input!");
            System.exit(0);
        }
        
        // input month
        // month should be between 1 and 9
        System.out.print("Month: ");
        month = keyboard.nextInt();
        if( month < 1 || month > 9){
            System.out.println("Invalid input!");
            System.exit(0);
            // return 0;
        }
        
        // close keyboard
        keyboard.close();

        
        // calculate basic charge
        // consider the charge in different sections separately
        double basicCharge;
        if (totalUnits <= 150){
            basicCharge = totalUnits * 0.729;
        } else if (totalUnits <= 300){
            basicCharge = 150 * 0.729 + (totalUnits - 150) * 0.868;
        } else if (totalUnits <= 500) {
            basicCharge = 150 * 0.729 + 150 * 0.868 + (totalUnits - 300) * 1.007;
        } else if (totalUnits <= 700) {
            basicCharge = 150 * 0.729 + 150 * 0.868 + 200 * 1.007 + (totalUnits - 500) * 1.243;
        } else if (totalUnits <= 1000) {
            basicCharge = 150 * 0.729 + 150 * 0.868 + 200 * 1.007 + 200 * 1.243 + (totalUnits - 700) * 1.382;
        } else if (totalUnits <= 1500) {
            basicCharge = 150 * 0.729 + 150 * 0.868 + 200 * 1.007 + 200 * 1.243 + 300 * 1.382 + (totalUnits - 1000) * 1.521;
        } else {
            basicCharge = 150 * 0.729 + 150 * 0.868 + 200 * 1.007 + 200 * 1.243 + 300 * 1.382 + 500 * 1.521 + (totalUnits - 1500) * 1.660;
        }
        
        System.out.printf("Basic Charge = $%.2f\n", basicCharge);
        
        // calculate fcc
        // nth month corresponds to fcc[month - 1], multiply 0.01 to convert cents to dollars
        double fcCharge = totalUnits * fcc[month - 1] * 0.01;
        System.out.printf("Fuel Clause Charge = $%.2f\n", fcCharge);
        
        // cal subsidy
        // if total units greater than 300, subsidy = 0 and don't print, else calculate and print
        double subsidy = 0;
        if(totalUnits >= 1 && totalUnits <= 300){
            subsidy = totalUnits * 0.095;
            System.out.printf("Special Electricity Subsidy = ($%.2f)\n", subsidy);
        }
        
        // calculate total amount
        // if total amount smaller than 18.8, then the bills cost changes to 18.8
        double total = basicCharge + fcCharge - subsidy;
        if(total < 18.8){
            total = 18.8;
        }
        System.out.printf("Total Amount = $%.2f\n", total);
    }
    
}
