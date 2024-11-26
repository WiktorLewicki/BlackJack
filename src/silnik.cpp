#include <bits/stdc++.h>
#define pb push_back
using namespace std;
map<vector<int>, long double> odw;
int price[12]={0, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int losowanie(int n) {
    random_device rd;
    knuth_b generator(rd());
    uniform_int_distribution<int> distribution(0, n - 1);
    return distribution(generator);
}
class Hand{
    int bet, suma;
    bool bst;
    vector<int> reka;
public:
    Hand(int hajs=0){
        reset(hajs);
    }
    int zaklad(){
        return bet;
    }
    void reset(int hajs){
        bst=false;
        reka.clear();
        bet=hajs;
        suma=0;
    }
    bool bust(){
        return bst;
    }
    int rozliczenie(int pkt_krupiera){
        if(!bust()&&suma>pkt_krupiera) return 2;
        else if(!bust()&&suma==pkt_krupiera) return 1;
        else return 0;
    }
    void insert(int card){
        reka.pb(card);
        judge();
    }
    void db(){
        bet<<=1;
    }
    int judge(){
        int sum=0, aces=0;
        for(auto &v : reka){
            if(v==11) aces++;
            sum+=price[v];
        }
        while(sum>21&&aces>0){
            sum-=10;
            aces--;
        }
        suma=sum;
        if(sum>21){
            bst=true;
            suma=-1;
            return -1;
        }
        return sum;
    }
    vector<int> talia(){
        return reka;
    }
    bool blackjack(){
        judge();
        if(suma==21&&(int)reka.size()==2) return true;
        return false;
    }
    int sum(){
        return suma;
    }
};
class Game{
    int money;
    int LICZBA_TALII;
    int ile_kart;
    vector<int> cards;
    vector<Hand> hands;
    void shuff(){
        cards.clear();
        cards.resize(12);
        for(int z=1;z<=LICZBA_TALII;z++){
            for(int i=2;i<=9;i++){
                cards[i]=LICZBA_TALII*4;
            }
            cards[10]=LICZBA_TALII*16;
            cards[11]=LICZBA_TALII*4;
        }
        ile_kart=52*LICZBA_TALII;
    }
public:
    void setuj_talie(int x){
        LICZBA_TALII=x;
        shuff();
    }
    int kwota(){
        return hands[0].zaklad();
    }
    void zasil_konto(int x){
        money+=x;
    }
    int kasa(){
        return money;
    }
    int akcja(){
        return hands[0].rozliczenie(hands[1].sum());
    }
    int give_card(){
        int r=losowanie(ile_kart);
        int pm=0;
        for(int i=2;i<=11;i++){
            pm+=cards[i];
            if(pm>r){
                cards[i]--;
                ile_kart--;
                return i;
            }
        }
        return -1;
    }
    void new_game(int stawka){
        hands.clear();
        Hand pm(stawka);
        hands.push_back(pm);
        hands.emplace_back();
        money-=stawka;
    }
    Game(int capital){
        money=capital;
        LICZBA_TALII=6;
        shuff();
    }
    bool double_down(){
        vector<int> pm=hands[0].talia();
        if(hands[0].zaklad()>money||pm.size()>2) return false;
        money-=hands[0].zaklad();
        hands[0].db();
        return true;
    }
    bool hit(int karta, int who){
        hands[who].insert(karta);
        if(hands[who].bust()) return true;
        return false;
    }
    int ile(int who){
        return hands[who].sum();
    }
    bool czy_tasowanie(){
        if(ile_kart>=LICZBA_TALII*16) return false;
        shuff();
        return true;
    }
    bool blackjack(int who){
        return hands[who].blackjack();
    }
};

int choose(Game gr) {
    int dok = 1e5;
    std::atomic<int> cnt1(0);
    std::atomic<int> cnt2(0);
    auto simulate_cnt1 = [&](int start, int end) {
        for (int i = start; i < end; i++) {
            Game G = gr;
            G.hit(G.give_card(), 0);
            while (G.ile(1) < 17) {
                G.hit(G.give_card(), 1);
                if (G.ile(1) == -1) {
                    break;
                }
            }
            int pm = G.akcja();
            if (pm == 2) cnt1++;
            if (pm == 0) cnt1--;
        }
    };
    auto simulate_cnt2 = [&](int start, int end) {
        for (int i = start; i < end; i++) {
            Game G = gr;
            while (G.ile(1) < 17) {
                G.hit(G.give_card(), 1);
                if (G.ile(1) == -1) {
                    break;
                }
            }
            int pm = G.akcja();
            if (pm == 2) cnt2++;
            if (pm == 0) cnt2--;
        }
    };
    int num_threads = 8;
    int chunk_size = dok / num_threads;
    vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(simulate_cnt1, i * chunk_size, (i + 1) * chunk_size));
    }
    for (auto &t : threads) {
        t.join();
    }
    threads.clear();
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(simulate_cnt2, i * chunk_size, (i + 1) * chunk_size));
    }
    for (auto &t : threads) {
        t.join();
    }
    if (cnt1 > cnt2) {
        if (cnt1 > 0 && gr.double_down()) return 2;
        else return 1;
    } else {
        if (gr.ile(0) < 11) return 1;
        return 0;
    }
}




