//
// Created by stef on 10/22/24.
//

#ifndef FILTER_H
#define FILTER_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include "Image.h"
#include "Frame.h"
#include "Exception.h"

class Filter {
protected:
    cv::Mat image;
    cv::Mat original_image;
    std::string path;
public:
    explicit Filter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");
    Filter(const Filter& filter);
    Filter& operator=(const Filter& filter);
    virtual ~Filter();
    friend std::ostream& operator<<(std::ostream &os, const Filter &filter);
    virtual void applyFilter() = 0;
};


class BlurFilter final : public Filter
{
    int blur{};
    public:
    explicit BlurFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");
    void applyFilter() override;
    void setBlur(const double blur){this->blur = static_cast<int>(blur);};
};


class CropFilter final : public Filter
{
    int a=0,b=0,c=0,d=0;
public:
    explicit CropFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");
    void applyFilter() override;
    void setCrop(int a, int b, int c, int d){this->a =a;this->b =b;this->c =c;this->d =d;};
};

class ContrastFilter final : public Filter
{
    double contrast = 1;
public:
    explicit ContrastFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");
    void applyFilter() override;
    void setContrast(double contrast){this->contrast = contrast;};
};

class SaturationFilter final : public Filter
{
    double saturation = 1;
public:
    explicit SaturationFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");
    void applyFilter() override;
    void setSaturation(double saturation){this->saturation = saturation;};
};



class FilterFactory {
public:
    enum FilterType {
        BLUR,
        CROP,
        CONTRAST,
        SATURATION
    };

    static std::unique_ptr<Filter> createFilter(FilterType type, const std::string& path = "") {
        switch (type) {
        case BLUR:
            return std::make_unique<BlurFilter>(path);
        case CROP:
            return std::make_unique<CropFilter>(path);
        case CONTRAST:
            return std::make_unique<ContrastFilter>(path);
        case SATURATION:
            return std::make_unique<SaturationFilter>(path);
        default:
            throw std::invalid_argument("Unknown filter type");
        }
    }
};


#endif //FILTER_H
