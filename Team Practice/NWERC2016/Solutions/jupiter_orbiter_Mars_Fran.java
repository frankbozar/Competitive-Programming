import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.TreeMap;

public class Mars_Fran {

	/*

2 2 2
1 2
3 3
5 2 2
5 2 2

2 2 2
1 2
3 3
1 2 2
5 2 2

3 2 3
1 1 2
3 3 3
5 2 2 2
5 2 2 2
5 2 2 2

	 */

	static String dir = "Mars/";

	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String[] data = reader.readLine().split(" ");
		N = Integer.parseInt(data[0]);
		Q = Integer.parseInt(data[1]);
		I = Integer.parseInt(data[2]);
		data = reader.readLine().split(" ");
		q = new int[data.length];
		for(int i = 0; i < q.length; i++) {
			q[i] = Integer.parseInt(data[i]) - 1;
		}
		data = reader.readLine().split(" ");
		c = new int[data.length];
		for(int i = 0; i < c.length; i++) {
			c[i] = Integer.parseInt(data[i]);
		}
		@SuppressWarnings("unchecked")
		TreeMap<Integer, Integer>[] g = new TreeMap[N * (2 * Q + 1) + 2];
		for(int i = 0; i < g.length; i++) {
			g[i] = new TreeMap<>();
		}
		int target = 0;
		int s = 0;
		int t = g.length - 1;
		int x = 1;
		for(int i = 0; i < N; i++) {
			data = reader.readLine().split(" ");
			int D = Integer.parseInt(data[0]);
			for(int j = 0; j < Q; j++) {
				// edge between left layer and right layer of i block
				g[x + j].put(x + j + Q,  c[j]);
				// edge between right layer and output of i block
				g[x + j + Q].put(x + 2 * Q, INF);
				if(i < N - 1) {
					// edge between right layer of i and left layer of i + 1
					g[x + j + Q].put(x + 2 * Q + 1 + j, INF);					
				}
			}
			for(int j = 0; j < I; j++) {
				if(g[s].containsKey(x + q[j])) {
					g[s].put(x + q[j], g[s].get(x + q[j]) + Integer.parseInt(data[j + 1]));
				} else {
					g[s].put(x + q[j], Integer.parseInt(data[j + 1]));
				}
				target += Integer.parseInt(data[j + 1]);
			}
			g[x + 2 * Q].put(t, D);
			x += 2 * Q + 1;
		}
		int flow = maxflowEK(g, s, t);
		if(flow == target) {
			System.out.println("possible");
		} else {
			System.out.println("impossible");
		}
	}
	static int N, Q, I;
	static int[] q, c;
	static int INF = 100000000;


	// FLOW

	static int maxflowEK(TreeMap<Integer, Integer>[] g, int source, int sink) {
		int flow = 0;
		int pcap;
		while((pcap = augmentBFS(g, source, sink)) != -1) {
			flow += pcap;
		}
		return flow;
	}


	static int augmentBFS(TreeMap<Integer, Integer>[] g, int source, int sink) {
		// initialize bfs
		Queue<Integer> Q = new LinkedList<Integer>();
		Integer[] p = new Integer[g.length];
		int[] pcap = new int[g.length];
		pcap[source] = Integer.MAX_VALUE;
		p[source] = -1;
		Q.add(source);
		// compute path
		while(p[sink] == null && !Q.isEmpty()) {
			int u = Q.poll(); 
			for(Entry<Integer, Integer> e : g[u].entrySet()) {
				int v = e.getKey();
				if(e.getValue() > 0 && p[v] == null) {
					p[v] = u;
					pcap[v] = Math.min(pcap[u], e.getValue());
					Q.add(v);
				}
			}
		}
		if(p[sink] == null) return -1;
		// update graph
		int cur = sink;
		while(cur != source) {
			int prev = p[cur];
			int cap = g[prev].get(cur);
			g[prev].put(cur, cap - pcap[sink]);
			Integer backcap = g[cur].get(prev);
			g[cur].put(prev, backcap == null? pcap[sink] : backcap + pcap[sink]);
			cur = prev;
		}
		return pcap[sink];
	}


}
