#include <stdio.h>
#include <stdbool.h>

void (*mqtt_connect_ptr)(const char *host, int port);
void (*mqtt_subscribe_ptr)(const char *topic);
void (*mqtt_receive_message_ptr)(char *topic, char *message);

void mqtt_connect(const char *host, int port) 
{
    printf("MQTT connect called with host: %s, port: %d\n", host, port);
}

void mqtt_subscribe(const char *topic) 
{
    printf("MQTT subscribe called with topic: %s\n", topic);
}

void mqtt_receive_message(char *topic, char *message) 
{
    printf("MQTT receive message called with topic: %s, message: %s\n", topic, message);
}

void subscribe_to_topic(const char *topic) 
{
    mqtt_subscribe(topic);
}

void test_subscribe_to_topic(void) 
{
    const char *test_topic = "/test/teste";

    mqtt_connect_ptr = mqtt_connect;
    mqtt_subscribe_ptr = mqtt_subscribe;

    subscribe_to_topic(test_topic);
}

int main(void) 
{
    test_subscribe_to_topic();

    return 0;
}
