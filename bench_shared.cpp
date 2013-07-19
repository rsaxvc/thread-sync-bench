#include "bench_shared.hpp"
#include <cstdlib>

void benchmark_shared::prepare( size_t num_threads )
{
total_pts_in_circle = 0;
total_pts_in_square = 0;
in_circle = new int32_t[ num_threads ];
in_square = new int32_t[ num_threads ];
}

void benchmark_shared::prepare_thread( size_t thread_num, thread_control_block & tcb )
{
tcb.in_circle = &in_circle[thread_num];
in_circle[thread_num] = 0;
tcb.in_square = &in_square[thread_num];
in_square[thread_num] = 0;
}

void benchmark_shared::count_circle( thread_control_block & tcb )
{
(*tcb.in_circle)++;
}

void benchmark_shared::count_square( thread_control_block & tcb )
{
(*tcb.in_square)++;
}

void benchmark_shared::finish_thread( thread_control_block & tcb )
{
total_pts_in_circle += *tcb.in_circle;
total_pts_in_square += *tcb.in_square;
}

void benchmark_shared::finish( void )
{
delete[] in_circle;
delete[] in_square;
}
