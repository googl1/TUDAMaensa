#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webparse.h"

#include <QTextCodec>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QMenuBar>
#include <QDockWidget>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setWindowTitle("TUDAMaensa");
    //this->setStyleSheet("background-color: black; border: none; color: white");

    m_veggie = false;
    checkVeggie = new QAction(tr("No meat please"), this);
    checkVeggie->setCheckable(true);
    checkVeggie->setChecked(false);
    connect(checkVeggie, SIGNAL(triggered(bool)), this, SLOT(veggieTriggered(bool)));
    menuBar()->addAction(checkVeggie);

//    QAction *settingsButton = new QAction(tr("Settings"), this);
//    settingsButton->setCheckable(false);
//    connect(settingsButton, SIGNAL(triggered(bool)), this, SLOT(menuButtonClicked()));
//    menuBar()->addAction("Settings");
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::setDay sets the label label_day
 * @param day QString to set in label_day
 */
void MainWindow::setDay(QString day)
{
    ui->label_day->setText(day);
}

/**
 * @brief MainWindow::work starts parsing
 *  and displaying data process
 */
void MainWindow::work()
{
    parser = new WebParse("Stadtmitte");
    setList(parser->download());
}

/**
 * @brief MainWindow::setList displays the results
 * @param list results as list of menues
 */
void MainWindow::setList(QList<Menue> list)
{
    QDateTime *date = new QDateTime();
    QTableWidgetItem *name;
    QTableWidgetItem *location;
    QTableWidgetItem *price;
    QTableWidgetItem *type;
    QString typePic;
    int v = 0;

    if (!parser->getDay().isEmpty())
         ui->label_day->setText(parser->getDay());
    else if(date->date().dayOfWeek() > 5 && list.isEmpty()) {
        ui->label_day->setText("It's weekend, no " \
                               "crappy cafeteria food!");
        //FIXME: test on weekend
        return;
    }

    ui->tableWidget->setRowCount(list.length());

    for (int i = 0; i < list.length(); i++) {

        if (m_veggie && !list.at(i).isVeggie()) {
            v++;
            ui->tableWidget->setRowCount(list.length() - v);
            continue;
        }

        name = new QTableWidgetItem();
        location = new QTableWidgetItem();
        price = new QTableWidgetItem();
        type = new QTableWidgetItem();

        typePic = QString(":/img/%1pict_k.png")
                .arg(list.at(i).getType());
        if (!QFile::exists(typePic))
            qDebug() << QString("Image %1 not found.")
                        .arg(typePic);
        else
            type->setIcon(QIcon(QPixmap(typePic)));

        name->setText(list.at(i).getName());
        location->setText(list.at(i).getLocation());
        price->setText(list.at(i).getPrice());

        ui->tableWidget->setItem(i - v, 1, name);
        ui->tableWidget->setItem(i - v, 2, location);
        ui->tableWidget->setItem(i - v, 3, price);
        ui->tableWidget->setItem(i - v, 0, type);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    //FIXME
    //test
    //old column-width for column 1: 500
    int a = ui->tableWidget->columnWidth(0) + ui->tableWidget->columnWidth(2) + ui->tableWidget->columnWidth(3);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width() - a - 30);
}

void MainWindow::redrawTable()
{
    ui->tableWidget->clearContents();
    setList(parser->download());
}

void MainWindow::veggieTriggered(bool veg)
{
    m_veggie = veg;
    redrawTable();
}

void MainWindow::menuButtonClicked()
{
//   // Qt::DockWidgetArea dwa(0x8);
//    QDockWidget *settings = new QDockWidget(tr("Settings"));
//    settings->addAction(new QAction(tr("test"), this));
//    this->addDockWidget(Qt::BottomDockWidgetArea, settings);
//    //settings->setLayout(QLayout settings));
//    settings->setWidget (new QLabel("test"));
//    settings->show();
}
