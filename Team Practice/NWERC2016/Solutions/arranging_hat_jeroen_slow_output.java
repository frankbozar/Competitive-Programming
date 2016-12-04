import java.util.*;
import java.io.*;

public class jeroen_slow_output
{
	static int n, m;
	static String[] v;
	
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		n = Integer.valueOf(ps[0]);
		m = Integer.valueOf(ps[1]);
		v = new String[n];
		for (int i = 0; i < n; ++i) {
		    v[i] = in.readLine();
		}

		// Recursive with memo, first compute the minimum number of changes
		done   = new boolean[n][n][m][10];
		mem    = new int[n][n][m][10];
		splitp = new int[n][n][m][10];
		rec(0, n - 1, 0, 0);

		// Then replay the recursion to set all digits and print
		ans    = new int[n][m];
		setNums(0, n - 1, 0, 0);
		for(int i = 0; i < n; i++) {
			if(i > 0)
				System.out.print(" ");
			for(int j = 0; j < m; j++)
				System.out.print(ans[i][j]);
		}
		System.out.println();
	}

	static boolean[][][][] done;
	static int[][][][] mem;
	static int[][][][] splitp;
	static int[][] ans;

	// What is the minimum number of digit changes to sort
	// the digits from 'from' to 'to', only considering the last part
	// of the number starting at 'dig', where we should start the list
	// with a 'curd'
	public static int rec(int from, int to, int dig, int curd) {
		int res = Integer.MAX_VALUE / 3;
		int cursplit = -2;
		
		// Base cases
		if(dig == m)
			return 0;
		if(curd == 10)
			return Integer.MAX_VALUE / 3;

		// Memo
		if(done[from][to][dig][curd]) return mem[from][to][dig][curd];
		done[from][to][dig][curd] = true;

		// Don't use this digit at all and directly try the next one
		if(curd < 9) {
			int cura = rec(from, to, dig, curd+1);
			if(cura < res) {
				res = cura;
				cursplit = -1;
			}
		}

		// How many number in a row get this digit
		int numc = 0;
		for(int i = from; i <= to; i++) {
			// If this digit was something else, we need to change
			if(v[i].charAt(dig) - '0' != curd)
				numc++;

			// Now this interval needs to be sorted using the next
			// digits, and the rest of the list needs to be sorted
			int cura = numc + rec(from, i, dig + 1, 0);
			if(i < to) cura += rec(i + 1, to, dig, curd + 1);

			if(cura < res) {
				res = cura;
				cursplit = i;
			}
		}
		splitp[from][to][dig][curd] = cursplit;
		return mem[from][to][dig][curd] = res;
	}

	// Do the recursion for the correct answer again to construct the final answer
	public static void setNums(int from, int to, int dig, int curd) {
		if(dig == m) return;
		int cursplit = splitp[from][to][dig][curd];
		if(cursplit == -1) {
			setNums(from, to, dig, curd+1);
		} else {
			for(int i = from; i <= cursplit; i++)
				ans[i][dig] = curd;
			setNums(from, cursplit, dig + 1, 0);
			if(cursplit < to) setNums(cursplit + 1, to, dig, curd+1);
		}
	}
}
