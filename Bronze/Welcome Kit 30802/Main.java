import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        long n = scan.nextInt();
        long[] sizes = new long[6];
        for(int i = 0; i < 6; ++i){
            sizes[i] = scan.nextInt();
        }
        long t=scan.nextInt(),p=scan.nextInt();
        long shirtCnt=0;
        for(int i = 0; i < 6; ++i){
            long lo=0,hi=(long)1e9;
            while(lo<hi){
                long mid = lo+(hi-lo)/2;
                if(mid*t >= sizes[i]){
                    hi = mid;
                }else{
                    lo = mid+1;
                }
            }
            shirtCnt+=lo;
        }
        System.out.printf("%d%n%d %d",shirtCnt,n/p,(n%p));
    }
}