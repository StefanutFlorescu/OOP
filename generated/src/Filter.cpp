//
// Created by stef on 10/22/24.
//

#include "../include/Filter.h"

// Constructor: Initialize Filter with a given image path
Filter::Filter(const std::string& path) : path(path) {
    if (Frame::getReady()) {
        image = cv::imread(path);
        if (image.empty()) {
            std::cerr << "Error: Could not open or find the image!" << std::endl;
        } else {
            std::cerr << "Please select an image!" << std::endl;
        }
    }
}

// Copy constructor: Create a deep copy of the filter
Filter::Filter(const Filter &filter) {
    this->path = filter.path;
    this->image = filter.image.clone(); // Clone the image
}

// Assignment operator: Assign one filter to another
Filter &Filter::operator=(const Filter &filter) {
    this->image = filter.image.clone(); // Clone the image
    return *this;
}

// Destructor: Release resources
Filter::~Filter() {
    image = cv::Mat(); // Clear the image matrix
}

// Overload the stream insertion operator to print the filter's path
std::ostream &operator<<(std::ostream &os, const Filter &filter) {
    os << filter.path;
    return os;
}

// -------------------------------- BlurFilter --------------------------------

// Constructor: Initialize BlurFilter with a default or given path
BlurFilter::BlurFilter(const std::string& path) : Filter(path) {}

// Apply Gaussian blur to the image
void BlurFilter::applyFilter() {
    try {
        image = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg");
        originalImage = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg");

        if (image.empty()) {
            throw FilterException("Could not find scaled image!");
        }

        if (originalImage.empty()) {
            throw FilterException("Could not find original image!");
        }

        // Apply Gaussian blur to the image
        cv::Mat blurred_image;
        cv::GaussianBlur(image, blurred_image, cv::Size(blur, blur), 0);

        // Save the blurred image
        std::string outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg";
        if (cv::imwrite(outputPath, blurred_image)) {
            std::cout << "Blurred image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred image!");
        }

        // Apply Gaussian blur to the original image
        cv::Mat blurred_original_image;
        cv::GaussianBlur(originalImage, blurred_original_image, cv::Size(15, 15), 0);

        outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg";
        if (cv::imwrite(outputPath, blurred_original_image)) {
            std::cout << "Blurred original image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the blurred original image!");
        }
    } catch (const FilterException &e) {
        std::cerr << e.what() << std::endl;
    }
}

// -------------------------------- CropFilter --------------------------------

// Constructor: Initialize CropFilter with a default or given path
CropFilter::CropFilter(const std::string& path) : Filter(path) {}

// Crop the image to the specified region of interest (ROI)
void CropFilter::applyFilter() {
    try {
        const cv::Mat src = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg");
        if (src.empty()) {
            throw FilterException("Could not find image!");
        }

        const cv::Rect roi(a, b, c, d); // Define the ROI for cropping
        const cv::Mat dst = src(roi);  // Crop the image

        // Save the cropped image
        std::string outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Cropped image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the cropped image!");
        }

        outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Cropped image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the cropped image!");
        }

    } catch (const FilterException &e) {
        std::cerr << e.what() << std::endl;
    }
}

// -------------------------------- ContrastFilter --------------------------------

// Function to adjust contrast using alpha and beta values
void adjustContrast(const cv::Mat &src, cv::Mat &dst, double alpha, double beta = 0) {
    src.convertTo(dst, -1, alpha, beta);
}

// Constructor: Initialize ContrastFilter with a default or given path
ContrastFilter::ContrastFilter(const std::string& path) : Filter(path) {}

// Apply contrast adjustment to the image
void ContrastFilter::applyFilter() {
    try {
        image = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg");
        if (image.empty()) {
            throw FilterException("Could not find the original image!");
        }

        originalImage = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg");
        if (originalImage.empty()) {
            throw FilterException("Could not find the temp image!");
        }

        cv::Mat dst;
        adjustContrast(originalImage, dst, contrast); // Adjust contrast for the original image

        cv::Mat dst2;
        adjustContrast(image, dst2, contrast); // Adjust contrast for the scaled image

        // Save the contrasted image
        std::string outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg";
        if (cv::imwrite(outputPath, dst2)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the contrasted image!");
        }

        outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Contrasted image saved successfully to " << outputPath << std::endl;
        } else {
            throw FilterException("Error: Could not save the contrasted image!");
        }

    } catch (const FilterException &e) {
        std::cerr << e.what() << std::endl;
    }
}

// -------------------------------- SaturationFilter --------------------------------

// Function to adjust saturation by modifying the HSV channels
void adjustSaturation(const cv::Mat &src, cv::Mat &dst, double alpha) {
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsv, hsvChannels);

    hsvChannels[1] = hsvChannels[1] * alpha; // Modify the saturation channel
    cv::threshold(hsvChannels[1], hsvChannels[1], 255, 255, cv::THRESH_TRUNC);

    cv::merge(hsvChannels, hsv);
    cv::cvtColor(hsv, dst, cv::COLOR_HSV2BGR);
}

// Constructor: Initialize SaturationFilter with a default or given path
SaturationFilter::SaturationFilter(const std::string& path) : Filter(path) {}

// Apply saturation adjustment to the image
void SaturationFilter::applyFilter() {
    try {
        image = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg");
        if (image.empty()) {
            throw FilterException("Could not find the scaled image!");
        }
        originalImage = cv::imread("/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg");
        if (originalImage.empty()) {
            throw FilterException("Could not find the original image!");
        }

        cv::Mat dst;
        adjustSaturation(image, dst, saturation); // Adjust saturation for the scaled image

        cv::Mat dst2;
        adjustSaturation(originalImage, dst2, saturation); // Adjust saturation

        // Save the adjusted image
        std::string outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/original.jpg";
        if (cv::imwrite(outputPath, dst2)) {
            //std::cout << "Saturation-adjusted image saved successfully to " << outputPath << std::endl;
            const std::string logMes = "Saturation-adjusted image saved successfully to " + outputPath;
            Frame::log(logMes);
        } else {
            throw FilterException("Error: Could not save the adjusted image!");
        }

        outputPath = "/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg";
        if (cv::imwrite(outputPath, dst)) {
            std::cout << "Saturation-adjusted image saved successfully to " << outputPath << std::endl;
            const std::string logMes = "Saturation-adjusted image saved successfully to " + outputPath;
            Frame::log(logMes);
        } else {
            throw FilterException("Error: Could not save the adjusted image!");
        }
    } catch (const FilterException &e) {
        std::cerr << e.what() << std::endl;
    }
}


///////---------------------Display------------------//////////

void Filter::display()
{
    vDisplay();// Calling the virtual function in the non-virtual function
}

void Filter::vDisplay()
{
    std::cout <<"Using BaseFilter class"<<std::endl;
}

void BlurFilter::vDisplay()
{
    std::cout <<"Using BlurFilter class"<<std::endl;
}

void CropFilter::vDisplay()
{
    std::cout <<"Using CropFilter class"<<std::endl;
}

void SaturationFilter::vDisplay()
{
    std::cout <<"Using SaturationFilter class"<<std::endl;
}

void ContrastFilter::vDisplay()
{
    std::cout <<"Using ContrastFilter class"<<std::endl;
}


