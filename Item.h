#ifndef ITEM_H          
#define ITEM_H

#include <string>
#include <iostream>
#include <vector>
#include "Character.h"
using namespace std;

// --- 物品重量與背包設定常數 ---
const int waterWeight = 4;
const int foodWeight = 2;
const int axeWeight = 8;
const int pistolWeight = 5;
const int gameWeight = 5;
const int bookWeight = 3;
const int gasMaskWeight = 5;
const int mapWeight = 2;
const int saxophoneWeight = 5;
const int radioWeight = 5;
const int medkitWeight = 10;
const int packageCapacity = 100;

class Item; // 前置宣告

// --- 背包類別：管理物品庫存 ---
class Package
{
    private:
        string packageName; // 背包名稱 (例如: "避難所", "探險背包")
        int capacity;       // 背包容量
        Item* items[11];    // 存放 11 種物品的指標陣列

    public:
        // 建構子：初始化背包名稱與各物品數量
        Package (string name, int qWater, int qFood, int qAxe, 
                 int qPistol, int qGame, int qBook, int qGasMask, int qMap, int qSaxophone, int qRadio, int qMedKit);
        
        // 增加物品
        void addItem(string addName, int q);
        
        // 使用物品 (消耗並對角色產生效果)
        void useItem(string useName, int q, Character& character);
        
        // 顯示特定物品的數量
        int showItemQuantity(string itemName);
        
        // 刪除物品 (直接移除，不產生效果)
        void deleteItem(string delName, int q);
        
        // 顯示背包內所有物品清單
        void displayItems();
        
        // 解構子：釋放記憶體
        ~Package();

        // 計算娛樂物品帶來的精神加成
        int entertainmentMentalBonus(); 
};

// --- 物品基底類別 (抽象類別) ---
class Item
{
    protected:
        string itemName; // 物品名稱
        int weight;      // 重量
        int quantity;    // 數量
        bool consumable; // 是否為消耗品

    public:
        Item (const string & n, int w, int q, bool c)
                : itemName (n), weight (w),quantity (q), consumable (c) {}
        
        string getName() const ;
        int getWeight() const;
        int getQuantity() const;
        void addQuantity(int newQuant); // 增減數量
        
        virtual ~Item() {}
        
        // 純虛擬函式：由子類別實作具體的使用效果
        virtual void use(Character& target, int quantity) = 0;
};

// --- 各種物品的子類別 ---

// 水：恢復口渴
class Water : public Item
{
    private:
        int thirstHeal;
    public:
        Water (const string & n, int q)
                : Item (n, waterWeight, q, true), thirstHeal(30) {}

        void use(Character& target, int quantity) override;
};

// 食物：恢復飢餓
class Food : public Item
{
    private:
        int hungerHeal;
    public:
        Food (const string & n, int q)
                : Item (n, foodWeight, q, true), hungerHeal(25){}
        
        void use(Character& target, int quantity) override;
};

// 斧頭：武器/工具
class Axe : public Item
{
    public:
        Axe (const string & n, int q)
                : Item (n, axeWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

// 手槍：武器
class Pistol : public Item
{
    public:
        Pistol (const string & n, int q)
                : Item (n, pistolWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

// 遊戲機：娛樂用品
class Game : public Item
{
    public:
        Game (const string & n, int q)
                : Item (n, gameWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

// 書本：娛樂用品
class Book : public Item
{
    public:
        Book (const string & n, int q)
                : Item (n, bookWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

// 防毒面具：探險裝備
class GasMask : public Item
{
    public:
        GasMask (const string & n, int q)
                : Item (n, gasMaskWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

// 地圖：探險裝備 (降低風險)
class Map : public Item
{
    public:
        Map (const string & n, int q)
                : Item (n, mapWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

// 薩克斯風：娛樂用品
class Saxophone : public Item
{
    public:
        Saxophone (const string & n, int q)
                : Item (n, saxophoneWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

// 收音機：特殊事件道具
class Radio : public Item
{
    public:
        Radio (const string & n, int q)
                : Item (n, radioWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

// 急救包：治療生病與恢復生命
class Medkit : public Item
{
    public:
        Medkit(const string & n ,int q)
                : Item (n, medkitWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

#endif