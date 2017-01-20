import java.util.*;
import java.math.*;

public class F
{
	public static void solve(int n, String str, BigInteger[] val, Boolean rev)
	{
		BigInteger t=BigInteger.ZERO, p=BigInteger.ONE;
		BigInteger b=BigInteger.valueOf(26);

		for(int i=0; i<n; i++)
		{
			t=t.multiply(b).add(BigInteger.valueOf(str.charAt(i)-'a'));
			p=p.multiply(b);
		}

		if( rev )
			str=new StringBuffer(str).reverse().toString();

		System.out.println(str);


		System.out.println(t);
		p=p.divide(b);

		for(int i=0; i<n; i++)
		{
			BigInteger idx=BigInteger.valueOf(rev ? n-i : i+1);

			if( t.compareTo(val[0])>0 )
			{
				val[0]=t;
				val[1]=idx;
			}
			else if( t.compareTo(val[0])==0 && val[1].compareTo(idx)>0 )
				val[1]=idx;

			t=t.divide(b).add(p.multiply(BigInteger.valueOf(str.charAt(n-i-1)-'a')));
		}
	}

	public static void main(String[] args)
	{
		Scanner sc=new Scanner(System.in);
		
		for(int N=sc.nextInt(); N>0; N--)
		{
			int n=sc.nextInt();		
			String s=sc.next();
			BigInteger[] val={BigInteger.ZERO, BigInteger.ZERO}, rev={BigInteger.ZERO, BigInteger.ZERO};
			solve(n, s, val, false);
			solve(n, s, rev, true);
			int i=val[1].intValue();
			int j=rev[1].intValue();

			System.out.println(val[0]);
			System.out.println(rev[0]);

			if( val[0].compareTo(rev[0])<0 )
				System.out.println(j+" 1");
			else if( val[0].compareTo(rev[0])>0 )
				System.out.println(i+" 0");
			else if( i<=j )
				System.out.println(i+" 0");
			else
				System.out.println(j+" 1");
		}
	}
}
