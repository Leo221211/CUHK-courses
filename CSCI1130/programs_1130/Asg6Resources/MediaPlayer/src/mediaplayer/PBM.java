package mediaplayer;

import java.util.Scanner;

/**
 * Portable BitMap (Black-and-White image file in ASCII text) Java application
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
public class PBM extends PNM {
  // instance field
  private int[][] image;

  /** Default constructor for creating a sample image */
  public PBM() {
    // note: height as row, width as column, 0 means black, 1 means white

    // array initializer can only be used during variable declaration
    int[][] CUHK_qrcode = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0},
        {0,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1,0},
        {0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0},
        {0,1,0,1,1,1,0,1,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0},
        {0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,0,0,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0},
        {0,1,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0},
        {0,1,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0},
        {0,1,0,1,0,0,1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,0},
        {0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0},
        {0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,0},
        {0,1,1,1,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0},
        {0,1,0,0,0,0,0,1,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0},
        {0,1,0,1,1,1,0,1,0,0,0,1,1,0,1,0,0,1,0,1,0,0,0},
        {0,1,0,1,1,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0},
        {0,1,0,1,1,1,0,1,0,0,0,1,1,1,1,0,1,1,1,0,1,1,0},
        {0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0},
        {0,1,1,1,1,1,1,1,0,1,1,0,0,1,0,0,1,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    image = CUHK_qrcode;

/** TODO:    
    assign imageName with "PBM Sample"
    assign header with "P1"
    assign width with CUHK_qrcode row 0 width
    assign height with CUHK_qrcode height (number of rows)
    assign maxValue with 1
 */
    imageName = "PBM Sample";
    header = "P1";
    width = CUHK_qrcode[0].length;
    height = CUHK_qrcode.length;
    maxValue = 1;
  }

  /**
   * Constructor for reading a PBM image file
   * @param filename
   */
  public PBM(String filename) {
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
    validate if header is P1
    assign maxValue with 1 (NEED NOT read maxValue from reader, it's NOT AVAILABLE in PBM!)
    create 2D array
    read pixel data
    return false on all abnormalities (and set height and width to -1)
*/
    try {
        if (header.charAt(1) != '1') {
            throw new Exception("Wrong PBM header!");
        }
        
        System.out.println("Reading PBM image of size " + width + "x" + height);

        maxValue = 1;
        
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
   * ALL three methods shall return the SAME value for a B/W pixel at given row and col.
   * @param row
   * @param col
   * @return int value 0 (for black) or 255 (for white)
   */
  

  
  /** FOR STUDENTS REFERENCE AND TESTING */    
  public static void main(String[] args)
  {
      PBM img = new PBM();
      img.showImage();
  }

    @Override
    protected int getRed(int row, int col) {
        if(image[row][col] == 0) {
            return 0;
        } else {
            return 255;
        }
    }

    @Override
    protected int getGreen(int row, int col) {
        if(image[row][col] == 0) {
            return 0;
        } else {
            return 255;
        }
    }

    @Override
    protected int getBlue(int row, int col) {
        if(image[row][col] == 0) {
            return 0;
        } else {
            return 255;
        }
    }
  
}
