//
// Created by stef on 10/22/24.
//

#ifndef FILTER_H
#define FILTER_H
#include <opencv2/opencv.hpp>
#include "Image.h"
#include "Frame.h"

class Filter {
    cv::Mat image;
    std::string path;
public:
    Filter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");
    Filter(const Filter& filter);
    Filter& operator=(const Filter& filter);
    virtual ~Filter();
    friend std::ostream& operator<<(std::ostream &os, const Filter &filter);

    //virtual void applyFilter();
};



#endif //FILTER_H
