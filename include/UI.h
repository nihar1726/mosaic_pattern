#ifndef UI_H
#define UI_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QSlider>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include "ImageProcessor.h"
#include "MosaicGenerator.h"
#include <opencv2/opencv.hpp>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadImage();
    void onGenerateMosaic();
    void onSaveMosaic();
    void onTileSizeChanged(int value);
    void onShapeChanged(int index);
    void onColorModeChanged(int index);

private:
    void setupUI();
    void updatePreview();
    QImage matToQImage(const cv::Mat& mat);

    // UI Components
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    
    // Image display
    QLabel* originalImageLabel;
    QLabel* mosaicImageLabel;
    
    // Controls
    QPushButton* loadImageButton;
    QPushButton* generateButton;
    QPushButton* saveButton;
    
    QSpinBox* tileSizeSpinBox;
    QLabel* tileSizeLabel;
    
    QComboBox* shapeComboBox;
    QLabel* shapeLabel;
    
    QComboBox* colorModeComboBox;
    QLabel* colorModeLabel;
    
    // Data
    ImageProcessor* imageProcessor;
    MosaicGenerator* mosaicGenerator;
    cv::Mat currentMosaic;
    
    static constexpr int PREVIEW_MAX_SIZE = 800;
};

#endif // UI_H
