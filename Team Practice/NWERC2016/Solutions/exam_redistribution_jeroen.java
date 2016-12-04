import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[] s = new int[n];
		String[] ps = in.readLine().split(" ");
		for(int i = 0; i < n; i++)
			s[i] = Integer.valueOf(ps[i]);

		// Find biggest and sum
		int sum = 0;
		int start = 0;
		for(int i = 0; i < n; i++) {
			sum += s[i];
			if(s[i] > s[start])
				start = i;
		}

		// If one room has more students than all the rest added, it's impossible
		if(sum < 2 * s[start]) {
			System.out.println("impossible");
			return;
		}

		// Otherwise, start with start and do the rest in some arbitrary order
		System.out.print(start + 1);
		for(int i = 0; i < n; i++)
			if(i != start)
				System.out.print(" " + (i + 1));
		System.out.println();
	}
}
