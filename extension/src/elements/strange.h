#ifndef STRANGE_H
#define STRANGE_H

#include "element.h"

class Strange: public Element {
public:
    const double PROCESS = 1.0 / 2.5;
    const double DECAY = 1.0 / 24;

    void process(SandSimulation *sim, int row, int col) override {
        // Adding a limit slows the explosion down
        if (sim->randf() > PROCESS) {
            return;
        }

        if (sim->touch_count(row, col, 74) + sim->touch_count(row, col, 0) >= 3 && sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
        } else {
            if (sim->in_bounds(row + 1, col) && sim->get_cell(row + 1, col) != 0) 
                sim->grow(row + 1, col, -1, 74);
            if (sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) != 0) 
                sim->grow(row - 1, col, -1, 74);
            if (sim->in_bounds(row, col + 1) && sim->get_cell(row, col + 1) != 0) 
                sim->grow(row, col + 1, -1, 74);
            if (sim->in_bounds(row, col - 1) && sim->get_cell(row, col - 1) != 0) 
                sim->grow(row, col - 1, -1, 74);
        }
    }

    double get_density() override {
        return 128.0;
    }

    double get_explode_resistance() override {
        return 1.0;
    }

    double get_acid_resistance() override {
        return 1.0;
    }
};

#endif // STRANGE_H