#include <QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // تحميل الأنماط من ملف qss
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        app.setStyleSheet(style);
        styleFile.close();
    }

    // إظهار شاشة الإطلاق أولاً
    LauncherDialog launcher;
    if (launcher.exec() == QDialog::Accepted) {
        // بعد اختيار مشروع، نفتح النافذة الرئيسية
        MainWindow w;
        w.show();
        return app.exec();
    }

    return 0;
}