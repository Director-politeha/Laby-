#ifndef MEDICINEWINDOW_H
#define MEDICINEWINDOW_H

#include "qlabel.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVector>

class MedicineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineWindow(QWidget *parent = nullptr);

private slots:
    void loadImagesFunction();
    void saveCollageFunction();
    void viewCollageFunction();
    void addCollageFunction();


private:
    QVBoxLayout *mainLayout;
    QLabel *imageLabel;
    QComboBox *layoutOptions;
    enum LayoutType {
        OneImage1,
        TwoImagesHorizontal11,
        FourImagesGrid22,
        SixImagesGrid23
    };
    LayoutType currentLayout;
    QVector<QPixmap> images;
    int currentImageIndex;

};

#endif // MEDICINEWINDOW_H
