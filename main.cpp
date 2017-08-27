#include <game.h>

using namespace std;

int main()
{
    bool isPlaying = true;
    bool isFirstPlay = true;
    Game *game;
    while(isPlaying) {
    game = new Game(isFirstPlay);
    game->GameLoop();
    isPlaying = game->IsPlaying();
    isFirstPlay = false;
    delete game;
    }
    return 0;
}
