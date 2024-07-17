#include <bits/stdc++.h>
using namespace std;
map<vector<int>, long double> odw;
class Game{
private:
    int money, bet;
    int price[15];
    queue<pair<int, int>> cards;
    vector<int> take[2];
    void shuff(){
        mt19937 generator;
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator = std::mt19937(seed);
        while(!cards.empty()){
            cards.pop();
        }
        vector<pair<int, int>> pm;
        for(int i=2;i<=14;i++){
            for(int j=1;j<=4;j++){
                pm.push_back({i, j});
            }
        }
        shuffle(pm.begin(), pm.end(), generator);
        for(auto &v : pm){
            cards.push(v);
        }
    }
public:
    Game(int capital=0){
        bet=0;
        money=capital;
        shuff();
        for(int i=2;i<=10;i++) price[i]=i;
        price[11]=price[12]=price[13]=10;
        price[14]=11;
    }
    bool czy_tasowanie(){
        if((int)cards.size()>=16) return false;
        shuff();
        return true;
    }
    pair<int, int> give(){
        pair<int, int> pm=cards.front();
        cards.pop();
        return pm;
    }
    int judge(int who){
        vector<int> pp=take[who];
        sort(pp.begin(), pp.end());
        int sum=0, aces=0;
        for(auto &v : pp){
            if(v==14) aces++;
            sum+=price[v];
        }
        while(sum>21&&aces>0){
            sum-=10;
            aces--;
        }
        if(sum>21) return -1;
        return sum;
    }
    void postaw(int x){
        bet=x;
    }
    void insert(int cd, int who){
        take[who].push_back(cd);
    }
    void clear(){
        take[0].clear();
        take[1].clear();
    }
    int kasa(){
        return money;
    }
    int kwota(){
        return bet;
    }
    void zasil_konto(int dd){
        money+=dd;
    }
    int hit_judge(){
        int sum=0;
        for(auto &v : take[0]){
            if(v==14) sum++;
            else sum+=price[v];
        }
        return sum;
    }
    long double hit_chances(){
        int sum=hit_judge(), cnt=0;
        vector<int> left;
        queue<pair<int, int>>pm=cards;
        while(!pm.empty()){
            left.push_back(price[(pm.front()).first]);
            pm.pop();
        }
        for(auto &v : left){
            if(v==11) v-=10;
            if(v+sum<=21){
                cnt++;
            }
        }
        long double res=(long double)cnt/(long double)left.size()*(long double)100.0;
        return res;
    }
    void recycle(pair<int, int>a){
        queue<pair<int, int>> pm;
        while(!cards.empty()){
            if(cards.front()!=a) pm.push(cards.front());
            cards.pop();
        }
        cards=pm;
    }
    vector<pair<int, int>> what(){
        vector<pair<int, int>> a;
        queue<pair<int, int>> b=cards;
        while(!b.empty()){
            a.push_back(b.front());
            b.pop();
        }
        return a;
    }
    vector<int> give_take(){
        vector<int> pm=take[1];
        return pm;
    }
};

void dfs(Game &G1, int points){
    vector<int> save=G1.give_take();
    if(odw.find(save)!=odw.end()) return;
    int how=G1.judge(1);
    if(how==-1){
        odw[save]=100;
        return;
    }
    if(how>=17){
        if(how<points){
            odw[save]=100;
            return;
        }
        else{
            odw[save]=0;
            return;
        }
    }
    vector<pair<int, int>> karty=G1.what();
    for(int i=0;i<(int)karty.size();i++){
        Game G2=G1;
        G2.insert(karty[i].first, 1);
        G2.recycle(karty[i]);
        dfs(G2, points);
        odw[save]+=odw[G2.give_take()];
    }
    odw[save]/=(long double)karty.size();
}
long double stand_chances(Game G){
    odw.clear();
    dfs(G, G.judge(0));
    return odw[G.give_take()];
}
