import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class SteelAge_Fran {
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		int n = reader.nextInt();
		int m = reader.nextInt();
		int k = reader.nextInt();
		int[] o = new int[m];
		for(int i = 0; i < m; i++) {
			o[i] = reader.nextInt()-1;
		}
		int[] c = new int[k];
		for(int i = 0; i < k; i++) {
			c[i] = reader.nextInt()-1;
		}
		LinkedList<Integer>[] g = new LinkedList[n];
		for(int i = 0; i < g.length; i++) {
			g[i] = new LinkedList<>();
		}
		for(int i = 0; i < n; i++) {
			int a = reader.nextInt();
			for(int j = 0; j < a; j++) {
				g[i].add(reader.nextInt()-1);
			}
		}
		LinkedList<Integer>[] gt = transpose(g);
		double[] dToOre = bfs(gt, o);
		double[] dToCoal = bfs(gt, c);
		double[] dFrom0 = bfs(g, new int[] {0});
		double ans = Double.POSITIVE_INFINITY;
		for(int x = 0; x < g.length; x++) {
			ans = Math.min(ans, dFrom0[x] + dToOre[x] + dToCoal[x]);
		}
		if(ans == Double.POSITIVE_INFINITY) {
			System.out.println("impossible");
		} else {
			System.out.println((int)ans);			
		}
		reader.close();
	}
	
	@SuppressWarnings("unchecked")
	static LinkedList<Integer>[] transpose(LinkedList<Integer>[] g) {
		LinkedList<Integer>[] gt = new LinkedList[g.length];
		for(int x = 0; x < g.length; x++) gt[x] = new LinkedList<>();
		for(int x = 0; x < g.length; x++) for(int y : g[x]) gt[y].add(x);
		return gt;
	}
	
	static double[] bfs(LinkedList<Integer>[] g, int[] s) {
		Queue<Integer> Q = new LinkedList<>();
		double[] d = new double[g.length];
		Arrays.fill(d, Double.POSITIVE_INFINITY);
		for(int x : s) {
			Q.add(x);
			d[x] = 0;
		}
		while(!Q.isEmpty()) {
			int cur = Q.poll();
			for(int next : g[cur]) {
				if(d[next] == Double.POSITIVE_INFINITY) {
					d[next] = 1 + d[cur];
					Q.add(next);
				}
			}
		}
		return d;
	}

}
