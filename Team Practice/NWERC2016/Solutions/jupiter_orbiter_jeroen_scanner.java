import java.util.*;
import java.io.*;
import java.util.Scanner;

public class jeroen_scanner
{
	public static void main(String[] args) throws Exception
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		// Read input
		String[] ps = in.readLine().split(" ");
		int N = Integer.valueOf(ps[0]);
		int Q = Integer.valueOf(ps[1]);
		int I = Integer.valueOf(ps[2]);
		
		int[] q = new int[I];
		ps = in.readLine().split(" ");
		for(int i = 0; i < I; i++)
			q[i] = Integer.valueOf(ps[i]);
		
		int[] c = new int[Q];
		ps = in.readLine().split(" ");
		for(int i = 0; i < Q; i++)
			c[i] = Integer.valueOf(ps[i]);

		int[][] window = new int[N][1 + I];
		for(int i = 0; i < N; i++) {
			ps = in.readLine().split(" ");
			for(int j = 0; j < 1 + I; j++)
				window[i][j] = Integer.valueOf(ps[j]);
		}

		// Construct maxflow problem
		MaxFlow mf = new MaxFlow(N * (Q + 1));
		int totaldata = 0;
		for(int i = 0; i < N; i++) {
			// The downlink
			mf.Add(i * (Q + 1), mf.Sink, window[i][0]);

			// Count per queue how much data comes in
			int[] perq = new int[Q];
			for(int j = 0; j < I; j++) {
				perq[q[j]-1] += window[i][j + 1];
				totaldata += window[i][j + 1];
			}

			// Now for each queue
			for(int j = 0; j < Q; j++) {
				// Check that data fits now
				if(perq[j] > c[j]) {
					System.out.println("impossible");
					return;
				}
				
				// The new incoming data to this queue
				mf.Add(mf.Source, i * (Q + 1) + j + 1, perq[j]);

				// We can download to the current downlink
				mf.Add(i * (Q + 1) + j + 1, i * (Q + 1), Integer.MAX_VALUE / 2);

				if(i > 0) {
					// The amount of data that can be left over from the previous window
					// is the queue size minus the amount of data that comes in currently.
					mf.Add((i - 1) * (Q + 1) + j + 1, i * (Q + 1) + j + 1, c[j] - perq[j]);
				}
			}
		}


		// Check if all data can be transferred
		System.out.println(mf.NetworkFlow() == totaldata ? "possible" : "impossible");
	}
}

class MaxFlow
{
	public int Nodes;
	public int Source;
	public int Sink;
	HashSet<Integer>[] Neighbours;
	HashMap<Integer,Integer>[] Capacity;
	HashMap<Integer,Integer>[] Flow;

	public MaxFlow(int Nodes)
	{
		this.Nodes = Nodes + 2;
		this.Source = Nodes;
		this.Sink = Nodes + 1;
		Neighbours = new HashSet[this.Nodes];
		Capacity = new HashMap[this.Nodes];
		Flow = new HashMap[this.Nodes];
		for (int i = 0; i < this.Nodes; i++) {
			Neighbours[i] = new HashSet<>();
			Flow[i] = new HashMap<>();
			Capacity[i] = new HashMap<>();
		}
	}

	public void Add(int From, int To, int Cap)
	{
		Neighbours[From].add(To);
		Neighbours[To].add(From);
		if (Capacity[From].get(To) == null) {
			Capacity[From].put(To, 0);
		}
		if (Capacity[To].get(From) == null) {
			Capacity[To].put(From, 0);
		}
		Capacity[From].put(To, Capacity[From].get(To) + Cap);
		if (Flow[From].get(To) == null) {
			Flow[From].put(To, 0);
		}
		if (Flow[To].get(From) == null) {
			Flow[To].put(From, 0);
		}
	}

	public int NetworkFlow()
	{
		int[] parent = new int[Nodes];
		int[] cap = new int[Nodes];

		int total = 0;
		while (true)
		{
			for (int i = 0; i < Nodes; i++)
				parent[i] = -1;
			parent[this.Source] = -2;
			cap[this.Source] = Integer.MAX_VALUE;
			Queue<Integer> Q = new LinkedList<Integer>();
			Q.offer(this.Source);
			while (!Q.isEmpty() && parent[this.Sink] == -1)
			{
				int act = Q.poll();
				for(int next : Neighbours[act])
				{
					if (parent[next] == -1 && Capacity[act].get(next) > Flow[act].get(next))
					{
						parent[next] = act;
						cap[next] = Math.min(cap[act], Capacity[act].get(next) - Flow[act].get(next));
						Q.offer(next);
					}
				}
			}

			if (parent[this.Sink] == -1)
				return total;

			total += cap[this.Sink];
			int j = this.Sink;
			while (j != this.Source)
			{
				Flow[parent[j]].put(j, Flow[parent[j]].get(j) + cap[this.Sink]);
				Flow[j].put(parent[j], Flow[j].get(parent[j]) - cap[this.Sink]);
				j = parent[j];
			}
		}
	}
}
