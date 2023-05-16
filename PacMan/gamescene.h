#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "maze.h"

class QGraphicsPixmapItem;
class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr);

private:
    void loadPixmap();
    void initMaze();
    void renderMaze();


    // Visual Game Elements
    QPixmap m_mazePixmap;
    QPixmap m_mazePixmaps[32];
    QGraphicsPixmapItem *m_mazePixmapItems[Maze::MazeWidth][Maze::MazeHeight];
    Maze m_mazeObj;
};

#endif // GAMESCENE_H
