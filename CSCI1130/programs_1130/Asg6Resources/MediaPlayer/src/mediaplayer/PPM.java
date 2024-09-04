package mediaplayer;

import java.util.Scanner;

/**
 * Portable PixMap (RGB color image file in ASCII text) Java application
 * employs 3D array and file I/O
 *
 * @author Michael FUNG, YP CHUI
 *
 * PROVIDED CODE, DO NOT MODIFY
 */
public class PPM extends PNM {
  // instance field
  private int[][][] image;

  /** Default constructor for creating a sample image */
  public PPM() {
    imageName = "PPM Sample";
    header = "P3";
    width  = 3;
    height = 2;
    maxValue = 255;
    
    // note: height as row, width as column, 3 elements for RGB components
    //       if R, G, B values are the same, the pixel is black (0) / gray (1-254) / white (255)
    
    // array initializer can only be used during variable declaration
    int[][][] sample = {
      {{255,   0,   0}, {0, 255, 0}, {  0,   0 , 255}},
      {{127, 127, 127}, {0,   0, 0}, {255, 255, 255}}
    };
    image = sample;
  }

  /**
   * Constructor for reading a PGM image file.
   * @param filename
   */
  public PPM(String filename) {
    super(filename);
  }

  
  /**
   * Read a PGM file using a given Scanner.
   * @param reader is a Scanner object reference that has read a header properly already
   * @return true after finishing the action
   */
  @Override
  public boolean readPixels(Scanner reader) {
    try {
      if (header.charAt(1) != '3')
          throw new Exception("Wrong PPM header!");

      System.out.println("Reading PPM image of size " + width + "x" + height);

      // read maxValue
      maxValue = reader.nextInt();
      

      // pixel data reading loops
      image = new int[height][width][3];

      for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
          for (int rgb = 0; rgb < 3; rgb++) {
            int p = reader.nextInt();
            if (p > maxValue) {
              throw new Exception("Pixel value " + p + " on row " + row + ", col " + col + " out of range!");
            }

            image[row][col][rgb] = p;
          }
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
  
  public boolean write(String filename)
  {
    System.out.println("Writing PPM image " + filename);
    try {
      java.io.PrintStream ps = new java.io.PrintStream(filename);
      ps.println(header);
      ps.println(width + " " + height);
      ps.println(maxValue);
      for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
          for (int rgb = 0; rgb < 3; rgb++)
            ps.println(image[row][col][rgb]);
      ps.close();
    }
    catch (Exception e) {
      System.out.println("Failed to write PPM");
      return false;
    }
    return true;
  }

  /**
   * Provide implementation (override) the three methods getRed(), getGreen() and getBlue().
   * These methods shall return the CORRESPONDING value for a RGB pixel at given row and col.
   * @param row
   * @param col
   * @return int value in the range [0, 255]
   */
  @Override
  protected int getRed(int row, int col) {
      return image[row][col][0];
  }

  @Override
  protected int getGreen(int row, int col) {
      return image[row][col][1];
  }

  @Override
  protected int getBlue(int row, int col) {
      return image[row][col][2];
  }

  
  
  // private method for testing
  private void makeColorPalette()
  {
    width = 256;
    height = 256;
    maxValue = 255;
    image = new int[height][width][3];
    
    for (int row = 0; row < height; row++)
      for (int col = 0; col < width; col++)
      {
        image[row][col][0] = row;
        image[row][col][1] = col;
        image[row][col][2] = maxValue - row;
      }
  }

  /** FOR STUDENTS REFERENCE AND TESTING */    
  public static void main(String[] args)
  {
    PPM colorImg = new PPM();
    colorImg.showImage();
    colorImg.write("color6.ppm");

    colorImg.makeColorPalette();
    colorImg.showImage();
    colorImg.write("rgb_cube.ppm");
  }
}
