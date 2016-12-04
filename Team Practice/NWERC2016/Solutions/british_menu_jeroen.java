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
		int[] a = new int[m];
		int[] b = new int[m];
		for(int i = 0; i < m; i++) {
			ps = in.readLine().split(" ");
			a[i] = Integer.valueOf(ps[0]) - 1;
			b[i] = Integer.valueOf(ps[1]) - 1;
		}

		// Construct initial graph
		Graph g = new Graph(n);
		for(int i = 0; i < m; i++)
			g.addEdge(a[i], b[i]);

		// Find the strongly connected components and brute-force each of them
		LinkedList<Node>[] components = g.scc();
		for(LinkedList<Node> component : components) {
			if(component.size() == 1) continue;
			// Create an in-node and an out-node for each node in the component
			Map<Node,Node> newIn = new HashMap<Node,Node>();
			Map<Node,Node> newOut = new HashMap<Node,Node>();
			for(Node node : component) {
				// Incoming node
				Node nin = g.addNode();
				newIn.put(node, nin);
				for(Edge prev : node.from)
					if(prev.n.component != node.component)
						g.addEdge(prev.n, nin, prev.len);

				// Outgoing node
				Node nout = g.addNode();
				newOut.put(node, nout);
				for(Edge next : node.to)
					if(next.n.component != node.component)
						g.addEdge(nout, next.n, next.len);

				// Connect them directly
				g.addEdge(nin, nout, 0);
			}
			
			// Do a brute-force bfs from each node to find longest path
			// between two nodes within the connected component.
			for(Node node : component) {
				Map<Node,Integer> furthest = new HashMap<Node,Integer>();
				bfComponent(node, new HashSet<Node>(), 0, furthest);

				for(Node other : component) {
					if(other == node) continue;
					if(!furthest.containsKey(other)) throw new Exception("Invariant broken");
					g.addEdge(newIn.get(node), newOut.get(other), furthest.get(other));
				}
			}

			// Remove the original nodes from the graph (we have now shortcutted the component)
			for(Node node : component) g.removeNode(node);
		}
		
		// Now the graph is a DAG, so the rest is easy. Simply start with nodes
		// that have no incoming edges, and proceed in a topsort way.
		Queue<Node> todo = new LinkedList<Node>();
		for(Node node : g.nodes) {
			node.indeg = node.from.size();
			node.longest = 1;
			if(node.indeg == 0) todo.add(node);
		}
		int ret = 0;
		while(!todo.isEmpty()) {
			Node node = todo.remove();
			ret = Math.max(ret, node.longest);
			for(Edge next : node.to) {
				next.n.indeg--;
				next.n.longest = Math.max(next.n.longest, node.longest + next.len);
				if(next.n.indeg == 0) todo.add(next.n);
			}
		}
		
		System.out.println(ret);
	}

	// Brute-force a connected component
	public static void bfComponent(Node cur, HashSet<Node> done, int dist, Map<Node,Integer> furthest) {
		if(!furthest.containsKey(cur) || furthest.get(cur) < dist)
			furthest.put(cur, dist);
		done.add(cur);
		for(Edge next : cur.to)
			if(next.n.component == cur.component && !done.contains(next.n))
				bfComponent(next.n, done, dist + next.len, furthest);
		done.remove(cur);
	}
	
}

class Graph {
	public ArrayList<Node> nodes;

	public Graph(int n) {
		nodes = new ArrayList<Node>(n);
		for(int i = 0; i < n; i++)
			nodes.add(new Node());
	}
	
	public void addEdge(int i, int j) {
		addEdge(i, j, 1);
	}

	public void addEdge(int i, int j, int len) {
		addEdge(nodes.get(i), nodes.get(j), len);
	}
	
	public void addEdge(Node i, Node j, int len) {
		Edge e1 = new Edge(j, len);
		Edge e2 = new Edge(i, len);
		e1.inv = e2;
		e2.inv = e1;
		i.to.add(e1);
		j.from.add(e2);
	}

	public Node addNode() {
		Node n = new Node();
		nodes.add(n);
		return n;
	}

	// soft-remove this node, just deconnect it
	public void removeNode(Node n) {
		for(Edge next : n.to)   next.n.from.remove(next.inv);
		for(Edge prev : n.from) prev.n.to.remove(prev.inv);
		n.to.clear();
		n.from.clear();
	}

	public void print() {
		System.out.println("digraph G {");
		for(Node n : nodes)
			for(Edge e : n.to)
				System.out.println("  " + n + " -> " + e.n + " [label=\"" + e.len + "\"];");
		System.out.println("}");
	}

	private Node[] order;
	private int order_num, num_components;
	
	public LinkedList<Node>[] scc()
	{
		// Init
		order_num = 0;
		order = new Node[nodes.size()];
		for(Node n : nodes) n.component = 0;

		// Do dfs in two different directions
		for(Node n : nodes) dfs1(n);
		num_components = 0;
		for (int i = nodes.size() - 1; i >= 0; i--)
		{
			if (order[i].component == -1)
			{
				dfs2(order[i]);
				num_components++;
			}
		}

		// Construct the resulting bins
		@SuppressWarnings("unchecked")
		LinkedList<Node>[] ret = new LinkedList[num_components]; // argh!
		for(int i = 0; i < num_components; i++)
			ret[i] = new LinkedList<Node>();
		for(Node n : nodes)
			ret[n.component].add(n);
		return ret;
	}

	private void dfs1(Node n)
	{
		if (n.component != 0) return;
		n.component = -1;
		for(Edge adj : n.to) dfs1(adj.n);
		order[order_num++] = n;
	}

	private void dfs2(Node n)
	{
		if (n.component != -1) return;
		n.component = num_components;
		for(Edge adj : n.from) dfs2(adj.n);
	}
}

class Node {
	public Set<Edge> to = new HashSet<Edge>();
	public Set<Edge> from = new HashSet<Edge>();
	public int component = -2;
	public int indeg, longest;

	public String toString() {
		return super.toString().replace("@","_");
	}
}

class Edge {
	public Node n;
	public int len;
	public Edge inv; // each edge has an inverse edge

	public Edge(Node n, int len) {
		this.n = n;
		this.len = len;
	}
}
