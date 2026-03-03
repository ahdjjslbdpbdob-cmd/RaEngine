#include "projectwizarddialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

ProjectWizardDialog::ProjectWizardDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("مشروع جديد");
    setFixedSize(450, 250);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // اسم المشروع
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("اسم اللعبة:"));
    nameEdit = new QLineEdit("لعبة الفرعون");
    nameLayout->addWidget(nameEdit);
    layout->addLayout(nameLayout);

    // جودة الرسوم
    QHBoxLayout *qualityLayout = new QHBoxLayout();
    qualityLayout->addWidget(new QLabel("جودة الرسوم:"));
    qualityCombo = new QComboBox();
    qualityCombo->addItem("عالية (ذهب)");
    qualityCombo->addItem("متوسطة (فضة)");
    qualityCombo->addItem("منخفضة (بردي)");
    qualityLayout->addWidget(qualityCombo);
    layout->addLayout(qualityLayout);

    // مسار الحفظ
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(new QLabel("مسار الحفظ:"));
    pathEdit = new QLineEdit("/storage/emulated/0/Download/RaProjects/");
    browseBtn = new QPushButton("تصفح");
    pathLayout->addWidget(pathEdit);
    pathLayout->addWidget(browseBtn);
    layout->addLayout(pathLayout);

    // الأزرار
    QHBoxLayout *btnLayout = new QHBoxLayout();
    okBtn = new QPushButton("إنشاء");
    cancelBtn = new QPushButton("إلغاء");
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    connect(browseBtn, &QPushButton::clicked, this, &ProjectWizardDialog::onBrowse);
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void ProjectWizardDialog::onBrowse()
{
    QString dir = QFileDialog::getExistingDirectory(this, "اختر مجلد الحفظ");
    if (!dir.isEmpty())
        pathEdit->setText(dir);
}

QString ProjectWizardDialog::projectName() const
{
    return nameEdit->text();
}

QString ProjectWizardDialog::quality() const
{
    return qualityCombo->currentText();
}

QString ProjectWizardDialog::savePath() const
{
    return pathEdit->text();
}