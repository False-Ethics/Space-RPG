#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

void Player::addPlayer() {
    cout << "\033[31m===== Player Creation =====\033" << endl;
    cout << "Please type player name: ";
    cin >> name;
    cout << endl;
    cout << "Player name: -={" << name << "}=-" << endl;
    cout << endl;

    cout << "=============== Please Choose your Ship ===============" << endl;
    cout << "1. Solace - Nano Cluster Repair: repairs 45% health" << endl;
    cout << "2. Diminisher - Weaken Shields: 50% shield penetration" << endl;
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
        cout << "Invalid input" << endl;
        return;
    }
    xp = 0;
    creds = 0;
    health = 100;
    shields = 200;

    cout << "Health: " << health << endl;
    cout << "Shield: " << shields << endl;
    cout << "XP: " << xp << endl;
    cout << "Creds: " << creds << endl;
    saveData();
}
void Player::saveData() {
    ofstream file("player_save.txt");
    if (file.is_open()) {
        file << "Player Name: " << name << endl;
        if (ship == 1)
            file << "Ship: Solace" << endl;
        else
            file << "Ship: Diminisher" << endl;
        file << "Health: " << health << endl;
        file << "Shield: " << shields << endl;
        file << "XP: " << xp << endl;
        file << "Creds: " << creds << endl;
        file.close();
        /*cout << "Save successful! Player data written to player_save.txt" << endl;*/
    }
    else {
        cout << "Error: Could not open save file!" << endl;
    }
}
bool Player::isAlive() {
    return health > 0;
}
void Player::damageTaken(int dmg) {
    if (shields > 0) {
        int shieldDmg;
        if (dmg <= shields) {
            shieldDmg = dmg;
        }
        else {
            shieldDmg = shields;
        }
        shields -= shieldDmg;
        dmg -= shieldDmg;
        cout << name << " shield absorbs " << shieldDmg << " damage." << endl;
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
        if (dmg <= shield) {
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
    cout << "\n--- " << e.name << " appears! ---\n" << endl;

    cout << "Press Enter to start combat...";
    cin.ignore(); 

    while (p.isAlive() && e.isAlive()) {
        cout << endl;
        cout << "=== Status ===" << endl;
        cout << p.name << " - Health: " << p.health << ", Shield: " << p.shields << endl;
        cout << e.name << " - Health: " << e.health << ", Shield: " << e.shield << endl << endl;
        cout << "Press Enter to attack...";
        cin.ignore();
        cout << endl;

        // Player attack
        int dmg = playerMin + rand() % (playerMax - playerMin + 1);
        cout << p.name << " attacks " << e.name << " for " << dmg << " damage!" << endl;
        e.damageTaken(dmg);

        if (!e.isAlive()) {
            cout << e.name << " defeated!\n" << endl;
            break;
        }

        // Enemy attack
        int enemyDmg = e.attack();
        cout << e.name << " attacks " << p.name << " for " << enemyDmg << " damage!" << endl;
        p.damageTaken(enemyDmg);

        if (!p.isAlive()) {
            cout << p.name << " has been defeated!\n";
            return p;
        }
    }
    return p;
}
