//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//using namespace std;

#define DART 10000
#define MAXPLAYER 1000

float player();
double fRand(double, double);

void main()
{
	srand(time(NULL));
	double avePI = 0;
	
	for (int i = 1; i <= MAXPLAYER; i++)
	{
		printf("\nPlayer #%i starts throwing darts in 3 seconds ...", i);
		//_sleep(3000);

		avePI += player();
	}
	avePI /= MAXPLAYER;

	printf("\n\n\tThe Average calculated PI is : %f\n", avePI);
}

float player()
{
	double pi, x, y, dart = DART, score = 0;
	//int dart = DART, score = 0;

	for (int i = 0; i < dart; i++)
	{
		x = fRand(-1.0, 1.0);
		y = fRand(-1.0, 1.0);
		//printf("\n\t%2i. X: %f ,\t Y: %f", i, x, y);

		if (((x*x) + (y*y)) <= 1.0)
			score++;
	}

	pi = 4.0 * (score / dart);

	printf("\n\n\t#### Pi Number for this player is: %f\n", pi);
	printf("*******************************************************************\n");
	return pi;
}

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}