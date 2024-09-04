package mediaplayer;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Scanner;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;

/**
 * Portable Any Map (Netpbm/ PNM image file in ASCII text) Java application
 * employs 2D array and file I/O
 *
 * @author Michael FUNG, YP CHUI
 * 
 * PROVIDED CODE, DO NOT MODIFY
 */
public abstract class PNM {
  // instance fields
  protected String imageName;
  protected String header;
  protected int width, height;
  protected int maxValue;

  /** Default constructor for creating an undefined image */
  public PNM() {
    imageName = this.getClass().getSimpleName();
    header = "P?";
    width  = -1;
    height = -1;
    maxValue = 255;  // default max value in pixel data
  }

  /**
   * Constructor for reading an image file.
   * This "super" constructor will read the file header, and then
   * invoke the abstract readPixels() method provided by the subclasses.
   * @param filename is an image filename
   */
  public PNM(String filename) {
    this.imageName = filename;
    Scanner reader = readHeader(filename);
    if (reader != null)
    {
        readPixels(reader);
        reader.close();
    }
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
   * Read an image file.
   * @param filename is an image filename
   * @return Scanner proper object reference for further processing pixel data
   * @return null if this operation failed
   */
  private Scanner readHeader(String filename)
  {
    try {
      System.out.println("Reading image file " + filename);

      File f = new File(filename);
      Scanner reader = new Scanner(f);

      header = reader.nextLine();
      if (header == null || header.length() < 2 || header.charAt(0) != 'P' || 
          (header.charAt(1) < '1' || header.charAt(1) > '6'))
      {
        throw new Exception("Wrong PNM header!");
      }

      String dimensions;
      do { // skip lines (if any) start with '#'
        dimensions = reader.nextLine();
      } while (dimensions.charAt(0) == '#');

      // interpret width and height from last non-comment line
      Scanner dimensionsInterpreter = new Scanner(dimensions);
      width = dimensionsInterpreter.nextInt();
      height = dimensionsInterpreter.nextInt();

      // Scanner reader object reference is returned 
      // for further processing the maxValue and pixel data that follows

      return reader;
    }
    catch (Exception e) {
      header = "P?";
      width  = -1;
      height = -1;
    }
    return null;
  }

  /**
   * Abstract method for reading pixel data from an image file through reader.
   * This method is to be overridden and provided by the subclasses.
   * @param reader is a Scanner object reference
   * @return true after finishing the action successfully
   */
  protected abstract boolean readPixels(Scanner reader);

  /**
   * Abstract methods for reading pixel RGB value at [row][col].
   * These methods are to be overridden and provided by the subclasses.
   * @param row is pixel row number starts at 0, from top to bottom
   * @param col is pixel col number starts at 0, from left to right
   * @return an int value in the range of [0, 255]
   */
  protected abstract int getRed(int row, int col);
  protected abstract int getGreen(int row, int col);
  protected abstract int getBlue(int row, int col);
  
  
  
  /**
   * Show image on screen, with proper scaling.
   * This method depends on getRed(), getGreen() and getBlue() methods
   * that are to be implemented in the subclasses.
   */
  public void showImage() {
    if (getHeight() <= 0 || getWidth() <= 0) {
      JOptionPane.showConfirmDialog(null, "Width x Height = " + getWidth() + "x" + getHeight(), imageName + " corrupted!", JOptionPane.CLOSED_OPTION, JOptionPane.ERROR_MESSAGE, null);
      return;
    }

    BufferedImage img = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_RGB);

    for (int row = 0; row < getHeight(); row++) {
      for (int col = 0; col < getWidth(); col++) {
        // gray and white pixels shall have SAME red, green, blue values
        // color pixels contains a mixture of red, green, blue values

        // expect returned int values in the range [0, 255]
        int red   = getRed(row, col);
        int green = getGreen(row, col);
        int blue  = getBlue(row, col);
        int rgb24BitValue = (red << 16) + (green << 8) + blue;
        //System.out.printf("DEBUG: row %d, col %d, red %d, green %d, blue %d, BitValue %08X\n", row, col, red, green, blue, rgb24BitValue);
        img.setRGB(col, row, rgb24BitValue);
      }
    }

    // scale the image for showing
    Image scaledImg;
    if (getWidth() > getHeight())
        scaledImg = img.getScaledInstance(256, -1, java.awt.Image.SCALE_SMOOTH);
    else
        scaledImg = img.getScaledInstance(-1, 256, java.awt.Image.SCALE_SMOOTH);
    
    JOptionPane.showConfirmDialog(null, "Width x Height = " + getWidth() + "x" + getHeight(), imageName, JOptionPane.CLOSED_OPTION, JOptionPane.INFORMATION_MESSAGE, new ImageIcon(scaledImg));
  }
}
