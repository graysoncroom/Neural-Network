//
// Created by Grayson Croom on 2020-02-21.
//

#include <string>
#include <fstream>
#include "mnist_reader.h"

mnist_reader::mnist_reader(std::string labels_path, std::string images_path) : labels_path(labels_path), images_path(images_path) {}

int mnist_reader::reverseInt(int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return (static_cast<int>(c1) << 24) + (static_cast<int>(c2) << 16) + (static_cast<int>(c3) << 8) + (c4);
}

int mnist_reader::get_image_size() const { return this->image_size; }
int mnist_reader::get_number_of_images() const { return this->number_of_images; }
int mnist_reader::get_number_of_labels() const { return this->number_of_labels; }


unsigned char * mnist_reader::get_labels() {
    std::ifstream file(this->labels_path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
        magic_number = mnist_reader::reverseInt(magic_number);

        if (magic_number != 2049) throw std::runtime_error("Invalid MNIST label file!");

        file.read(reinterpret_cast<char *>(&(this->number_of_labels)), sizeof(this->number_of_labels));
        this->number_of_labels = mnist_reader::reverseInt(number_of_labels);

        auto * dataset = new unsigned char [this->number_of_labels];
        for (int i = 0; i < this->number_of_labels; i++) {
            file.read(reinterpret_cast<char *>(&dataset[i]), 1);
        }

        return dataset;
    } else {
        throw std::runtime_error("Unable to open file `" + this->labels_path + "`!");
    }
}

unsigned char ** mnist_reader::get_images() {
    std::ifstream file(this->images_path, std::ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        int n_rows = 0;
        int n_cols = 0;

        file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
        magic_number = mnist_reader::reverseInt(magic_number);

        if(magic_number != 2051) throw std::runtime_error("Invalid MNIST image file!");

        file.read(reinterpret_cast<char *>(&(this->number_of_images)), sizeof(this->number_of_images));
        this->number_of_images = mnist_reader::reverseInt(this->number_of_images);

        file.read(reinterpret_cast<char *>(&n_rows), sizeof(n_rows));
        n_rows = mnist_reader::reverseInt(n_rows);

        file.read(reinterpret_cast<char *>(&n_cols), sizeof(n_cols));
        n_cols = mnist_reader::reverseInt(n_cols);

        this->image_size = n_rows * n_cols;

        auto ** dataset = new unsigned char * [this->number_of_images];
        for(int i = 0; i < this->number_of_images; i++) {
            dataset[i] = new unsigned char [this->image_size];
            file.read(reinterpret_cast<char *>(dataset[i]), this->image_size);
        }

        return dataset;
    } else {
        throw std::runtime_error("Cannot open file `" + this->images_path + "`!");
    }
}