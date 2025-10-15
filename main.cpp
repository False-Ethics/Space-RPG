#include <iostream>
#include "Header.h"
using namespace std;

int main() 
{
    srand(time(0));

    Player player;
    player.addPlayer();
    player.loadData();

    Enemy pheonix("-={Pheonix}=-", 20, 20, 5, 10);
    Enemy leonov("-={Leonov}=-", 20, 60, 15, 20);
    Enemy goliath("-={Goliath}=-", 100, 100, 15, 25);
    Enemy citadel("-={Citadel}=-", 100, 200, 5, 50);

    player = fight(player, pheonix, 25, 40);
    if (!player.isAlive()) return 0;
    player = fight(player, leonov, 25, 40);
    if (!player.isAlive()) return 0;
    player = fight(player, goliath, 25, 40);
    if (!player.isAlive()) return 0;
    player =fight(player, citadel, 25, 40);
    if (!player.isAlive()) return 0;

    cout << "All enemies defeated! You survived the combat!" << endl;

    return 0;
}