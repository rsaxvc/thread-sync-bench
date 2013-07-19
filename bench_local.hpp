#ifndef BENCH_LOCAL_HPP
#define BENCH_LOCAL_HPP

#include "bench.hpp"

class benchmark_local:public benchmark
	{
	virtual void prepare( size_t num_threads );
	virtual void prepare_thread( size_t thread_num, thread_control_block & );
	virtual void count_circle( thread_control_block & );
	virtual void count_square( thread_control_block &);
	virtual void finish_thread( thread_control_block & );
	virtual void finish(void);
	};

#endif
