//package tool;
package tool;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * CSCI1130 Assignment HSI_ArrayList
 * @author pffung
 * @since 2023
 *
 * I declare that the assignment here submitted is original
 * except for source material explicitly acknowled;
ged,
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
public class HSI_ArrayList {

    private History hsiHistory;
    
    public HSI_ArrayList(String filename)
    {
        // STUDENT WORK 
        System.out.println("Reading [" + filename + "]");
        
        hsiHistory = new History();
        try{
            // scanner
            Scanner fileScn = new Scanner(new File(filename));
            
            // print header
            System.out.println("Header: " + fileScn.nextLine());
            
            // add to history
            while(fileScn.hasNextLine()){
                Record r = new Record(fileScn.nextLine());
                hsiHistory.add(r);
            }
        }
        catch(FileNotFoundException fnfException){
            System.err.println("File not found!");
        }
    }
    
    public void hardCodeRecords()
    {
        System.out.println("Hardcoding records");
        Record r = new Record("2024-01-02", 20000, 21900, 19300, 20500, 20500, 100000000);
        hsiHistory.add(r);
        hsiHistory.add(new Record("2024-01-03", 20500, 21700, 18300, 20300, 20300, 200000000));
        hsiHistory.add(new Record("2024-01-04", 20300, 22450, 19050, 20000, 20000, 300000000));
    }
    
    // STUDENT WORK HERE
    public boolean isEmpty(){
        return hsiHistory.isEmpty();
    }

    public void list(){
        for(int i = 0; i < hsiHistory.size(); i++){
            System.out.println(hsiHistory.get(i).toString());
        }
        
        System.out.println("History size: " + hsiHistory.size());
    }
    
    public int findGainDays(){
        // count and sum
        int gainCnt = 0;
        double gainSum = 0;
        
        for(int i = 0; i < hsiHistory.size(); i++){
            if(hsiHistory.get(i).getChange() > 0){
                gainCnt ++;
                gainSum += hsiHistory.get(i).getChange();
            }
        }
        
        // print and return
        System.out.println("Total gain: " + String.format("%.2f", gainSum));
        return gainCnt;
    }
    
    public int findLossDays(){
        // count and sum
        int lossCnt = 0;
        double lossSum = 0;
        
        for(int i = 0; i < hsiHistory.size(); i++){
            if(hsiHistory.get(i).getChange() < 0){
                lossCnt ++;
                lossSum += hsiHistory.get(i).getChange();
            }
        }
        
        // print and return
        System.out.println("Total loss: " + String.format("%.2f", lossSum));
        return lossCnt;
    }

    public String findMostRecentDateOfLargestRange(){
        double maxRange = 0;
        String mostRecentDate = hsiHistory.get(0).getDate();
        
        for(int i = 0; i < hsiHistory.size(); i++){
            // double diff = maxRange - hsiHistory.get(i).getRange();
            // System.out.println("diff " + diff);
            if(maxRange - hsiHistory.get(i).getRange() <= 1e-9){
                maxRange = hsiHistory.get(i).getRange();
                mostRecentDate = hsiHistory.get(i).getDate();
            }
        }
        
        // return
        return mostRecentDate;
    }
    // Hint for method findMostRecentDateOfLargestRange():
    // - use floating-point comparison to find largest range
    // - we need a tie-breaking rule shall there be same OR VERY-NEAR max values
    // - we can process the records sequentially, i.e., chronologically
    // - we may use this checking condition (maxRange - r.getRange() <= 1e-9)
    // - simple condition (maxRange <= r.getRange()) may fail sometimes



    /**
     * main() method is given
     * DO NOT MODIFY
     * @param args
     */
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        
        System.out.print("Input HSI filename (.csv): ");
        String filename = keyboard.nextLine();
//        filename = "hsi2023.csv"; /* TEST/DEBUG */

        HSI_ArrayList obj;

        obj = new HSI_ArrayList(filename);

        if (obj.isEmpty())
            obj.hardCodeRecords();
        
        obj.list();

        System.out.println("Number of gain days: " + obj.findGainDays());
        System.out.println("Number of loss days: " + obj.findLossDays());
        System.out.println("Most recent date of largest range: " + obj.findMostRecentDateOfLargestRange());
    }
    
}
