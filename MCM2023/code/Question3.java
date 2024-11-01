import java.lang.Math;

public class Question3 {
    public static Question1 q1 = new Question1();
    public static Question3 obj = new Question3();

    public void printCurLine(){
        System.out.println(Thread.currentThread().getStackTrace()[2].getLineNumber());
    }

    public double calEtaQ3(double curPos, double lastPos){
        double hCur = q1.returnhs(curPos);
        double x1 = q1.calx1(hCur);
        double hLast = q1.returnhs(lastPos);
        double x2prime = q1.calx2(hLast) - (curPos - lastPos);
        double W = q1.returnW(hCur);

        return (x2prime - x1) / W;
    }

    public double biSearchEta(double left, double right, double lastPos){
        double delta = 0.00001;
        double temp = 0;
        // System.out.println("temp left right" + temp+ " " +left+" " + right);
        // System.out.println("here " + temp);

        while(true){
            temp = (left + right) / 2;
            // System.out.println("temp left right" + temp+ " " +left+" " + right);
            double curEta = calEtaQ3(temp, lastPos);
            // System.out.println(curEta);
            // obj.printCurLine();
            if(0.1 <= curEta && curEta <= 0.1 + delta)
            {
                // System.out.println("Current Pos: " + temp + " eta " + curEta);
                // System.out.println(temp +" "+curEta);
                return temp;
            }
            else if(curEta < 0.1)   // too far
            {
                // System.out.println("curEta: " + curEta);
                // obj.printCurLine();
                right = temp;
                // System.out.println("right " + right);
            }
            else{
                // obj.printCurLine();
                left = temp;
            }
        }
    }

    public static void main(String[] args){
        // initialize
        double nslen = q1.nauticalToMeter(2);
        double welen = q1.nauticalToMeter(4);
        // System.out.println(welen);
        q1.alpha = q1.toRad(1.5);
        // See most west is central
        q1.D = 110 + welen / 2 * Math.tan(q1.alpha);
        q1.theta = q1.toRad(120);

        int lineIdx = 0;
        double linePos[] = new double[1000];

        // cal first position
        linePos[lineIdx] = q1.D * Math.tan(q1.theta / 2);
        // System.out.println(linePos[lineIdx]);
        lineIdx ++;

        // cal lastSectionLeft
        double h0 =  110 - welen / 2 * Math.tan(q1.alpha);
        double lastSectionLeft = welen - h0 * Math.tan(q1.theta / 2);
        // System.out.println("LSL" + lastSectionLeft);

        // obj.printCurLine();
        // while pos not in range, bisearch find next
        do{
            linePos[lineIdx] = obj.biSearchEta(linePos[lineIdx - 1], welen, linePos[lineIdx -1]);
            lineIdx ++;
            // System.out.println("index Pos" + lineIdx + " " + linePos[lineIdx - 1]);
        }while(linePos[lineIdx - 1] <= lastSectionLeft);

        // obj.printCurLine();

        // cal total len
        System.out.println(lineIdx + " lines in total;");
        for(int i = 0; i < lineIdx; i ++)
        {
            System.out.printf("%.2f, ", linePos[i]);
        }
        System.out.println();

        System.out.println("Total length = " + lineIdx * nslen + " meters");
    }
}
