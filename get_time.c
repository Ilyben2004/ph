#include "philo.h"

void print_passed_time_in_ms(struct timeval start_time , char * operation , int id)
{
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    long total_milliseconds = (seconds * 1000) + (microseconds / 1000);

    printf("%s from philo[%d] lwe9t : %ld ms\n", operation ,id,total_milliseconds);
}

long get_time_between_2_times (struct  timeval start_time)
{
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    long total_milliseconds = (seconds * 1000) + (microseconds / 1000);
    return (total_milliseconds);
    
}