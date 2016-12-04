import java.util.*;
import java.io.*;
import java.math.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[][] dist = new int[n*2][n*2];
		for(int i = 0; i < n - 1; i++) {
			String[] ps = in.readLine().split(" ");
			for(int j = 0; j < n - i - 1; j++)
				dist[i][i+j+1] = dist[i+j+1][i] = Integer.valueOf(ps[j]);
		}

		// Find distances of internal nodes to node 0
		PriorityQueue<IntNode> Q = new PriorityQueue<IntNode>();
		for(int i = 1; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				int dst = (dist[i][0] + dist[j][0] - dist[i][j]) / 2;
				Q.add(new IntNode(i, j, dst));
			}
		}

		// Now start adding the internal nodes starting with the one
		// furthest away from 0, thereby joining two existing nodes.
		// New nodes are numbered from n.
		boolean[] done = new boolean[n*2];
		int idx = n;
		DiGraph g = new DiGraph(n*2 - 2); // n-2 internal nodes
		while(!Q.isEmpty()) {
			IntNode top = Q.poll();

			// Check whether either of the nodes has already been merged
			if(done[top.i] || done[top.j]) continue;
			done[top.i] = true;
			done[top.j] = true;

			// Compute distances from this new internal node to the rest
			dist[idx][0] = dist[0][idx] = top.dist;
			for(int i = 1; i < idx; i++) {
				if(done[i]) continue;
				dist[idx][i] = dist[i][idx] = dist[top.i][i] - dist[top.i][0] + top.dist;
				int dst = (top.dist + dist[i][0] - dist[idx][i]) / 2;
				Q.add(new IntNode(idx, i, dst));
			}

			// Construct the graph
			g.AddEdge(top.i, idx, dist[top.i][0] - top.dist);
			g.AddEdge(top.j, idx, dist[top.j][0] - top.dist);
			idx++;
		}

		// Finally connect 0 to the last internal node
		g.AddEdge(0, idx-1, dist[0][idx-1]);
		
		// Find the total distance between all ports with dfs
		DfsRet r = g.dfs(0, -1);
		BigInteger numPairs = r.ports.multiply(r.ports.subtract(BigInteger.ONE)).divide(new BigInteger("2"));
		BigDecimal ans = new BigDecimal(r.total).divide(new BigDecimal(numPairs), 10, BigDecimal.ROUND_HALF_EVEN);
		System.out.println(ans);
	}
}

/*
Sample 1:
                 1
                / 
0 -- . -- . -- 3
                \
                 2

Sample 2:
1 -- 4 -- 2
     5
    / \ 
   3   0

*/

class DiGraph {
	int n;
	ArrayList<Edge>[] nb;

	@SuppressWarnings("unchecked")
	public DiGraph(int n) {
		this.n = n;
		this.nb = new ArrayList[n];
		for(int i = 0; i < n; i++)
			this.nb[i] = new ArrayList<Edge>();
	}

	public void AddEdge(int i, int j, int d) {
		nb[j].add(new Edge(i, d));
		nb[i].add(new Edge(j, d));
		//System.err.println(i + " -- " + j + " ( " + d + " )");
	}

	
	static BigInteger TWO = new BigInteger("2");
	static BigInteger SIX = new BigInteger("6");

	// Helper, sum 1..n
	private static BigInteger rowSum(BigInteger n) {
		return n.multiply(n.add(BigInteger.ONE)).divide(TWO);
	}

	// Helper, sum 1^2,2^2,3^2..n^2
	private static BigInteger squareSum(BigInteger n) {
		// I had to Google this...
		// (n * (n + 1) * (2 n + 1)) / 6
		return n.multiply(n.add(BigInteger.ONE)).multiply(n.multiply(TWO).add(BigInteger.ONE)).divide(SIX);
	}	
	
	// Main dfs method for finding the total distance between all pairs
	// and the total amount of ports.
	public DfsRet dfs(int n, int from) throws Exception {
		// Do all edges that we not just entered
		ArrayList<DfsRet> others = new ArrayList<DfsRet>();
		for(Edge e : nb[n]) {
			if(e.to != from) {
				// Recursively do that part of the tree
				DfsRet r = dfs(e.to, n);
				BigInteger edst = BigInteger.valueOf(e.dist);
				BigInteger edstm1 = edst.subtract(BigInteger.ONE);

				// Include ports on the edge
				DfsRet other = new DfsRet();
				other.ports = r.ports.add(edst).subtract(BigInteger.ONE);
				other.total = r.total;
				other.dist  = r.dist.add(r.ports.multiply(edst)).add(rowSum(edstm1));

				// Distances from all 'edge ports' into r
				other.total = other.total.add(rowSum(edstm1).multiply(r.ports));
				other.total = other.total.add(edstm1.multiply(r.dist));

				// Distances between ports both on the edge
				other.total = other.total.add(rowSum(edstm1).multiply(edstm1));
				other.total = other.total.subtract(squareSum(edstm1));
				
				others.add(other);
			}
		}
		
		// Construct return value by combining all others
		DfsRet ret = new DfsRet();
		ret.total = BigInteger.ZERO;
		ret.ports = BigInteger.ONE;
		ret.dist  = BigInteger.ZERO;

		// Impact of the individual adjacent trees
		for(DfsRet r : others) {
			// All ports in the cluster e
			ret.total = ret.total.add(r.total);
			ret.total = ret.total.add(r.dist);
			ret.ports = ret.ports.add(r.ports);
			ret.dist  = ret.dist.add(r.dist);
		}

		// Combination all other pairs
		for(int i = 0; i < others.size(); i++) {
			for(int j = i + 1; j < others.size(); j++) {
				DfsRet r = others.get(i);
				DfsRet r2 = others.get(j);

				ret.total = ret.total.add(r.dist.multiply(r2.ports));
				ret.total = ret.total.add(r2.dist.multiply(r.ports));
			}
		}

		return ret;
	}
}


class DfsRet {
	// Total distance between all pairs of ports
	BigInteger total;
	// Number of ports
	BigInteger ports;
	// Total dist from all ports to the 'entry' port
	BigInteger dist;
}

class Edge {
	int to, dist;

	public Edge(int to, int dist) {
		this.to = to;
		this.dist = dist;
	}
}

class IntNode implements Comparable<IntNode> {
	public int i, j, dist;

	public IntNode(int i, int j, int dist) {
		this.i = i;
		this.j = j;
		this.dist = dist;
	}

	public int compareTo(IntNode other) {
		if(dist != other.dist)
			return other.dist - dist;
		return Math.max(other.i, other.j) - Math.max(i, j);
	}
}
