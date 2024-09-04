package coffeetime;

import javax.swing.JFrame;
import javax.swing.JLabel;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JComponent;
import javax.swing.JOptionPane;

/*
 * Given utility CoffeeDrawing class for drawing a cup of coffee 
 * DO NOT MODIFY this class
 * 
 * @author YPChui
 */
class CoffeeDrawing extends JComponent {
    
    // ALL static and instance fields/methods are given, DO NOT MODIFY

    private final int cup_width = 50, cup_height = 75;
    private int start_x, start_y;
    private int milk_percentage = 100;

    CoffeeDrawing(int milk_percentage, int start_x, int start_y) {
        this.milk_percentage = milk_percentage;
        this.start_x = start_x;
        this.start_y = start_y;
    }    
    
    @Override
    public void paint(Graphics g) {
        int x = start_x;
        int cup_thickness = 5, gap = 2;
        
        // draw cup
        g.setColor(Color.lightGray);
        g.fillRect(x-cup_thickness, start_y, cup_width+cup_thickness*2, cup_height+cup_thickness);
        g.setColor(this.getBackground());
        g.fillRect(x-gap, start_y, cup_width+gap*2, cup_height+gap);        
        
        // draw milk
        int milkHeight = (int)(cup_height*milk_percentage/100.0);
        g.setColor(Color.white);  
        g.fillRect(x, start_y, cup_width, milkHeight);
        
        // draw espresso
        int coffeeHeight = cup_height - milkHeight;
        g.setColor(new Color(100, 50, 0)); // coffee brown in color
        g.fillRect(x, start_y+milkHeight, cup_width, coffeeHeight);
    }    
}

/**
 * Given CoffeeMaker class for receiving coffee recipe and draw it on the panel display.
 * 
 * @author YPChui
 */
public class CoffeeMaker {
    
    final private JFrame window;
    private CoffeeDrawing coffeeFigure;
    private final static int MARGIN_LEFT = 20, MARGIN_TOP = 20;
    private static int numOfCoffee = 0;
    private static final int SLOT_WIDTH = 80;
    private static final int MAX_NUM_CUP = 5;

    public CoffeeMaker() {
        window = new JFrame("Coffee Maker");
        window.setSize(430, 150);
        window.setLocation(20, 20);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    /**
     * Make coffee by drawing and printing console message
     * @param coffeeRecipe a reference to a coffee recipe object
     * @return 1 for successful making, -1 means failing due to out of Java beans
     */
    public int makeCoffee(CoffeeRecipe coffeeRecipe) {
        if(numOfCoffee>=MAX_NUM_CUP) {
            JOptionPane.showMessageDialog(null, "Out of Java Beans!!");
            return -1;
        } else {
            coffeeRecipe.printMessage();
            return makeCoffee(coffeeRecipe.getName(), coffeeRecipe.getMilkPercent());
        }
    }
    
    /**
     * Make coffee by drawing 
     * @param name name of the coffee recipe
     * @param milkPercent milk percent of the coffee recipe
     * @return 1 for successful making
     */
    private int makeCoffee(String name, int milkPercent) {
        
        // Draw the coffee name on top
        JLabel coffeeName = new JLabel(name);
        coffeeName.setBounds(MARGIN_LEFT+numOfCoffee*SLOT_WIDTH, -40, 150, 100);
        window.getContentPane().add(coffeeName);
        
        // Draw a cup of coffee
        coffeeFigure = new CoffeeDrawing(milkPercent, MARGIN_LEFT+SLOT_WIDTH*numOfCoffee, MARGIN_TOP);
        window.getContentPane().add(coffeeFigure); 
        
        numOfCoffee++;
        window.revalidate();
        window.repaint();    
        return 1;
    }
    
  /*
   * Get the user input String from Coffee Menu
   * @return an integer of user input: 1, 2, 3, 4, -1 means Cancel/Close. 
   * -2 means out-of-range user input e.g. 0 or 5
   */
  public static int getChoiceFromCoffeeMenu() {
    String choice;
    choice = CoffeeTime.showCoffeeMenu();
    if (choice == null) {
      return -1; // "Cancel" is clicked
    }
    return parseChoices(choice);
  }

  /*
   * Parse the user input String, handle exception and get the user input as an integer
   * @param choice the user input String
   * @return an integer of user input: 1, 2, 3, 4, -1 means non number foramt 
   * -2 means out-of-range user input e.g. 0 or 5
   */
  private static int parseChoices(String choice) {
    int task;
    try { // exception handling for Invalid Number Format
      task = Integer.parseInt(choice);
      if(task < 1 || task > 4) {
          task = -2;
      }
    } catch (NumberFormatException e) {
      task = -1;
    }
    return task;
  }    
}
