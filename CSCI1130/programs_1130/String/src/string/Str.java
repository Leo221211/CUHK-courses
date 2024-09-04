/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package string;

import java.util.*;

/**
 *
 * @author ASUS
 */
public class Str {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // init 
        String str5 = new String("");
        System.out.println("["+str5+"]");
        
        
        // "" is null
        String nullStr =  "";
        System.out.println(nullStr == null);
        
        // init
        String str2 = new String();
        String str3 = "Hello World";
        
        System.out.println(str2 == null);
        
        // more API
        System.out.println("\n\nnow testing API");
        String toSplit = "  geekss@for@geeks@    ";
        String[] splitted = toSplit.split("@",0);
        
        for(int i = 0; i < splitted.length; i ++) {
            System.out.println(splitted[i]);
        }
        
        for(String spl : splitted) {
            System.out.println(spl);
        }
        
        Scanner strScn = new Scanner(toSplit);
        while(strScn.hasNext()) {
            break;
        }
        
        String str4 = new String("Hello");
        for(int i = 0; i < str4.length(); i ++) {
            System.out.println(str4.charAt(i));
        }
        
        System.out.println("       hello         ".trim().concat(" There"));
        
        System.out.println(String.valueOf(new Str()));
        
        System.out.println("\n\n\nNow testing String Builder");
        StringBuilder sb = new StringBuilder("");
        
        sb.append("Hello");
        sb.insert(1, "  ");
        sb.replace(1, 3, "[]");
        sb.delete(1, 4);
        sb.reverse();
        System.out.println(sb);
        
        
        System.out.println("12345".length());
    }
    
}
