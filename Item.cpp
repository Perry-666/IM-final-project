#include <iostream>
#include <string>
#include <iomanip>
#include "Character.h"
#include "Item.h"
using namespace std;

// --- Package 類別實作 ---

// 建構子：初始化所有物品物件
Package::Package(string name, int qWater, int qFood, int qAxe, 
        int qPistol, int qGame, int qBook, int qGasMask, int qMap, int qSaxophone, int qRadio, int qMedKit) 
{
    this->packageName = name;

    items[0] = new Water("bottled water", qWater);
    items[1] = new Food("can", qFood);
    items[2] = new Axe("axe", qAxe);
    items[3] = new Pistol("pistol", qPistol);
    items[4] = new Game("game", qGame);
    items[5] = new Book("book", qBook);
    items[6] = new GasMask("gas mask", qGasMask);
    items[7] = new Map("map", qMap);
    items[8] = new Saxophone("saxophone", qSaxophone);
    items[9] = new Radio("radio", qRadio);
    items[10] = new Medkit("medkit", qMedKit);
}

// 增加物品數量
void Package::addItem(string addName, int q)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == addName) 
        {
            items[i]->addQuantity(q);
            return;
        }
    }
    cout << "Item " << addName << " not found in the package." << endl;
}


// 使用物品 (扣除數量並觸發效果)
void Package::useItem(string useName, int q, Character& character)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == useName) 
        {
            if (items[i]->getQuantity() >= q) 
            {
                items[i]->addQuantity(-q);
                items[i]->use(character, q);
            } 
            else 
            {
                cout << useName << "沒有足夠數量使用" << endl;
            }
            return;
        }
    }
    cout << "Item " << useName << " not found in the package." << endl;
}


// 查詢物品數量
int Package::showItemQuantity(string itemName)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == itemName) 
        {
            return items[i]->getQuantity();
        }
    }
    return 0;
}

// 刪除物品 (僅扣除數量)
void Package::deleteItem(string delName, int q)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == delName) 
        {
            if (items[i]->getQuantity() >= q) 
            {
                items[i]->addQuantity(-q);
            } 
            return;
        }
    }
    cout << "Item " << delName << " not found in the package." << endl;
}

// 顯示背包清單 (格式化輸出)
void Package::displayItems()
{
    cout << "剩餘物資:" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < 11; ++i) 
    {
        // 使用 setw 設定寬度以對齊
        cout << left << setw(20) << (items[i]->getName() + ": " + to_string(items[i]->getQuantity()));

        // 每兩個物品換一行
        if (i % 2 == 1) {
            cout << endl;
        }
    }
    cout << endl;
    cout << "----------------------------------------" << endl;
}

// 解構子：刪除動態配置的物品
Package::~Package()
{
    for (int i = 0; i < 11; ++i) 
    {
        delete items[i];
    }
}

// 計算娛樂道具帶來的精神回復加成
int Package::entertainmentMentalBonus(){ 
    int bonus = 0;

    if(items[4]->getQuantity() > 0){ // 遊戲機
        bonus += 5;
    }
    if(items[5]->getQuantity() > 0){ // 書本
        bonus += 5;
    }
    if(items[8]->getQuantity() > 0){ // 薩克斯風
        bonus += 5;
    }

    return bonus;
}

// --- Item 類別實作 ---

string Item::getName() const 
{
    return itemName;
}

int Item::getWeight() const
{
    return weight;
}

int Item::getQuantity() const
{
    return quantity;
}

void Item::addQuantity(int newQuant)
{
    quantity += newQuant;
}

// --- 各物品的具體 Use 實作 ---

void Water::use(Character& target, int quantity)
{
    target.drinkWater(quantity);
}

void Food::use(Character& target, int quantity)
{
    target.eatFood(quantity);
}

void Medkit::use(Character& target, int quantity){ 
    target.recoveryFull();
}

// 以下物品通常不直接使用，主要是裝備或被動效果，但仍需實作函式介面

void Axe::use(Character& target, int quantity)
{
    cout << "斧頭是用來裝備或觸發事件的，無法直接使用。" << endl;
}

void Pistol::use(Character& target, int quantity)
{
    cout << "手槍是用來裝備或防身的，無法直接使用。" << endl;
}

void Game::use(Character& target, int quantity)
{
    cout << "這是一個娛樂用品，放在背包裡會自動增加精神回復。" << endl;
}

void Book::use(Character& target, int quantity)
{
    cout << "這是一本書，放在背包裡會自動增加精神回復。" << endl;
}

void GasMask::use(Character& target, int quantity)
{
    cout << "防毒面具是用來探索時攜帶的，無法直接使用。" << endl;
}

void Map::use(Character& target, int quantity)
{
    cout << "地圖是用來探索時降低風險的，無法直接使用。" << endl;
}

void Saxophone::use(Character& target, int quantity)
{
    cout << "這是一個樂器，放在背包裡會自動增加精神回復。" << endl;
}

void Radio::use(Character& target, int quantity)
{
    cout << "收音機可能會接收到特定的訊號..." << endl;
}