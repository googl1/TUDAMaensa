#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "menue.h"
#include "webparse.h"

namespace Ui {
    class MainWindow;
}

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

private:
    Ui::MainWindow *ui;
    WebParse *parser;

signals:
     void getDone(QList<Menue>);
};

#endif // MAINWINDOW_H
