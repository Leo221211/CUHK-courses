




class TrickyComparison
{
    public static void main(String[] args)
    {
        double high1 = 20000.100000, low1 = 10000.000000;
        double high2 = 20000.200000, low2 = 10000.100000;
        double range1 = high1 - low1, range2 = high2 - low2;
        System.out.printf("range1: %.15f\n", range1);
        System.out.printf("range2: %.15f\n", range2);
        System.out.println("range1 >  range2? " + (range1 >  range2) );
        System.out.println("range1 == range2? " + (range1 == range2) );
        System.out.println("range1 <  range2? " + (range1 <  range2) );
        System.out.println("range1 <= range2? " + (range1 <= range2) );
        System.out.println("range1 >= range2? " + (range1 >= range2) );
    }
}
