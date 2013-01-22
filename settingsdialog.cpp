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

    QString applicationPath = QApplication::applicationDirPath();
    if (applicationPath.endsWith("lib"))
        m_sSettingsFile = applicationPath % "/../tudamaensa.conf";
    else
        m_sSettingsFile = applicationPath % "/tudamaensa.conf";

    //carstens andorid-color-fix
    int r = 0; int g = 0; int b = 0;
    ui->locationComboBox->palette().color(ui->locationComboBox
                                          ->backgroundRole())
            .getRgb(&r, &g, &b);
    ui->locationComboBox->setStyleSheet
            (QString("QComboBox QAbstractItemView { background-color:" \
                     "rgb(%1,%2,%3) }").arg(r).arg(g).arg(b));

    //load settings
    load();

    ui->veggieCheckBox->setChecked(m_veggie);
    ui->veganCheckBox->setChecked(m_vegan);
    ui->locationComboBox->setCurrentIndex(m_location);

    connect(ui->veggieCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(veggieChanged(int)));
    connect(ui->veganCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(veganChanged(int)));
    connect(ui->locationComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(locationChanged(int)));
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

void SettingsDialog::veganChanged(int state)
{
    m_vegan = state;
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
    settings.setValue("vegan", m_vegan);

    settings.deleteLater();

    this->deleteLater();
}

void SettingsDialog::load()
{
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    m_veggie = settings.value("veggie", 0).toInt();
    m_vegan = settings.value("vegan", 0).toInt();
    m_location = settings.value("location", 0).toInt();

    settings.deleteLater();
}
