import java.util.Scanner;

public class GrayCode_Fran {

	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		long inputN = reader.nextLong();
		long a = reader.nextLong(2);
		long b = reader.nextLong(2);
		long n = getN(a, b);
		long i = getIndex(n, a, 0, (1l << n) - 1, false);
		long j = getIndex(n, b, 0, (1l << n) - 1, false);
		if(i == j) {
			System.out.println(0);
		} else {
			System.out.println(Math.abs(i - j) - 1);
		}
		reader.close();
	}

	static int getN(long a, long b) {
		long c = Math.max(a, b);
		int n = 1;
		while(c > 1) {c /= 2; n++;}
		return n;
	}

	static long getIndex(long n, long a, long l, long r, boolean reverse) {
		if(l == r) return l;
		if(reverse) {
			if(((a >> (n - 1)) & 1) == 1) {
				return getIndex(n - 1, a, l, (l + r) / 2, false);
			}
			return getIndex(n - 1, a, (l + r) / 2 + 1, r, true);
		} else {
			if(((a >> (n - 1)) & 1) == 1) {
				return getIndex(n - 1, a, (l + r) / 2 + 1, r, true);
			}
			return getIndex(n - 1, a, l, (l + r) / 2, false);
		}
	}

}
