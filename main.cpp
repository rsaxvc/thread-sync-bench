#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>

#include "bench_atomics.hpp"
#include "bench_mutex.hpp"
#include "bench_local.hpp"
#include "bench_shared.hpp"


#include <time.h>
static double my_time( void )
{
struct timespec tp;
if( 0 == clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp) )
	{
	return tp.tv_sec + (double)tp.tv_nsec / 1000000000.0;
	}
else
	{
	std::cerr<<"Error reading current time"<<std::endl;
	return 0;
	}
}

int main( int numArgs, const char * args[] )
{
size_t count;
size_t nthreads;

benchmark * b;

if( numArgs != 4 )
	{
	std::cerr<<"Usage: "<<args[0]<<" mode numPoints numThreads"<<std::endl;
	std::cerr<<"Modes: atomics mutex local shared"<<std::endl;
	exit(2);
	}

if(0){}
else if( 0 == strcmp( args[1], "atomics" ) )
	{
	b = new benchmark_atomics;
	}
else if( 0 == strcmp( args[1], "mutex" ) )
	{
	b = new benchmark_mutex;
	}
else if( 0 == strcmp( args[1], "local" ) )
	{
	b = new benchmark_local;
	}
else if( 0 == strcmp( args[1], "shared" ) )
	{
	b = new benchmark_shared;
	}
else
	{
	std::cerr<<"unknown mode"<<std::endl;
	exit(3);
	}

count = atoi(args[2]);
nthreads = atoi(args[3]);

std::cerr<<"Approximating the value of PI using "<<count<<" pseudorandomly placed points and "<<nthreads<<" threads"<<std::endl;

double time_start = my_time();
if( b->run( count, nthreads ) >= 0 )
	{
	}
else
	{
	std::cerr << "Error:" << b->errstring() <<std::endl;
	}
double time_end = my_time();

std::cout<<(time_end-time_start);
std::cerr<<"pi approx:"<< b->result() <<std::endl;
delete b;

//std::cerr<<"in circle:"<<in_circle<<" points"<<std::endl;
//std::cerr<<"in square:"<<in_square<<" points"<<std::endl;
}
