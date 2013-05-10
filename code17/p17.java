import java.math.BigInteger;
import java.util.Scanner;
public class p17
{
  public static void main (String args[]) throws Exception
  {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextInt()) {
      int N = sc.nextInt();
      BigInteger M = factorial (N);
      System.out.println (sumDigits(M));
  
    }
  }
  public static BigInteger factorial (int a)
  {
    BigInteger ans = BigInteger.ONE;
    for (int i = 1; i <= a; i++)
    {
      
      BigInteger factor = new BigInteger (String.valueOf(i));
      
      ans = ans.multiply(factor);
    }
    return ans;
  }
  public static int sumDigits (BigInteger b)
  {
    String s = b.toString();
    int ans = 0;
    for (int i = 0; i < s.length(); i++)
      ans += s.charAt(i)-'0';
    return ans;
  }
}