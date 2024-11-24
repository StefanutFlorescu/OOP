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


//Blur Filter
BlurFilter::BlurFilter(const std::string& path) : Filter(path){}
void BlurFilter::applyFilter()
{
    try
    {
        image = cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg");
        original_image =cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg");
        if (image.empty())
        {
            throw FilterException("Could not find scaled image!");
        }

        if(original_image.empty())
        {
            throw FilterException("Could not find original image!");
        }
        // Apply the blur
        cv::Mat blurred_image;
        cv::GaussianBlur(image, blurred_image, cv::Size(blur, blur), 0);

        // Save the blurred image
        std::string outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg";
        if (cv::imwrite(outputPath, blurred_image)) {
            std::cout << "Blurred image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;


        cv::Mat blurred_original_image;
        cv::GaussianBlur(original_image, blurred_original_image, cv::Size(15, 15), 0);

        // Save the blurred image
        outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg";
        if (cv::imwrite(outputPath, blurred_original_image)) {
            std::cout << "Blurred image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;
    }
    catch (const FilterException& e)
    {
        std::cerr << e.what() << std::endl;
    }

}


//Crop Filter
CropFilter::CropFilter(const std::string& path) : Filter(path){}
void CropFilter::applyFilter()
{
    try
    {
        cv::Mat src = cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg");
        if (src.empty()) {
            std::cerr << "Error loading image\n";
            throw FilterException("Could not find image!");
        }
        cv::Mat dst;
        cv::Rect roi(a, b, c, d);

        // Crop the image using the ROI
        dst = src(roi);

        std::string outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;

        outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;

    }catch (const FilterException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void adjustContrast(const cv::Mat& src, cv::Mat& dst, double alpha, double beta = 0) {
    src.convertTo(dst, -1, alpha, beta);
}
//Contrast Filter
ContrastFilter::ContrastFilter(const std::string& path) : Filter(path){}
void ContrastFilter::applyFilter()
{
    try
    {
        cv::Mat src = cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg");
        if (src.empty()) {
            std::cerr << "Error loading image\n";
            throw FilterException("Could not find image!");
        }
        cv::Mat dst;
        double alpha = contrast;
        double beta = 0;
        adjustContrast(src, dst, alpha, beta);
        adjustContrast(src, src, alpha, beta);

        std::string outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;

        outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg";
        if (cv::imwrite(outputPath, src)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;

    }catch (const FilterException& e)
    {
        std::cerr << e.what() << std::endl;
    }

}




void adjustSaturation(cv::Mat& src, cv::Mat& dst, double alpha) {
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);
    hsvChannels[1] = hsvChannels[1] * alpha;
    cv::threshold(hsvChannels[1], hsvChannels[1], 255, 255, cv::THRESH_TRUNC);
    cv::merge(hsvChannels, hsv);
    cv::cvtColor(hsv, dst, cv::COLOR_HSV2BGR);
    std::cout << "ContrastFilter::applyFilter" << std::endl;
}
//Saturation Filter
SaturationFilter::SaturationFilter(const std::string& path) : Filter(path){}
void SaturationFilter::applyFilter()
{
    try
    {
        cv::Mat src = cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg");
        if (src.empty()) {
            std::cerr << "Error loading image\n";
            throw FilterException("Could not find image!");
        }
        cv::Mat dst;
        adjustSaturation(src, dst, saturation);
        adjustSaturation(src, src, saturation);

        std::string outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;

        outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg";
        if (cv::imwrite(outputPath, src)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }
        std::cout << "BlurFilter::applyFilter" << std::endl;

    }catch (const FilterException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}


