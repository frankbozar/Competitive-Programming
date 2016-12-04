// O(N log N)

import java.util.*;
import java.io.*;

public class jeroen
{
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
		int M = pokeNum.size();

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
		int[] familyIdx = new int[M];
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
		evolveXP = 0;
		Queue<Integer> catchTimes = new LinkedList<Integer>();
		familyCandy = new int[M];
		amount = new int[M];
		evolved = new int[M];
		int[] familyAt = new int[M];
		int[] familyStart = new int[M];
		for(int i = 0; i < M; i++)
			familyStart[i] = familyAt[i] = -1;
		
		// Now go through all events
		for(int i = 0; i < N; i++) {
			// We caught one, yes!
			totalXP += 100;
			amount[pn[i]]++;

			// Keep a list of the catches in the last 1800 seconds
			catchTimes.add(t[i]);
			while(catchTimes.peek() <= t[i] - 1800)
				catchTimes.remove();

			// We also got some candy for this family
			int fam = familyNum[pn[i]];
			familyCandy[fam] += 3 + 1;  // We always get rid of the pokemon in the end

			// We want to get all pokemon in this family up the same level, so if this
			// pokemon is at a lower level we may need to undo some previous evolutions
			// to get it there.
			int cur = pn[i];
			if(familyStart[fam] == -1 || familyIdx[cur] < familyIdx[familyStart[fam]])
				familyStart[fam] = cur;
			int curAt = -1;
			while(familyAt[fam] != -1 && familyIdx[cur] < familyIdx[familyAt[fam]]) {
				// Do we have candy to evolve already?
				if(price[cur] < familyCandy[fam]) { // < because we can't use the last candy
					evolveGreedy(cur);
					curAt = cur;
					cur = next[cur];
				} else {
					// We need to undo the highest evolution.
					int undo = familyAt[fam];
					familyCandy[fam] += price[undo];
					evolveXP -= 500;
					amount[next[undo]]--;
					evolved[undo]--;
					amount[undo]++;

					// See if we have taken a step back in how far we are with evolving.
					if(evolved[undo] == 0) {
						familyAt[fam] = prev[undo];

						// Or maybe this was the last evolved pokemon?
						if(evolved[prev[undo]] == 0) {
							familyAt[fam] = -1;
						}
					}
				}
			}
			if(familyAt[fam] == -1) familyAt[fam] = curAt;
			
			// Now greedily evolve the family with the rest of the candy
			cur = familyAt[fam] == -1 ? familyStart[fam] : familyAt[fam];
			if(amount[cur] == 0 && next[cur] != -1)
				cur = next[cur];
			while(next[cur] != -1) {
				// Evolve some
				int am = evolveGreedy(cur);
				if(am == 0) break;
				familyAt[fam] = cur;
				if(amount[cur] != 0) break;
				cur = next[cur];
			}
		
			// What if we used the egg for the past 1800s?
			int curEggXP = catchTimes.size() * 100 + evolveXP * 2;
			bestEggXP = Math.max(bestEggXP, curEggXP);
		}

		System.out.println(totalXP + bestEggXP);
	}

	static int evolveXP;
	static int[] price, next, prev, amount, evolved, familyCandy, familyNum;

	static int evolveGreedy(int pok) {
		int fam = familyNum[pok];
		int am = Math.min(amount[pok], (familyCandy[fam] - 1) / price[pok]);
		evolveXP += am * 500;
		familyCandy[fam] -= am * price[pok];
		evolved[pok] += am;
		amount[next[pok]] += am;
		amount[pok] -= am;
		return am;
	}
	

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
