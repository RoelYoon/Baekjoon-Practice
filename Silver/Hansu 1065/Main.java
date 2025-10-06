import java.util.Scanner;
public class Main{
    public static boolean isHansu(int n){
        String s = Integer.toString(n);
        if(s.length()<2) return true;
        int d = (s.charAt(1)-48)-(s.charAt(0)-48);
        for(int i = 1; i < s.length()-1; ++i){
            if((s.charAt(i+1)-48)-(s.charAt(i)-48) != d){
                return false;
            }
        }
        return true;
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt(), cnt=0;
        for(int i = 1; i <= n; ++i){
            cnt+=(isHansu(i)?1:0);
        }
        System.out.println(cnt);
    }
}