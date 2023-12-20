#include "medicine.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MedicineWindow medicinewindow;
    medicinewindow.show();
    return a.exec();
}
