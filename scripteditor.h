#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QPushButton>

class ScriptEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptEditor(QWidget *parent = nullptr);

    void addNewScript(const QString &name = "script_ra.gd");

private slots:
    void onSave();
    void onDelete();

private:
    QTabWidget *tabWidget;
    QPushButton *saveBtn;
    QPushButton *deleteBtn;
};

#endif // SCRIPTEDITOR_H