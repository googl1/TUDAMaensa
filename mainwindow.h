#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "menue.h"
#include "webparse.h"

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

private:
    Ui::MainWindow *ui;
    WebParse *parser;
    bool m_veggie;
    QAction *checkVeggie;

signals:
     void getDone(QList<Menue>);
};

#endif // MAINWINDOW_H
