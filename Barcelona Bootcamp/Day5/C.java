import java.io.*;
import java.math.*;
import java.util.*;
import java.lang.*;

public class C{
	public static void main(String args[]) throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		long k = Long.parseLong(st.nextToken());
		long m = Long.parseLong(st.nextToken());
		st = new StringTokenizer(br.readLine());
		long a[] = new long[1<<11];
		for(int i = 0; i < n; i++)
			a[i] = Long.parseLong(st.nextToken());
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i <= k; i++)
		{
			long ans = 0;
			for(int j = n-1; j >= 0; j--)
				ans = (ans*i+a[j])%m;
			sb.append(ans+" ");
		}
		System.out.println(sb.toString());
	}
}
