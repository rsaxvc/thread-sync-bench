#include "bench.hpp"
#include "xorshift.h"

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
uint32_t r = xorshift_init;

for( size_t i = 0; i < tcb.num_points; ++i )
	{
	r = xorshift( r );
	uint16_t x = r & 0xFFF;

	r = xorshift( r );
	uint16_t y = r & 0xFFF;

	if( pt_in_circle( x, y ) )
		b->count_circle( tcb );
	else
		b->count_square( tcb );
	}

return NULL;
}

int benchmark::run( size_t num_points, size_t num_threads )
{
int approx_points_per_thread;
thread_control_block * tcbs;
size_t num_points_remaining;

prepare( num_threads );

tcbs = new thread_control_block[num_threads];
approx_points_per_thread = num_points / num_threads;
num_points_remaining = num_points;
for( size_t i = 0; i < num_threads; ++i )
	{
	tcbs[i].num_points = approx_points_per_thread;
	num_points_remaining -= approx_points_per_thread;

	tcbs[i].rand_seed = i;

	tcbs[i].bptr = this;
	prepare_thread( i, tcbs[i] );
    }
while( num_points_remaining > 0 )
	{
	tcbs[ num_points % num_threads ].num_points ++;
	num_points_remaining--;
	}

for( size_t i = 0; i < num_threads; ++i )
	{
	int errnum = pthread_create( &tcbs[i].id, NULL, threadrunner, &tcbs[i] );
	if( errnum )
		{
		errstr = "unable to create thread";
		return -2;
		}
	}

for( size_t i = 0; i < num_threads; ++i )
	{
	pthread_join( tcbs[i].id, NULL );
	finish_thread( tcbs[i] );
	}

delete[]( tcbs );

finish();

if( total_pts_in_circle + total_pts_in_square != num_points )
	{
	errstr = "accumulator mismatch - number of result points not equal to number of test points";
	return -1;
	}

return 0;
}
