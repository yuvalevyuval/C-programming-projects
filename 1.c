#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printIntro()
{
	printf("Hello master! Please enter '1' for \"Trinomial solver\", "
		"'2' for \"Third degree equation solver\", "
		"or '3' for \"Series calculations\". "
		"If you wish to leave me choose '0':\n");
}

void printChoice(int choice) 
{
	if (choice == -1)
		printf("No, this was not an option my lord, "
			"please choose again wisely:\n");
	if (choice == 1) 
	{
		printf("You choose to solve a trinomial. Please "
			"enter the 'b' and 'c' coefficients:\n");
	}
	if (choice == 2)
	{
		printf("You choose to solve a \"Third degree equation\"."
			" Please enter the coefficients - 'b', 'c' and 'd'\n");
	}
	if (choice == 3)
	{
		printf("You choose to solve a \"Series calculations\"."
			" Please enter the coefficients - 'a0', 'q' and 'n'\n");
	}
	if (choice == 0)
		printf("I bid you farewell, and thanks for the fish.\n");
}

void printNoRoots() 
{
	printf("No solution found for the trinomial!\n");
}

void printSameRoots(int root) {
	printf("Trinomial is solved! ");
	printf("The only root is: (%d)\n", root);
}

void printRoots(int root1, int root2) 
{
	printf("Trinomial is solved! ");
	printf("The roots are: (%d) and (%d)\n", root1, root2);
}

void printNoEqSol() 
{
	printf("No solution found for the equation!\n");
}

void printEqSol(int x1, int x2, int x3) 
{
	printf("Equation solved! ");
	printf("The roots are: (%d),(%d) and (%d)\n", x1, x2, x3);
}

void printSeries(int a_n) 
{
	printf("The n'th element is (%d)\n", a_n);
}

void printErrSeries() 
{
	printf("The number of elements in a series should be non - negative. Try again.\n");
}

void TrinomCalc(int b, int c)
{
	//first we define variables as roots so we can tell when we are out of the loop without a root
	int root1 = 1001, root2 = 1001, X1, X2;
	for (X1 = -1000; X1 < 1001; X1++)
	{
		for (X2 = -1000; X2 < 1001; X2++)
		{
			if ((X1 + X2 == -b) && (X1*X2 == c))
			{
				root1 = X1;
				root2 = X2;
			}
		}
	}
		//now we make shure that we have 2 roots, one root, or no roots
	if ((root1 == root2) && (root1!=1001))
	{
		printSameRoots(root1);
	}
	if ((root1 != root2)&&(root1!=1001)&&(root2!=1001))
	{
		printRoots(root1, root2);
	}
	if ((root1 == 1001) || (root2 == 1001))
	{
		printNoRoots();
	}
	
}

int calc2(b ,c ,d)
{
	int x1 = 1001, x2 = 1001, x3 = 1001, i =-1000;
	//we set the roots to be outside of the range so we can tell when we are out of the loop
	while (i < 1001)
	{
		//we put an i that runs from -1000 until + 1000, to avoid double counting and save time
		if ((i*i*i + i*i*b + i*c + d == 0) && (x1 == 1001))
		{
			x1 = i;
			i++;
		}

		if ((i*i*i + i * i*b + i * c + d == 0) && (x2 == 1001))
		{
			x2 = i;
			i++;
		}
		if ((i*i*i + i * i*b + i * c + d == 0) && (x3 == 1001))
		{
			x3 = i;
			i++;
			break;
		}
		else
			(i++);
	}
	//now categorize the results
	if ((x1 == 1001)||(x2 == 1001)||(x3 == 1001))
	{
		printNoEqSol();
		return 0;
	}
	else
	{
		printEqSol(x1, x2, x3);
	}
	return 1;
}

void SeriesCalc(a0, q, n)
{
	int i = 0;
	if (n < 0)
	{
		printErrSeries();
	}
	
	else
	{
		while (i < n) 
		{
			a0 = a0 * q;
			i++;
		}
		printSeries(a0);
	}

}


int calc(int choice)
{
	int b, c, B, C, D, a0, q, n;
	//this function is the general calculator, sends to each specific calc function
	printChoice(choice);

	if (choice == 1)
	{
		scanf("%d" "%d", &b, &c);
		TrinomCalc(b, c);
	}

	if (choice == 2)
	{
		scanf("%d" "%d" "%d", &B, &C, &D);
		calc2(B, C, D);
	}
	if (choice == 3)
	{
		scanf("%d" "%d" "%d", &a0, &q, &n);
		SeriesCalc(a0, q, n);
	}
	   
}
	
int play(choice)
{
	//we use this function so we can run forever until choice == 0
	scanf("%d", &choice);

	while ((choice < 0) || (choice > 3))
	{
		if (choice == 0)
		{
			printChoice(0);
			break;
		}
		else
		{
			printChoice(-1);
			play();
		}
		return 0;
	}

	while ((choice > -1) && (choice < 4))
	{
		if (choice == 0)
		{
			printChoice(0);
			break;
		}
		else
		{
			calc(choice);
			printIntro();
			play();
		}
		return 0;
	}
	//return 0;
}
void main()
{
	int choice, b, c, B, C, D , a0, q, n;

	printIntro();
	play();
	
	
}