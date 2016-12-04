import java.math.BigInteger;
import java.util.Scanner;

public class GrayCode_Fran_BigInt {

	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		int n = reader.nextInt();
		long a = Long.parseLong(reader.next(), 2);
		long b = Long.parseLong(reader.next(), 2);
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

	static long getIndex(int n, long a, long l, long r, boolean reverse) {
		if(l == r) return l;
		long mid = (BigInteger.valueOf(l).add(BigInteger.valueOf(r))).divide(BigInteger.valueOf(2)).longValue();
		if(reverse) {
			if(((a >> (n - 1)) & 1) == 1) {
				return getIndex(n - 1, a, l, mid, false);
			}
			return getIndex(n - 1, a, mid + 1, r, true);
		} else {
			if(((a >> (n - 1)) & 1) == 1) {
				return getIndex(n - 1, a, mid + 1, r, true);
			}
			return getIndex(n - 1, a, l, mid, false);
		}
	}

}
