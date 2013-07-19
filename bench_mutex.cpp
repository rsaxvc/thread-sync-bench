#include "bench_mutex.hpp"

void benchmark_mutex::prepare( size_t num_threads )
{
in_circle = 0;
in_square = 0;
pthread_mutex_init( &circle_lock, NULL );
pthread_mutex_init( &square_lock, NULL );
}

void benchmark_mutex::count_circle( thread_control_block & tcb )
{
pthread_mutex_lock( &circle_lock );
(*tcb.in_circle)++;
pthread_mutex_unlock( &circle_lock );
}

void benchmark_mutex::count_square( thread_control_block & tcb )
{
pthread_mutex_lock( &square_lock );
(*tcb.in_square)++;
pthread_mutex_unlock( &square_lock );
}

void benchmark_mutex::finish()
{
total_pts_in_circle = in_circle;
total_pts_in_square = in_square;
pthread_mutex_destroy(&circle_lock);
pthread_mutex_destroy(&square_lock);
}
