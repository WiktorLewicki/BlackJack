#ifndef SILNIK_H
#define SILNIK_H

#include <bits/stdc++.h>
using namespace std;

// Forward declaration of classes
class Hand;
class Game;

// Function declarations
int losowanie(int n);
int choose(Game gr);

// Class Hand definition
class Hand {
    int bet, suma;
    bool bst;
    vector<int> reka;
public:
    Hand(int hajs = 0);
    int zaklad();
    void reset(int hajs);
    bool bust();
    int rozliczenie(int pkt_krupiera);
    void insert(int card);
    void db();
    int judge();
    vector<int> talia();
    bool blackjack();
    int sum();
};

// Class Game definition
class Game {
    int money;
    int LICZBA_TALII;
    int ile_kart;
    vector<int> cards;
    vector<Hand> hands;
    void shuff();
public:
    void setuj_talie(int x);
    int kwota();
    void zasil_konto(int x);
    int kasa();
    int akcja();
    int give_card();
    void new_game(int stawka);
    Game(int capital);
    bool double_down();
    bool hit(int karta, int who);
    int ile(int who);
    bool czy_tasowanie();
    bool blackjack(int who);
};

#endif // SILNIK_H
