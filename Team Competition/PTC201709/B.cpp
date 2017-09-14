#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int T;
	scanf("%d", &T);

	for(int t = 0; t < T; t++)
	{
		char s[20480];
		bool ok[20480];
		memset(ok, false, sizeof(ok));

		scanf("%s", s);

		int len = strlen(s);
		s[len++] = ',';

		for(int i = 0, p = 0, to = -1; i < len; i++)
		{
			if( s[i] == '~' )
				to = i;
			else if( s[i] == ',' )
			{
				if( to == -1 )
				{
					s[i] = 0;
					ok[ atoi(s+p) ] = true;
				}
				else
				{
					s[to] = 0;
					s[i] = 0;
					int a = atoi(s+p);
					int b = atoi(s+to+1);

					for(int j = a; j <= b; j++)
						ok[j] = true;
				}

				p = i+1;
				to = -1;
			}
		}


		int cnt = 0;
		for(int i = 0; i < 1024; i++)
			cnt += ok[i];

		printf("%d:", cnt);
		for(int i = 0; i < 1024; i++)
			if( ok[i] )
				printf(" %d", i);
		puts("");


	}

	return 0;
}

/*
2
1,2~3,5,8~8
4~7,2,6~8,5
*/