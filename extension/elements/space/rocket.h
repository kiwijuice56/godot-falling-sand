#ifndef ROCKET_H
#define ROCKET_H

#include "../element.h"

class Rocket: public Element {
public:
    const double HORIZONTAL = 1.0 / 4;
    const double TRAIL = 1.0 / 16;
    const double EXPLODE = 1.0 / 2;
    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < TRAIL) {
            sim->grow(row + 1, col, 0, 69);
        }


        if (row == 0) {
            sim->set_cell(row, col, 0);
            return;
        }
        // Very long winded way of not allowing meteors to explode when touching meteor products
        if (sim->randf() < EXPLODE && (
        !sim->in_bounds(row - 1, col) 
        || sim->get_cell(row - 1, col) != 69 && sim->get_cell(row - 1, col) != 157 
        && sim->get_cell(row - 1, col) != 0 && sim->get_cell(row - 1, col) != 9 
        && sim->get_cell(row - 1, col) != 6 && sim->get_cell(row - 1, col) != 5 && sim->get_cell(row - 1, col) != 66
        && sim->get_cell(row - 1, col) != 67 && sim->get_cell(row - 1, col) != 68)) {
            for (int y = -9; y <= 9; y++) { 
                for (int x = -9; x <= 9; x++) {
                    if (sim->in_bounds(row + y, col + x) && x * x + y * y < 81.0) {
                        sim->set_cell(row + y, col + x, sim->randf() < EXPLODE ? 66 : 9);
                    }
                }
            }
            return;
        }

        if (sim->randf() < HORIZONTAL) {
            if (sim->randf() < 0.5)
            sim->move_and_swap(row, col, row - 1, col - 1);
            else 
             sim->move_and_swap(row, col, row - 1, col + 1);
        } else {
            sim->move_and_swap(row, col, row - 1, col);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.85;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

#endif // ROCKET_H