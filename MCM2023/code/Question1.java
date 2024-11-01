// all angle should be radius, all length in meter UNLESS STATED

import java.lang.Math;
import java.util.Scanner;
// import java.util.zip.CRC32;

public class Question1{
    // public double alpha = 1.5 * Math.PI / 180;
    public double alpha = toRad(1.5);
    public double D = 70;
    public double theta = toRad(120);
    public double d = 200;

    public static Question1 obj = new Question1();

    public double toRad(double degree){
        return degree * Math.PI / 180;
    }

    public double nauticalToMeter(double nau){
        return nau * 1852;
    }

    public double returnh(double n){
        double s = n * d;
        return D - s * Math.tan(alpha);
    }

    public double returnhs(double s){
        return D - s * Math.tan(alpha);
    }

    public double calx1(double h){
        return h / (Math.tan(alpha) - Math.tan(Math.PI/2 - theta/2));
    }

    public double calx2(double h){
        return h / (Math.tan(alpha) + Math.tan(Math.PI/2 - theta/2));
    }

    public double returnW(double h){
        return calx2(h) - calx1(h);
    }

    public double returneta(double n, double h, double W)
    {
        double hprime = returnh(n - 1);
        double x1 = calx1(h);
        double x2prime = calx2(hprime) - d;
        double eta = (x2prime - x1) / W;

        // System.out.println(hprime);
        // System.out.println(x2prime);

        return eta;
    }

    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        double n = input.nextDouble();
        input.close();

        // // new object
        // Question1 obj = new Question1();

        // calculate h
        double h = obj.returnh(n);
        System.out.println("h = " + h);

        // calculate W
        double W = obj.returnW(h);
        System.out.println("W = " + W);
        
        // calculate eta
        double eta = obj.returneta(n, h, W);
        System.out.println("eta = " + eta*100 + "%");
    }
}