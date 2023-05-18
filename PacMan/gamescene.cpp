#include "gamescene.h"
#include "resources.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent},
    m_loopTime(0.0f),
    m_loopSpeed(int(1000.0f/Resources::FPS))
{
    srand(time(0));
    loadPixmap();
    setSceneRect(0,0, Resources::Resolution.width(), Resources::Resolution.height());
    setBackgroundBrush(QBrush(Resources::BGColor));
    initMaze();
    renderMaze();
    initPacman();
    renderPacman();

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/Resources::FPS));
    m_elapsedTimer.start();
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;

    if (m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;
        if (pacmanCanMove()) {
            m_pacman->move();
            m_pacman->setPos(m_pacman->getScreenPosX(), m_pacman->getScreenPosY());
        } else {
            m_pacman->stop();
        }

        if (m_mazeObj.isIntersection(m_pacman->getTileX(), m_pacman->getTileY()))
        {
            m_pacman->stop();
        }

        renderMaze();
        teleportTunnels(m_pacman);
    }
}

void GameScene::restart()
{
    m_pacman->teleport(13, 16);
    m_pacman->clearQueueDirection();
}

void GameScene::loadPixmap()
{
    if (m_mazePixmap.load(Resources::PathToMazePixmap))
    {
        qDebug() << "Maze is loaded with success";
    } else {
        qFatal("Maze is not loaded");
    }

    QPixmap pacmanPixmap;
    if (pacmanPixmap.load(Resources::PathToPacmanPixmap))
    {
        qDebug() << "Pacman is loaded success";
    } else {
        qFatal("Pacman is loaded success");
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

void GameScene::initPacman()
{
    m_pacman = new Pacman();
    m_pacman->setFocus();
    m_pacman->setPos(m_pacman->getScreenPosX(), m_pacman->getScreenPosY());
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

void GameScene::renderPacman()
{
    addItem(m_pacman);
}

bool GameScene::pacmanCanMove()
{
    if (!m_pacman->getDirections().empty())
    {
        switch (m_pacman->getDirections().front())
        {
        case Resources::Direction::Up:
            return !m_mazeObj.tileBlocksEntity(m_pacman->getTileX(), m_pacman->getTileY() - 1);
            break;
        case Resources::Direction::Down:
            return !m_mazeObj.tileBlocksEntity(m_pacman->getTileX(), m_pacman->getTileY() + 1);
            break;
        case Resources::Direction::Left:
            return !m_mazeObj.tileBlocksEntity(m_pacman->getTileX() - 1, m_pacman->getTileY());
            break;
        case Resources::Direction::Right:
            return !m_mazeObj.tileBlocksEntity(m_pacman->getTileX() + 1, m_pacman->getTileY());
            break;
        case Resources::Direction::Unset:
            break;
        }
    }
    return true;
}

void GameScene::teleportTunnels(Entity* entity)
{
    if (entity->getTileX() == 0 && entity->getTileY() == 17)
        entity->teleport(26, 17);
    else if (entity->getTileX() == 27 && entity->getTileY() == 17)
        entity->teleport(1, 17);
}
