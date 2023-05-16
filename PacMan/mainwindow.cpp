#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resources.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_gameScene(new GameScene(this))
    , m_view(new QGraphicsView(m_gameScene, this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(m_view);
    resize(Resources::Resolution.width()+2, Resources::Resolution.height()+2);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete m_view;
    delete m_gameScene;
    delete ui;
}

