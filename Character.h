#ifndef CHARACTERV2_H   
#define CHARACTERV2_H

#include <string>
#include <iostream>
using namespace std;

// --- 角色基底類別 ---
class Character{
protected:
    string name;
    int thirst; // 飢渴值 (0-100)
    int hunger; // 飢餓值 (0-100)
    int mental; // 精神值 (0-100)
    
    // 每日消耗量
    int dailyWaterConsumed;
    int dailyFoodConsumed;        
    int dailySpiritConsumed;
    
    bool isAlive;
    bool isSick;
    int sickDays; // 生病天數

    const int bottleOfWaterRecoveryAmount;        
    const int cansOfFoodRecoveryAmount;        
    
    // 輔助函式：將數值轉為文字描述 (如：飽足、飢餓)
    string getStatus(int value, string type);    

public:
    Character(const string& n, int waterCons, int foodCons, int spiritCons);
    virtual ~Character();

    virtual void specialAbility() = 0; // 純虛擬函式：特殊能力

    virtual void passDay(int mentalBonus = 0); // 經過一天 (扣減數值)
    virtual void drinkWater(int bottles);      // 喝水
    virtual void eatFood(int cans);            // 吃飯
    
    void showStatus(); // 顯示角色狀態面板
    bool isSickStatus() const; // 回傳是否生病
    bool isAliveStatus() const { return isAlive; } // 回傳是否存活
    bool isInTheWild; // 標記是否正在外面冒險

    void recoveryFull(); // 使用急救包，恢復滿狀態並治癒生病
    void kill();         // 強制設定為死亡

    // 檢查身體狀況是否不佳 (用於事件判定)
    bool bodyNotGood() const { return (thirst < 20) || (hunger < 20) || (mental < 25); }

    string getName() const { return name; }

    // 直接設定數值 (用於事件懲罰)
    void setStatus(int t, int h, int m);

    // 增減數值 (正數加，負數減)
    void thirstChange(int units);
    void hungerChange(int units);
    void mentalChange(int units);
};

// --- Cindy 角色類別 ---
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

    void specialAbility() override{
        if(!isAlive){
            return;
        }
        // 特殊能力實作預留
    }
};

// --- Chris 角色類別 ---
class Chris : public Character{
public:
    Chris() : Character("Chris", 25, 25, 15){isInTheWild = false;}
    
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

    void specialAbility() override{
        if(!isAlive){
            return;
        }
        // 特殊能力實作預留
    }
};

#endif