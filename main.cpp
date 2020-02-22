#include <iostream>
#include <fstream>
#include "Config.h"

int reverseInt(int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return (static_cast<int>(c1) << 24) + (static_cast<int>(c2) << 16) + (static_cast<int>(c3) << 8) + (c4);
}

unsigned char * read_mnist_labels(std::string full_path, int& number_of_labels) {
    std::ifstream file(full_path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2049) throw std::runtime_error("Invalid MNIST label file!");

        file.read(reinterpret_cast<char *>(&number_of_labels),
                  sizeof(number_of_labels));
        number_of_labels = reverseInt(number_of_labels);

        auto * dataset = new unsigned char [number_of_labels];
        for (int i = 0; i < number_of_labels; i++) {
            file.read(reinterpret_cast<char *>(&dataset[i]), 1);
        }

        return dataset;
    } else {
        throw std::runtime_error("Unable to open file `" + full_path + "`!");
    }
}

unsigned char ** read_mnist_images(std::string full_path, int& number_of_images, int& image_size) {
    std::ifstream file(full_path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        int n_rows = 0;
        int n_cols = 0;

        file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if(magic_number != 2051) throw std::runtime_error("Invalid MNIST image file!");

        file.read(reinterpret_cast<char *>(&number_of_images), sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);

        file.read(reinterpret_cast<char *>(&n_rows), sizeof(n_rows));
        n_rows = reverseInt(n_rows);

        file.read(reinterpret_cast<char *>(&n_cols), sizeof(n_cols));
        n_cols = reverseInt(n_cols);

        image_size = n_rows * n_cols;

        auto ** dataset = new unsigned char * [number_of_images];
        for(int i = 0; i < number_of_images; i++) {
            dataset[i] = new unsigned char [image_size];
            file.read(reinterpret_cast<char *>(dataset[i]), image_size);
        }

        return dataset;
    } else {
        throw std::runtime_error("Cannot open file `" + full_path + "`!");
    }
}


int main(int argc, char ** argv) {
    int number_of_labels;
    int number_of_images;
    int image_size;

    unsigned char * label_dataset = read_mnist_labels("../train-labels-idx1-ubyte.dat", number_of_labels);
    unsigned char ** image_dataset = read_mnist_images("../train-images-idx3-ubyte.dat", number_of_images, image_size);

    for (int i = 0; i < image_size; i++) {
        std::cout << static_cast<int>(image_dataset[0][i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}