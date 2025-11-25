#include <string>
#include <iostream>
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
