#include "mainwindow.h"
#include "scripteditor.h"
#include <QMenuBar>
#include <QToolBar>
#include <QTreeWidget>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#ifdef QT_3DCORE_LIB
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QPointLight>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    createDockWindows();
    setup3DView();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi()
{
    setWindowTitle("𓊹 Ra Engine - Pharaoh Game Creator");
    resize(1200, 800);

    // قائمة رئيسية
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("𓂀 ملف");
    fileMenu->addAction("مشروع جديد");
    fileMenu->addAction("فتح مشروع");
    fileMenu->addAction("حفظ");
    fileMenu->addSeparator();
    fileMenu->addAction("خروج");

    QMenu *editMenu = menuBar->addMenu("𓃀 تعديل");
    QMenu *viewMenu = menuBar->addMenu("𓆣 عرض");
    QMenu *projectMenu = menuBar->addMenu("𓅓 مشروع");
    QMenu *helpMenu = menuBar->addMenu("𓃭 مساعدة");

    setMenuBar(menuBar);

    // شريط الأدوات
    QToolBar *toolBar = new QToolBar(this);
    QAction *runAction = toolBar->addAction("تشغيل");
    QAction *exportAction = toolBar->addAction("تصدير");
    QAction *backAction = toolBar->addAction("العودة");
    addToolBar(toolBar);

    connect(runAction, &QAction::triggered, this, &MainWindow::onRunGame);
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExport);
}

void MainWindow::createDockWindows()
{
    // لوحة المشهد (يسار)
    sceneDock = new QDockWidget("مشهد الآلهة", this);
    sceneDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    sceneTree = new QTreeWidget();
    QStringList headers;
    headers << "الكائنات";
    sceneTree->setHeaderLabels(headers);
    sceneTree->addTopLevelItem(new QTreeWidgetItem(QStringList() << "𓁹 رع (الإضاءة)"));
    sceneTree->addTopLevelItem(new QTreeWidgetItem(QStringList() << "𓅓 جب (الأرض)"));
    sceneTree->addTopLevelItem(new QTreeWidgetItem(QStringList() << "𓃀 نوت (السماء)"));
    sceneDock->setWidget(sceneTree);
    addDockWidget(Qt::LeftDockWidgetArea, sceneDock);

    // لوحة الفاحص (يمين)
    inspectorDock = new QDockWidget("خصائص الكائن", this);
    QWidget *inspectorWidget = new QWidget();
    QVBoxLayout *inspectorLayout = new QVBoxLayout(inspectorWidget);

    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("الاسم:"));
    nameLayout->addWidget(new QLineEdit("خپري (القمر)"));
    inspectorLayout->addLayout(nameLayout);

    QHBoxLayout *posXLayout = new QHBoxLayout();
    posXLayout->addWidget(new QLabel("الموقع X:"));
    posXLayout->addWidget(new QLineEdit("12.5"));
    inspectorLayout->addLayout(posXLayout);

    QHBoxLayout *posYLayout = new QHBoxLayout();
    posYLayout->addWidget(new QLabel("الموقع Y:"));
    posYLayout->addWidget(new QLineEdit("-3.2"));
    inspectorLayout->addLayout(posYLayout);

    QPushButton *addScriptBtn = new QPushButton("𓏏 إرفاق بردية (Script)");
    connect(addScriptBtn, &QPushButton::clicked, this, &MainWindow::onAddScript);
    inspectorLayout->addWidget(addScriptBtn);

    inspectorWidget->setLayout(inspectorLayout);
    inspectorDock->setWidget(inspectorWidget);
    addDockWidget(Qt::RightDockWidgetArea, inspectorDock);

    // محرر النصوص (أسفل)
    consoleDock = new QDockWidget("محرر البرديات", this);
    scriptEditor = new ScriptEditor(this);
    consoleDock->setWidget(scriptEditor);
    addDockWidget(Qt::BottomDockWidgetArea, consoleDock);
}

void MainWindow::setup3DView()
{
#ifdef QT_3DCORE_LIB
    // نافذة 3D باستخدام Qt3D
    Qt3DExtras::Qt3DWindow *view3D = new Qt3DExtras::Qt3DWindow();
    view3D->defaultFrameGraph()->setClearColor(QColor(0x11, 0x20, 0x2b));

    // إعداد الكاميرا
    Qt3DRender::QCamera *camera = view3D->camera();
    camera->setPosition(QVector3D(5, 5, 10));
    camera->setViewCenter(QVector3D(0, 1, 0));

    // إنشاء المشهد
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // إضاءة
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(rootEntity);
    light->setColor(QColor(0xff, 0xaa, 0x33));
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(QVector3D(3, 5, 2));
    rootEntity->addComponent(light);
    rootEntity->addComponent(lightTransform);

    // أرضية
    Qt3DCore::QEntity *ground = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCuboidMesh *groundMesh = new Qt3DExtras::QCuboidMesh();
    groundMesh->setXExtent(20);
    groundMesh->setYExtent(1);
    groundMesh->setZExtent(20);
    Qt3DExtras::QPhongMaterial *groundMat = new Qt3DExtras::QPhongMaterial();
    groundMat->setAmbient(QColor(0x9e, 0x7b, 0x4a));
    Qt3DCore::QTransform *groundTransform = new Qt3DCore::QTransform();
    groundTransform->setTranslation(QVector3D(0, -0.5, 0));
    ground->addComponent(groundMesh);
    ground->addComponent(groundMat);
    ground->addComponent(groundTransform);

    // هرم بسيط
    Qt3DCore::QEntity *pyramid = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QConeMesh *pyramidMesh = new Qt3DExtras::QConeMesh();
    pyramidMesh->setRadius(2);
    pyramidMesh->setLength(3);
    Qt3DExtras::QPhongMaterial *pyramidMat = new Qt3DExtras::QPhongMaterial();
    pyramidMat->setAmbient(QColor(0xc4, 0xa2, 0x4b));
    Qt3DCore::QTransform *pyramidTransform = new Qt3DCore::QTransform();
    pyramidTransform->setTranslation(QVector3D(4, 1.5, -3));
    pyramid->addComponent(pyramidMesh);
    pyramid->addComponent(pyramidMat);
    pyramid->addComponent(pyramidTransform);

    view3D->setRootEntity(rootEntity);

    // إضافة الـ 3D view إلى النافذة المركزية
    setCentralWidget(QWidget::createWindowContainer(view3D));
#else
    QLabel *placeholder = new QLabel("عرض 3D غير متاح (قم بتثبيت Qt3D)", this);
    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setStyleSheet("background-color: #0f1a1f; color: #b4944a;");
    setCentralWidget(placeholder);
#endif
}

void MainWindow::onRunGame()
{
    QMessageBox::information(this, "تشغيل", "بدء تشغيل المشروع...");
}

void MainWindow::onExport()
{
    QMessageBox::information(this, "تصدير", "تم تصدير المشروع إلى Android (محاكاة)");
}

void MainWindow::onAddScript()
{
    scriptEditor->addNewScript();
}