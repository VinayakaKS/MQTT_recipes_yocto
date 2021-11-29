#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mosquitto.h>

#define LEDON"\
#/bin/bash \n \
python3 /usr/bin/LED.py ON \n \
"
#define LEDOFF"\
#/bin/bash \n \
python3 /usr/bin/LED.py OFF \n \
"

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("ID: %d\n", * (int *) obj);
	if(rc) {
		printf("Error with result code: %d\n", rc);
		exit(-1);
	}
//LED is the topic
	mosquitto_subscribe(mosq, NULL, "LED", 0);
}


void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {

	char* message;
	message = (char*)msg->payload;
//LED switching logic based on message
	printf("LED switching: %s\n", message);
	if(strcmp("on", message) == 0){
		system(LEDON);
	}

	if(strcmp("off", message) == 0){
		system(LEDOFF);
	}

}

int main() {
	int rc, id=404;
	char ipv4[50];
    	printf("Provide the IP address(ipv4) of the client: ");
    	scanf("%[^\n]%*c", ipv4);
	printf("Address is %s\n",ipv4);

	mosquitto_lib_init();

	struct mosquitto *mosq;

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
