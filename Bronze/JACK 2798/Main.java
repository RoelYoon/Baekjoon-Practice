import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n=scan.nextInt(),m=scan.nextInt();
        int[] nums = new int[n];
        for(int i = 0; i < n; ++i){
            nums[i]=scan.nextInt();
        }
        int mx = 0;
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                for(int k = j+1; k < n; ++k){
                    int sum = nums[i]+nums[j]+nums[k];
                    if(sum<=m && sum>mx){
                        mx=sum;
                    }
                }
            }
        }
        System.out.println(mx);
    }
}