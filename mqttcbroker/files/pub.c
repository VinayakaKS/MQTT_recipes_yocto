
#include <stdio.h>
#include <mosquitto.h>
#include<stdlib.h>
#include <time.h>
#include<stdint.h>

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int main(){
	int rc, loop, num;
	struct mosquitto * mosq;
    time_t t1;
    char topics[4][50]= {"SM/temperature", "SM/disk_usage", "SM/humidity"};

	mosquitto_lib_init();
	mosq = mosquitto_new("publisher-test", true, NULL);

	rc = mosquitto_connect(mosq, "localhost", 1883, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}
	printf("We are now connected to the broker!\n");

	// Logic
	while(1){
		srand ( (unsigned) time (&t1));
		for(loop=0; loop<=2; loop++)
		{
       		num = (rand() % 100+1);
			int length = snprintf( NULL, 0, "%d", num );
			char* str = malloc( length + 1 );
			snprintf( str, length + 1, "%d", num);
			mosquitto_publish(mosq, NULL, topics[loop], 6, str, 0, false);	
			printf("%s: %s\n",topics[loop], str);
			delay(3000);  
		}
	}


	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}


