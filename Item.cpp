#include <string>
#include <iostream>
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
    for (int i = 0; i < 11; ++i) 
    {
        cout << items[i]->getName() << ": " << items[i]->getQuantity() << endl;
    }
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