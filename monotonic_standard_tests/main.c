/*
Code written by: Joanna Hsiao, Leila Hsiao, Ian McMahon, Briana Lamet, Abraham Arce
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

//if OSX
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void get_monotonic(struct timespec *my_spec){
    //if OSX
    #ifdef __MACH__
        clock_serv_t cclock;
        mach_timespec_t my_mach;
        host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
        clock_get_time(cclock, &my_mach);
        mach_port_deallocate(mach_task_self(), cclock);
        my_spec->tv_sec = my_mach.tv_sec;
        my_spec->tv_nsec = my_mach.tv_nsec;
    //windows, linux
    #else
        clock_gettime(CLOCK_MONOTONIC, my_spec);
    #endif
}

double get_time_passed(struct timespec *start, struct timespec *end){
  double passed_seconds=end->tv_sec-start->tv_sec;
  double passed_nanos=end->tv_nsec-start->tv_nsec;
  return(passed_seconds+(passed_nanos*(1e-9)));
}

long gen_values(long reps, int algorithm)
{
	struct timespec start;
	struct timespec end;
	long counter;
    get_monotonic(&start);
    if(algorithm==0){
        for(counter=0; counter<reps; counter++){
            xor32();
        }
    }
    else{
        for(counter=0; counter<reps; counter++){
            randomMT();
        }
    }
    get_monotonic(&end);
	return(get_time_passed(&start, &end));
}

void run_standard_tests(){
	long long avetime[]={0,0,0,0};
	int number_of_reps[]={1000,10000,100000,1000000};
    int number_of_trials=4;
    int number_of_sets=100;
    int algorithm;
    int number_of_algorithms=2;
	int counter;
	int current_trial;
    for(algorithm=0; algorithm<number_of_algorithms; algorithm++){
        if(algorithm==0){
            printf("\nUsing Xorshift:");
        }
        else{
            printf("\nUsing Mersenne Twister:");
        }
        printf("\nAverage time in seconds when generating %d repetitions:\n",number_of_sets);
        for(current_trial=0; current_trial<number_of_trials ;current_trial++){
            for(counter=0; counter<number_of_sets; counter++)
                avetime[current_trial]+=(long long)(gen_values(number_of_reps[current_trial],algorithm));
            avetime[current_trial]=avetime[current_trial]/(long long)(number_of_sets);
            printf("%d numbers take an average of:\t%lld\t seconds\n",number_of_reps[current_trial],avetime[current_trial]);
        }
    }
}

int main(){
    run_standard_tests();
    return(0);
}