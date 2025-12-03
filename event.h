#ifndef EVENT_H         
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include "CharacterV2.h"
#include "Item.h"
using namespace std;

// 冒險
class ExpeditionSystem 
{
    private:
        bool isActive;          // 現在是否有人在外面？
        string explorerName;    // 誰出去了？
        int daysRemaining;      // 還剩幾天回來？
        vector<string> log;     // 日誌
    public:
        bool neverBack;
        Package* expeditionBag;
        bool isDead;
        bool hadExpedition;
        ExpeditionSystem();
        bool isExpeditionActive(); // 檢查現在是否在外面
        void startExpedition(Character& adventurer, Package& playerPackage);
        void updateDaily(Character& adventurer);
        bool checkReturn();
        void resolveReturn(Package& mainPackage, Character& cindy, Character& chris);
        string getExpeditionName() {return explorerName;};
};


// 突發事件
class SuddenEvent{
protected:
    string title;
    string content;
public:
    SuddenEvent(string t, string c);
    virtual ~SuddenEvent();
    void showEvent();
    void makeChoice(char choice, Character& cindy, Character& chris, Package& bag, int currentDay);
    virtual void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) = 0;
    virtual void chooseNo(Character& cindy, Character& chris, Package& bag, int currentDay) = 0;
};

// 突發事件一：神秘皮箱
class MysteryCase : public SuddenEvent{
public:
    MysteryCase() : SuddenEvent("神秘皮箱", "「夜裡，我們聽到奇怪的腳步聲。今天早上，我們發現門外多了一個皮箱，但是上面沒有任何的地址和姓名。我們應該打開它嗎?」"){};
    void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「裡面是一瓶水，我們便打開喝下去了。本來以為我們很幸運，沒想到這瓶水似乎遭受到汙染。大家過沒多久便開始上吐下瀉，非常難受。」" << "\n";
        cout << "(所有人 飢渴 -20 飢餓 -10)" << "\n";
        if(cindy.isAliveStatus()){
            cindy.thirstChange(-20);
            cindy.hungerChange(-10);
        }
        if(chris.isAliveStatus()){
            chris.thirstChange(-20);
            chris.hungerChange(-10);
        }
    }
    void chooseNo(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「我們害怕裡面藏了輻射物質或是炸彈，便把整個皮箱丟掉了。」" << "\n";
    }
};

// 突發事件二：神秘的訪客
class StrangeVisitor : public SuddenEvent{  // 秉駪
public:
    StrangeVisitor() : SuddenEvent("神秘的訪客", "「不知道是誰這麼沒禮貌，大清早便猛敲我們避難所的門，把所有人都吵醒了。他們十分堅持，已經連續敲了五分鐘，我們應該開門嗎?」"){};
    void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「一群戴著防毒面具，拿著高端設備的旅行者們給了我們兩瓶水，我們還來不及感謝他們，他們便轉身離開了。」" << "\n";
        cout << "(獲得: 2x水)" << "\n";
        bag.addItem("bottled water", 2);
    }
    void chooseNo(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「開門感覺太危險了，我們一直等到他們停止敲門，過了好久才敢出來。」" << "\n";
    }
};

// 突發事件三:拜訪鄰居  
class VisitNeighbor : public SuddenEvent{  // 秉駪
public:
    VisitNeighbor() : SuddenEvent("拜訪鄰居", "「我們的物資越來越少了，再這樣下去不是辦法。我們知道一個鄰居避難所的暗門是壞的，而且我們更加強壯。我們應該拜訪他們嗎?」"){};
    void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「雖然我們有了更多物資，但是因為某些原因大家心裡感覺並不好，我們永遠別再提這件事了。」" << "\n";
        cout << "(獲得: 4x罐頭)" << "\n";
        bag.addItem("can", 4);
    }
    void chooseNo(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「有些事情我們不管怎樣是不會去做的，搶奪比我們弱小的鄰居就是其中之一。」" << "\n";
    }
};

// 突發事件四:樓上的噪音  
class NoiseUpstairs : public SuddenEvent{  // 秉駪
public:
    NoiseUpstairs() : SuddenEvent("樓上的噪音", "「我們聽到樓上一直傳來翻箱倒櫃的聲音，不過之前樓上應該都沒有人居住。我們應該上去看看嗎?」"){};
    void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        if(bag.showItemQuantity("axe") > 0 || bag.showItemQuantity("pistol") > 0){
            cout << "「上面是一群劫匪似乎想把我們的避難所挖個底朝天，幸好有武器把他們趕跑了。」" << "\n";
        }
        else{
            cout << "「沒有武器果然有點麻煩，不幸敗下陣來，幸好他們願意開出條件，讓我們捨棄一點物資來保全我們的小命。」" << "\n";
            cout << "(損失: 2x水, 4x罐頭)" << "\n";
            bag.deleteItem("bottled water", 2);
            bag.deleteItem("can", 4);
        }
    }
    void chooseNo(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「還是待在避難所安全點，什麼事都不要做最好。」" << "\n";
    }
};

extern int creatureDay;
//突發事件5
class HorrificCreature : public SuddenEvent{ 
public:
    HorrificCreature() : SuddenEvent("恐怖生物", "「角落有動靜!我們在地下室附近發現了一個奇怪的生物。它有著發光的眼睛和許多觸角，似乎在尋找食物。」"){}
    void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) override{  //things eaten 
        cout << "「竟然是變異大蟑螂，還把我們的東西給吃了，還好它吃完之後就溜去別的地方了。我們還沒看過這麼大隻的蟑螂，真是噁心。」" << "\n";
        if(bag.showItemQuantity("book") == 1){
            bag.deleteItem("book", 1);
            cout << "(損失: 1x書本)" << "\n";
        }
        else if(bag.showItemQuantity("map") == 1){
            bag.deleteItem("map", 1);
            cout << "(損失: 1x地圖)" << "\n";
        }
        else if(bag.showItemQuantity("game") == 1){
            bag.deleteItem("game", 1);
            cout << "(損失: 1x遊戲)" << "\n";
        }
        else{
            cout << "這隻變異大蟑螂居然賴著不走，我們只好躲開它生活，快發瘋了。" << "\n";
            cout << "(精神 -10)" << "\n";
            cindy.mentalChange(-10);
            chris.mentalChange(-10);
            creatureDay--;
        }   
    }
};

//突發事件6
class RadioSignal : public SuddenEvent{ 
public:
    RadioSignal() : SuddenEvent("無線電訊號", "「收音機發出聲音了! 裡頭似乎傳出軍方無線電的對話內容，說是明天會在附近發放一些物資。」"){}
    void chooseYes(Character& cindy, Character& chris, Package& bag, int currentDay) override{  //mental +5
        cout << "「解出來那組密碼了，原來是經緯度座標，我們出去看看好了。」" << "\n";
        cout << "(精神 +5)" << "\n";
        cindy.mentalChange(5);
        chris.mentalChange(5);
    }
    void chooseNo(Character& cindy, Character& chris, Package& bag, int currentDay) override{
        cout << "「收音機突然又有訊號了，似乎明天軍方準備要來救出我們，苦日子終於要結束了。」" << "\n";
    }   
};

#endif