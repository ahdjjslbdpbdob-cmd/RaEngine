#ifndef LAUNCHERDIALOG_H
#define LAUNCHERDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LauncherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LauncherDialog(QWidget *parent = nullptr);
    ~LauncherDialog();

private slots:
    void onNewProject();
    void onOpenProject();
    void onDeleteProject();
    void onRunProject();

private:
    void loadProjects();

    QListWidget *projectList;
    QPushButton *newBtn;
    QPushButton *openBtn;
    QPushButton *deleteBtn;
    QPushButton *runBtn;
};

#endif // LAUNCHERDIALOG_H