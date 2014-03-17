#include <stdio.h>
#include <sched.h>
#include <stdint.h>

#include <uv.h>

#include "light_lock.h"

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}


int main(int argc, char *argv[])
{
	light_lock_t lock = LIGHT_LOCK_INIT;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	long long ms;
	ms = timeInMilliseconds();

  register int i = 500000000;
  long long num = 0;

	while(i--)
	{
		light_lock(&lock);
		num++;
		light_unlock(&lock);
	}

	ms = timeInMilliseconds() - ms;
	if(ms > 0)
		printf("light_lock/unlock: %lld ops/sec\n", (sayi * 1000)/ms);


	// PTHREAD
	ms = timeInMilliseconds();

	i = 500000000;
	num = 0;

	while(i--)
	{
		pthread_mutex_lock(&mutex);
		num++;
		pthread_mutex_unlock(&mutex);
	}

	ms = timeInMilliseconds() - ms;
	if(ms > 0)
		printf("pthread_mutex_lock/unlock: %lld ops/sec\n", (num * 1000)/ms);

	return 0;
}
