#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

namespace Utils {
    // Color structure
    struct Color {
        int r, g, b;
        Color(int red = 0, int green = 0, int blue = 0) : r(red), g(green), b(blue) {}
    };

    // Calculate distance between two colors
    double colorDistance(const Color& c1, const Color& c2);

    // Convert OpenCV Vec3b to Color
    Color vec3bToColor(const cv::Vec3b& vec);

    // Convert Color to OpenCV Vec3b
    cv::Vec3b colorToVec3b(const Color& color);

    // File path utilities
    std::string getFileExtension(const std::string& filepath);
    std::string getFileNameWithoutExtension(const std::string& filepath);
    bool isValidImageFile(const std::string& filepath);

    // Color quantization - reduce to N dominant colors
    std::vector<Color> quantizeColors(const cv::Mat& image, int numColors);
}

#endif // UTILS_H
