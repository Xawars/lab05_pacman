#include "entity.h"
#include "resources.h"
#include <cmath>

Entity::Entity(int tilePosX, int tilePosY)
    : m_pacmanPixmap(Resources::PathToPacmanPixmap)
{
    m_tileX = tilePosX;
    m_tileY = tilePosY;
    m_screenPosX = tilePosX * Resources::MazeTileSize + 8.0f + 8.0f - Resources::PacmanTileSize/2;
    m_screenPosY = tilePosY * Resources::MazeTileSize + 8.0f - Resources::PacmanTileSize/2;
}

float Entity::getScreenPosX()
{
    return m_screenPosX;
}

float Entity::getScreenPosY()
{
    return m_screenPosY;
}

int Entity::getTileX()
{
    return m_tileX;
}

int Entity::getTileY()
{
    return m_tileY;
}

void Entity::move(float x, float y)
{
    m_screenPosX += x;
    m_screenPosY += y;

    if ((int)(m_screenPosX + 8 + Resources::PacmanTileSize/2) % 16 == 0 && (int)(m_screenPosY + 8 + Resources::PacmanTileSize/2) % 16 == 0)
    {
        m_tileX = (int) round((m_screenPosX - 8 + Resources::PacmanTileSize/2) / 16);
        m_tileY = (int) round((m_screenPosY - 8 + Resources::PacmanTileSize/2) / 16);
    }
}

void Entity::teleport(int x, int y)
{
    m_tileX = x;
    m_tileY = y;
    m_screenPosX = x * 16.0f + 8.0f - Resources::PacmanTileSize/2;
    m_screenPosY = y * 16.0f + 8.0f - Resources::PacmanTileSize/2;
}

