#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QDebug>
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    m_sSettingsFile = QApplication::applicationDirPath() + ":/tudamaensa.conf";
    qDebug() << QApplication::applicationDirPath().left(1) + ":/tudamaensa.conf";
    load();

    ui->veggieCheckBox->setChecked(m_veggie);
    ui->locationComboBox->setCurrentIndex(m_location);

    connect(ui->veggieCheckBox, SIGNAL(stateChanged(int)), this, SLOT(veggieChanged(int)));
    connect(ui->locationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(locationChanged(int)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::veggieChanged(int state)
{
    m_veggie = state;
    qDebug() << "veggie: " << state;
}

void SettingsDialog::locationChanged(int state)
{
    m_location = state;
    qDebug() << "location: " << state;
}

void SettingsDialog::save()
{
    qDebug() << "save everything, or it will get lost...";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
//    int sVeggie = (m_veggie) ? m_veggie : 0;
//    int sLocation = (m_location) ? m_location : 0;
    settings.setValue("location", m_location);
    settings.setValue("veggie", m_veggie);

    settings.deleteLater();

    this->deleteLater();
}

void SettingsDialog::load()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    m_veggie = settings.value("veggie", 2).toInt();
    m_location = settings.value("location", 2).toInt();

    settings.deleteLater();
}
