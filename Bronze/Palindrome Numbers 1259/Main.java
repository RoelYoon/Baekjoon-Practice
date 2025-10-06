import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        outer:
        while(true){
            String num = scan.next();
            if(num.equals("0")){
                break;
            }
            int j = num.length()-1;
            for(int i = 0; i < num.length();--j,++i){

                if(num.charAt(i) != num.charAt(j)){
                    System.out.println("no");
                    continue outer;
                }
            }
            System.out.println("yes");
        }
    }
}