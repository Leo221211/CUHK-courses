/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package type;

import java.nio.charset.Charset;

public class Type {
    public static void main(String[] args) {
        // miscellaneous
        char unicode = 'α';
        System.out.println(unicode);
        
        char c = 65;
        System.out.println(c);
        System.out.println(c + 1);
        System.out.println((char)(c + 1));
        
        // promotion
        byte b = 120;
        byte two = 2;
        byte mulCast = (byte) (b * two);
//        byte mul = b * two;   // error: already become an int 
//        byte mul2 = b * 2;
        byte four = 2 * 2;
//        byte four2 = two * two;   // error: is an int
        int i = b * two;
        
        char twochar = 2;
//        byte mul = b * twochar;   // char is also "int-similar"
        System.out.println(i + " " + mulCast + " " + four);
        
        // casting
        float f = 1;
        
        
    }
    
}
