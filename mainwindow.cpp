#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webparse.h"

#include <QTextCodec>
#include <QDebug>
#include <QFile>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TUDAMaensa");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDay(QString day)
{
    ui->label_day->setText(day);
}

void MainWindow::work()
{
    parser = new WebParse("Stadtmitte");
    setList(parser->download());
}

void MainWindow::setList(QList<Menue> list)
{
    QDateTime *date = new QDateTime();
    if (!parser->getDay().isEmpty())
         ui->label_day->setText(parser->getDay());
    else if(date->date().dayOfWeek() < 3)
        ui->label_day->setText("It's weekend, no crappy cafeteria food!");

    ui->tableWidget->setRowCount(list.length());

    for (int i = 0; i < list.length(); i++) {
        QTableWidgetItem *name = new QTableWidgetItem();
        QTableWidgetItem *location = new QTableWidgetItem();
        QTableWidgetItem *price = new QTableWidgetItem();
        QTableWidgetItem *type = new QTableWidgetItem();

        QString typeName(list.at(i).getType());
        if (!QFile::exists(QString(":/img/%1pict_k.png").arg(typeName)))
            qDebug() << QString("Image :/img/%1pict_k.png not found.").arg(typeName);
        else
            type->setIcon(QIcon(QPixmap(QString(":/img/%1pict_k.png").arg(typeName))));

        name->setText(list.at(i).getName());
        location->setText(list.at(i).getLocation());
        price->setText(list.at(i).getPrice());

        ui->tableWidget->setItem(i, 1, name);
        ui->tableWidget->setItem(i, 2, location);
        ui->tableWidget->setItem(i, 3, price);
        ui->tableWidget->setItem(i, 0, type);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setColumnWidth(1, 500);
}
