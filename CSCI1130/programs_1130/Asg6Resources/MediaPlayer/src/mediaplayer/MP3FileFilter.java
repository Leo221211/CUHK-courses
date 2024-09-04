package mediaplayer;

import java.io.File;
import javax.swing.filechooser.FileFilter;

/**
 * MP3 File Filter is a subclass (implementation/realization) of abstract class FileFilter.
 * @author pffung
 * 
 * PROVIDED CODE, DO NOT MODIFY
 */
public class MP3FileFilter extends FileFilter { 
    @Override
    public String getDescription() {
        return "MP3 files (*.mp3)";
    }

    @Override
    public boolean accept(File f) {
        if (f.isDirectory()) {
            return true;
        } else {
            String filename = f.getName().toLowerCase();
            return filename.endsWith(".mp3");
        }
    }    
}
