#include "bench.hpp"
#include <cstdlib>

float benchmark::result( void )
{
return 4.0 * (double)total_pts_in_circle / ( (double)total_pts_in_square + (double)total_pts_in_circle );
}

static __inline bool pt_in_circle( uint16_t x, uint16_t y )
{
return ( (uint32_t)x*(uint32_t)x + (uint32_t)y*(uint32_t)y ) < ( 0xFFF * 0xFFF );
}

void * benchmark::threadrunner( void * vptr )
{
thread_control_block & tcb = *(benchmark::thread_control_block*)vptr;
benchmark * b = tcb.bptr;

for( size_t i = 0; i < tcb.num_points; ++i )
    {
    uint16_t x = rand_r(&tcb.rand_seed) & 0xFFF;
    uint16_t y = rand_r(&tcb.rand_seed) & 0xFFF;
    if( pt_in_circle( x, y ) )
		b->count_circle( tcb );
	else
		b->count_square( tcb );
    }

return NULL;
}

void benchmark::run( size_t num_points, size_t num_threads )
{
int approx_points_per_thread;
thread_control_block * tcbs;

prepare( num_threads );

tcbs = new thread_control_block[num_threads];
approx_points_per_thread = num_points / num_threads;
for( size_t i = 0; i < num_threads; ++i )
    {
    tcbs[i].num_points=approx_points_per_thread;
    num_points -= approx_points_per_thread;

    tcbs[i].rand_seed = i;

	tcbs[i].bptr = this;
	prepare_thread( i, tcbs[i] );
    }
while( num_points > 0 )
    {
    tcbs[ num_points % num_threads ].num_points ++;
    num_points--;
    }

for( size_t i = 0; i < num_threads; ++i )
    {
    pthread_create( &tcbs[i].id, NULL, threadrunner, &tcbs[i] );
    }

for( size_t i = 0; i < num_threads; ++i )
    {
    pthread_join( tcbs[i].id, NULL );
	finish_thread( tcbs[i] );
    }

delete[]( tcbs );

finish();
}
