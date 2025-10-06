import java.util.Scanner;
public class Main{
    public static int generate(int c){
        int sum = c;
        String s = Integer.toString(c);
        for(int i = 0; i < s.length(); ++i){
            sum+=s.charAt(i)-48;
        }
        return sum;
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String num = scan.next();
        int reach = num.length() * 9;
        int dNum = Integer.parseInt(num);
        int c = Math.max(0,dNum-reach);
        for(; c<dNum; ++c){
            if(generate(c)==dNum){
                System.out.println(c);
                return;
            }
        }
        System.out.println(0);
    }
}