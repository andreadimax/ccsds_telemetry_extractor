#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <unistd.h>
//#include "serial_init.c"

#define PI 3.1415


int i=0;

void *function1(void *ptr);
void *function2(void *ptr);

int main(){
	pthread_t thread1, thread2;
	char *msg1 = "t1";
	char *msg2 = "t2";
	int iret1, iret2;

	iret1 = pthread_create(&thread1, NULL, function1, (void *)msg1);
	//iret2 = pthread_create(&thread2, NULL, function, (void *)msg2);
	while(i<100){
		printf("%d\n",i);
		sleep(1);
	}
	pthread_join(thread1,NULL);
	//pthread_join(thread2,NULL);

	return 0;
}

void *function1(void *ptr){
	while(1)
	{
		i++;
		sleep(1);
	}
}

