#include "../include/MosaicGenerator.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cmath>

MosaicGenerator::MosaicGenerator(ImageProcessor* processor) 
    : imageProcessor(processor), tilesX(0), tilesY(0) {
}

MosaicGenerator::~MosaicGenerator() {
}

cv::Mat MosaicGenerator::generateMosaic(int tileSize, TileShape shape, ColorMode mode) {
    if (!imageProcessor || !imageProcessor->isImageLoaded()) {
        return cv::Mat();
    }

    cv::Mat sourceImage = imageProcessor->getImage();
    int width = sourceImage.cols;
    int height = sourceImage.rows;

    tilesX = (width + tileSize - 1) / tileSize;
    tilesY = (height + tileSize - 1) / tileSize;

    cv::Mat mosaic = cv::Mat::zeros(height, width, CV_8UC3);

    // Prepare color palette if quantized mode
    std::vector<Utils::Color> palette = colorPalette;
    if (mode == ColorMode::QUANTIZED && palette.empty()) {
        palette = Utils::quantizeColors(sourceImage, 16);
    }

    for (int ty = 0; ty < tilesY; ++ty) {
        for (int tx = 0; tx < tilesX; ++tx) {
            int x = tx * tileSize;
            int y = ty * tileSize;
            int w = std::min(tileSize, width - x);
            int h = std::min(tileSize, height - y);

            cv::Rect region(x, y, w, h);
            Utils::Color tileColor;

            // Determine tile color based on mode
            switch (mode) {
                case ColorMode::AVERAGE:
                    tileColor = imageProcessor->getAverageColor(region);
                    break;
                case ColorMode::DOMINANT:
                    // For simplicity, use average (can be enhanced with histogram analysis)
                    tileColor = imageProcessor->getAverageColor(region);
                    break;
                case ColorMode::QUANTIZED:
                    {
                        Utils::Color avgColor = imageProcessor->getAverageColor(region);
                        tileColor = findClosestColor(avgColor, palette);
                    }
                    break;
            }

            // Draw the tile
            cv::Mat tile;
            cv::Size tileSizeMat(w, h);
            
            switch (shape) {
                case TileShape::SQUARE:
                    tile = drawSquareTile(tileSizeMat, tileColor);
                    break;
                case TileShape::CIRCLE:
                    tile = drawCircleTile(tileSizeMat, tileColor);
                    break;
                case TileShape::HEXAGON:
                    tile = drawHexagonTile(tileSizeMat, tileColor);
                    break;
            }

            // Place tile in mosaic
            tile.copyTo(mosaic(region));
        }
    }

    return mosaic;
}

void MosaicGenerator::setColorPalette(const std::vector<Utils::Color>& palette) {
    colorPalette = palette;
}

cv::Mat MosaicGenerator::generatePatternMosaic(int tileSize, const std::vector<cv::Mat>& tilePatterns) {
    if (!imageProcessor || !imageProcessor->isImageLoaded() || tilePatterns.empty()) {
        return cv::Mat();
    }

    cv::Mat sourceImage = imageProcessor->getImage();
    int width = sourceImage.cols;
    int height = sourceImage.rows;

    tilesX = (width + tileSize - 1) / tileSize;
    tilesY = (height + tileSize - 1) / tileSize;

    cv::Mat mosaic = cv::Mat::zeros(height, width, CV_8UC3);

    for (int ty = 0; ty < tilesY; ++ty) {
        for (int tx = 0; tx < tilesX; ++tx) {
            int x = tx * tileSize;
            int y = ty * tileSize;
            int w = std::min(tileSize, width - x);
            int h = std::min(tileSize, height - y);

            cv::Rect region(x, y, w, h);
            Utils::Color avgColor = imageProcessor->getAverageColor(region);

            // Select pattern based on color (simple hash-based selection)
            int patternIndex = (avgColor.r + avgColor.g + avgColor.b) % tilePatterns.size();
            cv::Mat selectedPattern = tilePatterns[patternIndex].clone();

            // Resize pattern to tile size
            cv::Mat resizedPattern;
            cv::resize(selectedPattern, resizedPattern, cv::Size(w, h));

            // Apply color tint to pattern
            cv::Mat colorMask = resizedPattern > 128;
            resizedPattern.setTo(Utils::colorToVec3b(avgColor), colorMask);

            // Place in mosaic
            resizedPattern.copyTo(mosaic(region));
        }
    }

    return mosaic;
}

cv::Mat MosaicGenerator::drawSquareTile(const cv::Size& size, const Utils::Color& color) {
    cv::Mat tile = cv::Mat::zeros(size, CV_8UC3);
    tile.setTo(Utils::colorToVec3b(color));
    return tile;
}

cv::Mat MosaicGenerator::drawCircleTile(const cv::Size& size, const Utils::Color& color) {
    cv::Mat tile = cv::Mat::zeros(size, CV_8UC3);
    cv::Point center(size.width / 2, size.height / 2);
    int radius = std::min(size.width, size.height) / 2 - 2;
    cv::circle(tile, center, radius, Utils::colorToVec3b(color), -1);
    return tile;
}

cv::Mat MosaicGenerator::drawHexagonTile(const cv::Size& size, const Utils::Color& color) {
    cv::Mat tile = cv::Mat::zeros(size, CV_8UC3);
    cv::Point center(size.width / 2, size.height / 2);
    int radius = std::min(size.width, size.height) / 2 - 2;

    std::vector<cv::Point> hexagon;
    for (int i = 0; i < 6; ++i) {
        double angle = i * M_PI / 3.0;
        hexagon.push_back(cv::Point(
            center.x + radius * std::cos(angle),
            center.y + radius * std::sin(angle)
        ));
    }

    cv::fillPoly(tile, std::vector<std::vector<cv::Point>>{hexagon}, Utils::colorToVec3b(color));
    return tile;
}

Utils::Color MosaicGenerator::findClosestColor(const Utils::Color& target, const std::vector<Utils::Color>& palette) {
    if (palette.empty()) {
        return target;
    }

    double minDistance = Utils::colorDistance(target, palette[0]);
    Utils::Color closest = palette[0];

    for (const auto& color : palette) {
        double distance = Utils::colorDistance(target, color);
        if (distance < minDistance) {
            minDistance = distance;
            closest = color;
        }
    }

    return closest;
}
