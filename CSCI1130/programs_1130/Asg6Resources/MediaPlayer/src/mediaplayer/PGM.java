package mediaplayer;

import java.util.Scanner;

/**
 * Portable GrayMap (Gray-scale image file in ASCII text) Java application
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
 * Student Name : Muquan YU
 * Student ID   : 1155191596
 * Class/Section: CSCI1130B
 * Date         : 26 Nov 2023
 */

/** FIRST ACTION: click NetBeans editor light bulb hint "Implement all abstract methods" below */
public class PGM extends PNM
{
  // instance field

/** TODO:
  declare a 2D array of int
 */
private int[][] image;


  /** Default constructor for creating a sample image */
  public PGM() {
/** TODO:    
    assign imageName with "PGM Sample"
    assign header with "P2"
    assign width with 2
    assign height with 3
    assign maxValue with 255

    create the 2D array for storing image pixels
    note: height as row, width as column, 0 means black, 255 means white, 1-254 are gray levels
    initialization:
    image[0][0] = image[1][1] = 255;  // white dots
    image[0][1] = image[2][0] = 127;  // gray dots
    image[1][0] = image[2][1] = 0;    // black dots
 */

    imageName = "PBM Sample";
    header = "P2";
    width = 2;
    height = 3;
    maxValue = 255;
    
    image = new int[3][2];
    image[0][0] = image[1][1] = 255;  // white dots
    image[0][1] = image[2][0] = 127;  // gray dots
    image[1][0] = image[2][1] = 0;    // black dots
  }

  /**
   * Constructor for reading a PGM image file
   * @param filename
   */
  public PGM(String filename) {
    super(filename);
  }

  /**
   * Read a PGM file using a given Scanner.
   * @param reader is a Scanner object reference that has read a header properly already
   * @return true after finishing the action
   */
  @Override
  public boolean readPixels(Scanner reader) {
/** TODO:
    handles all exceptions gracefully
    validate if header is P2
    read maxValue
    create 2D array
    read pixel data
    return false on all abnormalities (and set height and width to -1)
*/
    try {
        if (header.charAt(1) != '2') {
            throw new Exception("Wrong PGM header!");
        }
        
        System.out.println("Reading PGM image of size " + width + "x" + height);

        // read maxValue
        maxValue = reader.nextInt();
        
        image = new int[height][width];
        
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int p = reader.nextInt();
                image[row][col] = p;
            }
        }
    }
    catch (Exception e) {
      image = null;
      width = -1;
      height = -1;
      return false;
    }
    return true;
  }
  
  /** TODO:
   * Provide implementation (override) the three methods getRed(), getGreen() and getBlue().
   * ALL three methods shall return the SAME value for a gray pixel at given row and col.
   * @param row
   * @param col
   * @return int value in the range [0, 255]
   */
  

  
  /** FOR STUDENTS REFERENCE AND TESTING */    
  public static void main(String[] args)
  {
      PGM img = new PGM();
      img.showImage();
  }

    @Override
    protected int getRed(int row, int col) {
        return image[row][col];
    }

    @Override
    protected int getGreen(int row, int col) {
        return image[row][col];
    }

    @Override
    protected int getBlue(int row, int col) {
        return image[row][col];
    }
}
