import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        long n = scan.nextLong();
        long l=1,h=(long)1e9;
        while(l<h){
            long x = l+(h-l)/2;
            if(1+(3*x*(x-1)) >= n){
                h=x;
            }
            else{
                l=x+1;
            }
        }
        System.out.println(l);
    }
}