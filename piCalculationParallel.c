#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define DART 1000000	// Number of darts each player throws
						// Number of random dots in the square[-1,+1]

#define MAXPLAYER 8		// Maximume number of participant players
						// Number of threads

/**
	Generates random dots on the board

	@param: playerDarts, total number of darts to throw
	@return: score, number of darts thrown in the circle
*/ 
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


/**
	Generates a random number between two params given

	@param: random number scope
	@return: desired random number
*/
long double fRand(long double fMin, long double fMax)
{
	long double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


void main()
{
	long double pi;
	long const double REAL_PI = 3.141592653589;
	int score = 0, playersNum = MAXPLAYER, playersDarts;

////////////////////////////////////////////////////
//	Parallel									  //
////////////////////////////////////////////////////

	// devide the total number of DARTS between players
	playersDarts = DART / playersNum;
	double beginParallel = omp_get_wtime();
#pragma omp parallel for
	for (int i = 1; i <= playersNum; i++)
		score += player(playersDarts);
	double endParallel = omp_get_wtime();
	pi = 4.0 * ((long double)score / (long double)DART);

	double time_spent_parallel = endParallel - beginParallel;

	printf("%i\n%i", score, DART);
	printf("\n\t Calculated pi : %.12Lf\n", pi);
	printf(	 "\t       Real pi : %.12Lf\n", REAL_PI);
	printf("\n\t Parallel Execution Time: %f\n", time_spent_parallel);


	
////////////////////////////////////////////////////
//	Serial										  //
////////////////////////////////////////////////////

	double beginSerial = omp_get_wtime();
	pi = 4.0 * ((long double) player(DART) / (long double)DART);
	double endSerial = omp_get_wtime();
	double time_spent_serial = endSerial - beginSerial;
	printf("\n\t Calculated pi : %.12Lf\n", pi);
	printf(	 "\t       Real pi : %.12Lf\n", REAL_PI);
	printf("\n\t Serial Execution Time: %f\n", time_spent_serial);
}


