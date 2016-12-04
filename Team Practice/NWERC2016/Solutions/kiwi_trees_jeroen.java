import java.util.*;
import java.io.*;
import java.awt.geom.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		Point2D.Double[] pt = new Point2D.Double[n];
		for(int i = 0; i < n; i++) {
			String[] xy = in.readLine().split(" ");
			pt[i] = new Point2D.Double(Double.valueOf(xy[0]) / 1000, Double.valueOf(xy[1]) / 1000);
		}

		// All of the circles we found (of which some might intersect)
		ArrayList<Point2D.Double> circles = new ArrayList<Point2D.Double>();

		// Try to put circle between each pair of consecutive poles
		for(int i = 0; i < n; i++) {
			Point2D.Double A = pt[i];
			Point2D.Double B = pt[(i+1)%n];
			Point2D.Double C = pt[(i+2)%n];
			// Compute inner angle of A-B-C
			double angleA = Math.atan2(A.x - B.x, A.y - B.y);
			double angle = angleA - Math.atan2(C.x - B.x, C.y - B.y);
			// Distance from corner
			double dst = (4.0 + 1e-9) / Math.sin(angle / 2.0);
			// Create the candidate point
			double absAngle = angleA - angle / 2.0;
			Point2D.Double p = new Point2D.Double(B.x + Math.sin(absAngle) * dst, B.y + Math.cos(absAngle) * dst);

			// Test if this candidate fits
			boolean ok = PointInPolygon(p, pt);
			for(int j = 0; ok && j < n; j++)
				if(LinePointDist(pt[j], pt[(j+1)%n], p, true) < 4 - 1e-9)
					ok = false;
			if(ok) {
				// We've found half of an answer!
				circles.add(p);
			}
		}

		// Match up the circles with brute force
		for (Point2D.Double a : circles) {
			for (Point2D.Double b : circles) {
				if (a == b) {
					break;
				}
				if (a.distance(b) >= 8) {
					// We've found an answer!
					System.out.println(a.x * 1000 + " " + a.y * 1000);
					System.out.println(b.x * 1000 + " " + b.y * 1000);
					return;
				}
			}
		}

		// Bummer
		System.out.println("impossible");
	}

	// Prewritten code
	
	public static double LinePointDist(Point2D.Double L1, Point2D.Double L2, Point2D.Double P, boolean isSegment)
	{
		double dist = cross(minus(L2,L1), minus(P, L1)) / L1.distance(L2);
		if (isSegment)
		{
			if (dot(minus(P, L2), minus(L2, L1)) > 0) return L2.distance(P);
			if (dot(minus(P, L1), minus(L1, L2)) > 0) return L1.distance(P);
		}
		return Math.abs(dist);
	}

	public static boolean PointInPolygon(Point2D.Double P, Point2D.Double[] polygon)
	{
		int j = polygon.length - 1, c = 0;
		for (int i = 0; i < polygon.length; j = i++) {
			if ((polygon[j].y <= P.y) && (P.y < polygon[i].y) &&
				(cross(minus(polygon[j], P), minus(polygon[i], P))) > 0) ++c;
			if ((polygon[i].y <= P.y) && (P.y < polygon[j].y) &&
				(cross(minus(polygon[j], P), minus(polygon[i], P))) < 0) --c;
		}
		return c != 0;
	}
	
	public static double dot(Point2D.Double A, Point2D.Double B)
	{
		return A.x * B.x + A.y * B.y;
	}
	
	public static double cross(Point2D.Double A, Point2D.Double B)
	{
		return A.x * B.y - A.y * B.x;
	}
	
	public static Point2D.Double minus(Point2D.Double A, Point2D.Double B)
	{
		return new Point2D.Double(A.x - B.x, A.y - B.y);
	}
}
