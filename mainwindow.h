#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>

class Okno : public QWidget
{
    Q_OBJECT

public:
    Okno(QWidget *parent=nullptr);
    ~Okno();

private:
    QPushButton *Error;
    QPushButton *Warning;
    QPushButton *Information;
    QHBoxLayout *m_hLayout;

private slots:
    void error();
    void warning();
    void information();

};

#endif // WIDGET_H
