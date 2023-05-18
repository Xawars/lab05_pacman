#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <queue>
#include "resources.h"
#include "entity.h"

using namespace std;

class Pacman : public QObject, public QGraphicsPixmapItem, public Entity
{
    Q_OBJECT

public:
    explicit Pacman();

private slots:
    void updatePixmap();

private:
    void loadPixmap();
    queue<Resources::Direction> m_directions;

    QPixmap m_upPixmap, m_downPixmap, m_leftPixmap, m_rightPixmap;
    int m_currentIndex;
    QTimer m_timer;
    constexpr static float Speed = 0.8f;
    constexpr static int AnimSpeed  = 125;

public:
    void clearQueueDirection();
    void queueDirection(Resources::Direction dir);
    void move();
    queue<Resources::Direction> getDirections();
    void stop();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // PACMAN_H
