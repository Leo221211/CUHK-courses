/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package inheritance;

import java.io.PrintStream;
import java.util.Scanner;

/**
 *
 * @author ASUS
 */
public class Inheritance {
    public static void main(String[] args) {
        Girl amy = new Girl();
        
       
       amy.eat();
       amy.run();
       amy.sing();
       amy.study();
       Girl.staticRun();
       
       System.out.println();
       
       Human human = new Girl();
       Girl bunny = (Girl)human;
       human.run();
       bunny.study();
//       human.study();
       human = new Human();
       human.run();
       
       
       
       // overriding fields
       System.out.println("now testing field overriding");
       System.out.println(amy.h + " " + human.h);
       System.out.println(amy.priv);
//       System.out.println(amy.hp);
       
       Integer i = 10;
       System.out.println(i);
       System.out.println(i.toString());
       
       System.out.println(amy);
       System.out.println(amy.toString());
       
       Human hu = new Girl();
       Girl gir;
       gir = (Girl)hu;
       
       Girl leonie = new Girl();
       Human ma;
       Human zhang = new Human();
//       ma = (Girl)zhang;
//       
//       
//       
//       
//       ((Girl)zhang).yima();
       
        Human eater;
        eater = new Girl();
        
        eater.eat();
//        eater.yima(); // wrong                              
       PrintStream s = System.out;
        Girl cindy = new Girl();
        boolean b = new Girl() instanceof Human;
        s.println(b);
        s.println(new Human() instanceof Human);
        s.println(new Girl() instanceof Human);
        s.println(new Human() instanceof Girl);
        
//        Human hh =  new Human();
//        ((Girl)hh).eat();
        
        
//        s.println(new Girl[12] instanceof Human);

        Student sdt;
        sdt = new Girl();
        sdt.study();
//        sdt.eat();  // wrong
        ((Girl)sdt).eat();
        ((Human)sdt).eat();
//        ((Human)sdt).study();     // wrong
        
        ((Student)amy).study();
        
//        ((Student)zhang).study();
//        ((Teacher)zhang).teach();     // both compile error
//        ((Scanner)zhang).hasNext();       // wrong

//        Girl pp = (Girl)new Human();
//        pp.eat();\

        Human xx = new Human();
//        Teacher t = ((Teacher)xx);
        
        Human yy = new Girl();
        Girl zz = (Girl) new Human();
    }
    
    
        
    
}
