#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*TODO: 
2. A mode that calculate time spent to run 100, 1000, 10000.... in one single run
3. A mode that calcutate the average time spent to generate x time of y amount random number
4. A mode that does samething as 2 but calculate in x run and calculate average time
*/
clock_t getRnGenTime(long long RNamount);
void genTableTime();
void genTableAveTime(long long timeToGen);
void genSingleAveTime();
void printHelp();

// usage: ./rng [argument]
//	argument must be postive number
//	right now this function calculate time spent to generate [argument] random number.
int main(int argc, char *argv[])
{

	long long amount;
	long long timeToGen;	
	double time;
	
	

	if(argc < 2 || argc > 4)
	{
		printHelp();
		exit(1);
	}
	
	if(( amount = atoll(argv[1]) ) <= 0)
	{
		if (argc == 2 && strcmp("t",argv[1])== 0 ) 
			genTableTime();
		else if (argc == 3 && strcmp("ta",argv[1]) == 0 && ( timeToGen = atoll(argv[2]) ) > 0)
			genTableAveTime(timeToGen);
		else if (argc == 3 && strcmp("a",argv[1]) && (amount = atoll(argv[2])) > 0 && (timeToGen = atoll(argv[3]			)) > 0)
			genSingleAveTime();
		else
		{
			printHelp();
			exit(1);
		}
	}
	else if(argc == 2)
	{
		time = (double)(getRnGenTime(amount));
		printf("\nTime spent to generate %lld random number: %f clock tick(s)\n", amount, time);
	}
	return 0;
}

void genTableTime()
{
	long long amount[] = {1000,10000,100000,1000000};
	double time[4];
	int i;

	for(i = 0; i < 4; i++)
	{
		time[i] = (double)(getRnGenTime(amount[i]));
		printf("%lld number:\t%f\tclock ticks\n",amount[i],time[i]);
	}
}

void genTableAveTime(long long timeToGen)
{
	double avetime[4];
	long long amount[] = {1000,10000,100000,1000000};
	long long i;
	long long k;
	
	printf("Average clock ticks when generate %lld time:\n",timeToGen);
	for(k = 0; k < 4 ;k++)
	{
		for(i = 0; i < timeToGen; i++)
			avetime[k] = avetime[k] + (double)(getRnGenTime(amount[k]));

		avetime[k] = avetime[k] / (double)(timeToGen);
		printf("%lld number:\t%f\t clock ticks\n",amount[k],avetime[k]);
	}
}

void genSingleAveTime()
{}

// this function calculate time spent to generate RNamount of random number
clock_t getRnGenTime (long long RNamount)
{
	clock_t start, end;
	long long i;

	seedMT(0);
	start = clock();
	for(i = 0; i < RNamount; i++)
	{
//		printf("\t%lu%s", (unsigned long) randomMT()%100, (i%7)==6 ? "\n" : "");
		randomMT();
	}
	end = clock();

	return (end - start); 
}

void printHelp()
{
        printf ("\n\
Usage:\n\
	Enter [postive number x]:\n\
	get the generation time of x random number.\n\
	\n\
	Enter 't':\n\
	get a table of generation time of fix number\n\
	\n\
	Enter 'ta' [postive number y]:\n\
	to get a table of average generation time of fix numbers ran y time\n\
	\n\
	Enter 'a' [postive number x] [postive number y]:\n\
	to get the average generation time of x number ran y time\n\
");

}
