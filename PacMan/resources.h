#ifndef RESOURCES_H
#define RESOURCES_H
#include <QSize>
#include <QColor>
#include <QString>
#include <QPoint>

class Resources
{
public:
    Resources();

    enum class Direction
    {
        Up = 1,
        Down = -1,
        Left = 2,
        Right = -2,
        Unset = 0
    };

    constexpr static const QSize Resolution = QSize(448, 596);
    constexpr static const QColor BGColor = QColor(0, 0, 0);

    static void loadMaze();

    static const QString PathToMazePixmap;
    constexpr static const unsigned int MazeTileSize = 16;

    static const QString PathToPacmanPixmap;
    constexpr static const unsigned int PacmanTileSize = 30;

    constexpr static const unsigned int PacmanCountAnimFrames = 3;
    constexpr static const QPoint PacmanUp = QPoint(0, 0);
    constexpr static const QPoint PacmanDown = QPoint(90, 0);
    constexpr static const QPoint PacmanLeft = QPoint(180, 0);
    constexpr static const QPoint PacmanRight = QPoint(270, 0);

    constexpr static int FPS = 120;
};

#endif // RESOURCES_Hs
