package tool;

import java.util.Scanner;

/**
 * CSCI1130 Assignment HSI_ArrayList
 * Record abstracts a trading record.
 * @author pffung
 * @since 2023
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
 * Faculty of Engineering Guidelines to Academic Honesty:
 *   http://www.erg.cuhk.edu.hk/erg-intra/upload/documents/ENGG_Discipline.pdf
 *
 * Student Name: Muquan YU
 * Student ID  : 1155191596
 * Date        : 30 Oct 2023
 */
public class Record {
    private String date;
    private double open;
    private double high;
    private double low;
    private double close;
    private double adjClose;
    private double volume;
    
    /**
     * Constructor taking individual parameters for all fields.
     * @param d is a date String in the form of "YYYY-MM-DD"
     * @param o is open
     * @param h is high
     * @param l is low
     * @param c is close
     * @param adjC is adjusted close
     * @param v is volume
     */
    public Record(String d, double o, double h, double l, double c, double adjC, double v)
    {
        date = d;
        open = o;
        high = h;
        low =  l;
        close = c;
        adjClose = adjC;
        volume = v;
    }
    
    /**
     * Constructor taking a CSV String parameter in the form of:
     *       DateInYYYY-MM-DD,Open,High,Low,Close,AdjustedClose,Volume
     * E.g.: 2022-10-19,16805.910156,16923.119141,16508.369141,16511.279297,16511.279297,1713974900
     * @param s is a String containing a comma-delimited line of CSV trading record
     */
    public Record(String s)
    {
        // create scanner
        Scanner strScn = new Scanner(s).useDelimiter(",");
        
        // scan
        date = strScn.next();
        open = strScn.nextDouble();
        high = strScn.nextDouble();
        low =  strScn.nextDouble();
        close =strScn.nextDouble();
        adjClose = strScn.nextDouble();
        volume = strScn.nextDouble();
    }
    
    public String getDate()
    {
        return date;
    }
    
    public double getChange()
    {
        // STUDENT WORK HERE
        return close - open;
    }
    
    public double getRange()
    {
        // STUDENT WORK HERE
        return high - low;

    }
    
    @Override
    public String toString()
    {
        String representation;
        representation = date;
        representation += " close: " + String.format("%.2f", close);
        // STUDENT WORK HERE
        representation += " change: " + String.format("%.2f", getChange());
        representation += " range: " + String.format("%.2f", getRange());
        
        return representation;
    }
}
