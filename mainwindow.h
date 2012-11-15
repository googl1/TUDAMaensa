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
