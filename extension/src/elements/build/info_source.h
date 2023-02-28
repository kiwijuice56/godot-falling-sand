#ifndef INFO_SOURCE_H
#define INFO_SOURCE_H

class SandSimulation;

#include "../element.h"

class InfoSource: public Element {
public:

    void process(SandSimulation *sim, int row, int col) override {

    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.99;
    }
};

#endif // INFO_SOURCE_H