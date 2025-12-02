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


int creatureDay = 4; // 突發事件5:恐怖生物停留日期計數
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