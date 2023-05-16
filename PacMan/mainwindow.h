#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamescene.h"
#include <QMainWindow>
#include <QGraphicsView>

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
    GameScene *m_gameScene;
    QGraphicsView *m_view;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
