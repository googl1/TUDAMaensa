#include <QSettings>
#include <QStringBuilder>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    m_sSettingsFile = QApplication::applicationDirPath() % "/tudamaensa.conf";
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
}

void SettingsDialog::locationChanged(int state)
{
    m_location = state;
}

void SettingsDialog::save()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    settings.setValue("location", m_location);
    settings.setValue("veggie", m_veggie);

    settings.deleteLater();

    this->deleteLater();
}

void SettingsDialog::load()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    m_veggie = settings.value("veggie", 0).toInt();
    m_location = settings.value("location", 0).toInt();

    settings.deleteLater();
}
