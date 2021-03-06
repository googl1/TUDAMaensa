/**
 *  This file is part of TUDA Maensa.
 *
 *  TUDA Maensa is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TUDA Maensa is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TUDA Maensa.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <QDebug>
#include <QFile>
#include <QMenuBar>
#include <QSettings>
#include <QStringBuilder>
#include <QLocale>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webparse.h"
#include "settingsdialog.h"

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont f = ui->tableWidget->font();
    f.setPixelSize(23);
    ui->tableWidget->setFont(f);

    ui->tableWidget->setWordWrap(true);

    QString applicationPath = QApplication::applicationDirPath();
    if (applicationPath.endsWith("lib"))
        m_sSettingsFile = applicationPath % "/../tudamaensa.conf";
    else
        m_sSettingsFile = applicationPath % "/tudamaensa.conf";

    //carstens android-color-fix
    int r = 0; int g = 0; int b = 0;
    ui->tableWidget->palette().color(ui->tableWidget->backgroundRole())
            .getRgb(&r, &g, &b);
    ui->tableWidget->setStyleSheet(QString("QTableWidget { background" \
                                           "-color: rgb(%1,%2,%3) }")
                                   .arg(r).arg(g).arg(b));

    //fill menuBar
    m_veggie = 0;
    checkVeggie = new QAction(tr("No meat please"), this);
    checkVeggie->setCheckable(true);
    connect(checkVeggie, SIGNAL(triggered(bool)), this,
            SLOT(veggieTriggered(bool)));
    menuBar()->addAction(checkVeggie);

    m_vegan = 0;
    checkVegan = new QAction(tr("Fuck! I'm vegan."), this);
    checkVegan->setCheckable(true);
    connect(checkVegan, SIGNAL(triggered(bool)), this,
            SLOT(veganTriggered(bool)));
    menuBar()->addAction(checkVegan);

    QAction *settingsButton = new QAction(tr("Settings"), this);
    settingsButton->setCheckable(false);
    connect(settingsButton, SIGNAL(triggered(bool)), this,
            SLOT(menuButtonClicked()));
    menuBar()->addAction(settingsButton);

    QAction *refreshButton = new QAction(tr("Refresh"), this);
    settingsButton->setCheckable(false);
    connect(refreshButton, SIGNAL(triggered(bool)), this,
            SLOT(refreshClicked()));
    menuBar()->addAction(refreshButton);

    load();
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
    parser = new WebParse(m_location);
    setList(parser->download());
}

/**
 * @brief MainWindow::setList displays the results
 * @param list results as list of menues
 */
void MainWindow::setList(QList<Menue> list)
{
    QTableWidgetItem *name;
    QTableWidgetItem *location;
    QTableWidgetItem *price;
    QTableWidgetItem *type;
    QString typePic;
    int v = 0;

    if (!parser->getDay().isEmpty())
         ui->label_day->setText(parser->getLocationName()
                                % " - " % parser->getDay());
    else if(list.isEmpty()) {
        ui->label_day->setText("No crappy cafeteria food today!");
        return;
    }

    ui->tableWidget->setRowCount(list.length());

    for (int i = 0; i < list.length(); i++) {
        m_jump = 0;
        if (m_veggie && !list.at(i).isVeggie()) {
            v++;
            ui->tableWidget->setRowCount(list.length() - v);
            m_jump = 1;
            continue;
        }
        if(m_vegan && !list.at(i).isVegan() && !m_jump) {
            v++;
            ui->tableWidget->setRowCount(list.length() - v);
            continue;
        }

        name = new QTableWidgetItem();
        location = new QTableWidgetItem();
        price = new QTableWidgetItem();
        type = new QTableWidgetItem();

        if (!list.at(i).getType().isEmpty()) {
            typePic = QString(":/img/%1pict_k.png")
                    .arg(list.at(i).getType());
            if (!QFile::exists(typePic))
                qDebug() << QString("Image %1 not found.")
                            .arg(typePic);
            else
                type->setIcon(QIcon(QPixmap(typePic)));
        }

        name->setText(list.at(i).getName());
        location->setText(list.at(i).getLocation());
        price->setText(list.at(i).getPrice());

        ui->tableWidget->setItem(i - v, 1, name);
        ui->tableWidget->setItem(i - v, 2, location);
        ui->tableWidget->setItem(i - v, 3, price);
        ui->tableWidget->setItem(i - v, 0, type);
    }

    ui->tableWidget->resizeColumnsToContents();
    int a = ui->tableWidget->columnWidth(0)
            + ui->tableWidget->columnWidth(2)
            + ui->tableWidget->columnWidth(3);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()
                                    - a - 40);
    ui->tableWidget->resizeRowsToContents();
}

void MainWindow::redrawTable()
{
    parser->setLocation(m_location);
    ui->tableWidget->clearContents();
    setList(parser->download());
}

void MainWindow::veggieTriggered(bool veg)
{
    m_veggie = veg;
    redrawTable();
}

void MainWindow::veganTriggered(bool vgn)
{
    m_vegan = vgn;
    redrawTable();
}

void MainWindow::menuButtonClicked()
{
    settingsDialog = new SettingsDialog();
    settingsDialog->show();
}

void MainWindow::refreshClicked()
{
    load();
    redrawTable();
}

void MainWindow::load()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    m_veggie = settings.value("veggie", 0).toInt();
    m_location = settings.value("location", 0).toInt();
    m_vegan = settings.value("vegan", 0).toInt();

    checkVegan->setChecked(m_vegan);
    checkVeggie->setChecked(m_veggie);

    settings.deleteLater();
}
