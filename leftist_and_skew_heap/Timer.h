#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

class Timer {
private:

	timeval startTime;

public:

	void start(){
		gettimeofday(&startTime, NULL);
	}

	// Returns time in seconds
	double stop(){
		timeval endTime;
		long seconds, nseconds;
		double duration;

		gettimeofday(&endTime, NULL);

		seconds  = endTime.tv_sec  - startTime.tv_sec;
		nseconds = endTime.tv_usec - startTime.tv_usec;

		duration = seconds + nseconds/1000000.0;

		return duration;
	}
	
	// Prints time in seconds
	static void printTime(double duration){
		printf("%5.3f seconds\n", duration);
	}
};

#endif /* TIMER_H_ */
