
import java.io.*;
import java.util.*;
import java.math.*;

public class B
{
    public static void main(String[] args)
{
Scanner sc=new Scanner(System.in);
    int T=sc.nextInt();
    for(; T>0; T--)
    {
        long nn=sc.nextLong();
        
        for(; nn>1; nn--)
        {
            BigInteger n=new BigInteger(String.valueOf(nn));
            
            if( n.isProbablePrime(10) /*&& n.isProbablePrime(100)*/ )
                break;
        }
        
        System.out.println(nn);
    }

}
}
