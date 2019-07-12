#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[2048];
void test_file(void)
{
	int fd, i, total, cc;
	fd = open("testfile", O_CREATE | O_RDWR);
	if(fd < 0){
    		printf(1, "cannot create testfile\n");
    		exit();
  	}
	for(i=0;i<64;i++){
		memset(buf,i,1000);
		//printf(1,"%d\n",i);
		if(write(fd,buf,1000)!=1000){
			printf(1,"write to file failed!\n");
			exit();
		}
	}
	close(fd);
 	fd = open("testfile", O_RDONLY);
	if(fd < 0){
    		printf(1, "cannot open testfile\n");
    		exit();
  	}
	total = 0;
  	for(i = 0; ; i++){
    		cc = read(fd, buf, 1000);
    		if(cc < 0){
      			printf(1, "read testfile failed\n");
      			exit();
    		}
    		if(cc == 0)
      			break;
    		if(cc != 1000){
      			printf(1, "short read testfile\n");
      			exit();
    		}
    		if(buf[0] != i || buf[999] != i){
      			printf(1, "read testfile wrong data\n");
      			exit();
    		}
    		total += cc;
  	}
	close(fd);
	if(total != 1000*64){
		printf(1, "read testfile wrong data\n");
      		exit();
	}
	unlink("testfile");
	printf(1, "test file ok\n");
}


int main()
{

	test_file();
	exit();

}
