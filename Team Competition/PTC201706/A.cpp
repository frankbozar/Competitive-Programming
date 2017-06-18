#include <stdio.h>
#include <string.h>

int main()
{
	int n;
	scanf("%d", &n);


	for(int i = 0; i < n; i++)
	{
		int st = 0;
		char s[512];
		scanf("%s", s);

		int len = strlen(s);
		int cnt = 0;
		bool ans = true;

		for(int j = 0; j < len; j++)
		{
			if( s[j] >= 'a' && s[j] <= 'j' )
				cnt++;
			else if( s[j] == 'U' || s[j] == 'M' || s[j] == 'T' || s[j] == 'R' )
				cnt--;
			else if( s[j] != 'Z' )
				cnt = 0;
			ans &= (cnt > 0);
		}
		
		if( ans && cnt == 1 )
			puts("YES");
		else
			puts("NO");
	}

	return 0;
}

/*
5
aM
cZ
abU
dZbcTT
az
*/