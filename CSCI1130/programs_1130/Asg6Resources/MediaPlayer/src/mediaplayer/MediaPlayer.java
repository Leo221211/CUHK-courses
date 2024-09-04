package mediaplayer;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;

/**
 * Java Assignment Media Player
 * Focus: Inheritance and Polymorphism
 * @author Michael FUNG (pffung@cse.cuhk.edu.hk) and Dr Y.P. CHUI (ypchui@cse.cuhk.edu.hk)
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
public class MediaPlayer extends JFrame implements ActionListener {
    
    private final MP3FileFilter mp3FileFilter = new MP3FileFilter();
    private final PNMFileFilter pnmFileFilter = new PNMFileFilter();
    private final JButton pickSongButton = new JButton("Pick a song");
    private final JButton pickImageButton = new JButton("Pick some images");

    /** MediaPlayer constructor: initialize window using inherited methods from JFrame */
    public MediaPlayer()
    {
        setLayout(new GridLayout(2, 1));
        add(pickSongButton);
        add(pickImageButton);
        pickSongButton.addActionListener(this);
        pickImageButton.addActionListener(this);

/** TODO:
        set title: "Media Player"
        set size: 300 x 200
        set location: 400 x 100
        set default close operation: EXIT_ON_CLOSE
        set visible: true
 */
        setTitle("Media Player");
        setSize(300, 200);
        setLocation(400, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    /**
     * Callback/response method on JButton click action.
     * This method is declared in ActionListener interface.
     * This method will be invoked by Java AWT system to provide response on user action.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == pickSongButton)
            pickAndPlayMP3();
        else
            pickAndShowImages();
    }
    
    public void pickAndPlayMP3() {
        JFileChooser fileDialog = new JFileChooser();
        fileDialog.setCurrentDirectory(new File("."));
        fileDialog.setDialogTitle("Choose a MP3 file");
        fileDialog.setMultiSelectionEnabled(false);
        fileDialog.setFileFilter(mp3FileFilter);
        fileDialog.showOpenDialog(this);
        
        File f = fileDialog.getSelectedFile();
        if (f != null) {
/** TODO:
            Extract filename from f using method getPath()
            Create new MP3Player object with the filename
            Invoke MP3Player instance method playInBackground()
            
            // once a song is chosen, disable the button
            pickSongButton.setEnabled(false);
 */
            String filePath = f.getPath();
            MP3Player mp3Player = new MP3Player(filePath);
            mp3Player.playInBackground();
            
            // once a song is chosen, disable the button
            pickSongButton.setEnabled(false);
        }
    }
    
    public void pickAndShowImages()
    {
        JFileChooser fileDialog = new JFileChooser();
        fileDialog.setCurrentDirectory(new File("."));
        fileDialog.setDialogTitle("Choose SOME image file(s)");

        /* user may select multiple files using Ctrl/Shift/Meta keys */
        fileDialog.setMultiSelectionEnabled(true);
        
/** TODO:
        set pnmFileFilter
        show fileDialog
        
        obtain an array from getSelectedFiles()
         
        for each File f in the returned array:
            obtain the filename using getPath()
            declare a PNM variable img
            according to suffix of the filename, create corresponding PBM/PGM/PPM object
            img.showImage()
 */ 
        fileDialog.setFileFilter(pnmFileFilter);
        fileDialog.showOpenDialog(this);

        File[] selectedFiles = fileDialog.getSelectedFiles();
        
        if (selectedFiles != null) {
            for (File file : selectedFiles) {
                String fileName = file.getPath();
                PNM img;
                String fileExtension = fileName.substring(fileName.lastIndexOf('.') + 1);

                switch (fileExtension) {
                    case "pbm":
                        img = new PBM(fileName);
                        break;
                    case "pgm":
                        img = new PGM(fileName);
                        break;
                    case "ppm":
                        img = new PPM(fileName);
                        break;
                    default:
                        continue; // Skip files with unsupported extensions
                }

                img.showImage();
            }
        }
    }
            
    /**
     * MediaPlayer Application starts here.
     * Creating a MediaPlayer (JFrame subclass) object will start a new thread under AWT.
     * Therefore, the end of the main() method is NOT the end of the application yet.
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
/** TODO:
        create a new MediaPlayer object, thus calling the constructor
 */
        MediaPlayer mediaPlayer = new MediaPlayer();
//        mediaPlayer.testAllMediaClasses();
        
        System.out.println("MediaPlayer main() ends here.");
        System.out.println("Another AWT thread is still executing...");
        System.out.println("The application will end on closing the MediaPlayer window (EXIT_ON_CLOSE).");
    }

    /** FOR STUDENTS REFERENCE AND TESTING */
    private void testAllMediaClasses() {
        MP3Player song = new MP3Player();
        song.playInBackground();

        PNM img;
        img = new PPM("rgb_256.ppm");
        img.showImage();

        img = new PGM("peppers_256x256.pgm");
        img.showImage();

        img = new PBM("CUHK_QRcode.pbm");
        img.showImage();

        System.out.println("Exit to stop background music...");
        System.exit(0);
    }
}
