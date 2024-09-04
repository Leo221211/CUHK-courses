/**
 * Read the specification, start your work by creating ANOTHER New Java Class!
 * DO NOT MODIFY THIS FILE!!!
 */

package exercise;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.util.concurrent.TimeUnit;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 * CSCI1130 Java Assignment 1
 * class ShakeMeBase is provided to students in a NetBeans 18 project.
 * 
 * Aim: Ensure students will work with JDK 20 + NetBeans 18.
 *      Reduce amount of code typing for beginners.
 *
 * @author pffung
 */
public abstract class ShakeMeBase extends JFrame implements ActionListener {
    /** Instance fields indicating size width x height. */
    protected int width, height;
    /** 2D array of JButton object references. */
    protected JButton buttons[][];
    
    /** Initialize the ShakeMe window. */
    public final void initDisplay() {
        try {
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
        } catch (ClassNotFoundException |
                 IllegalAccessException |
                 InstantiationException |
                 UnsupportedLookAndFeelException exceptionObject) {
        }
        
        setTitle("Java Shake Me");
        setLayout(new GridLayout(height, width));
        buttons = new JButton[height][width];
        for (int row = 0; row < height; row++)
            for (int col = 0; col < width; col++)
            {
                buttons[row][col] = new JButton(row + ", " + col);
                buttons[row][col].setMargin(new Insets(1, 1, 1, 1));
                buttons[row][col].addActionListener(this);
                add(buttons[row][col]);
                if (row == height - 1)
                    buttons[row][col].setForeground(Color.RED);
            }
        setSize(width * 40, height * 40);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    /**
     * Slow down this process by sleeping this thread.
     * @param sleepInMS delay time in millisecond, at least/approximately
     */
    protected static void delay(long sleepInMS) {
        try {
            TimeUnit.MILLISECONDS.sleep(sleepInMS);
        } catch (InterruptedException exceptionObject) {
            Thread.currentThread().interrupt();
        }
    }
}
