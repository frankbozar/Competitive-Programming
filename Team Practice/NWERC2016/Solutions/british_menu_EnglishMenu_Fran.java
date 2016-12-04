import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map.Entry;

public class EnglishMenu_Fran {

	static final int MAX_SCC = 6;

	static int n, m;
	static LinkedList<Integer>[] g;
	static SCC scc;
	static DistMap[] d;
	static int[] dp;

	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws FileNotFoundException, IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String[] data = reader.readLine().split(" ");
		n = Integer.parseInt(data[0]);
		m = Integer.parseInt(data[1]);
		g = new LinkedList[n];
		for(int i = 0; i < n; i++) {
			g[i] = new LinkedList<>();
		}
		for(int i = 0; i < m; i++) {
			data = reader.readLine().split(" ");
			int x = Integer.parseInt(data[0])- 1;
			int y = Integer.parseInt(data[1]) - 1;
			g[x].add(y);
		}
		scc = new SCC(g);
		// compute distances in SCC
		d = new DistMap[scc.nbSCC()];
		for(int i = 0; i < scc.nbSCC(); i++) {
			d[i] = APLP(i);
		}
		dp = new int[g.length];
		Arrays.fill(dp, 0);
		// initialize for the first SCC
		for(int x : scc.toposort) {
			// distance coming from other scc
			int sccIndex = scc.sccIds[x];
			for(Edge in : scc.inEdges[sccIndex]) {
				dp[x] = Math.max(dp[x], d[sccIndex].get(in.dest, x) + dp[in.orig] + 1);
			}
			// distance within scc
			for(int y : scc.sccNodes[sccIndex]) {
				dp[x] = Math.max(dp[x], d[sccIndex].get(y, x));
			}
		}
		int max = -1;
		for(int i = 0; i < dp.length; i++) {
			max = Math.max(max, dp[i]);
		}
		System.out.println(max + 1);

	}

	// SCC

	@SuppressWarnings("unchecked")
	static class SCC {

		public boolean[] visited;
		public int[] toposort, sccIds, sccSize;
		public int topoIndex, sccId, sccIndex;
		public int[][] sccNodes;
		public boolean firstPass;
		public List<Edge>[] inEdges;

		public SCC(LinkedList<Integer>[] g) {
			firstPass = true;
			dfs(transpose(g));
			int[] order = Arrays.copyOf(toposort, g.length);
			firstPass = false;
			dfsInit(g);
			sccNodes = new int[g.length][MAX_SCC];
			inEdges = new LinkedList[g.length];
			for(int x : order) {
				if(!visited[x]) {
					inEdges[sccId] = new LinkedList<>();
					sccIndex = 0;
					Arrays.fill(sccNodes[sccId], -1);
					dfsVisit(g, x);	
					sccNodes[sccId] = Arrays.copyOf(sccNodes[sccId], sccIndex);
					sccId++;
				}
			}
		}

		public int nbSCC() {
			return sccId;
		}

		private LinkedList<Integer>[] transpose(LinkedList<Integer>[] g) {
			LinkedList<Integer>[] gt = new LinkedList[g.length];
			for(int x = 0; x < g.length; x++) gt[x] = new LinkedList<>();
			for(int x = 0; x < g.length; x++) for(int y : g[x]) gt[y].add(x);
			return gt;
		}

		private void dfsInit(LinkedList<Integer>[] g) {
			visited = new boolean[g.length];
			sccIds = new int[g.length];
			sccSize = new int[g.length];
			toposort = new int[g.length];
			topoIndex = g.length - 1;
			sccId = 0;
		}

		private void dfs(LinkedList<Integer>[] g) {
			dfsInit(g);
			for(int x = 0; x < g.length; x++) {
				if(!visited[x]) {
					dfsVisit(g, x);
				}
			}
		}

		private void dfsVisit(LinkedList<Integer>[] g, int x) {
			visited[x] = true;
			sccIds[x] = sccId;
			sccSize[sccId]++;
			if(!firstPass) sccNodes[sccId][sccIndex++] = x;
			for(int y : g[x]) {
				if(sccIds[x] != sccIds[y]) {
					inEdges[sccIds[y]].add(new Edge(x, y));
				}
				if(!visited[y]) {
					dfsVisit(g, y);
				}
			}
			toposort[topoIndex--] = x;
		}
	}


	// EDGE

	static class Edge {

		public int orig, dest;

		public Edge(int orig, int dest) {
			this.orig = orig;
			this.dest = dest;
		}

		public String toString() {
			return String.format("(%d, %d)", orig, dest);
		}

	}

	// LONGEST PATH

	static DistMap APLP(int sccIndex) {
		DistMap D = new DistMap();
		for(int s : scc.sccNodes[sccIndex]) {
			longetsPathsFrom(s, sccIndex, D);
		}
		return D;
	}

	static void longetsPathsFrom(int s, int sccIndex, DistMap D) {
		HashSet<Integer> inPath = new HashSet<>();
		inPath.add(s);
		search(s, sccIndex, inPath, s, 0, D);
	}

	static void search(int s, int sccIndex, HashSet<Integer> inPath, int prev, int dist, DistMap D) {
		D.update(s, prev, dist);
		for(int x : g[prev]) {
			if(scc.sccIds[x] != sccIndex) continue;
			if(!inPath.contains(x)) {
				inPath.add(x);
				search(s, sccIndex, inPath, x, dist + 1, D);
				inPath.remove(x);
			}
		}
	}

	// MAP

	public static class DistMap {

		private HashMap<Long, Integer> M;

		public DistMap() {
			M = new HashMap<>();
		}

		public void set(int x, int y, int d) {
			M.put(h(x, y), d);
		}

		public void update(int x, int y, int d) {
			M.put(h(x, y), Math.max(get(x, y), d));
		}

		public int get(int x, int y) {
			Integer d = M.get(h(x, y));
			return d == null ? Integer.MIN_VALUE : d;
		}


		public long h(int x, int y) {
			return ((long)x << 31) | y;
		}

		public String toString() {
			StringBuilder sb = new StringBuilder();
			for(Entry<Long, Integer> e : M.entrySet()) {
				int x = (int)(e.getKey() >> 31);
				int y = (int)(e.getKey() & 0x7fffffff);
				sb.append(x + " " + y + ": " + e.getValue() + "\n");
			}
			return sb.toString();
		}

	}


}

