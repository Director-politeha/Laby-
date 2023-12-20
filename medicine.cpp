#include "medicine.h"
#include "qpushbutton.h"
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QScrollArea>

MedicineWindow::MedicineWindow(QWidget *parent) : QWidget(parent), currentImageIndex(0) {
    QVBoxLayout *mainlayout = new QVBoxLayout(this);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);

    QPushButton *loadImagesButton = new QPushButton("Загрузить изображения", this);
    connect(loadImagesButton, &QPushButton::clicked, this, &MedicineWindow::loadImagesFunction);

    QPushButton *saveCollageButton = new QPushButton("Сохранить коллаж", this);
    connect(saveCollageButton, &QPushButton::clicked, this, &MedicineWindow::saveCollageFunction);

    QPushButton *viewCollageButton = new QPushButton("Посмотреть коллаж", this);
    connect(viewCollageButton, &QPushButton::clicked, this, &MedicineWindow::viewCollageFunction);


    layoutOptions = new QComboBox(this);
    layoutOptions->addItem("Одно изображение");
    layoutOptions->addItem("Два изображения горизонтально");
    layoutOptions->addItem("Четыре изображения в сетке 2x2");
    layoutOptions->addItem("Шесть изображений в сетке 2x3");
    connect(layoutOptions, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MedicineWindow::addCollageFunction);

    mainlayout->addWidget(loadImagesButton);
    mainlayout->addWidget(saveCollageButton);
    mainlayout->addWidget(viewCollageButton);
    mainlayout->addWidget(layoutOptions);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(imageLabel);
    mainlayout->addWidget(scrollArea);

    setLayout(mainlayout);

    setFixedSize(800, 800);

    currentLayout = OneImage1;
}

void MedicineWindow::loadImagesFunction()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Выберите медицинские изображения", "", "Изображения (*.png *.jpg *.bmp);;Все файлы (*)");

    if (fileNames.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Не выбраны изображения.");
        return;
    }

    images.clear();
    for (const QString &fileName : fileNames) {
        QFileInfo fileInfo(fileName);
        QString ext = fileInfo.suffix().toLower();
        if (!(ext == "png" || ext == "jpg" || ext == "bmp" || ext == "jpeg" || ext == "gif")) {
            QMessageBox::warning(this, "Предупреждение", "Выбран файл с недопустимым расширением. Пожалуйста, выберите файл в поддерживаемом формате (PNG, JPG, BMP, JPEG, GIF).");
            return;
        }

        QPixmap pixmap(fileName);
        if (pixmap.isNull()) {
            QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение: " + fileName);
            return;
        }

        images.push_back(pixmap);
    }

    addCollageFunction();
}

void MedicineWindow::saveCollageFunction()
{
    if (images.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Нет изображений для сохранения.");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Сохранить коллаж", "", "Изображения (*.png)");

    if (savePath.isEmpty()) {
        return;
    }

    QPixmap collage;
    int fixedWidth = imageLabel->width();
    int fixedHeight = imageLabel->height();

    switch (currentLayout) {
    case OneImage1:
        if (!images.isEmpty()) {
            QPixmap scaledImage = images.first().scaled(imageLabel->size(), Qt::KeepAspectRatio);
            imageLabel->setPixmap(scaledImage);
            collage = scaledImage;
        }
        break;
    case TwoImagesHorizontal11:
        if (images.size() >= 2) {
            collage = QPixmap(fixedWidth * 2, fixedHeight);
            collage.fill(Qt::white);

            QPainter painter(&collage);
            painter.drawPixmap(0, 0, images[0].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
            painter.drawPixmap(fixedWidth, 0, images[1].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
        }
        break;
    case FourImagesGrid22:
        if (images.size() >= 4) {
            collage = QPixmap(fixedWidth * 2, fixedHeight * 2);
            collage.fill(Qt::white);

            QPainter painter(&collage);
            for (int i = 0; i < qMin(4, images.size()); ++i) {
                int row = i / 2;
                int col = i % 2;
                painter.drawPixmap(col * fixedWidth, row * fixedHeight, images[i].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
            }
        }
        break;
    case SixImagesGrid23:
        if (images.size() >= 6) {
            collage = QPixmap(fixedWidth * 2, fixedHeight * 3);
            collage.fill(Qt::white);

            QPainter painter(&collage);
            for (int i = 0; i < qMin(6, images.size()); ++i) {
                int row = i / 2;
                int col = i % 2;
                painter.drawPixmap(col * fixedWidth, row * fixedHeight, images[i].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
            }
        }
        break;
    }

    if (collage.save(savePath)) {
        QMessageBox::information(this, "Сохранение", "Коллаж успешно сохранен.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить коллаж.");
    }
}

void MedicineWindow::addCollageFunction()
{
    currentLayout = static_cast<LayoutType>(layoutOptions->currentIndex());

    int fixedWidth = imageLabel->width();
    int fixedHeight = imageLabel->height();

    switch (currentLayout) {
    case OneImage1:
        if (!images.isEmpty()) {
            QPixmap scaledImage = images.first().scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio);
            imageLabel->setPixmap(scaledImage);
        }
        break;
    case TwoImagesHorizontal11:
        if (images.size() >= 2) {
            int halfWidth = fixedWidth / 2;

            QPixmap collage(fixedWidth, fixedHeight);
            collage.fill(Qt::white);

            QPainter painter(&collage);

            QPixmap scaledImage1 = images[0].scaledToWidth(halfWidth);
            painter.drawPixmap(0, 0, scaledImage1);

            QPixmap scaledImage2 = images[1].scaledToWidth(halfWidth);
            painter.drawPixmap(halfWidth, 0, scaledImage2);

            imageLabel->setPixmap(collage);
        }
        break;
    case FourImagesGrid22:
        if (images.size() >= 4) {
            int imagesPerRow = 2;
            int imagesPerColumn = 2;

            int cellWidth = fixedWidth / imagesPerRow;
            int cellHeight = fixedHeight / imagesPerColumn;

            QPixmap collage(fixedWidth, fixedHeight);
            collage.fill(Qt::white);

            QPainter painter(&collage);
            for (int i = 0; i < qMin(imagesPerRow * imagesPerColumn, images.size()); ++i) {
                int row = i / imagesPerRow;
                int col = i % imagesPerRow;

                int xOffset = col * cellWidth;
                int yOffset = row * cellHeight;

                painter.drawPixmap(xOffset, yOffset, images[i].scaled(cellWidth, cellHeight, Qt::KeepAspectRatio));
            }

            imageLabel->setPixmap(collage);
        }
        break;
    case SixImagesGrid23:
        if (images.size() >= 6) {
            int imagesPerRow = 2;
            int imagesPerColumn = 3;

            int cellWidth = fixedWidth / imagesPerRow;
            int cellHeight = fixedHeight / imagesPerColumn;

            QPixmap collage(fixedWidth, fixedHeight);
            collage.fill(Qt::white);

            QPainter painter(&collage);
            for (int i = 0; i < qMin(imagesPerRow * imagesPerColumn, images.size()); ++i) {
                int row = i / imagesPerRow;
                int col = i % imagesPerRow;
                painter.drawPixmap(col * cellWidth, row * cellHeight, images[i].scaled(cellWidth, cellHeight, Qt::KeepAspectRatio));
            }

            imageLabel->setPixmap(collage);
        }
        break;
    }
}


void MedicineWindow::viewCollageFunction() {
    if (images.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Нет изображений для просмотра.");
        return;
    }

    QString savePath;

    if (currentLayout == OneImage1 || currentLayout == TwoImagesHorizontal11 || currentLayout == FourImagesGrid22 || currentLayout == SixImagesGrid23) {
        savePath = QFileDialog::getSaveFileName(this, "Сохранить коллаж", "", "Изображения (*.png)");

        if (savePath.isEmpty()) {
            return;
        }

        QPixmap collage;
        int fixedWidth = imageLabel->width();
        int fixedHeight = imageLabel->height();

        if (QFileInfo::exists(savePath)) {
            collage = QPixmap(savePath);
        } else {
            switch (currentLayout) {
            case OneImage1:
                if (!images.isEmpty()) {
                    collage = images.first().scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio);
                }
                break;
            case TwoImagesHorizontal11:
                if (images.size() >= 2) {
                    collage = QPixmap(fixedWidth * 2, fixedHeight);
                    collage.fill(Qt::white);

                    QPainter painter(&collage);
                    painter.drawPixmap(0, 0, images[0].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
                    painter.drawPixmap(fixedWidth, 0, images[1].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
                }
                break;
            case FourImagesGrid22:
                if (images.size() >= 4) {
                    collage = QPixmap(fixedWidth * 2, fixedHeight * 2);
                    collage.fill(Qt::white);

                    QPainter painter(&collage);
                    for (int i = 0; qMin(4, images.size()); ++i) {
                        int row = i / 2;
                        int col = i % 2;
                        painter.drawPixmap(col * fixedWidth, row * fixedHeight, images[i].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
                    }
                }
                break;
            case SixImagesGrid23:
                if (images.size() >= 6) {
                    collage = QPixmap(fixedWidth * 2, fixedHeight * 3);
                    collage.fill(Qt::white);

                    QPainter painter(&collage);
                    for (int i = 0; qMin(6, images.size()); ++i) {
                        int row = i / 2;
                        int col = i % 2;
                        painter.drawPixmap(col * fixedWidth, row * fixedHeight, images[i].scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio));
                    }
                }
                break;
            }

            if (!collage.save(savePath)) {
                QMessageBox::warning(this, "Ошибка", "Не удалось сохранить коллаж.");
                return;
            }
        }
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(savePath));
}
