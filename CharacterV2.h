#include <string>
#include <iostream>
using namespace std;

class Character{
protected:
    string name;
    int thirst;
    int hunger;
    int mental;
    int dailyWaterConsumed;
    int dailyFoodConsumed;        
    int dailySpiritConsumed;
    
    bool isAlive;
    bool isSick;
    int sickDays;

    const int bottleOfWaterRecoveryAmount;        
    const int cansOfFoodRecoveryAmount;        
    string getStatus(int value, string type);                

public:
    Character(const string& n, int waterCons, int foodCons, int spiritCons);
    
    
    virtual ~Character();
    virtual void passDay(int mentalBonus = 0);
    virtual void drinkWater(int bottles);
    virtual void eatFood(int cans);
    
    void showStatus();

    bool isSickStatus() const;

    void recoveryFull();
    
    bool isInTheWild;

    bool isAliveStatus() const { return isAlive; } // 皓瑋

    void kill();   // 皓瑋

    bool bodyNotGood() const { return (thirst < 20) || (hunger < 20) || (mental < 25); }  // 皓瑋

    string getName() const { return name; }

    void setStatus(int t, int h, int m);

    void thirstChange(int units);

    void hungerChange(int units);

    void mentalChange(int units);

};


class Cindy : public Character{
public:
    Cindy() : Character("Cindy", 35, 20, 15) {isInTheWild = false;}
    
    
    void drinkWater(int bottles) override{
        if(!isAlive) return; 
        
        
        this->thirst += bottles * bottleOfWaterRecoveryAmount;
        if(this->thirst > 100){
            this->thirst = 100;
        }
    }

    
    void eatFood(int cans) override{
        if(!isAlive) return;
        
        this->hunger += cans * cansOfFoodRecoveryAmount;
        if(this->hunger > 100){
            this->hunger = 100;
        }
    }
};


class Chris : public Character{
public:
    Chris() : Character("Chris", 25, 25, 15){isInTheWild = false;}
    
    void drinkWater(int bottles) override {
        if(!isAlive) return;
        
        this->thirst += bottles * bottleOfWaterRecoveryAmount;
        if(this->thirst > 100){
            this->thirst = 100;
        }
    }

    void eatFood(int cans) override {
        if(!isAlive) return;
        
        this->hunger += cans * cansOfFoodRecoveryAmount;
        if(this->hunger > 100){
            this->hunger = 100;
        }
    }
};





