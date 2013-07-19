#include "bench_local.hpp"
#include <cstdlib>

void benchmark_local::prepare( size_t num_threads )
{
total_pts_in_circle = 0;
total_pts_in_square = 0;
}

void benchmark_local::prepare_thread( size_t thread_num, thread_control_block & tcb )
{
tcb.in_circle = new int32_t[2];
tcb.in_square = tcb.in_circle + 1;
*tcb.in_circle = 0;
*tcb.in_square = 0;
}

void benchmark_local::count_circle( thread_control_block & tcb )
{
(*tcb.in_circle)++;
}

void benchmark_local::count_square( thread_control_block & tcb )
{
(*tcb.in_square)++;
}

void benchmark_local::finish_thread( thread_control_block & tcb )
{
total_pts_in_circle += *tcb.in_circle;
total_pts_in_square += *tcb.in_square;
delete[] tcb.in_circle;
}

void benchmark_local::finish( void )
{
}
