#include <string>
#include <iostream>
#include <vector>
#include "CharacterV2.h"
using namespace std;
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


class Package
{
    private:
        string packageName;
        int capacity;
        Item* items[11];
    public:
        Package (int qWater, int qFood, int qAxe, 
        int qPistol, int qGame, int qBook, int qGasMask, int qMap, int qSaxophone, int qRadio, int qMedKit);
        void addItem(string addName, int q);
        void useItem(string useName, int q, Character& character);
        int showItemQuantity(string itemName);
        void deleteItem(string delName, int q);
        void displayItems();
        ~Package();

        int entertainmentMentalBonus(); //承毅
};

class Item
{
    protected:
        string itemName;
        int weight;
        int quantity;
        bool consumable;
    public:
        Item (const string & n, int w, int q, bool c)
                : itemName (n), weight (w),quantity (q), consumable (c) {}
        
        string getName() const ;
        int getWeight() const;
        int getQuantity() const;
        void addQuantity(int newQuant);
        virtual ~Item() {}
        virtual void use(Character& target, int quantity) = 0;
};

// Derived item classes
class Water : public Item
{
    private:
        int thirstHeal;
    public:
        Water (const string & n, int q)
                : Item (n, waterWeight, q, true), thirstHeal(30) {}

        void use(Character& target, int quantity) override;
};

class Food : public Item
{
    private:
        int hungerHeal;
    public:
        Food (const string & n, int q)
                : Item (n, foodWeight, q, true), hungerHeal(25){}
        
        void use(Character& target, int quantity) override;
};

class Axe : public Item
{
    private:
        
    public:
        Axe (const string & n, int q)
                : Item (n, axeWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

class Pistol : public Item
{
    private:
        
    public:
        Pistol (const string & n, int q)
                : Item (n, pistolWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

class Game : public Item
{
    private:
        
    public:
        Game (const string & n, int q)
                : Item (n, gameWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

class Book : public Item
{
    private:
        
    public:
        Book (const string & n, int q)
                : Item (n, bookWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

class GasMask : public Item
{
    private:
        
    public:
        GasMask (const string & n, int q)
                : Item (n, gasMaskWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

class Map : public Item
{
    private:
        
    public:
        Map (const string & n, int q)
                : Item (n, mapWeight, q, true) {}
        void use(Character& target, int quantity) override;
};

class Saxophone : public Item
{
    private:
        
    public:
        Saxophone (const string & n, int q)
                : Item (n, saxophoneWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

class Radio : public Item
{
    private:
        
    public:
        Radio (const string & n, int q)
                : Item (n, radioWeight, q, false) {}
        void use(Character& target, int quantity) override;
};

class Medkit : public Item
{
    private:
        
    public:
        Medkit (const string & n ,int q)
                : Item (n, medkitWeight, q, true) {}
        void use(Character& target, int quantity) override;
};
