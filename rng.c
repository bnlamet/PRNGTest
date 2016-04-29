#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*TODO: 
2. A mode that calculate time spent to run 100, 1000, 10000.... in one single run
3. A mode that calcutate the average time spent to generate x time of y amount random number
4. A mode that does samething as 2 but calculate in x run and calculate average time
*/

clock_t getRnGenTime(long long RNamount);

// usage: ./rng [argument]
//	argument must be postive number
//	right now this function calculate time spent to generate [argument] random number.
int main(int argc, char *argv[])
{

	long long amount;
	double time;

	if(argc != 2)
	{
		printf("Please enter only one number as argument.\n");
		exit(1);
	}
	if(( amount = atoll(argv[1]) )== 0 && amount <= 0)
	{
		printf("Please enter a postive number as argument.\n");
		exit(1);
	}

	time = (double)(getRnGenTime(amount));
	printf("Time spent to generate %lld random number: %f clock tick(s)\n", amount, time);
	
	return 0;
}

// this function calculate time spent to generate RNamount of random number
clock_t getRnGenTime (long long RNamount)
{
	clock_t start, end;
	int i;

	srand(0);
	start = clock();
	for(i = 0; i < RNamount; i++)
	{
		//printf( rand() % 100);
		rand();
	}
	end = clock();

	return (end - start); 
}
