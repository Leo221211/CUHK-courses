/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package traceme;

/**
 *
 * @author ASUS
 */
public class TraceMe {
    public static void unknownOperation(int[] inputs) {
        int m, t;
        for (int i= 0; i < inputs.length - 1; i++) {
            m = i;
            for (int j= i+1; j < inputs.length; j++) 
                if (inputs[j]< inputs[m])
                    m=j;
            
            t =inputs[i];
            inputs[i] = inputs[m];
            inputs[m] = t;
        }
    }
    
    public static void main(String[] args) {
        int i[]={1,2,3,-4,-5,-6,7,8,9,-10};
        int prime[] ={2,3,5,7,11,13,17,19,23,29};
        int temp;
        
        unknownOperation(i);
        
        for (int j=0;j< 10; j++)
            System.out.print(i[j] + " ");
        
        System.out.println();
        
        for (int j=0;j<10;j++){
            try{ 
                temp = prime[i[j]];
                System.out.print(temp + " " );
            }
            catch (ArrayIndexOutOfBoundsException e) {
                System.out.print("e " );
            }
        }
        System.out.println();
    }
}
