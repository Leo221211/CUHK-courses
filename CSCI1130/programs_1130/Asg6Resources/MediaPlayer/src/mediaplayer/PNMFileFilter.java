package mediaplayer;

import java.io.File;
import javax.swing.filechooser.FileFilter;

/**
 * PNM File Filter is a subclass (implementation/realization) of abstract class FileFilter.
 * @author pffung
 * 
 * PROVIDED CODE, DO NOT MODIFY
 */
public class PNMFileFilter extends FileFilter {
    @Override
    public String getDescription() {
        return "PNM images (*.pbm, *.pgm, *.ppm)";
    }

    @Override
    public boolean accept(File f) {
        if (f.isDirectory()) {
            return true;
        } else {
            String filename = f.getName().toLowerCase();
            return filename.endsWith(".pbm") ||
                    filename.endsWith(".pgm") ||
                    filename.endsWith(".ppm");
        }
    }    
}
