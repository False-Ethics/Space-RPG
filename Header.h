#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
    string name;
    int ship, xp, creds, health, shields;

    void addPlayer();
    void saveData();
    void loadData();
    bool isAlive();
    void damageTaken(int dmg);
};

class Enemy {
public:
    string name;
    int health, shield, minDamage, maxDamage;
    Enemy(string n, int h, int s, int maxD, int minD) {
        name = n;
        health = h;
        shield = s;
        maxDamage = maxD;
        minDamage = minD;
    }
    void damageTaken(int dmg);
    bool isAlive();
    int attack();
};

Player fight(Player p, Enemy e, int playerMin, int playerMax);
#endif