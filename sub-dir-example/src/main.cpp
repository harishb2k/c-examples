//
// Created by Harish Bohara on 16/09/19.
//

#include "main.h"
#include <iostream>
#include <helper/helper.h>
#include <cppkafka/cppkafka.h>

using namespace std;
using namespace cppkafka;

int main() {
    cout << "Sub Dir Example " << endl;


    Helper helper;
    helper.printHelp();


    // Create the config
    Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" }
    };

    // Create the producer
    Producer producer(config);

    // Produce a message!
    string message = "hey there!";
    producer.produce(MessageBuilder("my_topic").partition(0).payload(message));
    producer.flush();

    return 0;
}