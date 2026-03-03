#include "launcherdialog.h"
#include "projectwizarddialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

LauncherDialog::LauncherDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("𓊹 Ra Engine 𓊹");
    setFixedSize(500, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);

    projectList = new QListWidget(this);
    layout->addWidget(projectList);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    newBtn = new QPushButton("مشروع جديد", this);
    openBtn = new QPushButton("فتح مشروع", this);
    deleteBtn = new QPushButton("حذف مشروع", this);
    runBtn = new QPushButton("تشغيل", this);

    btnLayout->addWidget(newBtn);
    btnLayout->addWidget(openBtn);
    btnLayout->addWidget(deleteBtn);
    btnLayout->addWidget(runBtn);
    layout->addLayout(btnLayout);

    connect(newBtn, &QPushButton::clicked, this, &LauncherDialog::onNewProject);
    connect(openBtn, &QPushButton::clicked, this, &LauncherDialog::onOpenProject);
    connect(deleteBtn, &QPushButton::clicked, this, &LauncherDialog::onDeleteProject);
    connect(runBtn, &QPushButton::clicked, this, &LauncherDialog::onRunProject);

    loadProjects();
}

LauncherDialog::~LauncherDialog() {}

void LauncherDialog::loadProjects()
{
    QFile file("projects.json");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray projects = doc.array();

    projectList->clear();
    for (const QJsonValue &val : projects) {
        QJsonObject obj = val.toObject();
        QString name = obj["name"].toString();
        QString quality = obj["quality"].toString();
        projectList->addItem(name + " (" + quality + ")");
    }
    file.close();
}

void LauncherDialog::onNewProject()
{
    ProjectWizardDialog wizard(this);
    if (wizard.exec() == QDialog::Accepted) {
        loadProjects(); // إعادة تحميل القائمة
    }
}

void LauncherDialog::onOpenProject()
{
    if (projectList->currentItem()) {
        accept(); // فتح النافذة الرئيسية
    } else {
        QMessageBox::warning(this, "تنبيه", "اختر مشروعاً أولاً");
    }
}

void LauncherDialog::onDeleteProject()
{
    if (!projectList->currentItem())
        return;

    // تنفيذ الحذف
    QMessageBox::information(this, "حذف", "تم حذف المشروع (محاكاة)");
}

void LauncherDialog::onRunProject()
{
    QMessageBox::information(this, "تشغيل", "سيتم تشغيل المشروع على المحاكي");
}