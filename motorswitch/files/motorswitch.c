#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#define MOTORON "\
#/bin/bash \n \
python3 motor.py ON \n \
"
#define MOTOROFF "\
#/bin/bash \n \
python3 motor.py OFF \n \
"


void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("ID: %d\n", * (int *) obj);
	if(rc) {
		printf("Error with result code: %d\n", rc);
		exit(-1);
	}
	mosquitto_subscribe(mosq, NULL, "motor", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	
	int message=0;
	message=atoi(msg->payload);
	char* arr;
	arr = (char*)msg->payload;
	
	printf("Motor switching: %s\n", arr);
	if(strcmp("on", arr) == 0){
		system(MOTORON);
	}

	if(strcmp("off", arr) == 0){
		system(MOTORON);
	}

}

int main() {
	int rc, id=12;
	char ipv4[50];
    	printf("Provide the IP address(ipv4) of the client: ");
    	scanf("%[^\n]%*c", ipv4);
	printf("Address is %s",ipv4);
	struct mosquitto *mosq;

	mosquitto_lib_init();
	mosq = mosquitto_new("subscribe-test", true, &id);
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);
	
	rc = mosquitto_connect(mosq, ipv4, 1883, 10);
	if(rc) {
		printf("Could not connect to Broker with return code %d\n", rc);
		return -1;
	}

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	return 0;
}
