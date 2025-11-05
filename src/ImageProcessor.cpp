#include "../include/ImageProcessor.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

ImageProcessor::ImageProcessor() {
}

ImageProcessor::~ImageProcessor() {
}

bool ImageProcessor::loadImage(const std::string& filepath) {
    if (!Utils::isValidImageFile(filepath)) {
        std::cerr << "Invalid image file format: " << filepath << std::endl;
        return false;
    }

    currentImage = cv::imread(filepath, cv::IMREAD_COLOR);
    
    if (currentImage.empty()) {
        std::cerr << "Failed to load image: " << filepath << std::endl;
        return false;
    }

    currentFilePath = filepath;
    std::cout << "Image loaded successfully: " << filepath 
              << " (" << currentImage.cols << "x" << currentImage.rows << ")" << std::endl;
    
    return true;
}

cv::Mat ImageProcessor::resizeImage(const cv::Mat& image, int maxWidth, int maxHeight) {
    if (image.empty()) {
        return cv::Mat();
    }

    double scale = std::min(
        static_cast<double>(maxWidth) / image.cols,
        static_cast<double>(maxHeight) / image.rows
    );

    if (scale >= 1.0) {
        return image.clone(); // No need to upscale
    }

    cv::Mat resized;
    cv::resize(image, resized, cv::Size(), scale, scale, cv::INTER_AREA);
    return resized;
}

Utils::Color ImageProcessor::getAverageColor(const cv::Rect& region) {
    if (currentImage.empty() || 
        region.x < 0 || region.y < 0 ||
        region.x + region.width > currentImage.cols ||
        region.y + region.height > currentImage.rows) {
        return Utils::Color(0, 0, 0);
    }

    cv::Mat roi = currentImage(region);
    cv::Scalar meanColor = cv::mean(roi);
    
    return Utils::Color(
        static_cast<int>(meanColor[2]), // BGR to RGB
        static_cast<int>(meanColor[1]),
        static_cast<int>(meanColor[0])
    );
}

Utils::Color ImageProcessor::getAverageColor() const {
    if (currentImage.empty()) {
        return Utils::Color(0, 0, 0);
    }

    cv::Scalar meanColor = cv::mean(currentImage);
    return Utils::Color(
        static_cast<int>(meanColor[2]), // BGR to RGB
        static_cast<int>(meanColor[1]),
        static_cast<int>(meanColor[0])
    );
}

cv::Vec3b ImageProcessor::getPixel(int x, int y) const {
    if (currentImage.empty() || 
        x < 0 || x >= currentImage.cols ||
        y < 0 || y >= currentImage.rows) {
        return cv::Vec3b(0, 0, 0);
    }
    return currentImage.at<cv::Vec3b>(y, x);
}

bool ImageProcessor::saveImage(const cv::Mat& image, const std::string& filepath) {
    if (image.empty()) {
        std::cerr << "Cannot save empty image" << std::endl;
        return false;
    }

    bool success = cv::imwrite(filepath, image);
    if (success) {
        std::cout << "Image saved successfully: " << filepath << std::endl;
    } else {
        std::cerr << "Failed to save image: " << filepath << std::endl;
    }
    return success;
}
