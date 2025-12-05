#include <string>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include "Character.h"
#include "Item.h"
#include "event.h"
using namespace std;

// --- 冒險系統實作 ---

ExpeditionSystem::ExpeditionSystem()
{
    isActive = false;
    daysRemaining = 0;
    hadExpedition = false;
};

bool ExpeditionSystem::isExpeditionActive()
{
    return isActive;
} 

// 開始探險：初始化狀態、建立探險背包、選擇裝備
void ExpeditionSystem::startExpedition(Character& adventurer, Package& playerPackage)
{
    neverBack = false;
    isDead = false;
    // 建立一個名為 "Expedition Bag" 的臨時背包
    expeditionBag = new Package("Expedition Bag", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
    hadExpedition = true;
    isActive = true;
    explorerName = adventurer.getName();
    daysRemaining = rand() % 3 + 2; // 隨機設定 2~4 天
    log.clear(); 

    cout << "此次冒險中你派出了 " << explorerName << " 去尋找物資！\n";
    cout << "\n=== 請選擇攜帶裝備 (最多 2 樣) ===\n";
    cout << "0. 結束選擇\n";
    cout << "1. Pistol (手槍)   - 庫存: " << playerPackage.showItemQuantity("pistol") << "\n";
    cout << "2. Axe (斧頭)      - 庫存: " << playerPackage.showItemQuantity("axe") << "\n";
    cout << "3. Gas Mask (面具) - 庫存: " << playerPackage.showItemQuantity("gas mask") << "\n";
    cout << "4. Map (地圖)      - 庫存: " << playerPackage.showItemQuantity("map") << "\n";
    
    int itemsCount = 0;
    while (itemsCount < 2) 
    {
        int choice;
        cout << "請輸入第 " << (itemsCount + 1) << " 樣物品編號 (0~4): ";
        cin >> choice;

        if (choice == 0) {
            break; // 使用者不想帶了
        }

        string targetName = "";
        
        switch(choice)
        {
            case 1: targetName = "pistol"; break;
            case 2: targetName = "axe"; break;
            case 3: targetName = "gas mask"; break;
            case 4: targetName = "map"; break;
            default:
                cout << "無效的選項，請重新輸入。\n";
                continue; 
        }

        // 檢查庫存並轉移
        if (playerPackage.showItemQuantity(targetName) > 0) 
        {
            playerPackage.deleteItem(targetName, 1);
            expeditionBag->addItem(targetName, 1);
            cout << ">> 已裝備: " << targetName << "\n";
            itemsCount++;
        } 
        else 
        {
            cout << ">> 庫存不足！你沒有 " << targetName << "。\n";
        }
    }

    cout << "\n>>> " << explorerName << " 帶著裝備，消失在荒野中...\n";
}

// 每日更新探險進度 (隨機事件、搜刮、危險)
void ExpeditionSystem::updateDaily(Character& adventurer)
{
    if (!isActive) return;
    daysRemaining--;
    if (isDead) return;

    int noEventProb = 20; 
    int lootEventProb = 80;

    // 有地圖時，平安無事機率降低(代表更容易搜刮到東西)，搜刮機率提高
    if(expeditionBag->showItemQuantity("map") > 0)
    {
        noEventProb = 10; 
        lootEventProb = 90;
    }

    int eventRoll = rand() % 100 + 1; // 1~100 的隨機數

    // 1. 平安無事
    if (eventRoll <= noEventProb) 
    {
        log.push_back(explorerName + " 度過平安無事的一天。");
    } 
    // 2. 搜刮事件
    else if (eventRoll <= lootEventProb) 
    {
        int lootType = rand() % 3;
        if (lootType == 0) 
        {
            expeditionBag->addItem("bottled water", 1);
            log.push_back("在一間廢棄屋子裡找到了一瓶水！");
        } 
        else if (lootType == 1) 
        {
            expeditionBag->addItem("can", 2);
            log.push_back("翻找垃圾堆時發現了兩個罐頭！");
        } 
        else 
        {
            // 小機率撿到急救包
            if (rand() % 5 == 0) {
                expeditionBag->addItem("medkit", 1);
                log.push_back("幸運地在藥局廢墟找到了急救包！");
            } else {
                log.push_back("搜索了一整天，但只找到一些沒用的垃圾。");
            }
        }
    } 
    // 3. 危險事件 (劫匪或意外)
    else if (eventRoll <= 100) 
    {
        // 如果有武器，可以擊退敵人並獲得戰利品
        if(expeditionBag->showItemQuantity("pistol") > 0 || expeditionBag->showItemQuantity("axe") > 0)
        {
            log.push_back(explorerName + " 路上遭遇了劫匪，但幸好有武器在身，成功趕跑了劫匪，他們還掉了一些水和罐頭。");
            expeditionBag->addItem("bottled water", 2);
            expeditionBag->addItem("can", 2);
            return;
        }
        
        // 沒武器，判定生死
        int deadRoll = rand() % 5;
        if(deadRoll <= 1) // 40% 機率死亡
        {
            isDead = true;
            log.push_back("悲劇！" + explorerName + " 在探險途中不幸遇難，永遠地留在了荒野中...");
        } 
        else 
        {
            log.push_back(explorerName + " 在野外遭遇危險，受了點傷但靠著身法活了下來，損失了一些物資。");
            if (expeditionBag->showItemQuantity("bottled water") > 0) {
                expeditionBag->deleteItem("bottled water", 1);
            }
            if (expeditionBag->showItemQuantity("can") > 0) {
                expeditionBag->deleteItem("can", 1);
            }
        }
    }
    
    // 檢查角色身體狀況 (生病或虛弱會增加死亡率)
    if(adventurer.isSickStatus() || adventurer.bodyNotGood())
    {
        int sicknessRoll = rand() % 5;
        if(sicknessRoll <= 3) // 80% 機率死亡
        {
            isDead = true;
            log.push_back("悲劇！" + explorerName + " 因為身體狀況不佳，在探險途中不幸遇難，永遠地留在了荒野中...");
        }
    }
}

bool ExpeditionSystem::checkReturn() 
{
    return (isActive && daysRemaining <= 0);
}

// 探險回歸結算：顯示報告、轉移物資、設定角色狀態
void ExpeditionSystem::resolveReturn(Package& mainPackage, Character& cindy, Character& chris) 
{
    cout << "\n========================================\n";
    cout << ">>> [探險報告] " << explorerName << " 的探險結果：\n";
    
    // 處理生死
    if (isDead) 
    {
        neverBack = true;
        
        // 設定角色死亡
        if (explorerName == "Cindy") 
        {
            cindy.kill(); 
        } 
        else if (explorerName == "Chris") 
        {
            chris.kill();
        }
    } 
    // 活著回來：結算物資
    else 
    {
         // 顯示日誌 (讓玩家知道發生什麼事)
        for (const string& entry : log) 
        {
            cout << " - " << entry << endl;
        }
        
        cout << "\n>>> " << explorerName << " 平安歸來！\n" << "但身體非常虛弱...\n";
        cout << ">>> 帶回來的物資：\n";
        
        string allItems[] = {"bottled water", "can", "axe", "pistol", "game", "book", "gas mask", "map", "saxophone", "radio", "medkit"};
        
        // 將探險背包的東西轉移回主背包
        for (const string& itemName : allItems) 
        {
            int qty = expeditionBag->showItemQuantity(itemName);
            if (qty > 0) 
            {
                mainPackage.addItem(itemName, qty); 
            }
        }
        // 設定角色狀態為瀕死 (探險後的虛弱)
        if (explorerName == "Cindy") 
        {
            cindy.setStatus(25, 25, 30); 
        } 
        else if (explorerName == "Chris") 
        {
            chris.setStatus(25, 25, 30);
        }
    }
    cout << "========================================\n\n";

    // 重置並刪除暫存背包
    delete expeditionBag;
    expeditionBag = nullptr;
    isActive = false;
}

int creatureDay = 4; // 初始化生物滯留天數

/*-------------------------------------------------------------------------------*/
/*-------------------------------- 突發事件實作 ----------------------------------*/

SuddenEvent::SuddenEvent(string t, string c) : title(t), content(c){}

void SuddenEvent::showEvent(){
    cout << "========================================" << "\n";
    cout << " [突發事件: " << title << "] " << "\n";
    cout << content << "\n";
    cout << "----------------------------------------" << "\n";
    cout << "請選擇: 打勾 (輸入y)   打叉 (輸入n)" << "\n";
    cout << "========================================" << "\n";
}

void SuddenEvent::makeChoice(char choice, Character& cindy, Character& chris, Package& bag, int currentDay){
    if(choice == 'y' || choice == 'Y'){
        cout << "\n[你們選擇了 打勾 (Yes)]\n";
        chooseYes(cindy, chris, bag, currentDay);
    }
    else{
        cout << "\n[你們選擇了 打叉 (No)]\n";
        chooseNo(cindy, chris, bag, currentDay);
    }
}

SuddenEvent::~SuddenEvent()
{
}