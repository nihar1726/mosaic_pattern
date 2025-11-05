#ifndef MOSAICGENERATOR_H
#define MOSAICGENERATOR_H

#include <opencv2/opencv.hpp>
#include "ImageProcessor.h"
#include "Utils.h"
#include <vector>

enum class TileShape {
    SQUARE,
    CIRCLE,
    HEXAGON
};

enum class ColorMode {
    AVERAGE,        // Average color of the region
    DOMINANT,       // Most dominant color in the region
    QUANTIZED       // Quantized color palette
};

class MosaicGenerator {
public:
    MosaicGenerator(ImageProcessor* processor);
    ~MosaicGenerator();

    // Generate mosaic from the current image
    cv::Mat generateMosaic(int tileSize, TileShape shape = TileShape::SQUARE, 
                          ColorMode mode = ColorMode::AVERAGE);

    // Set color palette for quantized mode
    void setColorPalette(const std::vector<Utils::Color>& palette);

    // Generate mosaic with custom tile patterns
    cv::Mat generatePatternMosaic(int tileSize, const std::vector<cv::Mat>& tilePatterns);

    // Get the number of tiles used
    int getTileCountX() const { return tilesX; }
    int getTileCountY() const { return tilesY; }

private:
    ImageProcessor* imageProcessor;
    int tilesX, tilesY;
    std::vector<Utils::Color> colorPalette;

    // Helper methods
    cv::Mat drawSquareTile(const cv::Size& size, const Utils::Color& color);
    cv::Mat drawCircleTile(const cv::Size& size, const Utils::Color& color);
    cv::Mat drawHexagonTile(const cv::Size& size, const Utils::Color& color);
    Utils::Color findClosestColor(const Utils::Color& target, const std::vector<Utils::Color>& palette);
};

#endif // MOSAICGENERATOR_H
