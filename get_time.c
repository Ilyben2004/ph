#include "philo.h"

void print_passed_time_in_ms(struct timeval start_time)
{
    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    long total_milliseconds = (seconds * 1000) + (microseconds / 1000);

    printf("Elapsed time: %ld ms\n", total_milliseconds);
}