#ifndef COLLECTOR_H
#define COLLECTOR_H
#pragma once

#include <cstring>

namespace deliver {
namespace collector {

class Collector {
private:

public:
    Collector();
    Collector(std::string description_string);
    ~Collector();
};

};
};

#endif