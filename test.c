#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%d\n", tv.tv_usec);
	return (0);
}