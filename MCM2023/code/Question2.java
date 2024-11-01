import java.lang.Math;
import java.util.Scanner;

public class Question2 {
    public static Question1 q1 = new Question1();
    public static Question2 obj = new Question2();

    public double calNewAlpha(double oldAlpha, double beta){
        return Math.atan(Math.tan(oldAlpha) * Math.cos(beta - q1.toRad(90)));
    }

    public double nauticalToMeter(double nau){
        return nau * 1852;
    }

    public static void main(String[] args){
        // initialize data
        double ans[][] = new double[8][8];
        q1.theta = q1.toRad(120);
        q1.D = 120;
        q1.d = obj.nauticalToMeter(0.3);
        double oldAlpha = q1.toRad(1.5);

        // loop answer
        for(int betaIndex = 0; betaIndex <= 7; betaIndex ++)
        {
            for(int n = 0; n <= 7; n ++)
            {
                // initialize
                double beta = q1.toRad(betaIndex * 45);
                q1.alpha = obj.calNewAlpha(oldAlpha, beta);

                double h = q1.returnh(n);
                ans[betaIndex][n] = q1.returnW(h);
            }
        }

        // print answer
        for (int i = 0; i < ans.length; i++) {
            for (int j = 0; j < ans[i].length; j++) {
                String formattedNumber = String.format("%.2f", ans[i][j]);
                System.out.print(formattedNumber + " ");
            }
            System.out.println();
        }
    }
}
