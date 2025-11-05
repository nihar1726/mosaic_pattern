#include "../include/UI.h"
#include <QtWidgets/QMessageBox>
#include <QtCore/QDir>
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      imageProcessor(new ImageProcessor()),
      mosaicGenerator(nullptr),
      currentMosaic() {
    
    mosaicGenerator = new MosaicGenerator(imageProcessor);
    setupUI();
    
    setWindowTitle("Mosaic Pattern Creator");
    resize(1200, 700);
}

MainWindow::~MainWindow() {
    delete imageProcessor;
    delete mosaicGenerator;
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    // Top controls
    QHBoxLayout* controlLayout = new QHBoxLayout();
    
    loadImageButton = new QPushButton("Load Image", this);
    generateButton = new QPushButton("Generate Mosaic", this);
    saveButton = new QPushButton("Save Mosaic", this);
    
    generateButton->setEnabled(false);
    saveButton->setEnabled(false);
    
    controlLayout->addWidget(loadImageButton);
    controlLayout->addWidget(generateButton);
    controlLayout->addWidget(saveButton);
    controlLayout->addStretch();
    
    // Parameter controls
    QHBoxLayout* paramLayout = new QHBoxLayout();
    
    tileSizeLabel = new QLabel("Tile Size:", this);
    tileSizeSpinBox = new QSpinBox(this);
    tileSizeSpinBox->setMinimum(5);
    tileSizeSpinBox->setMaximum(100);
    tileSizeSpinBox->setValue(20);
    tileSizeSpinBox->setSingleStep(5);
    
    shapeLabel = new QLabel("Shape:", this);
    shapeComboBox = new QComboBox(this);
    shapeComboBox->addItem("Square");
    shapeComboBox->addItem("Circle");
    shapeComboBox->addItem("Hexagon");
    
    colorModeLabel = new QLabel("Color Mode:", this);
    colorModeComboBox = new QComboBox(this);
    colorModeComboBox->addItem("Average");
    colorModeComboBox->addItem("Dominant");
    colorModeComboBox->addItem("Quantized");
    
    paramLayout->addWidget(tileSizeLabel);
    paramLayout->addWidget(tileSizeSpinBox);
    paramLayout->addWidget(shapeLabel);
    paramLayout->addWidget(shapeComboBox);
    paramLayout->addWidget(colorModeLabel);
    paramLayout->addWidget(colorModeComboBox);
    paramLayout->addStretch();
    
    // Image display area
    QHBoxLayout* imageLayout = new QHBoxLayout();
    
    QVBoxLayout* originalLayout = new QVBoxLayout();
    originalLayout->addWidget(new QLabel("Original Image", this));
    originalImageLabel = new QLabel(this);
    originalImageLabel->setMinimumSize(400, 300);
    originalImageLabel->setAlignment(Qt::AlignCenter);
    originalImageLabel->setStyleSheet("border: 1px solid gray;");
    originalImageLabel->setText("No image loaded");
    originalLayout->addWidget(originalImageLabel);
    
    QVBoxLayout* mosaicLayout = new QVBoxLayout();
    mosaicLayout->addWidget(new QLabel("Mosaic Preview", this));
    mosaicImageLabel = new QLabel(this);
    mosaicImageLabel->setMinimumSize(400, 300);
    mosaicImageLabel->setAlignment(Qt::AlignCenter);
    mosaicImageLabel->setStyleSheet("border: 1px solid gray;");
    mosaicImageLabel->setText("Generate mosaic to preview");
    mosaicLayout->addWidget(mosaicImageLabel);
    
    imageLayout->addLayout(originalLayout);
    imageLayout->addLayout(mosaicLayout);
    
    // Assemble main layout
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(paramLayout);
    mainLayout->addLayout(imageLayout);
    
    // Connect signals
    connect(loadImageButton, &QPushButton::clicked, this, &MainWindow::onLoadImage);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateMosaic);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveMosaic);
    connect(tileSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onTileSizeChanged);
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onShapeChanged);
    connect(colorModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onColorModeChanged);
}

void MainWindow::onLoadImage() {
    QString filepath = QFileDialog::getOpenFileName(
        this,
        "Open Image",
        QDir::homePath(),
        "Image Files (*.png *.jpg *.jpeg *.bmp)"
    );
    
    if (filepath.isEmpty()) {
        return;
    }
    
    if (imageProcessor->loadImage(filepath.toStdString())) {
        updatePreview();
        generateButton->setEnabled(true);
    } else {
        QMessageBox::warning(this, "Error", "Failed to load image!");
    }
}

void MainWindow::onGenerateMosaic() {
    if (!imageProcessor->isImageLoaded()) {
        return;
    }
    
    int tileSize = tileSizeSpinBox->value();
    TileShape shape = static_cast<TileShape>(shapeComboBox->currentIndex());
    ColorMode mode = static_cast<ColorMode>(colorModeComboBox->currentIndex());
    
    currentMosaic = mosaicGenerator->generateMosaic(tileSize, shape, mode);
    
    if (!currentMosaic.empty()) {
        QImage mosaicQImage = matToQImage(currentMosaic);
        QPixmap mosaicPixmap = QPixmap::fromImage(mosaicQImage);
        
        // Scale for preview if needed
        if (mosaicPixmap.width() > PREVIEW_MAX_SIZE || mosaicPixmap.height() > PREVIEW_MAX_SIZE) {
            mosaicPixmap = mosaicPixmap.scaled(PREVIEW_MAX_SIZE, PREVIEW_MAX_SIZE,
                                              Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        
        mosaicImageLabel->setPixmap(mosaicPixmap);
        saveButton->setEnabled(true);
    }
}

void MainWindow::onSaveMosaic() {
    if (currentMosaic.empty()) {
        return;
    }
    
    QString filepath = QFileDialog::getSaveFileName(
        this,
        "Save Mosaic",
        QDir::homePath(),
        "PNG Files (*.png);;JPEG Files (*.jpg);;All Files (*.*)"
    );
    
    if (filepath.isEmpty()) {
        return;
    }
    
    if (imageProcessor->saveImage(currentMosaic, filepath.toStdString())) {
        QMessageBox::information(this, "Success", "Mosaic saved successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save mosaic!");
    }
}

void MainWindow::onTileSizeChanged(int value) {
    // Auto-regenerate if image is loaded and mosaic exists
    if (imageProcessor->isImageLoaded() && !currentMosaic.empty()) {
        onGenerateMosaic();
    }
}

void MainWindow::onShapeChanged(int index) {
    // Auto-regenerate if image is loaded and mosaic exists
    if (imageProcessor->isImageLoaded() && !currentMosaic.empty()) {
        onGenerateMosaic();
    }
}

void MainWindow::onColorModeChanged(int index) {
    // Auto-regenerate if image is loaded and mosaic exists
    if (imageProcessor->isImageLoaded() && !currentMosaic.empty()) {
        onGenerateMosaic();
    }
}

void MainWindow::updatePreview() {
    cv::Mat image = imageProcessor->getImage();
    QImage qImage = matToQImage(image);
    QPixmap pixmap = QPixmap::fromImage(qImage);
    
    // Scale for preview if needed
    if (pixmap.width() > PREVIEW_MAX_SIZE || pixmap.height() > PREVIEW_MAX_SIZE) {
        pixmap = pixmap.scaled(PREVIEW_MAX_SIZE, PREVIEW_MAX_SIZE,
                              Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    
    originalImageLabel->setPixmap(pixmap);
}

QImage MainWindow::matToQImage(const cv::Mat& mat) {
    if (mat.empty()) {
        return QImage();
    }
    
    cv::Mat rgbMat;
    if (mat.channels() == 3) {
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
    } else {
        rgbMat = mat;
    }
    
    QImage qImage(rgbMat.data, rgbMat.cols, rgbMat.rows,
                  static_cast<int>(rgbMat.step), QImage::Format_RGB888);
    
    return qImage.copy(); // Make a deep copy
}
