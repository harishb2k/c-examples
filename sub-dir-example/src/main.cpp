//
// Created by Harish Bohara on 16/09/19.
//

#include "main.h"
#include <iostream>
#include <helper/helper.h>
#include <cppkafka/cppkafka.h>
#include "rocksdb/db.h"
#include <assert.h>
#include <nlohmann/json.hpp>
#include "person.h"

// for convenience
using json = nlohmann::json;
using namespace std;
using namespace cppkafka;
using namespace rocksdb;
using namespace ns;

std::string kDBPath = "/tmp/rocksdb_simple_example";

void main_rocks();

int main() {
    cout << "Sub Dir Example " << endl;


    Helper helper;
    helper.printHelp();


    // Create the config
    Configuration config = {
            {"metadata.broker.list", "127.0.0.1:9092"}
    };

    // Create the producer
    Producer producer(config);

    // Produce a message!
    string message = "hey there!";
    for (int i = 0; i < 1; i++) {
        // producer.produce(MessageBuilder("my_topic").partition(0).payload(message));

        std::string text = "Hi";
        text += std::to_string(i);
        producer.produce(MessageBuilder("my_topic").payload(text));
        producer.flush();
    }


    main_rocks();

    return 0;
}


void main_rocks() {
    rocksdb::DB *db;
    Status status;

    rocksdb::Options options;
    options.create_if_missing = true;

    status = DB::Open(options, kDBPath, &db);
    assert(status.ok());

    status = db->Put(WriteOptions(), Slice("key"), Slice("value-1"));
    assert(status.ok());

    std::string value;
    status = db->Get(ReadOptions(), Slice("key"), &value);
    cout << value << endl;

    ns::person p{"Ned Flanders", "744 Evergreen Terrace", 60};
    json jr = p;
    std::cout << jr << std::endl;


    status = db->Put(WriteOptions(), Slice(p.name), Slice(jr.dump()));
    assert(status.ok());
    status = db->Get(ReadOptions(), Slice(p.name), &value);
    cout << value << endl;


    delete db;
}