#include <iostream>
#include <string>
#include <iomanip>
#include "CharacterV2.h"
#include "Item.h"
using namespace std;

Package::Package(int qWater, int qFood, int qAxe, 
        int qPistol, int qGame, int qBook, int qGasMask, int qMap, int qSaxophone, int qRadio, int qMedKit) 
{
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

void Package::addItem(string addName, int q)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == addName) 
        {
            items[i]->addQuantity(q);
            cout << q << " " << addName << "(s) added to the package." << endl;
            return;
        }
    }
    cout << "Item " << addName << " not found in the package." << endl;
}

void Package::useItem(string useName, int q, Character& character)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == useName) 
        {
            if (items[i]->getQuantity() >= q) 
            {
                items[i]->addQuantity(-q);
                cout << q << " " << useName << "(s) used from the package." << endl;
                items[i]->use(character, q);
            } 
            else 
            {
                cout << "Not enough " << useName << " to use." << endl;
            }
            return;
        }
    }
    cout << "Item " << useName << " not found in the package." << endl;
}

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

void Package::deleteItem(string delName, int q)
{
    for (int i = 0; i < 11; ++i) 
    {
        if (items[i]->getName() == delName) 
        {
            if (items[i]->getQuantity() >= q) 
            {
                items[i]->addQuantity(-q);
                cout << q << " " << delName << "(s) deleted from the package." << endl;
            } 
            else 
            {
                cout << "Not enough " << delName << " to delete." << endl;
            }
            return;
        }
    }
    cout << "Item " << delName << " not found in the package." << endl;
}

void Package::displayItems()
{
    cout << "Items in the package:" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < 11; ++i) 
    {
        cout << left << setw(20) << (items[i]->getName() + ": " + to_string(items[i]->getQuantity()));

        if (i % 2 == 1) {
            cout << endl;
        }
    }
    cout << endl;
    
    cout << "----------------------------------------" << endl;
}

Package::~Package()
{
    for (int i = 0; i < 11; ++i) 
    {
        delete items[i];
    }
}

int Package::entertainmentMentalBonus(){ //承毅
    int bonus = 0;


    if(items[4]->getQuantity() > 0){ //遊戲
        bonus += 5;
    }
    if(items[5]->getQuantity() > 0){ //書
        bonus += 5;
    }
    if(items[8]->getQuantity() > 0){ //薩克斯風
        bonus += 5;
    }


    return bonus;
}

// ------------------------------------------------------------
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

// ------------------------------------------------------------

void Water::use(Character& target, int quantity)
{
    target.drinkWater(quantity);
}

void Food::use(Character& target, int quantity)
{
    target.eatFood(quantity);
}

void Medkit::use(Character& target, int quantity){ // 承毅
    target.recoveryFull();
}

// ==================== 補上缺少的 use 實作 ====================

void Axe::use(Character& target, int quantity)
{
    cout << "斧頭是用來裝備或觸發事件的，無法直接使用。" << endl;
    // 這裡只是為了滿足編譯器，實際上斧頭邏輯可能在 Event 裡判斷
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