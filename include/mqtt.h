#include <MQTTClient.h>
#define MQTT_SERVER     "localhost"
#define CLIENT_ID       "ExampleClientSub"
#define CLIENT_ID_PUB   "ExampleClientPub"
#define TOPIC           "/test/trimble"
#define QOS             0
#define TIMEOUT         10000L

int init_mqtt();
int start_mqtt_subscriber();
