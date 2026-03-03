#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;
class QDockWidget;
class QTreeWidget;
class ScriptEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRunGame();
    void onExport();
    void onAddScript();

private:
    void setupUi();
    void createDockWindows();
    void setup3DView();

    QDockWidget *sceneDock;
    QDockWidget *inspectorDock;
    QDockWidget *consoleDock;
    QTreeWidget *sceneTree;
    ScriptEditor *scriptEditor;
    QWidget *viewport; // يمكن أن يكون QWidget لـ 2D/3D
};

#endif // MAINWINDOW_H