#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DART 1000000000
#define MAXPLAYER 8

int player(int);
long double fRand(long double, long double);
void main()
{
	long double pi;
	long const double realPi = 3.141592653589;
	int score = 0, playersNum = MAXPLAYER, playersDarts;

	playersDarts = DART / playersNum;

	clock_t beginParallel = clock();
#pragma omp parallel for
	for (int i = 1; i <= playersNum; i++)
		score += player(playersDarts);
	clock_t endParallel = clock();
	pi = 4.0 * ((long double)score / (long double)DART);
	double time_spent_parallel = (double)(endParallel - beginParallel) / CLOCKS_PER_SEC;
	printf("%i\n%i", score, DART);
	printf("\n\t Calculated pi : %.12Lf\n", pi);
	printf(	 "\t       Real pi : %.12Lf\n", realPi);
	printf("\n\t Parallel Execution Time: %f\n", time_spent_parallel);

	clock_t beginSerial = clock();
	pi = 4.0 * ((long double) player(DART) / (long double)DART);
	clock_t endSerial = clock();
	double time_spent_serial = (double)(endSerial - beginSerial) / CLOCKS_PER_SEC;
	printf("\n\t Calculated pi : %.12Lf\n", pi);
	printf(	 "\t       Real pi : %.12Lf\n", realPi);
	printf("\n\t Serial Execution Time: %f\n", time_spent_serial);
}

int player(int playersDarts)
{
	srand(time(NULL));
	long double pi, x, y;
	int score = 0;

	for (int i = 0; i < playersDarts; i++)
	{
		x = fRand(-1.0, 1.0);
		y = fRand(-1.0, 1.0);

		if (x*x + y*y < 1.0)
			score++;
	}
	return score;
}

long double fRand(long double fMin, long double fMax)
{
	long double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}