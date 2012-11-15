#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
    int m_veggie;
    int m_location;
    QString m_sSettingsFile;
    void load();

private slots:
    void locationChanged(int state);
    void veggieChanged(int state);
    void save();
};

#endif // SETTINGSDIALOG_H
