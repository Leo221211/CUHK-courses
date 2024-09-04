/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package arrayandtable;

import java.util.*;

/**
 *
 * @author ASUS
 */
public class ArrayAndTable {

    public static void main(String[] args) {
        int[][] pixels;
        pixels = new int[][] {{1, 2}, {}};
        
        
        int[][] pixelss;
        pixelss = new int[2][1];
        pixelss = new int[][]{{}};
        
        // pixelss = {{}};  // incorrect
        
        // init 
        int[] arr1 = {1,2,3};
        arr1 =  new int[4];
        int[][] table1 = {
            {1,2,3},
            {2,3},
            {1,2,3}
        };
        System.out.println(table1[0][2] + " " + table1[1].length);
        System.out.println("table1: " + table1[1]);
        
        int[] arr = {1,2};
        for(int i : arr) {
            System.out.println(i);
        }
        
        System.out.println("\n\n\nNow testing array API");
        double[] numbers = {Math.PI, Math.E, Math.pow(Math.E, Math.PI), Math.pow(Math.PI, Math.PI), Math.TAU, Math.sin(10)};
        System.out.println(Arrays.binarySearch(numbers, Math.TAU));
        Arrays.sort(numbers);
        
        for(double d : numbers) {
            System.out.printf("%.2f ", d);
        }
        System.out.println();
        
        
        System.out.println("\n\n\nNow testing 2D array");
        Scanner[][] table = new Scanner[3][];
        
        table[0] = new Scanner[3];
        table[1] = table[0];
        table[2] = new Scanner[2];
    }
    
}
