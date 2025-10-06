import java.util.Scanner;
public class Main{
    public static boolean isPrime(int n){
        if(n<=1) return false;
        for(int i = 2; i*i<=n; ++i){
            if(n%i==0){
                return false;
            }
        }
        return true;
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            int x = scan.nextInt();
            cnt+=(isPrime(x)?1:0);
        }
        System.out.println(cnt);
    }
}