#ifndef HYDROGEN_EXPLOSION_H
#define HYDROGEN_EXPLOSION_H

#include "element.h"

class HydrogenExplosion: public Element {
public:
    const double PROCESS = 1.0 / 4;
    const double DECAY = 1.0 / 3.0;

    void process(SandSimulation *sim, int row, int col) override {
        // Adding a limit slows the explosion down
        if (sim->randf() > PROCESS) {
            return;
        // We eliminate explosions that reach the end, as they tend to linger for a long time if not checked
        } else if (sim->randf() < DECAY || sim->touch_count(row, col, 6) > 1 ||
            row == sim->get_height() - 1 || col == sim->get_width() - 1 || col == 0 || row == 0) {
            sim->set_cell(row, col, 6);
        } else {
            sim->grow(row + 1, col, -1, 48);
            sim->grow(row - 1, col, -1, 48);
            sim->grow(row, col + 1, -1, 48);
            sim->grow(row, col - 1, -1, 48);
            sim->grow(row - 2, col, -1, 48);
            sim->grow(row + 2, col, -1, 48);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.0;
    }

    double get_acid_resistance() override {
        return 0.0;
    }
};

#endif // HYDROGEN_EXPLOSION_H