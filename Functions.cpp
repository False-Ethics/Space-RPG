#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

void Player::addPlayer() {
    cout << "\033[31m=============== Player Creation ===============\033" << endl;
    cout << "aPlease type your name: "; //if it works, it works. 
    getline(cin, name);
    cout << endl;
    cout << "Player name: -={" << name << "}=-" << endl;
    cout << endl;

    cout << "=============== Please Choose your Ship ===============" << endl;
    cout << "1. Solace - Nano Cluster Repair: repairs 45% health" << endl;
    cout << "2. Diminisher - Weaken Shields: 50% shield penetration" << endl;
    cout << endl;
    cout << ">>>>> I know what you are thinking, don't do it. <<<<<" << endl;
    cout << "-={" << name << "}=- selects: ";
    cin >> ship;
    cout << endl;

    if (ship == 1) {
        cout << "-={" << name << "}=- has selected Solace" << endl << endl;
    }
    else if (ship == 2) {
        cout << "-={" << name << "}=- has selected Diminisher" << endl << endl;
    }
    else {
        cout << "Invalid input: try again" << endl;
        addPlayer();
    }
    xp = 0;
    creds = 0;
    health = 200;
    shields = 200;

    cout << "Health: " << health << endl;
    cout << "Shield: " << shields << endl;
    cout << "XP: " << xp << endl;
    cout << "Creds: " << creds << endl;
    saveData();
}
void Player::saveData() {
    ofstream file("-={" + name + "}=-.txt");
    if (file.is_open()) {
        file << "Player name: -={" << name << "}=-" << endl;
        if (ship == 1)
            file << "Ship: Solace" << endl;
        else
            file << "Ship: Diminisher" << endl;
        file << "Health: " << health << endl;
        file << "Shield: " << shields << endl;
        file << "XP: " << xp << endl;
        file << "Creds: " << creds << endl;
        file.close();
        cout << "Save successful! Player data written to -={" << name << "}=-.txt" << endl;
    }
    else {
        cout << "Error: Could not open save file!" << endl;
    }
}
void Player::loadData() {
    name = name;
    ship = 0;
    health = health;
    shields = shields;
    xp = 0;
    creds = 0;

    ifstream file("-={" + name + "}=-.txt");
    if (file.is_open()) {
        file >> name;
        file >> ship;
        file >> health;
        file >> shields;
        file >> xp;
        file >> creds;
        file.close();

        cout << "Loaded player: " << name << endl;
    }
    else {
        cout << "No save found. Creating new player..." << endl;
        addPlayer();
    }
}
bool Player::isAlive() {
    return health > 0;
}
void Player::damageTaken(int dmg) {
    if (shields > 0) {
        int shieldDmg;
        if (dmg*0.8f <= shields) { //numeric conversion
            shieldDmg = dmg;
        }
        else {
            shieldDmg = shields;
        }
        shields -= shieldDmg;
        dmg -= shieldDmg;
        cout << "-={" << name << "}=- shield absorbs " << shieldDmg << " damage." << endl;
    }
    if (dmg > 0) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " takes " << dmg << " damage." << endl;
    }
};

void Enemy::damageTaken(int dmg) {
    if (shield > 0) {
        int shieldDmg;
        if (dmg*0.8f <= shield) { //numeric conversion
            shieldDmg = dmg ;
        }
        else {
            shieldDmg = shield;
        }
        shield -= shieldDmg;
        dmg -= shieldDmg;
        cout << name << " shield absorbs " << shieldDmg << " damage." << endl;
    }
    if (dmg > 0) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " takes " << dmg << " damage." << endl;
    }
};
bool Enemy::isAlive() {
    return health > 0;
}
int Enemy::attack() {
    return minDamage + rand() % (maxDamage - minDamage + 1);
}

Player fight(Player p, Enemy e, int playerMin, int playerMax) {
    cout << endl;
    cout << "\\\\\\ " << e.name << " appears! ///" << endl; //if it works, it works. 
    cout << endl;
    cout << "Press Enter to start combat...";
    cout << endl;
    cin.ignore(); 


    while (p.isAlive() && e.isAlive()) {
        cout << endl;
        while (p.shields, e.shield < 0) {
            p.shields, e.shield = 0;
        }
        cout << "=============== Status ===============" << endl;
        cout << "-={" << p.name << "}=-" << " - Health: " << p.health << ", Shield: " << p.shields << endl;
        cout << "-={" << p.name << "}=-" << " - Health: " << e.health << ", Shield: " << e.shield << endl << endl;
        cout << "Press Enter to attack...";
        cin.ignore();
        cout << endl;

        
        int dmg = playerMin + rand() % (playerMax - playerMin + 1);
        cout << "-={" << p.name << "}=-" << " attacks " << e.name << " for " << dmg << " damage!" << endl;
        e.damageTaken(dmg);

        if (!e.isAlive()) {
            cout << e.name << " defeated!" << endl;
            cout << endl;
            break;
        }
        int enemyDmg = e.attack();
        cout << e.name << " attacks " << "-={" << p.name << "}=-" << " for " << enemyDmg << " damage!" << endl;
        p.damageTaken(enemyDmg);

        if (!p.isAlive()) {
            cout << "-={" << p.name << "}=-" << " has been defeated!";
            cout << endl;
            return p;
        }
    }
    return p;
}