#include "CharacterV2.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;


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
Character::Character(const string& n, int waterCons, int foodCons, int spiritCons)
         : name(n), dailyWaterConsumed(waterCons), dailyFoodConsumed(foodCons), dailySpiritConsumed(spiritCons), 
           bottleOfWaterRecoveryAmount(30), cansOfFoodRecoveryAmount(10){
            thirst = 100;
            hunger = 100;
            mental = 100;
            isAlive = true; 
            isSick = false; 
            sickDays = 0;
}
Character::~Character(){
}
void Character::passDay(int mentalBonus){
    if(!isAlive) return;


    thirst -= dailyWaterConsumed;
    hunger -= dailyFoodConsumed;
    mental -= dailySpiritConsumed;


    if(mentalBonus > 0){
        mental += mentalBonus;
    }
    if(mental > 100){
        mental = 100;
    }


    if(thirst <= 0 || hunger <= 0 || mental <= 0){
        isAlive = false;
        if(thirst < 0) thirst = 0; 
        if(hunger < 0) hunger = 0; 
        if(mental < 0) mental = 0;
        cout << "!!! " << name << " 不幸死亡了 !!!" << "\n";
        return;
    }

    if(isSick){
        sickDays++; 
        cout << name << "處於生病狀態 (第 " << sickDays << " 天)..." << "\n";
        
        if(sickDays >= 3){
            isAlive = false;
            cout << "!!! " << name << "因為重病不幸身亡 !!!" << "\n";
            return;
        }
    }
    else{
        bool inDanger = (thirst < 20) || (hunger < 20) || (mental < 25);
        if(inDanger){
            if(rand() % 2 == 0){
                isSick = true;
                sickDays = 0;
                cout << "!!! " << name << " 因為狀況不佳而生病了 !!!" << "\n";
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
void Character::showStatus(){
    cout << "狀態 [" << name << "] :";
    if(!isAlive){
        cout << "(已死亡 💀)";
    }
    else if(isSick){
        cout << " (生病中 😷 - 第" << sickDays << "天)";
    }
    cout << "\n";
    cout << ">------------<" << "\n";
    cout << "飢渴 : " << thirst << " (" << getStatus(thirst, "water") << ")" << "\n";
    cout << "飢餓 : " << hunger << " (" << getStatus(hunger, "food") << ")" << "\n";
    cout << "精神 : " << mental << " (" << getStatus(mental, "spirit") << ")" << "\n";
    cout << ">------------<" << "\n";
}
bool Character::isSickStatus() const{
    return isSick;
}
void Character::recoveryFull(){
    isSick = false;
    sickDays = 0;


    thirst = 100;
    hunger = 100;
    mental = 100;


    cout << name << "使用了急救包後身體完全康復" << "\n";
}

