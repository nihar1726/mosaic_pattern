#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>
#include "Utils.h"

class ImageProcessor {
public:
    ImageProcessor();
    ~ImageProcessor();

    // Load image from file
    bool loadImage(const std::string& filepath);

    // Get the current image
    cv::Mat getImage() const { return currentImage; }

    // Check if an image is loaded
    bool isImageLoaded() const { return !currentImage.empty(); }

    // Resize image while maintaining aspect ratio
    cv::Mat resizeImage(const cv::Mat& image, int maxWidth, int maxHeight);

    // Get average color of a region
    Utils::Color getAverageColor(const cv::Rect& region);

    // Get average color of entire image
    Utils::Color getAverageColor() const;

    // Extract pixel data
    cv::Vec3b getPixel(int x, int y) const;

    // Get image dimensions
    int getWidth() const { return currentImage.cols; }
    int getHeight() const { return currentImage.rows; }

    // Save image to file
    bool saveImage(const cv::Mat& image, const std::string& filepath);

private:
    cv::Mat currentImage;
    std::string currentFilePath;
};

#endif // IMAGEPROCESSOR_H
