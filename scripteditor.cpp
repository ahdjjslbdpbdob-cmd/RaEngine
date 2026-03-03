#include "scripteditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

ScriptEditor::ScriptEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    tabWidget = new QTabWidget(this);
    layout->addWidget(tabWidget);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    saveBtn = new QPushButton("حفظ", this);
    deleteBtn = new QPushButton("حذف", this);
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(deleteBtn);
    layout->addLayout(btnLayout);

    connect(saveBtn, &QPushButton::clicked, this, &ScriptEditor::onSave);
    connect(deleteBtn, &QPushButton::clicked, this, &ScriptEditor::onDelete);

    // إضافة سكريبت افتراضي
    addNewScript("script_ra.gd");
    addNewScript("enemy_ankh.gd");
}

void ScriptEditor::addNewScript(const QString &name)
{
    QTextEdit *editor = new QTextEdit();
    editor->setPlainText("extends RaObject\n\n# بردية جديدة\nfunc _ready():\n    print(\"مرحباً من Ra\")\n");
    tabWidget->addTab(editor, "𓏏 " + name);
}

void ScriptEditor::onSave()
{
    int index = tabWidget->currentIndex();
    if (index >= 0) {
        QTextEdit *editor = qobject_cast<QTextEdit*>(tabWidget->widget(index));
        if (editor) {
            // حفظ المحتوى (محاكاة)
            QMessageBox::information(this, "حفظ", "تم حفظ السكريبت الحالي.");
        }
    }
}

void ScriptEditor::onDelete()
{
    int index = tabWidget->currentIndex();
    if (index >= 0 && tabWidget->count() > 1) {
        tabWidget->removeTab(index);
    } else {
        QMessageBox::warning(this, "حذف", "لا يمكن حذف السكريبت الوحيد.");
    }
}