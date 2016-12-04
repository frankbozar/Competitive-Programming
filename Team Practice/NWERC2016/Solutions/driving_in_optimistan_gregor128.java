import java.math.BigInteger;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.TreeMap;

public class gregor128 {
	static BigInteger[][] dst = new BigInteger[2000][2000];
	static int N;

	static BigInteger[] sts = new BigInteger[2000];
	static List<Integer>[] adj = new List[2000];
	static List<BigInteger>[] d = new List[2000];

	static class LongPair {
		int first;
		BigInteger second;

		public LongPair(int a, BigInteger b) {
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

		Map<BigInteger, List<LongPair>> subtrees = new TreeMap<>();

		// build node groups
		for (int i : nodes) {
			BigInteger perpen = dst[x][i].add(dst[i][y]).subtract(dst[x][y])
					.divide(BigInteger.valueOf(2));
			BigInteger distToX = dst[x][i].subtract(perpen);
			if (!subtrees.containsKey(distToX))
				subtrees.put(distToX, new LinkedList<LongPair>());
			subtrees.get(distToX).add(new LongPair(i, perpen));
		}

		// insert root node if necessary and build distances
		BigInteger last = BigInteger.ZERO;
		int prev = x;
		for (Entry<BigInteger, List<LongPair>> subTree : subtrees.entrySet()) {
			int root = -1;
			for (LongPair i : subTree.getValue())
				if (i.second.equals(BigInteger.ZERO)) {
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

			BigInteger length = subTree.getKey().subtract(last);
			if (prev != root) {
				adj[prev].add(root);
				d[prev].add(length);
			}
			prev = root;
			last = subTree.getKey();
		}

		return;
	}

	static BigInteger calSTS(int x) {
		sts[x] = BigInteger.ONE;
		for (int i = 0; i < adj[x].size(); i++)
			sts[x] = sts[x].add(calSTS(adj[x].get(i))).add(d[x].get(i))
					.subtract(BigInteger.ONE);
		return sts[x];
	}

	static BigInteger calculate(int x) {
		BigInteger res = BigInteger.ZERO;
		for (int i = 0; i < adj[x].size(); i++) {
			BigInteger above = sts[0].subtract(sts[adj[x].get(i)])
					.subtract(d[x].get(i)).add(BigInteger.ONE);
			BigInteger below = sts[adj[x].get(i)];

			res = res.add(d[x].get(i).multiply(above).multiply(below));

			res = res.add(d[x].get(i).multiply(
					(d[x].get(i).subtract(BigInteger.ONE))).divide(
							BigInteger.valueOf(2)).multiply(above.add(below)));
			res = res.add(d[x].get(i)
					.multiply(d[x].get(i).subtract(BigInteger.ONE))
					.multiply(d[x].get(i).subtract(BigInteger.valueOf(2)))
					.divide(BigInteger.valueOf(6)));

			res = res.add(calculate(adj[x].get(i)));
		}

		return res;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		for (int i = 0; i < 2*N; i++)
			dst[i][i] = BigInteger.valueOf(0);
		for (int i = 0; i < 2000; i++)
			adj[i] = new LinkedList<Integer>(); // I guess it should be 2*N ?!
		for (int i = 0; i < 2000; i++)
			d[i] = new LinkedList<BigInteger>(); // I guess it should be 2*N ?!
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++) {
				dst[i][j] = BigInteger.valueOf(sc.nextInt());
				dst[j][i] = dst[i][j];
			}

		List<Integer> allNodes = new LinkedList<>();
		for (int i = 0; i < N; i++)
			allNodes.add(i);

		reconstruct(allNodes);
		calSTS(0);

		double d = calculate(0).doubleValue();
		double n = sts[0].doubleValue();

		System.out.println(d/(n*(n-1)/2));

		sc.close();
	}

}

