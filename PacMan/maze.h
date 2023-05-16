#ifndef MAZE_H
#define MAZE_H

#include <QObject>

class Maze : public QObject
{
    Q_OBJECT
public:
    explicit Maze();

    static const uint MazeWidth = 28;
    static const uint MazeHeight = 36;

    uint tiles(int x, int y) const;
    bool tileBlocksEntity(int x, int y);
    bool isIntersection(int x, int y);

private:
    uint m_tiles[MazeWidth][MazeHeight];
    static constexpr int NoneField = 30;
    static constexpr int SmallDotField = 26;
    static constexpr int BigDotField = 27;
};

#endif // MAZE_H
