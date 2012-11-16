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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "menue.h"
#include "webparse.h"
#include "settingsdialog.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief The MainWindow class is the main window of TUDAMaensa
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setDay(QString day);
    void work();

private slots:
    void setList(QList<Menue> list);
    void redrawTable();
    void veggieTriggered(bool veg);
    void menuButtonClicked();
    void refreshClicked();

private:
    Ui::MainWindow *ui;
    WebParse *parser;
    QAction *checkVeggie;
    SettingsDialog *settingsDialog;
    QAction *settingsButton;
    QAction *refreshButton;
    QString m_sSettingsFile;
    void load();
    int m_location;
    int m_veggie;

signals:
     void getDone(QList<Menue>);
};

#endif // MAINWINDOW_H
