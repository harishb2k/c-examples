//
// Created by Harish Bohara on 16/09/19.
//

#ifndef SUB_DIR_EXAMPLE_PERSON_H
#define SUB_DIR_EXAMPLE_PERSON_H


#include <stdio.h>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


namespace ns {
    struct person {
        std::string name;
        std::string address;
        int age;
    };

    void to_json(json &j, const person &p);
    void from_json(const json &j, person &p);
}

#endif //SUB_DIR_EXAMPLE_PERSON_H
