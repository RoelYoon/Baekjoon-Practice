import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] l = new int[n];
        int mx = 0;
        double avg = 0;
        for(int i = 0; i < n; ++i){
            l[i] = scan.nextInt();
            mx=Math.max(mx,l[i]);
        }
        for(int i = 0; i < n; ++i){
            avg+=((double)l[i]/mx*100.0D);
        }
        System.out.printf("%.3f\n",avg/n);
    }
}