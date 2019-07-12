#include "types.h"
#include "stat.h"
#include "user.h"

char p[50000];

void test_IO(void)
{
	int i,j;
	for(j=0;j<10000;j++){
	for(i=0;i<50000;i++){
		*(p+i)=i&0x0f;
	}
	for(i=0;i<49000;i++){
		*(p+i+1000)=(*(p+i))&0x0f;
	}
	for(i=0;i<=50000;i++){
	        *(p+i)=i&0x0f;
	}
	}
}

int main(void)
{
	test_IO();
	printf(1, "pid = %d \nI/Otest usetime(timeslices)=%d\n", getpid(), gprt());
	exit();
}
