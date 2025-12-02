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


int cretureDay = 4; // 突發事件5:恐怖生物停留日期計數