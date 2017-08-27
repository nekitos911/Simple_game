#ifndef LEVEL_H
#define LEVEL_H

#include "constants.h"
struct Object {
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);
    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string,std::string> properties;

    sf::Sprite sprite;
};

struct Layer {
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level
{
public:
    Level();
    bool LoadFromFile(std::string filename);
    Object GetObject(std::string name);
    float GetMapW();
    float GetMapH();
    std::vector<Object> GetObjects(std::string name);
    std::vector<Object> GetAllObjects();

    void Draw(sf::RenderWindow &window);
    sf::Vector2i GetTileSize();
private:
    float w,h,tileW,tileH;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};

#endif // LEVEL_H
