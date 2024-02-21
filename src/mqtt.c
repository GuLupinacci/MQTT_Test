#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include <unistd.h>
#include "../include/mqtt.h"
#include <json-c/json.h>

#define MQTT_SERVER "localhost"
#define CLIENT_ID   "ExampleClientSub"
#define TOPIC       "/test/trimble"
#define QOS         0
#define TIMEOUT     10000L

int main() {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    MQTTClient_create(&client, MQTT_SERVER, CLIENT_ID, MQTTCLIENT_PERSISTENCE_DEFAULT, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to MQTT server, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to subscribe to topic %s, return code %d\n", TOPIC, rc);
        MQTTClient_disconnect(client, 0);
        MQTTClient_destroy(&client);
        exit(EXIT_FAILURE);
    }

    printf("Subscribed to topic %s\n", TOPIC);
    int subscribed = 1;
    MQTTClient_message *message = NULL;
    while (subscribed) {
        
        char *topicName = NULL, *ptr;
        int topicLen;
        sleep(2);
        rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 10000);
        if (rc != MQTTCLIENT_SUCCESS && rc != MQTTCLIENT_TOPICNAME_TRUNCATED)
        {
            subscribed = 0;
        }
        else if (message)
        {
            ptr = (char *) message->payload;
            *(ptr + message->payloadlen) = 0;
            printf("%s\n", message->payload);
            MQTTClient_freeMessage(&message);
            MQTTClient_free(topicName);
        }
    // Keep the program running to receive messages
    }

    MQTTClient_disconnect(client, 0);
    MQTTClient_destroy(&client);

    return EXIT_SUCCESS;
}
