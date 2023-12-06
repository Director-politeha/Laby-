#include "mainwindow.h"

Okno ::Okno(QWidget  *parent)
    : QWidget(parent)
{
    Error= new  QPushButton("Show Error");
    Warning = new QPushButton("Show Warning");
    Information = new  QPushButton("Show Information");
    m_hLayout = new QHBoxLayout(this);

    m_hLayout->addWidget(Error);
    m_hLayout->addWidget(Warning);
    m_hLayout->addWidget(Information);

    connect(Error, &QPushButton::clicked,this,  &Okno::error);
    connect(Warning, &QPushButton::clicked,this,  &Okno::warning);
    connect(Information, &QPushButton::clicked,this,  &Okno::information);

}

Okno::~Okno() {}

void Okno::error(){
    QMessageBox::critical(this, "Копылов", "Ахтунг");
}

void Okno::warning(){
    QMessageBox::warning(this, "Копылов","Warning");
}

void Okno::information(){
    QMessageBox::information(this, "Копылов", "Добро пожаловать");
}
