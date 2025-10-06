import java.util.Scanner;
public class Main{
    static final long MOD = 1234567891;
    public static long modPow(int a, int b){
        long res = 1;
        for(int i = 0; i < b; ++i){
            res=(res*a)%MOD;
        }
        return res;
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        String s = scan.next();
        long sum = 0;
        for(int i = 0; i < n; ++i){
            sum=(sum+((s.charAt(i)-96)*modPow(31,i))%MOD)%MOD;
        }
        System.out.println(sum);
    }
}