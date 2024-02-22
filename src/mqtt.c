#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include <unistd.h>
#include "../include/mqtt.h"
#include "../include/display.h"
#include <ctype.h>
#include <json-c/json.h>

#define MQTT_SERVER "localhost"
#define CLIENT_ID   "ExampleClientSub"
#define TOPIC       "/test/trimble"
#define QOS         0
#define TIMEOUT     10000L

void decode_mqtt_payload(char *payload)
{
    struct json_object *json, *obj ;
    json = json_tokener_parse(payload);

    if (json != NULL) 
    {
        if (json_object_is_type(json, json_type_object)) {
            if (json_object_object_get_ex(json, "print", &obj)) 
            {
                if (json_object_is_type(obj, json_type_string)) 
                {
                    const char *print_str = json_object_get_string(obj);
                    write_on_display(0, (char*) print_str);
                } 
                else 
                    printf("Error: 'print' value is not a string\n");
            } 
            else 
                printf("Error: 'print' key not found\n");
        } 
        else if (isdigit(*payload))
            write_on_display(2, payload);
        else
            printf("Error: Payload is not valid\n");

        json_object_put(json);
    } else 
        printf("Error: Payload is not valid JSON\n");
}

int init_mqtt() 
{
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
            decode_mqtt_payload(message->payload);
            MQTTClient_freeMessage(&message);
            MQTTClient_free(topicName);
        }
    // Keep the program running to receive messages
    }

    MQTTClient_disconnect(client, 0);
    MQTTClient_destroy(&client);

    return EXIT_SUCCESS;
}
