import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int m = Integer.valueOf(ps[1]);
		int k = Integer.valueOf(ps[2]);

		int[] o = new int[m];
		ps = in.readLine().split(" ");
		for(int i = 0; i < m; i++)
			o[i] = Integer.valueOf(ps[i])-1;
		
		int[] c = new int[k];
		ps = in.readLine().split(" ");
		for(int i = 0; i < k; i++)
			c[i] = Integer.valueOf(ps[i])-1;

		ArrayList<Integer>[] adj = new ArrayList[n];
		ArrayList<Integer>[] adjr = new ArrayList[n];
		for(int i = 0; i < n; i++) {
			adj[i] = new ArrayList<Integer>();
			adjr[i] = new ArrayList<Integer>();
		}
		
		for(int i = 0; i < n; i++) {
			ps = in.readLine().split(" ");
			for(int j = 1; j < ps.length; j++) {
				adj[i].add(Integer.valueOf(ps[j])-1);
				adjr[Integer.valueOf(ps[j])-1].add(i);
			}
		}


		// Compute for each cell the distance to nearest iron ore
		int[] idist = new int[n];
		for(int i = 0; i < n; i++)
			idist[i] = Integer.MAX_VALUE;
		Queue<Integer> Q = new LinkedList<Integer>();
		for(int i = 0; i < m; i++) {
			Q.add(o[i]);
			Q.add(0);
		}
		while(!Q.isEmpty()) {
			int i = Q.poll();
			int d = Q.poll();
			if(idist[i] < Integer.MAX_VALUE) continue;
			idist[i] = d;
			for(int j : adjr[i]) {
				Q.add(j);
				Q.add(d+1);
			}
		}

		// Compute for each cell the distance to nearest coal
		int[] cdist = new int[n];
		for(int i = 0; i < n; i++)
			cdist[i] = Integer.MAX_VALUE;
		Q = new LinkedList<Integer>();
		for(int i = 0; i < k; i++) {
			Q.add(c[i]);
			Q.add(0);
		}
		while(!Q.isEmpty()) {
			int i = Q.poll();
			int d = Q.poll();
			if(cdist[i] < Integer.MAX_VALUE) continue;
			cdist[i] = d;
			for(int j : adjr[i]) {
				Q.add(j);
				Q.add(d+1);
			}
		}

		// And finally the distance to the start
		int[] sdist = new int[n];
		for(int i = 0; i < n; i++)
			sdist[i] = Integer.MAX_VALUE;
		Q = new LinkedList<Integer>();
		Q.add(0);
		Q.add(0);
		while(!Q.isEmpty()) {
			int i = Q.poll();
			int d = Q.poll();
			if(sdist[i] < Integer.MAX_VALUE) continue;
			sdist[i] = d;
			for(int j : adj[i]) {
				Q.add(j);
				Q.add(d+1);
			}
		}

		// Find final answer by finding the 'split' point
		int ans = Integer.MAX_VALUE;
		for(int i = 0; i < n; i++) {
			if(idist[i] < Integer.MAX_VALUE &&
			   cdist[i] < Integer.MAX_VALUE &&
			   sdist[i] < Integer.MAX_VALUE) {
				ans = Math.min(ans, idist[i] + cdist[i] + sdist[i]);
			}
		}
		if(ans < Integer.MAX_VALUE)
			System.out.println(ans);
		else
			System.out.println("impossible");
	}
}
