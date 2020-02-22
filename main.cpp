#include <iostream>
#include <cmath>
#include "Config.h"
#include "mnist_reader.h"

int main(int argc, char ** argv) {
    mnist_reader reader("../train-labels.idx1-ubyte.dat", "../train-images-idx3-ubyte.dat");

    unsigned char * label_dataset = reader.get_labels();
    unsigned char ** image_dataset = reader.get_images();

    for (int i = 0, size = reader.get_image_size(); i < size; i++) {
        std::cout << static_cast<int>(image_dataset[0][i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}