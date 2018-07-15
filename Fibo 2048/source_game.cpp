#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

struct mygame
{
	int rank;
	char *date;
	char *name;
	char *bdtype;
	int moves;
};

int fail = 0;
int choice()
{
	printf("OPTIONS:  1 -> 2*2 Board   2 -> 4*4 Board\n");
	int n;
	printf("Enter choice: ");
	scanf("%d",&n);
	if (n == 1) return 2;
	else return 4;
}
void print(int ch,int **a)
{
	int i, j;
	for (i = 0; i < ch; i++)
	{
		for (j = 0; j < ch; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}
int all_equal(int a, int b, int c, int d)
{
	if (a == c && b == d)
		return 0;
	return 1;
}
void init(int ch,int **a,char *str)
{
	int r[4];
	srand(time(NULL));
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			r[i] = rand() % ch;
		}
		if (all_equal(r[0], r[1], r[2], r[3]) == 1)
			break;
	}
	a[r[0]][r[1]] = 1;
	a[r[2]][r[3]] = 1;
	//print(ch,a);
}


int sea(int x)
{
	int i;
	int * fib = (int*)malloc(32 * sizeof(int));
	fib[0] = 1;
	fib[1] = 1;
	for (i = 2; i < 32; i++)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	for (i = 0; i < 32; i++)
	{
		if (x == fib[i])
			return 1;
	}
	return 0;
}
int side(int x, int y)
{
	int i;
	int * fib = (int*)malloc(32 * sizeof(int));
	fib[0] = 1;
	fib[1] = 1;
	for (i = 2; i < 32; i++)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	for (i = 0; i < 32; i++)
	{
		if (x == fib[i])
		{
			if (fib[i - 1] == y || fib[i + 1] == y)
				return 1;
		}
	}
	return 0;
}
void leftmove(int **a, int ch)
{
	int k,x,y,i,d;
	for (k = 0; k < ch; k++)
	{
		d = 0;
		int * arr = (int*)calloc(ch, sizeof(int));
		for (i = 0; i <ch; i++)
		{
			while (i<ch)
			{
				if (a[k][i] == 0)
					i++;
				else
					break;
			}
			if (i == ch)
				goto lace;
			x = a[k][i];
			int p = sea(x);
			if (p == 1)
			{
				while (i<ch)
				{
					if (i + 1 < ch)
					{
						if (a[k][i + 1] == 0)
							i++;
						else
							break;
					}
					else
						break;
				}
				if (i == ch - 1)
				{
					arr[d] = x;
					d++;
					goto lace;
				}
				y = a[k][i + 1];
				int q = sea(y);
				if (q == 1)
				{
					int r = side(x, y);
					if (r == 1)
					{
						i++;
						arr[d] = x + y;
						d++;
					}
					else
					{
						arr[d] = x;
						d++;
					}
				}
				else
				{
					arr[d] = x;
					d++;
				}
			}
			else
			{
				arr[d] = x;
				d++;
			}
		}
		lace:
		for (i = 0; i < ch; i++)
		{
			a[k][i] = arr[i];
		}
	}
}
void upmove(int **a, int ch)
{
	int k, x, y, i, d;
	for (k = 0; k < ch; k++)
	{
		d = 0;
		int * arr = (int*)calloc(ch, sizeof(int));
		for (i = 0; i <ch; i++)
		{
			while (i<ch)
			{
				if (a[i][k] == 0)
					i++;
				else
					break;
			}
			if (i == ch)
				goto uace;
			x = a[i][k];
			int p = sea(x);
			if (p == 1)
			{
				while (i<ch)
				{
					if (i + 1 < ch)
					{
						if (a[i + 1][k] == 0)
							i++;
						else
							break;
					}
					else
						break;
				}
				if (i == ch - 1)
				{
					arr[d] = x;
					d++;
					goto uace;
				}
				y = a[i + 1][k];
				int q = sea(y);
				if (q == 1)
				{
					int r = side(x, y);
					if (r == 1)
					{
						i++;
						arr[d] = x + y;
						d++;
					}
					else
					{
						arr[d] = x;
						d++;
					}
				}
				else
				{
					arr[d] = x;
					d++;
				}
			}
			else
			{
				arr[d] = x;
				d++;
			}
		}
		uace:
		for (i = 0; i < ch; i++)
		{
			a[i][k] = arr[i];
		}
	}
}
void rightmove(int **a, int ch)
{
	int k,i,f,x,y;
	for (k = 0; k < ch; k++)
	{
		f = ch - 1;
		int * arr = (int*)calloc(ch, sizeof(int));
		for (i = ch - 1; i >= 0; i--)
		{
			while (i >= 0)
			{
				if (a[k][i] == 0)
					i--;
				else
					break;
			}
			if (i == -1)
				goto race;
			x = a[k][i];

			int p = sea(x);
			if (p == 1)
			{
				while (i - 1 >= 0)
				{
					if (i - 1 > 0)
					{
						if (a[k][i - 1] == 0)
							i--;
						else
							break;
					}
					else
						break;
				}
				if (i == 0)
				{
					arr[f] = x;
					f--;
					goto race;
				}
				y = a[k][i - 1];
				int q = sea(y);
				if (q == 1)
				{
					int r = side(x, y);
					if (r == 1)
					{
						i--;
						arr[f] = x + y;
						f--;
					}
					else
					{
						arr[f] = x;
						f--;
					}
				}
				else
				{
					arr[f] = x;
					f--;
				}
			}
			else
			{
				arr[f] = x;
				f--;
			}
		}
		race:
		for (i = 0; i < ch; i++)
		{
			a[k][i] = arr[i];
		}
	}
}
void downmove(int **a, int ch)
{
	int k, i, f, x, y;
	for (k = 0; k < ch; k++)
	{
		f = ch - 1;
		int * arr = (int*)calloc(ch, sizeof(int));
		for (i = ch - 1; i >= 0; i--)
		{
			while (i >= 0)
			{
				if (a[i][k] == 0)
					i--;
				else
					break;
			}
			if (i == -1)
				goto dace;
			x = a[i][k];

			int p = sea(x);
			if (p == 1)
			{
				while (i - 1 >= 0)
				{
					if (i - 1 > 0)
					{
						if (a[i - 1][k] == 0)
							i--;
						else
							break;
					}
					else
						break;
				}
				if (i == 0)
				{
					arr[f] = x;
					f--;
					goto dace;
				}
				y = a[i - 1][k];
				int q = sea(y);
				if (q == 1)
				{
					int r = side(x, y);
					if (r == 1)
					{
						i--;
						arr[f] = x + y;
						f--;
					}
					else
					{
						arr[f] = x;
						f--;
					}
				}
				else
				{
					arr[f] = x;
					f--;
				}
			}
			else
			{
				arr[f] = x;
				f--;
			}
		}
		dace:
		for (i = 0; i < ch; i++)
		{
			a[i][k] = arr[i];
		}
	}
}
int check(int **a, int ch)
{
	int i,j,t;
	t = (ch*ch*2);
	int * fibo = (int*)malloc((t) * sizeof(int));
	fibo[0] = 0;
	fibo[1] = 1;
	for (i = 2; i < t; i++)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	}
	for (i = 0; i < ch; i++)
	{
		for (j = 0; j < ch; j++)
		{
			if (a[i][j] == fibo[t - 1])
				return 1;
		}
	}
	return 0;
}
void gen(int **a, int ch)
{
	int i, j,k=0,rn,p,q;
	int *st1 = (int*)malloc(15 * sizeof(int));
	int *st2 = (int*)malloc(15 * sizeof(int));
	for (i = 0; i < ch; i++)
	{
		for (j = 0; j < ch; j++)
		{
			if (a[i][j] == 0)
			{
				st1[k] = i;
				st2[k] = j;
				k++;
			}
		}
	}
	if (k == 0) return;
	srand(time(NULL));
	rn = rand() % k;
	p = st1[rn];
	q = st2[rn];
	a[p][q] = 1;
}
void copy(int **a, int **b, int ch)
{
	int i, j;
	for (i = 0; i < ch; i++)
	{
		for (j = 0; j < ch; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}
int pos(int **a, int ch,int i,int j)
{
	int p;
	if (i - 1 >= 0)
	{
		p = side(a[i][j],a[i-1][j]);
		if (p == 1) return 1;
	}
	if (i + 1 < ch)
	{
		p = side(a[i][j], a[i + 1][j]);
		if (p == 1) return 1;
	}
	if (j - 1 >= 0)
	{
		p = side(a[i][j], a[i][j-1]);
		if (p == 1) return 1;
	}
	if (j + 1 < ch)
	{
		p = side(a[i][j], a[i][j+1]);
		if (p == 1) return 1;
	}
	return 0;
}
int eq(int **a, int **b, int ch)
{
	int i, j,tp=0;
	
	for (i = 0; i < ch; i++)
	{
		for (j = 0; j < ch; j++)
		{
			if (b[i][j] == a[i][j])
				tp++;
		}
	}
	if (tp == (ch*ch))
	{
		for (i = 0; i < ch; i++)
		{
			for (j = 0; j < ch; j++)
			{
				if (a[i][j] == 0)
					return 0;
				if (pos(a, ch, i, j) == 1)
					return 0;
			}
		}
		return 2;
	}
	else return 1;
}

struct pass
{
	char *name;
	int moov;
	int board;
};
pass *go = (pass*)malloc(3 * sizeof(pass));
void game(int **a, int ch,int *mv,char *str)
{
	while (1)
	{
		int ck,w,v;
		int **b = (int**)calloc(ch, sizeof(int*));
		for (int i = 0; i < ch; i++)
		{
			b[i] = (int*)calloc(ch, sizeof(int));
		}
		copy(a, b,ch);


		FILE *fz;
		fz = fopen("pauseboard.txt","w");
		go->name = str;
		go->moov = *mv;
		go->board = ch;
		fprintf(fz,"%s\n%d\n%d\n",go->name,go->moov,go->board);
		for (w = 0; w < ch; w++)
		{
			for (v = 0; v < ch; v++)
			{
				fprintf(fz,"%d",b[w][v]);
			}
		}
		fprintf(fz,"\n");
		fclose(fz);

		goto label;
		again:
			printf("Moves: %d\n", *mv);
			print(ch, a);
		label:
		char dr;
		printf("w-UP  a-LEFT  s-DOWN  d-RIGHT \n");
		printf("Enter direction: ");
		scanf(" %c", &dr);
		system("cls");
		if (dr == 'a')
		{
			leftmove(a, ch);
			ck = eq(a, b, ch);
			if (ck == 0)
				goto again;
			else if (ck == 2)
			{
				fail = 1;
				break;
			}
			else
				*mv = *mv + 1;
		}
		else if (dr == 'w')
		{
			upmove(a, ch);
			ck = eq(a, b, ch);
			if (ck == 0)
				goto again;
			else if (ck == 2)
			{
				fail = 1;
				break;
			}
			else
				*mv = *mv + 1;
		}
		else if (dr == 'd')
		{
			rightmove(a, ch);
			ck = eq(a, b, ch);
			if (ck == 0)
				goto again;
			else if (ck == 2)
			{
				fail = 1;
				break;
			}
			else
				*mv = *mv + 1;
		}
		else if (dr == 's')
		{
			downmove(a, ch);
			ck = eq(a, b, ch);
			if (ck == 0)
				goto again;
			else if (ck == 2)
			{
				fail = 1;
				break;
			}
			else
				*mv = *mv + 1;
		}
		printf("Moves: %d\n",*mv);
		int sd = check(a, ch);
		if (sd == 1) break;
		else
		{
			gen(a, ch);
			print(ch, a);
		}
	}
}

int conv(char *str, int len)
{
	int n = 0, i, k = 0;
	for (i = len - 1; i >= 0; i--)
	{
		n = n + (pow(double(10), k)*(str[i] - 48));
		k++;
	}
	return n;
}
void sort()
{
	FILE *fp,*fpo;
	fp = fopen("leaderboard.txt", "r");
	mygame **fibg = (mygame**)malloc(20 * sizeof(mygame));
	for (int as = 0; as < 20; as++)
	{
		fibg[as] = (mygame*)malloc(sizeof(mygame));
	}
	char * buf = (char*)calloc(100000, sizeof(char));
	int jz = 0,b,nc=0,t,i,w,j;
	char kl;
	kl = fgetc(fp);
	while (kl != EOF)
	{
		buf[jz++] = kl;
		kl = fgetc(fp);
	}
	buf[jz] = '\0';

	for (b = 0; b < jz; b++)
	{
		if (buf[b] == '\n')
			nc++;
	}
	t = nc - 1;
	int ch = 0;
	while (buf[ch] != '\n')
	{
		ch++;
	}
	for (i = 0; i < t; i++)
	{
		char *str = (char*)calloc(2, sizeof(char));
		w = 0;
		ch++;
		while (buf[ch] != '\t')
		{
			str[w] = buf[ch];
			w++;
			ch++;
		}
		str[w] = '\0';
		int s = conv(str, w);
		fibg[i]->rank = s;

		char *str2 = (char*)calloc(10, sizeof(char));
		w = 0;
		ch++;
		while (buf[ch] != '\t')
		{
			str2[w] = buf[ch];
			w++;
			ch++;
		}
		str2[w] = '\0';
		fibg[i]->date = str2;

		char *str3 = (char*)calloc(10, sizeof(char));
		w = 0;
		ch++;
		while (buf[ch] != '\t')
		{
			str3[w] = buf[ch];
			w++;
			ch++;
		}
		str3[w] = '\0';
		fibg[i]->name = str3;

		char *str4 = (char*)calloc(3, sizeof(char));
		w = 0;
		ch++;
		while (buf[ch] != '\t')
		{
			str3[w] = buf[ch];
			w++;
			ch++;
		}
		str3[w] = '\0';
		fibg[i]->bdtype = str3;

		char *str5 = (char*)calloc(3, sizeof(char));
		w = 0;
		ch++;
		while (buf[ch] != '\n')
		{
			str5[w] = buf[ch];
			w++;
			ch++;
		}
		str5[w] = '\0';
		int zx = conv(str, w);
		fibg[i]->moves = zx;
	}
	struct mygame *temp;
	if (t > 1)
	{
		for (i = t - 1; i >= 0; i--)
		{
			if (fibg[i]->moves < fibg[i - 1]->moves)
			{
				temp = fibg[i];
				fibg[i] = fibg[i - 1];
				fibg[i - 1] = temp;
			}
			else
				break;
		}
	}
	fpo = fopen("leaderbord.txt","w");
	fprintf(fp,"S.No	Date	Name	Board	Moves\n");
	for (i = 0,j=1; i < t; i++,j++)
	{
		fprintf(fpo, "%d\t%s\t%s\t%s\t%d\n", j, fibg[i]->date, fibg[i]->name, fibg[i]->bdtype, fibg[i]->moves);
	}
}

void paste(char *str,int mv,int ch)
{
	FILE *fp,*fip;
	char gc;
	fip = fopen("leaderBoard.txt", "r");
	if (fip == NULL)
		printf("FILE NOT FOUND!\n");
	else
	{
		int sp=0;
		char cg;
		cg = fgetc(fip);
		while (cg != EOF)
		{
			if (cg == '\n')
				sp++;
			cg = fgetc(fip);
		}
		fp = fopen("leaderBoard.txt", "a");
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			fprintf(fp, "%d\t", sp);
			fprintf(fp, "%d-%d-%d\t", tm.tm_year + 1900, tm.tm_mon, tm.tm_mday);
			fprintf(fp, "%s\t", str);
			fprintf(fp, "%d*%d\t", ch, ch);
			fprintf(fp, "%d", mv);
			fprintf(fp, "\n");

			sort();
	}
}
void playGame()
{
	printf("PLAY GAME Fibo2048\n");
	printf("Enter Player Name: ");
	char *str = (char*)malloc(20 * sizeof(char));
	scanf("%s", str);
	int ch = choice();
	int mv = 0;
	int **a = (int**)calloc(ch, sizeof(int*));
	for (int i = 0; i < ch; i++)
	{
		a[i] = (int*)calloc(ch, sizeof(int));
	}
	init(ch, a,str);
	printf("Moves: %d\n", mv);
	print(ch, a);
	game(a, ch, &mv,str);
	print(ch, a);
	if (fail == 1)
	{
		FILE *fq;
		fq = fopen("pauseboard.txt", "w");
		fclose(fq);
		printf("You've lost the Game!\n");
	}
	else
	{
		printf("%s won the Game in %d Moves\n", str, mv);
		FILE *fc;
		fc = fopen("pauseboard.txt","w");
		fclose(fc);
		paste(str, mv, ch);
	}
}
void replayGame()
{
	FILE *fq;
	fq = fopen("pauseboard.txt","r");
	char * buf = (char*)calloc(100000, sizeof(char));
	int jz = 0,len,w,t,r,p,i,j;
	char kl;
	kl = fgetc(fq);
	while (kl != EOF)
	{
		buf[jz++] = kl;
		kl = fgetc(fq);
	}
	buf[jz] = '\0';
	len = jz;
	w = 0;
	char *str = (char*)calloc(15, sizeof(char));
	while (buf[w] != '\n')
	{
		str[w] = buf[w];
		w++;
	}
	str[w] = '\0';
	w++;
	t = 0;
	char *str1 = (char*)calloc(3, sizeof(char));
	while (buf[w] != '\n')
	{
		str1[t++] = buf[w++];
	}
	str1[t] = '\0';
	int mv = conv(str1,t);
	w++;
	t = 0;
	char *str2 = (char*)calloc(1, sizeof(char));
	while (buf[w] != '\n')
	{
		str2[t++] = buf[w++];
	}
	str2[t] = '\0';
	int ch = conv(str2, t);
	w++;
	p = 0;
	int *ck = (int*)calloc((ch*ch),sizeof(int));
	for (r = 0; r < (ch*ch); r++)
	{
		t = 0;
		char *nh = (char*)calloc(1, sizeof(char));
		nh[t++] = buf[w++];
		nh[t] = '\0';
		ck[p++] = conv(nh,t);
	}

	int **a = (int**)calloc(ch, sizeof(int*));
	for (i = 0; i < ch; i++)
	{
		a[i] = (int*)calloc(ch, sizeof(int));
	}
	p = 0;
	for (i = 0; i < ch; i++)
	{
		for (j = 0; j < ch; j++)
		{
			a[i][j] = ck[p++];
		}
	}
	printf("Moves: %d\n", mv);
	print(ch, a);
	game(a, ch, &mv, str);
	print(ch, a);
	if (fail == 1)
	{
		FILE *fq;
		fq = fopen("pauseboard.txt", "w");
		fclose(fq);
		printf("You've lost the Game!\n");
	}
	else
	{
		printf("%s won the Game in %d Moves\n", str, mv);
		FILE *fc;
		fc = fopen("pauseboard.txt", "w");
		fclose(fc);
		paste(str, mv, ch);
	}
}
void viewLeaderBoard()
{
	if (fail == 0)
	{
		FILE *fpo;
		char gc;
		fpo = fopen("leaderBoard.txt", "r");
		if (fpo == NULL)
			printf("FILE NOT FOUND!\n");
		else
		{
			gc = fgetc(fpo);
			while (gc != EOF)
			{
				printf("%c", gc);
				gc = fgetc(fpo);
			}
		}
		printf("\n");
	}
}
void cool()
{
	FILE *fg;
	fg = fopen("pauseboard.txt","r");
	char c = fgetc(fg);
	int l = 0;
	while (c != EOF)
	{
		if (c == '\n')
			l++;
		c = fgetc(fg);
	}
	if (l>0)
		printf("1-Play Game   2-View LeaderBoard    3-Replay Last Saved Game\n");
	else
		printf("1-Play Game   2-View LeaderBoard\n");
	int choice;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		playGame();
		break;
	case 3:
		replayGame();
		break;
	case 2:
		viewLeaderBoard();
		break;
	}
}
void main()
{
	cool();
}