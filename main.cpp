#include <iostream>
#include "CharacterV2.h"
#include "Item.h"
using namespace std;

int main()
{
    cout << "Welcome to the survival game!\n";
    cout << "You have 15 days to keep  at least one of your characters alive.\n";
    cout << "Below are the initial endowments.\n";
    cout << "Please refer to the table of the share of each item.\n";
    cout << "Allocate them wisely, the maximum capacity is 100.\n";

    cout << "Water"<< waterWeight <<endl;
    cout << "Food" << foodWeight << endl;
    cout << "Axe" << axeWeight << endl;
    cout << "Pistol" << pistolWeight << endl;
    cout << "Game" << gameWeight << endl; //精神
    cout << "Book" << bookWeight << endl; //精神
    cout << "GasMask" << gasMaskWeight << endl;
    cout << "Map" << mapWeight << endl;
    cout << "Saxophone" << saxophoneWeight << endl; //精神
    cout << "Radio" << radioWeight << endl;
    cout << "medKit" << medkitWeight << endl; //生病

    int initials[11] = {0};

    while (true)
    {   
        int total = 0;
        cout << "Please allocate your items: \n";
        
        for (int i = 0; i < 11; i++)
        {
            cout << "Current package capacity remaining: " << packageCapacity - total << endl;
            
            if (i == 0){
                cout << "Water : " ; 
                cin >> initials[i] ;
                total += initials[i] * waterWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * waterWeight;
                    continue;
                }  
            }
            else if (i == 1){
                cout << "Food : " ; 
                cin >> initials[i] ;
                total += initials[i] * foodWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * foodWeight;
                    continue;
                }   
            }
            else if (i == 2){
                cout << "Axe : " ; 
                cin >> initials[i] ;
                total += initials[i] * axeWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負且不可超過1
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * axeWeight;
                    continue;
                }
            }
            else if (i == 3){
                cout << "Pistol : " ; 
                cin >> initials[i] ;
                total += initials[i] * pistolWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負且不可超過1
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * pistolWeight;
                    continue;
                }
            }
            else if (i == 4){
                cout << "Game : " ; 
                cin >> initials[i] ;
                total += initials[i] * gameWeight;
                if(initials[i] < 0|| initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * gameWeight;
                    continue;
                }
            }
            else if (i == 5)
                total += initials[i] * bookWeight;
            else if (i == 6)
                total += initials[i] * gasMaskWeight;
            else if (i == 7)
                total += initials[i] * mapWeight;
            else if (i == 8)
                total += initials[i] * saxophoneWeight;
            else if (i == 9)
                total += initials[i] * radioWeight;
            else if (i == 10)
                total += initials[i] * medkitWeight;

            else if (total > packageCapacity)
            {
                cout << "Allocation exceeds capacity. Please reallocate.\n"; 
                total = 0; //超過總額需重新分配
                break;
            }   
        }
    }   

    Package playerPackage(initials[0], initials[1], initials[2], initials[3], initials[4],initials[5], 
                      initials[6], initials[7], initials[8], initials[9], initials[10]);

    
    int days = 1;
    Cindy cindy;
    Chris chris;

    

    /*
    int bonus = playerPackage.entertainmentMentalBonus();
    cindy.passDay(bonus);
    chris.passDay(bonus);
    */
    
    while(days <= 5)
    {
        cout << "Day " << days << ":\n";
        cindy.isAlive() ? cout << "Cindy is alive.\n" : cout << "Cindy has perished.\n";
        cindy.displayStatus();
        cindy.passDay();

        int feedAmount, waterAmount, entertainAmount;
        cin >> feedAmount >> waterAmount >> entertainAmount;
        cindy.feed(feedAmount);
        cindy.giveWater(waterAmount);
        cindy.entertain(entertainAmount);

        cout << "this day ends\n";
        cout << "-----------------------\n";
        days++;
    }
}