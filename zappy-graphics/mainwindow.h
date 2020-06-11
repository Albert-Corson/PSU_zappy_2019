#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
    Qt3DExtras::Qt3DWindow *m_view;
    Qt3DCore::QEntity *m_rootEntity;
    Scene *m_mainScene;
};
#endif // MAINWINDOW_H
