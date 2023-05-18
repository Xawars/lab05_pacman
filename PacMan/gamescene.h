#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QElapsedTimer>
#include "maze.h"
#include "pacman.h"

class QGraphicsPixmapItem;
class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr);

private slots:
    void loop();
    void restart();

private:
    void loadPixmap();
    void initMaze();
    void initPacman();
    void renderMaze();
    void renderPacman();

    bool pacmanCanMove();
    void teleportTunnels(Entity *entity);


    // Visual Game Elements
    QPixmap m_mazePixmap;
    QPixmap m_mazePixmaps[32];
    QGraphicsPixmapItem *m_mazePixmapItems[Maze::MazeWidth][Maze::MazeHeight];
    Maze m_mazeObj;
    Pacman *m_pacman;

    // To server frame
    int currentFrame;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime, m_loopTime;
    const float m_loopSpeed;

};

#endif // GAMESCENE_H
