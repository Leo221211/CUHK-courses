package image;

/**
 * AsciiArt
 * Java application employs 2D array and file I/O
 * @author YP Chui
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
 *   http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : Muquan YU
 * Student ID   : 1155191596
 * Class/Section: CSCI1130B
 * Date         : 26 Nov 2023
 */
public class AsciiArt {

    /**
     * main() method, starting point of the Java application.
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception { 

        String filename;        

        PGM pgmSimple;
        pgmSimple = new PGM();
        pgmSimple.showImage();
        
        PGM pgmDefault;
        pgmDefault = new PGM("MidGray", 40, 30);
        pgmDefault.showImage();
        
        filename = "WRONG_FILENAME.ppm";
        PGM imgFileCorrupted;
        imgFileCorrupted = new PGM(filename);
        imgFileCorrupted.showImage();

        // Uncomment the following lines after PGM methods are implemente
        filename = "cameraman_256x256.pgm";
//        filename = "lake_256x256.pgm";
//        filename = "peppers_256x256.pgm";
        
        PGM imgFileNormal;
        imgFileNormal = new PGM(filename);
        imgFileNormal.showImage();

        PGM pgmDownsampled;
        pgmDownsampled = imgFileNormal.halfsize();
        pgmDownsampled.showImage();
        pgmDownsampled.exportAsciiArt("ascii_art.txt");    
    }
    
}
