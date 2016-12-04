import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		String a = sc.next();
		String b = sc.next();
		System.out.println(before(b,n) - before(a,n) - 1);
	}

	public static long before(String x, int n) {
		if(n == 0) return 0;
		
		char bit = x.charAt(x.length() - n);
		if(bit == '1') {
			return (1L << (n - 1)) + after(x, n - 1);
		} else {
			return before(x, n - 1);
		}
	}

	public static long after(String x, int n) {
		if(n == 0) return 0;
		
		char bit = x.charAt(x.length() - n);
		if(bit == '1') {
			return before(x, n - 1);
		} else {
			return (1L << (n - 1)) + after(x, n - 1);
		}
	}
}
