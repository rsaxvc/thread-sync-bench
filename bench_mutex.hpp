#ifndef BENCH_MUTEX_HPP
#define BENCH_MUTEX_HPP

#include "bench.hpp"
class benchmark_mutex:public benchmark
    {
	pthread_mutex_t circle_lock;
	pthread_mutex_t square_lock;

	int in_circle;
	int in_square;

    virtual void prepare( size_t num_threads );
	virtual void prepare_thread( size_t thread_num, thread_control_block & tcb )
		{
		tcb.in_circle = &in_circle;
		tcb.in_square = &in_square;
		};
	virtual void count_circle( thread_control_block & );
	virtual void count_square( thread_control_block & );
	virtual void finish_thread( thread_control_block & ){};
    virtual void finish( void );
    };

#endif
