import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		int x = Integer.valueOf(ps[0]);
		int y = Integer.valueOf(ps[1]);
		int n = Integer.valueOf(in.readLine());
		int[] l = new int[n];
		int[] u = new int[n];
		double[] f = new double[n];
		for(int i = 0; i < n; i++) {
			ps = in.readLine().split(" ");
			l[i] = Integer.valueOf(ps[0]);
			u[i] = Integer.valueOf(ps[1]);
			f[i] = Double.valueOf(ps[2]);
		}

		// Binary search over the horizontal velocity
		int ax = x < 0 ? -x : x;
		double low = 0;
		double up = 10 * ax;
		for(int i = 0; i < 100; i++) {
			double v = (low + up) / 2;

			// Simulate what x-location we would reach with this velocity
			double ans = v * y;
			for(int j = 0; j < n; j++) {
				ans -= v * (u[j] - l[j]);
				ans += f[j] * v * (u[j] - l[j]);
			}

			// Now check on which side we are
			if(ans < ax) low = v;
			else         up = v;
		}
		System.out.println((x < 0 ? -1 : 1) * (low+up)/2);
	}
}
