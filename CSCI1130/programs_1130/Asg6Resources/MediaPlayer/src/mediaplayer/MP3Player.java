package mediaplayer;

import javazoom.jl.player.JavaSoundAudioDeviceFactory;
import javazoom.jl.player.jlp;

/**
 * MP3Player class uses jlp (jLayer) services.
 * jLayer 1.0.2 is included as a JAR Library under this project.
 * MP3Player object supports playing music in both foreground and background.
 * @author pffung
 * 
 * PROVIDED CODE, DO NOT MODIFY
 */
public class MP3Player implements Runnable {

    // private instance fields
    private String filename;
    
    // Default constructor invokes another constructor through this() to set a default filename.
    public MP3Player()
    {
        this("cccollegesong.mp3");
    }
    
    // Constructor that initializes and plays MP3 with given filename.
    public MP3Player(String filename)
    {
        this.filename = filename;
    }
    
    // Play MP3 in background using another thread.
    public void playInBackground()
    {
        System.out.println("Playing " + filename + " in background...");
        Thread backgroundTask = new Thread(this);
        backgroundTask.start();
    }
    
    // Play MP3, either in foreground or in background
    @Override
    public void run()
    {
        try {
            jlp jLayerPlayerObj = new jlp(filename);
            jLayerPlayerObj.setAudioDevice(new JavaSoundAudioDeviceFactory().createAudioDevice());
            System.out.print("MP3Player.run() is ");
            jLayerPlayerObj.play();
        }
        catch (Exception e) {
            System.out.println("Failed to play MP3!");
        }
    }
    
    

    /** FOR STUDENTS REFERENCE AND TESTING */    
    public static void main(String[] args)
    {
        // play a song in background
        new MP3Player("ccsusong.mp3").playInBackground();
        
        // play default song in foreground
        new MP3Player().run();
    }
}
