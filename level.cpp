#include "level.h"

using namespace tinyxml2;

int Object::GetPropertyInt(std::string name) {
    return atoi(properties[name].c_str());
}
float Object::GetPropertyFloat(std::string name) {
    return strtod(properties[name].c_str(),NULL);
}
std::string Object::GetPropertyString(std::string name) {
    return properties[name];
}

Level::Level() {}
// XML parser
bool Level::LoadFromFile(std::string filename) {
    XMLDocument levelFile(filename.c_str());

    if(levelFile.LoadFile(filename.c_str())) {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    XMLElement *map;
    map = levelFile.FirstChildElement("map");

    w = atoi(map->Attribute("width"));
    h = atoi(map->Attribute("height"));
    tileW = atoi(map->Attribute("tilewidth"));
    tileH = atoi(map->Attribute("tileheight"));

    XMLElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    XMLElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    sf::Image img;
    if (!img.loadFromFile(imagepath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    img.createMaskFromColor(sf::Color(41,145,179)); // mask for map(can be different)
    tilesetImage.loadFromImage(img);
    tilesetImage.setSmooth(false);

    int columns = tilesetImage.getSize().x / tileW;
    int rows = tilesetImage.getSize().y / tileH;

    std::vector<sf::Rect<int> > subRects;

    for(int y = 0;y < rows;y++)
        for (int x = 0;x < columns;x++) {
            sf::Rect<int> rect;

            rect.top = y * tileH;
            rect.height = tileH;
            rect.left = x * tileW;
            rect.width = tileW;

            subRects.push_back(rect);
        }

    XMLElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while(layerElement) {
        Layer layer;

        if(layerElement->Attribute("opacity") != NULL) {
            float opacity = strtod(layerElement->Attribute("opacity"),NULL);
            layer.opacity = 255 * opacity;
        }
        else layer.opacity = 255;

        XMLElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if(layerDataElement == NULL)
            std::cout << "Bad map. No layer information found." << std::endl;

        XMLElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while(tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if(subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileW,y * tileH);
                sprite.setColor(sf::Color(255,255,255,layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if(x >=w) {
                x = 0;
                y++;
                if(y >= h)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    XMLElement *objectGroupElement;

    if(map->FirstChildElement("objectgroup") != NULL) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while(objectGroupElement) {
            XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while(objectElement) {
                std::string objectType;
                if(objectElement->Attribute("type") != NULL)
                    objectType = objectElement->Attribute("type");
                std::string objectName;
                if(objectElement->Attribute("name") != NULL)
                    objectName = objectElement->Attribute("name");

                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int w;
                int h;
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(sf::Rect<int>(0,0,0,0));
                sprite.setPosition(x,y);

                if(objectElement->Attribute("width") != NULL) {
                    w = atoi(objectElement->Attribute("width"));
                    h = atoi(objectElement->Attribute("height"));
                }
                else {
                    w = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    h = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }
                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;
                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = h;
                objectRect.width = w;
                object.rect = objectRect;

                XMLElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if(properties != NULL) {
                    XMLElement *prop;
                    prop = properties->FirstChildElement("property");
                    if(prop != NULL) {
                        while(prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
        std::cout << "No object layers found..." << std::endl;

    return true;
}

Object Level::GetObject(std::string name) {
    for (size_t i = 0;i < objects.size();i++)
        if(objects[i].name == name)
            return objects[i];
}
std::vector<Object> Level::GetObjects(std::string name) {
    std::vector<Object> vec;
    for(size_t i = 0;i < objects.size();i++)
        if(objects[i].name == name)
            vec.push_back(objects[i]);
    return vec;
}
std::vector<Object> Level::GetAllObjects() {
    return objects;
}

sf::Vector2i Level::GetTileSize() { return sf::Vector2i(tileW,tileH); }

void Level::Draw(sf::RenderWindow &window) {
    for(size_t layer = 0;layer < layers.size();layer++)
        for(size_t tile = 0;tile < layers[layer].tiles.size();tile++)
            window.draw(layers[layer].tiles[tile]);
}

int Level::GetMapW() { return tileW * w; }
int Level::GetMapH() { return tileH * h; }
