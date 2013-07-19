#ifndef BENCH_HPP
#define BENCH_HPP

extern "C"
	{
	#include <stddef.h>
	#include <stdint.h>
	#include <pthread.h>
	}

class benchmark
	{
	private:
		static void * threadrunner( void * vtcb );

	protected:
		struct thread_control_block
			{
			benchmark * bptr;
			size_t num_points;
			unsigned int rand_seed;
			pthread_t id;

			/*Internal thread use*/
			int32_t * in_circle;
			int32_t * in_square;
			};

		//implement these for each syncronization primitive
		virtual void prepare( size_t num_threads )=0;
		virtual void prepare_thread( size_t thread_num, thread_control_block & tcb )=0;
		virtual void count_circle(thread_control_block&)=0;
		virtual void count_square(thread_control_block&)=0;
		virtual void finish_thread(thread_control_block & tcb )=0;
		virtual void finish(void)=0;

		//populate these in 'finish'
		size_t total_pts_in_circle;
		size_t total_pts_in_square;

	public:
		void run( size_t points, size_t threads );
		float result();
		virtual ~benchmark(){};
	};

#endif
