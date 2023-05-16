#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>

class Game : public QGraphicsScene {
    Q_OBJECT

public:
    Game(QObject *parent = nullptr);
    void loadMap();
};

#endif // GAME_H
