#include "../include/Utils.h"
#include <cmath>
#include <algorithm>
#include <set>
#include <opencv2/imgproc.hpp>

namespace Utils {
    double colorDistance(const Color& c1, const Color& c2) {
        // Euclidean distance in RGB space
        int dr = c1.r - c2.r;
        int dg = c1.g - c2.g;
        int db = c1.b - c2.b;
        return std::sqrt(dr * dr + dg * dg + db * db);
    }

    Color vec3bToColor(const cv::Vec3b& vec) {
        return Color(vec[2], vec[1], vec[0]); // BGR to RGB
    }

    cv::Vec3b colorToVec3b(const Color& color) {
        return cv::Vec3b(color.b, color.g, color.r); // RGB to BGR
    }

    std::string getFileExtension(const std::string& filepath) {
        size_t pos = filepath.find_last_of('.');
        if (pos != std::string::npos) {
            std::string ext = filepath.substr(pos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            return ext;
        }
        return "";
    }

    std::string getFileNameWithoutExtension(const std::string& filepath) {
        size_t lastSlash = filepath.find_last_of("/\\");
        size_t lastDot = filepath.find_last_of('.');
        
        if (lastSlash == std::string::npos) lastSlash = 0;
        else lastSlash++;
        
        if (lastDot == std::string::npos || lastDot < lastSlash) {
            return filepath.substr(lastSlash);
        }
        
        return filepath.substr(lastSlash, lastDot - lastSlash);
    }

    bool isValidImageFile(const std::string& filepath) {
        std::string ext = getFileExtension(filepath);
        return ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "bmp";
    }

    std::vector<Color> quantizeColors(const cv::Mat& image, int numColors) {
        if (image.empty() || numColors <= 0) {
            return {};
        }

        cv::Mat data = image.reshape(1, image.total());
        data.convertTo(data, CV_32F);

        cv::Mat labels, centers;
        cv::kmeans(data, numColors, labels,
                   cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0),
                   3, cv::KMEANS_PP_CENTERS, centers);

        std::vector<Color> palette;
        for (int i = 0; i < centers.rows; ++i) {
            cv::Vec3f center = centers.at<cv::Vec3f>(i);
            palette.push_back(Color(
                static_cast<int>(center[2]), // BGR to RGB
                static_cast<int>(center[1]),
                static_cast<int>(center[0])
            ));
        }

        return palette;
    }
}
