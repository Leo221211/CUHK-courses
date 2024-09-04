package image;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.PrintStream;
import java.util.Scanner;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;

/**
 * Portable Gray Map (Gray-scale image file in ASCII text) Java application
 * employs 2D array and file I/O
 *
 * @author Michael FUNG, YP CHUI
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
 * http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : xxx [fill in yourself]
 * Student ID   : xxx [fill in yourself]
 * Class/Section: xxx [fill in yourself]
 * Date         : xxx [fill in yourself]
 */
public class PGM {
    // instance fields
    private String imageName;
    private int width, height;
    private int maxValue;
    private int[][] image;
    private String[] charsMap = {"@@", "##", "++", ";;", ",,", "..", "``", "  "};
    /** Default constructor for creating a simple checker PGM image of 2 x 3 */

    public PGM() {      // 2x3
        imageName = "Simple";
        width = 2;
        height = 3;
        maxValue = 255;                   // value for white in default/given file
        image = new int[height][width];   // note: height as row, width as column
        image[0][0] = image[1][1] = 255;  // white dots
        image[0][1] = image[2][0] = 127;  // gray dots
        image[1][0] = image[2][1] = 0;    // black dots
    }

    /** Constructor for creating an "mid-gray" PGM image of w x h 
    * // All pixels shall carry value of 127 */
    public PGM(String name, int w, int h) {     // with name and height
        imageName = name;
        width = w;
        height = h;
        maxValue = 255;
        image = new int[height][width];

        for (int row = 0; row < height; row++) 
            for (int col = 0; col < width; col++) 
            image[row][col] = 127;    
    }

    /** 
     * Constructor for reading a PGM image file
     * @param filename 
     */
    public PGM(String filename) {   // from a file 
        this.imageName = filename;
        read(filename);
    }

    /**
     * Get the width of the image
     * @return image width in int
     */
    public int getWidth() { return width; }

    /**
     * Get the height of the image
     * @return image height in int
     */
    public int getHeight() { return height; }

    /**
     * Get the image 2D array
     * @return image 2D array in int[][]
     */
    public int[][] getImage() { return image; }

    /** Show image on screen  
     * // given and NEED NOT be modified */
    public void showImage() {
        if (getHeight() <= 0 || getWidth() <= 0 || image == null) {
            JOptionPane.showConfirmDialog(null, "Width x Height = " + getWidth() + "x" + getHeight(), imageName + " corrupted!", JOptionPane.CLOSED_OPTION, JOptionPane.ERROR_MESSAGE, null);
            // System.out.println("here4 " + getHeight() + "x" + getWidth()); image is null
            return;
        }

        BufferedImage img = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_BYTE_GRAY);

        int grayLevel, gray; 

        for (int row = 0; row < getHeight(); row++) {
            for (int col = 0; col < getWidth(); col++) {        
                grayLevel = image[row][col];
                gray = (grayLevel << 16) + (grayLevel << 8) + grayLevel; 
                img.setRGB(col, row, gray);
            }
         }

        JOptionPane.showConfirmDialog(null, "Width x Height = " + getWidth() + "x" + getHeight(), imageName, JOptionPane.CLOSED_OPTION, JOptionPane.INFORMATION_MESSAGE, new ImageIcon(img));
    }

    /**
     * read a PGM file
     * @param filename is the PGM filename in String
     * @return true after finishing the action
     */
    public boolean read(String filename) {
        try {
            File f = new File(filename);
            Scanner reader = new Scanner(f);
            String header = reader.nextLine();

            // check header to make sure the file is PGM
            if (header == null || header.length() < 2 || header.charAt(0) != 'P' || header.charAt(1) != '2') {
                throw new Exception("Wrong PGM header!");
            }

            // skip lines (if any) start with '#'
            do { 
                header = reader.nextLine();
            } while (header.charAt(0) == '#');

            Scanner readStr = new Scanner(header);  // get w, h from last line scanned instead of file
            width = readStr.nextInt();
            height = readStr.nextInt();
            maxValue = reader.nextInt();  // get the rest from file

            System.out.println("Reading PGM image of size " + width + "x" + height);

            // Write your code here
            image = new int[height][width];
            
            for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {        
                    image[row][col] = reader.nextInt();
                } 
            }
            // End of your code        
        }
        catch(Exception e){
            height=-1;
            width=-1;
        }
        return true;
    }

    /**
     * downsample the current image by half
     * @return the half-sized image in a PGM object reference
     */
    public PGM halfsize() {
        // Write your code here
        int halfW = width / 2;
        int halfH = height / 2;
        PGM halfedPGM = new PGM("Halfsized",halfW , halfH);
        for (int row = 0; row < halfH; row++) {
            for (int col = 0; col < halfW; col++) {        
                // System.out.println(halfW + "," + halfH);
                halfedPGM.image[row][col] = (image[2*row][2*col] + image[2*row +1][2*col] + image[2*row][2*col +1] + image[2*row +1][2*col +1]) / 4;
            } 
        }
        return halfedPGM;
        // End of your code     
    }

    /**
     * generate and export the ASCII art as a .txt file
     * @param filename for storing the ASCII art 
     */
    public void exportAsciiArt(String filename) {
        // Write your code here
        PrintStream asciiPrint;
        try {
            asciiPrint = new PrintStream(filename);
            for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {        
                    asciiPrint.print(charsMap[image[row][col] / 32]);
                } 
                asciiPrint.println();
            }
        }
        catch(Exception e){}
        // End of your code      
    }
}
