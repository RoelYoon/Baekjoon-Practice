import java.util.Scanner;
import java.util.Arrays;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        while(true){
            long[] sides = new long[3];
            sides[0]=scan.nextInt();
            sides[1]=scan.nextInt();
            sides[2]=scan.nextInt();
            if(sides[0]==0 && sides[1]==0 && sides[2]==0){
                return;
            }
            Arrays.sort(sides);
            System.out.println((sides[0]*sides[0]+sides[1]*sides[1]==sides[2]*sides[2]?"right":"wrong"));
        }        
    }
}