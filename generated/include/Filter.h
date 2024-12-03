//
// Created by stef on 10/22/24.
//

#ifndef FILTER_H
#define FILTER_H

// Include necessary headers
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include "Image.h"
#include "Frame.h"
#include "Exception.h"

/**
 * @class Filter
 * Here we have tall the filters to modify the image
 */

// Base class for filters
class Filter {
protected:
    cv::Mat image;                // Current image after applying filter
    cv::Mat originalImage;       // Original unaltered image
    std::string path;             // Path to the image file

    virtual void vDisplay()=0;
public:
    // Constructor with default image path
    explicit Filter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");

    // Copy constructor
    Filter(const Filter& filter);

    // Assignment operator
    Filter& operator=(const Filter& filter);

    // Virtual destructor for proper cleanup
    virtual ~Filter();

    // Overload << operator for printing filter information
    friend std::ostream& operator<<(std::ostream &os, const Filter &filter);

    // Pure virtual function to apply a specific filter (to be overridden by derived classes)
    virtual void applyFilter() = 0;

    // Non-virtual display
    void display();
};

// BlurFilter class: Applies a blur effect
class BlurFilter final : public Filter {
    int blur{}; // Blur intensity

public:
    // Constructor with default image path
    explicit BlurFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");

    // Override applyFilter to implement blur effect
    void applyFilter() override;

    // Setter for blur intensity
    void setBlur(const double blur) { this->blur = static_cast<int>(blur); };

    // Virtual Display
    void vDisplay() override;
};

// CropFilter class: Crops the image to a specific rectangle
class CropFilter final : public Filter {
    int a = 0, b = 0, c = 0, d = 0; // Crop rectangle parameters (x, y, width, height)

public:
    // Constructor with default image path
    explicit CropFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");

    // Override applyFilter to implement cropping
    void applyFilter() override;

    // Setter for crop parameters
    void setCrop(const int a, const int b, const int c, const int d) {
        this->a = a; this->b = b; this->c = c; this->d = d;
    };

    // Virtual Display
    void vDisplay() override;
};

// ContrastFilter class: Adjusts the image contrast
class ContrastFilter final : public Filter {
    double contrast = 1; // Contrast factor

public:
    // Constructor with default image path
    explicit ContrastFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");

    // Override applyFilter to implement contrast adjustment
    void applyFilter() override;

    // Setter for contrast value
    void setContrast(double contrast) { this->contrast = contrast; };

    // Virtual Display
    void vDisplay() override;
};

// SaturationFilter class: Adjusts the image saturation
class SaturationFilter final : public Filter {
    double saturation = 1; // Saturation factor

public:
    // Constructor with default image path
    explicit SaturationFilter(const std::string& path = "/home/stef/CLionProjects/PhotoEditorPhoto/resources/temp.jpg");

    // Override applyFilter to implement saturation adjustment
    void applyFilter() override;

    // Setter for saturation value
    void setSaturation(double saturation) { this->saturation = saturation; };

    // Virtual Display
    void vDisplay() override;
};

// FilterFactory: Factory class for creating filters
class FilterFactory {
public:
    // Enum to define filter types
    enum FilterType {
        BLUR,
        CROP,
        CONTRAST,
        SATURATION
    };

    // Factory method to create filters based on the type
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

#endif // FILTER_H
