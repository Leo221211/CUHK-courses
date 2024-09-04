/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package complexnumber;

import java.util.Scanner;

/**
 *
 * @author ASUS
 */
public class ComplexNumber {

    private int a, b;
    
    public ComplexNumber(int real, int imagine) {
        a = real;
        b = imagine;
    }
    
    public String toString() {
        if (a == 0 && b == 0) {
            return "0";
        }
        else if(a == 0 && b != 0) {
            return b + "i";
        }
        else if (a != 0 && b == 0) {
//            return a.toString();
            return String.valueOf(a);
        }
        else {
            return String.format("%d%+di", a, b);
        }
    }
    
    public ComplexNumber sum (ComplexNumber c) {
        ComplexNumber newCN = new ComplexNumber (this.a, this.b);
        newCN.a += c.a;
        newCN.b += c.b;
        return newCN;
    }
    
    public ComplexNumber product (ComplexNumber c) {
        ComplexNumber newCN = new ComplexNumber(a, b);
        newCN.a = this.a*c.a - this.b*c.b;
        newCN.b = this.b*c.a + this.a*c.b;
        return newCN;
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner scn = new Scanner(System.in);
        
        ComplexNumber w = new ComplexNumber(scn.nextInt(), scn.nextInt());
        ComplexNumber x = new ComplexNumber(scn.nextInt(), scn.nextInt());
        System.out.println(w.sum(x) + "\n" + w.product(x));
        
        w = new ComplexNumber(scn.nextInt(), scn.nextInt());
        x = new ComplexNumber(scn.nextInt(), scn.nextInt());
        System.out.println(w.sum(x) + "\n" + w.product(x));
        
        
        
    }
    
}
