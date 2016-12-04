import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.TreeSet;

public class Rack_Fran {

	static StreamTokenizer st = new StreamTokenizer(new InputStreamReader(System.in));
	
	static int nextInt() {
		try {
			st.nextToken();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return (int)st.nval;
	}
	
	public static void main(String[] args) {
		int n = nextInt();
		int[] a = new int[n];
		int[] b = new int[n];
		TreeSet<Integer> T = new TreeSet<>();
		T.add(0);
		for(int i = 0; i < n; i++) {
			a[i] = nextInt();
			T.add(a[i]);
		}
		for(int i = 0; i < n; i++) {
			b[i] = nextInt();
			T.add(b[i]);
		}
		int[] c = new int[T.size()];
		int i = 0;
		for(int x : T) c[i++] = x;
		int min1 = min(a, c);
		int min2 = min(b, c);
		System.out.println(Math.max(min1, min2));
	}
	
	static int min(int[] a, int[] c) {
		int lb = 0;
		int ub = c.length - 1;
		while(ub - lb > 1) {
			int mid = (lb + ub) / 2;
			if(canDo(a, c[mid])) {
				ub = mid;
			} else {
				lb = mid;
			}
		}
		if(canDo(a, lb)) return c[lb];
		return c[ub];
	}
	
	static boolean canDo(int[] a, int k) {
		int prev = -1;
		for(int i = 0; i < a.length; i++) {
			if(a[i] > k) {
				if(prev == -1) prev = a[i];
				else if(prev == a[i]) prev = -1;
				else return false;
			}
		}
		return prev == -1;
	}
	
}
