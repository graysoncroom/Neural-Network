//
// Created by Grayson Croom on 2020-02-21.
//

#ifndef NEURAL_NETWORK_MNIST_READER_H
#define NEURAL_NETWORK_MNIST_READER_H


class mnist_reader {
public:
    mnist_reader(std::string, std::string);

    unsigned char * get_labels();
    unsigned char ** get_images();

    int get_number_of_labels() const;
    int get_number_of_images() const;
    int get_image_size() const;
private:
    int number_of_labels;
    int number_of_images;
    int image_size;
    std::string labels_path;
    std::string images_path;

    static int reverseInt(int);
};


#endif //NEURAL_NETWORK_MNIST_READER_H
