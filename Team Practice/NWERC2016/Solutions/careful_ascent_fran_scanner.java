import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class fran_scanner {

	static int x, y, n;
	static int[] l, u;
	static double[] f;

	static String dir = "Heist/";

	public static void main(String[] args) throws FileNotFoundException, IOException {
		Scanner sc = new Scanner(System.in);
		x = sc.nextInt();
		y = sc.nextInt();
		Point target = new Point(x, y);
		n = sc.nextInt();
		l = new int[n];
		u = new int[n];
		f = new double[n];
		for(int i = 0; i < n; i++) {
			l[i] = sc.nextInt();
			u[i] = sc.nextInt();
			f[i] = sc.nextDouble();
		}
		if(y == 0) {
			System.out.println(0);
		} else {
			double lb = -1000010;
			double ub =  1000010;
			while(Math.abs(lb - ub) > Cmp.eps) {
				double dx = (lb + ub) / 2.0;
				Point p = new Point(0, 0);
				for(int i = 0; i < n; i++) {
					Line trajectory = new Line(p.x, p.y, p.x + dx, p.y + 1);
					Line lowShild = new Line(0, l[i], 1, l[i]);
					Point q = trajectory.intersection(lowShild);
					trajectory = new Line(q.x, q.y, q.x + dx * f[i], q.y + 1);
					Line highShild = new Line(0, u[i], 1, u[i]);
					p = trajectory.intersection(highShild);
				}
				Line trajectory = new Line(p.x, p.y, p.x + dx, p.y + 1);
				double val = trajectory.eval(target);
				if(Cmp.leq(val, 0)) {
					lb = dx;
				} else {
					ub = dx;
				}
			}
			double dx = (lb + ub) / 2.0;
			System.out.println(dx);
		}
	}

	// GEOMETRY
	
	static class Point {
		
		double x, y;
		
		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}
		
		public String toString() {
			return String.format("(%.3f, %.3f)", x, y);
		}
		
	}
	
	static class Line {

		public double A, B, C, m, b;
		public Point p1, p2;
		public String id;

		public Line(double x1, double y1, double x2, double y2) {
			p1 = new Point(x1, y1);
			p2 = new Point(x2, y2);
			A = y2 - y1;
			B = x1 - x2;
			C = A * x1 + B * y1;
			m = -A / B;
			b = C / B;
		}
	
		public double eval(Point p) {
			double temp = A * p.x + B * p.y;
			return C - temp;
		}
		
		public boolean parallel(Line other) {
			return Cmp.eq(det(other), 0);
		}
		
		public Point intersection(Line other) {
			if(parallel(other)) return null;
			double d = det(other);
			return new Point((other.B * C - B * other.C) / d, (-other.A * C + A * other.C) / d);
		}
		
		public double det(Line other) {
			return A * other.B - other.A * B;
		}
		
		public String toString() {
			return String.format("%.3f x + %.3f y = %.3f", A, B, C);
		}
		
	}
	
	static class Cmp {
		
		static double eps = 1e-8;
		
		public static boolean eq(double x, double y) {
			return Math.abs(x - y) <= eps;
		}
		
		public static boolean le(double x, double y) {
			return x < y - eps;
		}
		
		public static boolean ge(double x, double y) {
			return x > y + eps;
		}
		
		public static boolean leq(double x, double y) {
			return x <= y + eps;
		}
		
		public static boolean geq(double x, double y) {
			return x >= y - eps;
		}
		
		public static int cmp(double x, double y) {
			if(eq(x, y)) return 0;
			if(le(x, y)) return -1;
			return 1;
		}
		

		public static int sgn(double x) {
			if(Cmp.le(x, 0)) return -1;
			if(Cmp.ge(x, 0)) return 1;
			return 0;
		}
		
	}

}
