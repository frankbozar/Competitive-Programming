import java.util.*;
import java.io.*;

public class jeroen2
{
	static final int CANDIES = 4;
	static final int CATCHXP = 100;
	static final int EVOLVEXP = 500;
	
	static int M;
	static int[] next, prev, price, familyIdx, familyNum;
	
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int f = Integer.valueOf(in.readLine());

		int[] s = new int[f];
		String[][] fp = new String[f][];
		int[][] c = new int[f][];
		for(int i = 0; i < f; i++) {
			String[] ps = in.readLine().split(" ");
			s[i] = Integer.valueOf(ps[0]);
			fp[i] = new String[s[i]];
			c[i] = new int[s[i]-1];
			for(int j = 0; j < s[i] - 1; j++) {
				fp[i][j] = ps[j*2+1];
				c[i][j] = Integer.valueOf(ps[j*2+2]);
			}
			fp[i][s[i]-1] = ps[s[i] * 2 - 1];
		}

		int N = Integer.valueOf(in.readLine());
		int[] t = new int[N];
		String[] p = new String[N];
		for(int i = 0; i < N; i++) {
			String[] ps = in.readLine().split(" ");
			t[i] = Integer.valueOf(ps[0]);
			p[i] = ps[1];
		}

		// Number all pokemon from the input
		int[][] fpn = new int[f][];
		for(int i = 0; i < f; i++) {
			fpn[i] = new int[s[i]];
			for(int j = 0; j < s[i]; j++)
				fpn[i][j] = getNum(fp[i][j]);
		}
		int[] pn = new int[N];
		for(int i = 0; i < N; i++)
			pn[i] = getNum(p[i]);
		
		// There are M pokemon in total
		M = pokeNum.size();

		// Make next/prev values for each pokemon number
		next  = new int[M];
		prev  = new int[M];
		price = new int[M];
		for(int i = 0; i < M; i++)
			next[i] = prev[i] = -1;
		for(int i = 0; i < f; i++) {
			for(int j = 0; j < s[i]; j++) {
				if(j < s[i] - 1) {
					next[fpn[i][j]] = fpn[i][j+1];
					price[fpn[i][j]] = c[i][j];
				}
				if(j > 0)
					prev[fpn[i][j]] = fpn[i][j-1];
			}
		}

		// Give a family number to each pokemon (first pokemon in chain),
		// and and index specifying where this pokemon is in the chain
		familyNum = new int[M];
		familyIdx = new int[M];
		for(int i = 0; i < M; i++)
			familyNum[i] = -1;
		for(int i = 0; i < M; i++) { // this loop is O(M)
			if(familyNum[i] != -1) continue;
			int j = i;
			while(prev[j] != -1)
				j = prev[j];
			int fam = j;
			int idx = 0;
			while(j != -1) {
				familyNum[j] = fam;
				familyIdx[j] = idx++;
				j = next[j];
			}
		}

		// Some bookkeeping to do
		int totalXP = 0;
		int bestEggXP = 0;
		Queue<Integer> catchTimes = new LinkedList<Integer>();
		
		// Now go through all events
		Families eggfam = new Families();
		for(int i = 0; i < N; i++) {
			// We caught one, yes!
			totalXP += CATCHXP;
			eggfam.Catch(pn[i]);

			// Keep a list of the catches in the last 1800 seconds
			catchTimes.add(t[i]);
			while(catchTimes.peek() <= t[i] - 1800)
				catchTimes.remove();

			// Greedily do evolutions within the egg time,
			// make sure they are balanced again.
			int fam = familyNum[pn[i]];
			int cur = pn[i];
			while(eggfam.end[fam] != -1 && familyIdx[cur] < familyIdx[eggfam.end[fam]]) {
				if(eggfam.candy[fam] > price[cur]) {
					// Yes we can
					eggfam.GreedyEvolve(cur, 1);
					cur = next[cur];
				} else {
					// Undo highest evolution to get some money back
					eggfam.UndoHighest(fam);
				}
			}

			// As long as we've got candies, go on!
			while(true) {
				int am = eggfam.GreedyEvolve(eggfam.start[fam], -1);
				if(am == 0) break;
			}
			
			// What if we used the egg for the past 1800s?
			int curEggXP = catchTimes.size() * CATCHXP + eggfam.xp * 2;
			bestEggXP = Math.max(bestEggXP, curEggXP);
		}

		System.out.println(totalXP + bestEggXP);
	}

	// A set of families with their evolved states
	static class Families {
		int[] candy;
		int xp = 0;
		int[] amount;
		int[] evolved;
		int[] start; // first non-evolved pokemon
		int[] end;   // highest evolved pokemon

		public Families() {
			candy = new int[M];
			amount = new int[M];
			evolved = new int[M];
			start = new int[M];
			end = new int[M];
			for(int i = 0; i < M; i++)
				start[i] = end[i] = -1;
		}

		// Catch a new pokemon
		public void Catch(int pn) {
			int fam = familyNum[pn];
			amount[pn]++;
			if(start[fam] == -1 || familyIdx[pn] < familyIdx[start[fam]])
				start[fam] = pn;
			candy[fam] += CANDIES;
		}

		// Greedily evolve some pokemon in this family
		public int GreedyEvolve(int pn, int maxAmount) {
			if(next[pn] == -1) return 0;
			if(maxAmount == -1) maxAmount = amount[pn];
			int fam = familyNum[pn];
			
			int am = Math.min(Math.min(amount[pn], maxAmount), (candy[fam] - 1) / price[pn]);
			evolved[pn] += am;
			amount[pn] -= am;
			amount[next[pn]] += am;
			candy[fam] -= am * price[pn];
			xp += EVOLVEXP * am;

			if(pn == start[fam] && amount[pn] == 0)
				start[fam] = next[pn];

			if(am > 0 && (end[fam] == -1 || familyIdx[end[fam]] < familyIdx[pn]))
				end[fam] = pn;

			return am;
		}	

		// Undo the highest evolution	
		public void UndoHighest(int fam) throws Exception{ 
			if(end[fam] == -1) throw new Exception("Can't undo!");
			Undo(end[fam]);
		}

		// Undo a single evolution
		public void Undo(int undo) throws Exception {
			int fam = familyNum[undo];
			if(amount[next[undo]] == 0 || evolved[undo] == 0) throw new Exception("Invariant broken");

			xp -= EVOLVEXP;
			candy[fam] += price[undo];
			
			amount[next[undo]]--;
			amount[undo]++;
			evolved[undo]--;

			if(evolved[undo] == 0 && end[fam] == undo)
				end[fam] = evolved[prev[undo]] == 0 ? -1 : prev[undo];

			if(start[fam] == -1 || familyIdx[start[fam]] > familyIdx[undo])
				start[fam] = undo;
		}
	}


	// Numbering the strings, easy part
	public static Map<String,Integer> pokeNum = new HashMap<String,Integer>();

	public static int getNum(String poke) {
		if(pokeNum.containsKey(poke))
			return pokeNum.get(poke);
		else {
			int n = pokeNum.size();
			pokeNum.put(poke, n);
			return n;
		}
	}
}
