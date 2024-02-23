#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "../../include/mqtt.h"
#include <MQTTClient.h>

int running = 1;
int seconds_running = 0;


int main() {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, MQTT_SERVER, CLIENT_ID_PUB,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;


    while (running) {
        if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
            fprintf(stderr, "Failed to connect, return code %d\n", rc);
            sleep(1);
            continue;
        }

        char payload[10];
        sleep(10);
        seconds_running += 10;
        snprintf(payload, sizeof(payload), "%d", seconds_running);
        pubmsg.payload = payload;
        pubmsg.payloadlen = strlen(payload);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("Publishing: %s\n", payload);
        rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        
        MQTTClient_disconnect(client, 10000);
    }

    MQTTClient_destroy(&client);
    return rc;
}
