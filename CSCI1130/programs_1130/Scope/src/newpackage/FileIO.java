/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package newpackage;

import java.util.*;
import java.io.*;
import java.net.*;

/**
 *
 * @author ASUS
 */
public class FileIO {
    public static void main(String[] args) throws IOException {
        URL link = new URL("http://www.hko.gov.hk");
        Scanner net = new Scanner(link.openStream());
        
        while (net.hasNext()) {
            System.out.println(net.nextLine());
        }
    }
    
    
}
