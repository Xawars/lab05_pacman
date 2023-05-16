#ifndef RESOURCES_H
#define RESOURCES_H
#include <QSize>
#include <QColor>
#include <QString>

class Resources
{
public:
    Resources();

    constexpr static const QSize Resolution = QSize(448, 596);
    constexpr static const QColor BGColor = QColor(0, 0, 0);

    static void loadMaze();

    static const QString PathToMazePixmap;
    constexpr static const unsigned int MazeTileSize = 16;
};

#endif // RESOURCES_Hs
