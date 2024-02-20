#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include <json-c/json.h>

#define MQTT_SERVER "tcp://mqtt.server.com:1883"
#define CLIENT_ID   "ExampleClientSub"
#define TOPIC       "/test/trimble"
#define QOS         1
#define TIMEOUT     10000L

void messageArrived(MessageData* data) {
    char* message = malloc(data->message->payloadlen + 1);
    memcpy(message, data->message->payload, data->message->payloadlen);
    message[data->message->payloadlen] = '\0';

    struct json_object* root = json_tokener_parse(message);
    if (root != NULL) {
        struct json_object* print;
        if (json_object_object_get_ex(root, "print", &print)) {
            const char* print_str = json_object_get_string(print);
            if (print_str != NULL) {
                printf("Received message: %s\n", print_str);
            }
        }
        json_object_put(root);
    }

    free(message);
}

int start_mqtt_subscriber(int argc, char* argv[]) {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    MQTTClient_create(&client, MQTT_SERVER, CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to MQTT server, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    if ((rc = MQTTClient_subscribe(client, TOPIC, QOS, messageArrived)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to subscribe to topic %s, return code %d\n", TOPIC, rc);
        MQTTClient_disconnect(client, 0);
        MQTTClient_destroy(&client);
        exit(EXIT_FAILURE);
    }

    printf("Subscribed to topic %s\n", TOPIC);

    while (1) {
        // Keep the program running to receive messages
    }

    MQTTClient_disconnect(client, 0);
    MQTTClient_destroy(&client);

    return EXIT_SUCCESS;
}
