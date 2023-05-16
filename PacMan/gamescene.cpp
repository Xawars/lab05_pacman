#include "gamescene.h"
#include "resources.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}
{
    loadPixmap();
    setSceneRect(0,0, Resources::Resolution.width(), Resources::Resolution.height());
    setBackgroundBrush(QBrush(Resources::BGColor));
    initMaze();
    renderMaze();
}

void GameScene::loadPixmap()
{
    if (m_mazePixmap.load(Resources::PathToMazePixmap))
    {
        qDebug() << "Maze is loaded with success";
    } else {
        qFatal("Maze is not loaded");
    }
}

void GameScene::initMaze()
{
    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++)
        {
            m_mazePixmaps[index] = m_mazePixmap.copy(i * Resources::MazeTileSize, j * Resources::MazeTileSize,
                                                     Resources::MazeTileSize, Resources::MazeTileSize);
            index++;
        }
    }

    for (int i = 0; i < int(Maze::MazeWidth); i++)
    {
        for (int j = 0; j < int(Maze::MazeHeight); j++)
        {
            m_mazePixmapItems[i][j] = new QGraphicsPixmapItem();
            m_mazePixmapItems[i][j]->setPixmap(m_mazePixmaps[m_mazeObj.tiles(i, j)]);
            m_mazePixmapItems[i][j]->setPos(i*Resources::MazeTileSize, j*Resources::MazeTileSize);
            addItem(m_mazePixmapItems[i][j]);
        }
    }
}

void GameScene::renderMaze()
{
    for (int i = 0; i < int(Maze::MazeWidth); i++)
    {
        for (int j = 0; j < int(Maze::MazeHeight); j++)
        {
            m_mazePixmapItems[i][j]->setPixmap(m_mazePixmaps[m_mazeObj.tiles(i, j)]);
        }
    }
}
