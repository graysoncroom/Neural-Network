//
// Created by Grayson Croom on 2020-02-24.
//

#include "neuron_group.h"

neuron_group::neuron_group(int layer_count, int * layer_sizes) : layer_count(layer_count), layer_sizes(layer_sizes) {
    this->group = new double * [this->layer_count];
    for (auto i = 0; i < this->layer_count; i++) {
        this->group[i] = new double[this->layer_sizes[i]]();
    }
}

neuron_group::~neuron_group() {
    for (auto i = 0; i < this->layer_count; i++) {
        delete this->group[i];
    }
    delete this->group;
}