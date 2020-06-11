#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qt3DAnimation/QAnimationAspect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_view(new Qt3DExtras::Qt3DWindow)
    , m_rootEntity(new Qt3DCore::QEntity)
{
    m_ui->setupUi(this);
    m_view->setRootEntity(m_rootEntity);
    m_view->registerAspect(new Qt3DAnimation::QAnimationAspect(m_rootEntity));
    m_mainScene = new Scene(m_view, m_rootEntity);
    setCentralWidget(QWidget::createWindowContainer(m_view));
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_view;
    delete m_rootEntity;
}

