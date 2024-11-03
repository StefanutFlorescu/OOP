//
// Created by stef on 10/22/24.
//

#include "../include/Filter.h"

Filter::Filter(const std::string& path) : path(path) {
    if(Frame::getReady()) {
        image = cv::imread(path);
        if (image.empty()) {
            std::cerr << "Error: Could not open or find the image!" << std::endl;
        }else {
            std::cerr << "Please select an image!" << std::endl;
        }
    }
}

Filter::Filter(const Filter &filter) {
    this->path = filter.path;
    this->image = filter.image.clone();
    //filter.image.copyTo(this->image);
}
Filter &Filter::operator=(const Filter &filter) {
    this->image = filter.image.clone();
    //filter.image.copyTo(this->image);
    return *this;
}

Filter::~Filter() {
    image = cv::Mat();
}

std::ostream &operator<<(std::ostream &os, const Filter &filter) {
    os << std::string(filter.path);
    return os;
}

