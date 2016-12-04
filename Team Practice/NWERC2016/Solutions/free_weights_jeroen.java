import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception {
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());

		String[] ps = in.readLine().split(" ");
		int[] v1 = new int[n];
		for(int i = 0; i < n; i++)
			v1[i] = Integer.valueOf(ps[i]);

		ps = in.readLine().split(" ");
		int[] v2 = new int[n];
		for(int i = 0; i < n; i++)
			v2[i] = Integer.valueOf(ps[i]);

		// Handle the two rows separately
		int res = 0;
		res = Math.max(res, perRow(n, v1));
		res = Math.max(res, perRow(n, v2));

		// Print final answer
		System.out.println(res);
	}

	public static int perRow(int n, int[] v) {
		// Add to a tree to do an efficient max-range query
		RMQ rmq = new RMQ(n);
		for(int i = 0; i < n; i++)
			rmq.Set(i, v[i]);
		
		// Go through the weights and at the second one, do a range query
		int res = 0;
		Map<Integer,Integer> pos = new HashMap<Integer,Integer>();
		for(int i = 0; i < n; i++) {
			if(pos.containsKey(v[i])) {
				// Now see what the maximum weight is that there is in between
				int p = pos.get(v[i]);
				int maxw = p == i - 1 ? 0 : rmq.Query(p + 1, i - 1);

				// We need to either move this weight or the ones in between
				res = Math.max(res, Math.min(maxw, v[i]));
				pos.remove(v[i]);
			} else {
				pos.put(v[i], i);
			}
		}

		// Weights that we saw once must always be lifted
		for(int k : pos.keySet())
			res = Math.max(res, k);
				
		return res;
	}
}

// Range maximum query
class RMQ
{
	private Node topnode;

	public RMQ(int n)
	{
		topnode = new Node(0, n - 1);
	}

	public void Set(int index, int val)
	{
		topnode.Set(index, val);
	}

	public int Query(int from, int to)
	{
		return topnode.Query(from, to);
	}
}

class Node
{
	private int f, t, m;
	private Node l, r;
	
	public Node(int f, int t)
	{
		this.f = f;
		this.t = t;
		m = 0;
		if (f != t) {
			l = new Node(f, (f + t) / 2);
			r = new Node((f + t) / 2 + 1, t);
		}
	}
	
	public void Set(int index, int val)
	{
		if (index == f && index == t)
			m = val;
		else {
			if (index <= (f + t) / 2)
				l.Set(index, val);
			else
				r.Set(index, val);
			m = Math.max(l.m, r.m);
		}
	}
	
	public int Query(int from, int to)
	{
		if (from == f && to == t) return m;
		int ans = 0;
		if (from <= (f + t) / 2)
			ans = Math.max(ans, l.Query(from, Math.min(to, (f + t) / 2)));
		if (to > (f + t) / 2)
			ans = Math.max(ans, r.Query(Math.max(from, (f + t) / 2 + 1), to));
		return ans;
	}
}
