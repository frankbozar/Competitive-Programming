import java.util.Map.Entry;
import java.util.*;
import java.io.*;

public class gregor_bufread {
	static long[][] dst = new long[2000][2000];
	static int N;

	static double[] sts = new double[2000];
	static List<Integer>[] adj = new List[2000];
	static List<Long>[] d = new List[2000];

	static class LongPair {
		int first;
		long second;

		public LongPair(int a, long b) {
			first = a;
			second = b;
		}
	}

	// returns number of nodes
	static void reconstruct(List<Integer> nodes) {
		if (nodes.size() < 2)
			return;
		// take two nodes
		int x = nodes.get(0);
		int y = nodes.get(1);

		Map<Long, List<LongPair>> subtrees = new TreeMap<>();

		// build node groups
		for (int i : nodes) {
			long perpen = (dst[x][i] + dst[i][y] - dst[x][y]) / 2;
			long distToX = dst[x][i] - perpen;
			if (!subtrees.containsKey(distToX))
				subtrees.put(distToX, new LinkedList<LongPair>());
			subtrees.get(distToX).add(new LongPair(i, perpen));
		}

		// insert root node if necessary and build distances
		long last = 0;
		int prev = x;
		for (Entry<Long, List<LongPair>> subTree : subtrees.entrySet()) {
			int root = -1;
			for (LongPair i : subTree.getValue())
				if (i.second == 0) {
					root = i.first;
					break;
				}
			// add root
			if (root == -1) {
				for (LongPair i : subTree.getValue())
					dst[N][i.first] = dst[i.first][N] = i.second;
				root = N++;
			}

			List<Integer> st = new LinkedList<>();
			st.add(root);
			for (LongPair i : subTree.getValue())
				if (i.first != root)
					st.add(i.first);

			reconstruct(st);

			long length = subTree.getKey() - last;
			if (prev != root) {
				adj[prev].add(root);
				d[prev].add(length);
			}
			prev = root;
			last = subTree.getKey();
		}

		return;
	}

	static double calSTS(int x){
		sts[x] = 1;
		for (int i = 0; i < adj[x].size(); i++)
			sts[x] += calSTS(adj[x].get(i)) + d[x].get(i) - 1;
		return sts[x];
	}

	static double calculate(int x) {
		double res = 0;
		for (int i = 0; i < adj[x].size(); i++) {
			double above = sts[0] - sts[adj[x].get(i)] - d[x].get(i) + 1;
			double below = sts[adj[x].get(i)];

			res += above * below * d[x].get(i) +
					(above + below) * d[x].get(i)	* (d[x].get(i) - 1) / 2 +
					(double)(d[x].get(i)) * (d[x].get(i) - 1) * (d[x].get(i) - 2) / 6;
			res += calculate(adj[x].get(i));
		}

		return res;
	}

	public static void main(String[] args) throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(reader.readLine());
		for (int i = 0; i < N; i++)
			dst[i][i] = 0;
		for (int i = 0; i < 2000; i++)
			adj[i] = new LinkedList<Integer>(); // I guess it should be 2*N ?!
		for (int i = 0; i < 2000; i++)
			d[i] = new LinkedList<Long>(); // I guess it should be 2*N ?!
		for (int i = 0; i < N - 1; i++) {
			StringTokenizer strtok = new StringTokenizer(reader.readLine());
			for (int j = i + 1; j < N; j++) {
				dst[i][j] = Integer.parseInt(strtok.nextToken());
				dst[j][i] = dst[i][j];
			}
		}

		List<Integer> allNodes = new LinkedList<>();
		for (int i = 0; i < N; i++)
			allNodes.add(i);

		reconstruct(allNodes);
		calSTS(0);

		System.out.println(2*calculate(0) / (sts[0]*(sts[0]-1)));
	}

}

