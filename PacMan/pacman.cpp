#include "pacman.h"
#include <QKeyEvent>

Pacman::Pacman()
    : QGraphicsPixmapItem(), Entity(13, 26), m_currentIndex(0)
{
    loadPixmap();
    setPixmap(m_rightPixmap);
    setTransformOriginPoint(Resources::PacmanTileSize, Resources::PacmanTileSize);
    connect(&m_timer, &QTimer::timeout, this, &Pacman::updatePixmap);
    m_timer.start(AnimSpeed);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Pacman::updatePixmap()
{
    if(m_directions.empty())
    {
        setPixmap(m_pacmanPixmap.copy(0,0, Resources::PacmanTileSize, Resources::PacmanTileSize));
        return;
    }

    if(m_directions.front() == Resources::Direction::Up)
    {
        setPixmap(m_upPixmap.copy(m_currentIndex*Resources::PacmanTileSize, 0, Resources::PacmanTileSize, Resources::PacmanTileSize));
    }
    else if(m_directions.front() == Resources::Direction::Right)
    {
        setPixmap(m_rightPixmap.copy(m_currentIndex*Resources::PacmanTileSize, 0, Resources::PacmanTileSize, Resources::PacmanTileSize));
    }
    else if(m_directions.front() == Resources::Direction::Down)
    {
        setPixmap(m_downPixmap.copy(m_currentIndex*Resources::PacmanTileSize, 0, Resources::PacmanTileSize, Resources::PacmanTileSize));
    }
    else if(m_directions.front() == Resources::Direction::Left)
    {
        setPixmap(m_leftPixmap.copy(m_currentIndex*Resources::PacmanTileSize, 0, Resources::PacmanTileSize, Resources::PacmanTileSize));
    }

    m_currentIndex += 1;
    m_currentIndex %= Resources::PacmanCountAnimFrames;
}

void Pacman::loadPixmap()
{
    m_upPixmap    = m_pacmanPixmap.copy(Resources::PacmanUp.x(), Resources::PacmanUp.y(), Resources::PacmanTileSize*Resources::PacmanCountAnimFrames, Resources::PacmanTileSize);
    m_downPixmap  = m_pacmanPixmap.copy(Resources::PacmanDown.x(), Resources::PacmanDown.y(), Resources::PacmanTileSize*Resources::PacmanCountAnimFrames, Resources::PacmanTileSize);
    m_leftPixmap  = m_pacmanPixmap.copy(Resources::PacmanLeft.x(), Resources::PacmanLeft.y(), Resources::PacmanTileSize*Resources::PacmanCountAnimFrames, Resources::PacmanTileSize);
    m_rightPixmap = m_pacmanPixmap.copy(Resources::PacmanRight.x(), Resources::PacmanRight.y(), Resources::PacmanTileSize*Resources::PacmanCountAnimFrames, Resources::PacmanTileSize);
}

void Pacman::clearQueueDirection()
{
    queue<Resources::Direction> clear;
    swap(m_directions, clear);
}

void Pacman::queueDirection(Resources::Direction dir)
{
    if (!m_directions.empty())
    {
        if (int(dir) == -int(m_directions.front()))
        {
            queue<Resources::Direction> clear;
            swap(m_directions, clear);
        }
    }

    if(m_directions.size() < 2)
        m_directions.push(dir);
}

void Pacman::move()
{
    if (!m_directions.empty())
    {
        switch (m_directions.front())
        {
        case Resources::Direction::Up:
            Entity::move(0, -Speed);
            break;
        case Resources::Direction::Down:
            Entity::move(0, Speed);
            break;
        case Resources::Direction::Left:
            Entity::move(-Speed, 0);
            break;
        case Resources::Direction::Right:
            Entity::move(Speed, 0);
            break;
        case Resources::Direction::Unset:

            break;
        }
    }
}

queue<Resources::Direction> Pacman::getDirections()
{
    return m_directions;
}

void Pacman::stop()
{
    if (m_directions.size() > 1)
    {
        if ((int)(m_screenPosX + 8 + Resources::PacmanTileSize/2) % 16 == 0 && (int)(m_screenPosY + 8 + Resources::PacmanTileSize/2) % 16 == 0)
        {
            switch (m_directions.front())
            {
            case Resources::Direction::Up:
                m_directions.pop();
                break;
            case Resources::Direction::Down:
                m_directions.pop();
                break;
            case Resources::Direction::Left:
                m_directions.pop();
                break;
            case Resources::Direction::Right:
                m_directions.pop();
                break;
            case Resources::Direction::Unset:
                m_directions.pop();
                break;
            }
        }
    }
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    if(true)
    {
        switch (event->key()) {
        case Qt::Key_Up:
            queueDirection(Resources::Direction::Up);
            break;
        case Qt::Key_Right:
            queueDirection(Resources::Direction::Right);
            break;
        case Qt::Key_Down:
            queueDirection(Resources::Direction::Down);
            break;
        case Qt::Key_Left:
            queueDirection(Resources::Direction::Left);
            break;
        }
    }

    QGraphicsPixmapItem::keyPressEvent(event);
}
