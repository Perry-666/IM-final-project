#include "Character.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <iomanip>
using namespace std;

// 取得狀態描述文字
string Character::getStatus(int value, string type){
    if(type == "water"){
        if(value >= 80) return "滿水";
        if(value >= 50) return "口渴";
        if(value >= 20) return "脫水";
        return "危險";
    }
    else if(type == "food"){
        if(value >= 85) return "飽足";
        if(value >= 60) return "小餓";
        if(value >= 20) return "超餓";
        return "危險";
    }
    else if(type == "spirit"){
        if(value >= 75) return "清醒";
        if(value >= 50) return "暴躁";
        if(value >= 25) return "發瘋";
        return "危險";
    }
    return "未知";
}

// 建構子
Character::Character(const string& n, int waterCons, int foodCons, int spiritCons)
         : name(n), dailyWaterConsumed(waterCons), dailyFoodConsumed(foodCons), dailySpiritConsumed(spiritCons), 
           bottleOfWaterRecoveryAmount(35), cansOfFoodRecoveryAmount(25){
            thirst = 100;
            hunger = 100;
            mental = 100;
            isAlive = true; 
            isSick = false; 
            sickDays = 0;
}

Character::~Character(){
}

// 過一天的邏輯處理
void Character::passDay(int mentalBonus){
    if(!isAlive) return;

    // 扣除每日消耗
    thirst -= dailyWaterConsumed;
    hunger -= dailyFoodConsumed;
    mental -= dailySpiritConsumed;

    // 加上精神獎勵 (娛樂道具)
    if(mentalBonus > 0){
        mental += mentalBonus;
    }
    if(mental > 100){
        mental = 100;
    }

    // 檢查是否死亡 (數值歸零)
    if(thirst <= 0 || hunger <= 0 || mental <= 0){
        isAlive = false;
        if(thirst < 0) thirst = 0; 
        if(hunger < 0) hunger = 0; 
        if(mental < 0) mental = 0;
        
        // 只有在避難所內才印出訊息，避免探險時劇透
        if (!isInTheWild) {
            cout << "!!! " << name << " 不幸死亡了 !!!" << "\n";
        }
        return;
    }

    // 處理生病邏輯
    if(isSick){
        sickDays++; 
        if (!isInTheWild) {
            cout << name << "處於生病狀態 (第 " << sickDays << " 天)..." << "\n";
        }
        
        // 生病超過 3 天死亡
        if(sickDays >= 3){
            isAlive = false;
            if (!isInTheWild) {
                cout << "!!! " << name << "因為重病不幸身亡 !!!" << "\n";
            }
            return;
        }
    }
    else{
        // 檢查是否因為數值過低而患病
        bool inDanger = (thirst < 20) || (hunger < 20) || (mental < 25);
        if(inDanger){
            if(rand() % 3 == 0){ // 1/3 機率生病
                isSick = true;
                sickDays = 0;
                if (!isInTheWild) {
                    cout << "!!! " << name << " 因為狀況不佳而生病了 !!!" << "\n";
                }
            }
        }
    }
}

void Character::drinkWater(int bottles){
    if(!isAlive){
        cout << name << "已經死亡，無法喝水。" << endl;
        return;
    }
    thirst += bottles * bottleOfWaterRecoveryAmount;
    if(thirst > 100) thirst = 100; 
}

void Character::eatFood(int cans){
    if(!isAlive){
        cout << name << "已經死亡，無法進食。" << endl;
        return;
    }
    hunger += cans * cansOfFoodRecoveryAmount;
    if(hunger > 100) hunger = 100; 
}

// 顯示狀態面板
void Character::showStatus(){
    cout << "+--------------------------------------+" << "\n";
    cout << "| 狀態[" << name << "]                         |" << "\n"; 
    
    if(!isAlive){
        cout << "|             (已死亡 💀)              |" << "\n";
    }
    else if(isSick){
        cout << "| (生病中 😷 - 第 " << sickDays << " 天)              |" << "\n";
    }
    
    if(isAlive) {
        cout << "|--------------------------------------|" << "\n";
        // 使用 setw 排版讓數值對齊
        cout << "| 飢渴 : " << " (" << setw(6) << getStatus(thirst, "water") << ")                      |\n";
        cout << "| 飢餓 : " << " (" << setw(6) << getStatus(hunger, "food") << ")                      |\n";
        cout << "| 精神 : " << " (" << setw(6) << getStatus(mental, "spirit") << ")                      |\n";
    }
    cout << "+--------------------------------------+" << "\n";
}

bool Character::isSickStatus() const{
    return isSick;
}

// 完全康復 (急救包效果)
void Character::recoveryFull(){
    isSick = false;
    sickDays = 0;

    thirst = 100;
    hunger = 100;
    mental = 100;

    cout << name << "使用了急救包後身體完全康復" << "\n";
}

void Character::kill()
{ 
    isAlive = false; 
    thirst = 0; hunger = 0; mental = 0;
}

void Character::setStatus(int t, int h, int m)
{       
    thirst = t;
    hunger = h;
    mental = m;
}

void Character::thirstChange(int units){
    thirst += units;
}

void Character::hungerChange(int units){
    hunger += units;
}

void Character::mentalChange(int units){
    mental += units;
}