#include "bench_atomics.hpp"
#include <cstdlib>

void benchmark_atomics::count_circle( thread_control_block & tcb )
{
__sync_fetch_and_add( tcb.in_circle, 1 );
}

void benchmark_atomics::count_square( thread_control_block & tcb )
{
__sync_fetch_and_add( tcb.in_square, 1 );
}

void benchmark_atomics::finish( void )
{
total_pts_in_circle = in_circle;
total_pts_in_square = in_square;
}
