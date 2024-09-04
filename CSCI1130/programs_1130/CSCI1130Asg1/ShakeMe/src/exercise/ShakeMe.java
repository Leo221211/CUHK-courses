/**
 * CSCI1130 Java Assignment 1 ShakeMe
 * Aim: Get acquaint with the JDK + NetBeans programming environment.
 *      Learn the structure and format of a Java program by example.
 * 
 * Platform: JDK 20 + NetBeans 18, with a given class ShakeMeBase.
 * 
 * Note: Windows/Mac/Linux may show different look-and-feel.
 * 
 * Requirements: Key in class names, variable names, method names, etc. AS IS.
 * You MUST type also ALL the comment lines (text in gray).
 * 
 * TO DO: Customize the method showMyInfo() with your own information.
 * 
 * Extra Learning Fun: Study the code and figure out how to end/win the game!
 * 
 * I declare that the assignment here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   http://www.cuhk.edu.hk/policy/academichonesty
 * Faculty of Engineering Guidelines to Academic Honesty:
 *   https://www.erg.cuhk.edu.hk/erg/AcademicHonesty
 * 
 * Course  Code: CSCI1130B
 * Student Name: Muquan YU
 * Student ID  : 1155191596
 * Date        : 13 September 2023
 */

package exercise;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * ShakeMe Game
 * Java Assignment
 * @author Michael FUNG
 * @since 6 September 2023
 */
public class ShakeMe extends ShakeMeBase {
    
    /** Number of YELLOW (turned-on) buttons. */
    protected int counter = 0;
    
    /** Default constructor. */
    public ShakeMe()
    {
        width = 20;
        height = 10;
        initDisplay();
    }
    
    /**
     * Constructor with given width and height of the ShakeMe object.
     * @param w is number of boxes left-to-right
     * @param h is number of boxes top-to-bottom
     */
    public ShakeMe(int w, int h)
    {
        width = w;
        height = h;
        initDisplay();
    }

    /**
     * ActionPerformed on user clicking a target button, try to turn off the target.
     * On clearing all "YELLOW" targets, shake and show Done and Bye
     * @param eventObject tells us which button object is triggered
     */
    @Override
    public void actionPerformed(ActionEvent eventObject) {
        JButton target = (JButton) (eventObject.getSource());
        target.setForeground(Color.BLUE);
        if (!turnOffButton(target))
            // wrong target, shake()!
            shake();
        else if (counter == 0) {
            shake();
            JOptionPane.showMessageDialog(null, "Done!  Bye!");
            shake();
            System.exit(0);
        }
    }
    
    /** Shake the window. */
    private void shake() {
        Point windowLocation = getLocation();

        double round = 5, max_radius = 10, step = 100;
        
        double limit = 2 * Math.PI * round;
        double angle_increment = limit / step;
        double radius_increment = max_radius / step;
        
        for (double angle = 0, radius = 0;
             angle < limit;
             angle += angle_increment, radius += radius_increment)
        {
            setLocation((int) (Math.cos(angle) * radius) + windowLocation.x,
                        (int) (Math.sin(angle) * radius) + windowLocation.y);
            delay(6);
        }
        this.setLocation(windowLocation);
    }
    
    /**
     * Turn on a button and increase the counter, taking two coordinates.
     * @param h is the top-to-bottom coordinate (row index)
     * @param w is the left-to-right coordinate (column index)
     */
    public void turnOnButton(int h, int w) {
        if (Color.YELLOW != buttons[h][w].getBackground()) {
            buttons[h][w].setBackground(Color.YELLOW);
            counter++;
        }
    }
    
    /**
     * Turn off a button "object" and decrease the counter.
     * @param target is a JButton object reference
     * @return false if the target is NOT on; true after finishing the action
     */
    public boolean turnOffButton(JButton target) {
        if (Color.YELLOW != target.getBackground())
            return false;
        target.setBackground(null);
        counter--;
        return true;
    }
    
    /**
     * TO DO: students should customize this method.
     * to show the last FIVE digits of your SID in YELLOW in BIG PIXELS; AND
     * to show first 10-char of your SURNAME 1-by-1 RED-ON-YELLOW on the bottom
     */
    public void showMyInfo()
    {
        // example digit: 7 in YELLOW
        // example surname with 4-char: N A M E
        // add more lines as you need here
        turnOnButton(1, 0); turnOnButton(1, 1); turnOnButton(1, 2);
        turnOnButton(2, 0);                     turnOnButton(2, 2);
        turnOnButton(3, 0); turnOnButton(3, 1); turnOnButton(3, 2);
                                                turnOnButton(4, 2);
        turnOnButton(5, 0); turnOnButton(5, 1); turnOnButton(5, 2);
        
        turnOnButton(1, 4);
        turnOnButton(2, 4);
        turnOnButton(3, 4);
        turnOnButton(4, 4);
        turnOnButton(5, 4);
        
        turnOnButton(1, 6); turnOnButton(1, 7); turnOnButton(1, 8);
        turnOnButton(2, 6);
        turnOnButton(3, 6); turnOnButton(3, 7); turnOnButton(3, 8);
                                                turnOnButton(4, 8);
        turnOnButton(5, 6); turnOnButton(5, 7); turnOnButton(5, 8);
        
        turnOnButton(1, 10); turnOnButton(1, 11); turnOnButton(1, 12);
        turnOnButton(2, 10);                      turnOnButton(2, 12);
        turnOnButton(3, 10); turnOnButton(3, 11); turnOnButton(3, 12);
                                                  turnOnButton(4, 12);
        turnOnButton(5, 10); turnOnButton(5, 11); turnOnButton(5, 12);
        
        turnOnButton(1, 14); turnOnButton(1, 15); turnOnButton(1, 16); 
        turnOnButton(2, 14);
        turnOnButton(3, 14); turnOnButton(3, 15); turnOnButton(3, 16);
        turnOnButton(4, 14);                      turnOnButton(4, 16);
        turnOnButton(5, 14); turnOnButton(5, 15); turnOnButton(5, 16);
        
        int c = 0;
        buttons[height - 1][c].setText("Y");
        turnOnButton(height - 1, c++);
        buttons[height - 1][c].setText("U");
        turnOnButton(height - 1, c++);
    }
    
    /**
     * main() method, starting point of the Java application.
     * @param args are command line arguments in a String array
     */
    public static void main(String[] args) {
        ShakeMe myObj;
        // create a ShakeMe object of size 30 x 10
        myObj = new ShakeMe(30, 10);
        myObj.showMyInfo();
    }
}