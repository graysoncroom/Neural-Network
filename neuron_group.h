//
// Created by Grayson Croom on 2020-02-24.
//

#ifndef NEURAL_NETWORK_NEURON_GROUP_H
#define NEURAL_NETWORK_NEURON_GROUP_H

class neuron_group {
public:
    neuron_group(int, int *);
    ~neuron_group();
private:
    int layer_count;
    int * layer_sizes;

    // Will be represented as the transpose of traditional network orientation (i.e. a layer lies on a row)
    double ** group;
};


#endif //NEURAL_NETWORK_NEURON_GROUP_H
