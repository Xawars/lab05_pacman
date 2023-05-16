#include "game.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

Game::Game(QObject *parent) : QGraphicsScene(parent) {
    loadMap();
}

void Game::loadMap() {
    QPixmap map(":/res/sprite/maze.png");
    QGraphicsPixmapItem *item = addPixmap(map);
    item->setPos(0, 0);
}
