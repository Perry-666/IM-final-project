#include <iostream>
#include "CharacterV2.h"
#include "Item.h"
#include "event.h"
using namespace std;

int main()
{

    srand(time(0)); // 設定隨機種子

    cout << "\n================ GAME START ================\n";
    cout << "Welcome to the survival game!\n";
    cout << "You have 15 days to keep  at least one of your characters alive.\n";
    cout << "Below are the initial endowments.\n";
    cout << "Please refer to the table of the share of each item.\n";
    cout << "Allocate them wisely, the maximum capacity is 100.\n";
    cout << "----------------------------------------" << "\n";

    cout << "Water: "<< waterWeight <<endl;
    cout << "Food: " << foodWeight << endl;
    cout << "Axe: " << axeWeight << endl;
    cout << "Pistol: " << pistolWeight << endl;
    cout << "Game: " << gameWeight << endl; //精神
    cout << "Book: " << bookWeight << endl; //精神
    cout << "GasMask: " << gasMaskWeight << endl;
    cout << "Map: " << mapWeight << endl;
    cout << "Saxophone: " << saxophoneWeight << endl; //精神
    cout << "Radio: " << radioWeight << endl;
    cout << "medKit: " << medkitWeight << endl; //生病

    int initials[11] = {0};

    while (true)
    {   
        int total = 0;
        cout << "Please allocate your items below.\n";
        cout << "Except for water and food, each item can only be chosen once (0 or 1).\n";
        
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
            else if (i == 5){
                cout << "Book : " ; 
                cin >> initials[i] ;
                total += initials[i] * bookWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * bookWeight;
                    continue;
                }
            }
            else if (i == 6){
                cout << "GasMask : " ; 
                cin >> initials[i] ;
                total += initials[i] * gasMaskWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * gasMaskWeight;
                    continue;
                }
            }
            else if (i == 7){
                cout << "Map : " ; 
                cin >> initials[i] ;
                total += initials[i] * mapWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * mapWeight;
                    continue;
                }
            }
            else if (i == 8){
                cout << "Saxophone : " ; 
                cin >> initials[i] ;
                total += initials[i] * saxophoneWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * saxophoneWeight;
                    continue;
                }
            }
            else if (i == 9){
                cout << "Radio : " ;
                cin >> initials[i] ;
                total += initials[i] * radioWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * radioWeight;
                    continue;
                }
            }
            else if (i == 10){
                cout << "Medkit : " ; 
                cin >> initials[i] ;
                total += initials[i] * medkitWeight;
                if(initials[i] < 0 || initials[i] > 1) //不可為負
                {
                    cout << "Invalid input for item " << endl;
                    i--;
                    total -= initials[i] * medkitWeight;
                    continue;
                }
            }
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

    
   
    Cindy cindy;
    Chris chris;
    ExpeditionSystem myExpedition;


    int days = 1;
    
    // 秉駪
    int event1Day = rand() % 3 + 1; // 突發事件開始日（1-3)
    int event2Day = rand() % 2 + 3; // 突發事件開始日 (3-4)
    int event3Day = rand() % 3 + 6; // 突發事件開始日 (6-8)
    int event4Day = rand() % 3 + 8; // 突發事件開始日 (9-11)
    int event5Day = rand() % 3 + 11; // 突發事件開始日 (11-13)

    while(days <= 15)
    {   


        /*

        if(!cindy.isAliveStatus() && !chris.isAliveStatus()){
            cout << "\n========= GAME OVER =========\n";
            cout << "所有人都不幸身亡了..." << "\n";
            return 0;
        }

        */


        cout << "\n========================================\n";
        cout << " [ Day " << days << " ]\n";
        cout << "========================================\n";


        // 計算本日娛樂精神加成
        int mentalBonus  = playerPackage.entertainmentMentalBonus();
        if(mentalBonus > 0){
            cout << ">>> 娛樂道具發揮作用，本日精神回復 +" << mentalBonus << "\n";
        }

        

        // 冒險部分
        if (myExpedition.checkReturn()) 
        {
            myExpedition.resolveReturn(playerPackage, cindy, chris);
            if(myExpedition.getExpeditionName() == "Cindy" && myExpedition.neverBack)
            {
                cindy.isInTheWild = false;
            }
            if(myExpedition.getExpeditionName() == "Chris" && myExpedition.neverBack)
            {
                chris.isInTheWild = false;
            }
        }
        // 已經死在外面不會回來了
        int nextNeverBackMsg = 0;
        if(myExpedition.neverBack && nextNeverBackMsg < 2)
        {
            cout << myExpedition.getExpeditionName() << "已經好久沒回來了，不知道在外頭發生什麼事";
            nextNeverBackMsg++;
        }
        else if(myExpedition.neverBack && nextNeverBackMsg >= 2)
        {
            cout << myExpedition.getExpeditionName() << "似乎永遠不會回來了吧...";
        }


        // Cindy回合
        if(cindy.isAliveStatus()){
            if(cindy.isInTheWild){
                cout << ">> Cindy目前正在外面探險" << "\n";
            }
            else{
                cindy.showStatus();
                if(cindy.isSickStatus()){ // 生病檢查
                    int kits = playerPackage.showItemQuantity("medkit");
                    if(kits > 0){
                        cout << "!!! Cindy 生病了 (背包擁有 Medkit:" << kits << ") !!!\n";
                        cout << "要使用急救包醫治嗎? (y/n): ";
                        char choice;
                        cin >> choice;
                        if(choice == 'y' || choice == 'Y') {
                            playerPackage.useItem("medKit", 1, cindy);
                            cout << ">> Cindy 使用了急救包，恢復健康！\n";
                        }
                    }
                    else{
                        cout << "!!! Cindy 生病了，但已無急救包可用 (若持續 3 天將死亡)。\n";
                    }
                }
                // 補給
                cout << "分配給 Cindy -> 食物: ";
                int f;
                cin >> f;
                cout << "             -> 水: ";
                int w;
                cin >> w;
                if(f > 0){
                    playerPackage.useItem("can", f, cindy);
                }
                if(w > 0){
                    playerPackage.useItem("bottled water", w, cindy);
                }


                cindy.passDay(mentalBonus);
            }
        }
        else{
            cout << ">> Cindy 已死亡。\n";
        }
        

        cout << "----------------------------------------\n";


        // Chris回合
        if(chris.isAliveStatus()){
            if(chris.isInTheWild){
                cout << ">> Chris目前正在外面探險" << "\n";
            }
            else{
                chris.showStatus();
                if(chris.isSickStatus()){ // 生病檢查
                    int kits = playerPackage.showItemQuantity("medkit");
                    if(kits > 0){
                        cout << "!!! Chris 生病了 (背包擁有 MedKit:" << kits << ") !!!\n";
                        cout << "要使用急救包醫治嗎? (y/n): ";
                        char choice;
                        cin >> choice;
                        if(choice == 'y' || choice == 'Y') {
                            playerPackage.useItem("medkit", 1, chris);
                            cout << ">> Chris 使用了急救包，恢復健康！\n";
                        }
                    }
                    else{
                        cout << "!!! Chris 生病了，但已無急救包可用 (若持續 3 天將死亡)。\n";
                    }
                }
                // 補給
                cout << "分配給 Chris -> 食物: ";
                int f;
                cin >> f;
                cout << "             -> 水: ";
                int w;
                cin >> w;
                if(f > 0){
                    playerPackage.useItem("can", f, chris);
                }
                if(w > 0){
                    playerPackage.useItem("bottled water", w, chris);
                }


                chris.passDay(mentalBonus);
            }
        }
        else{
            cout << ">> Chris 已死亡。\n";
        }


        // ====================
        // 第1-2天突發事件：神秘皮箱
        if(days == event1Day){
            MysteryCase event1;
            event1.showEvent();


            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;


            event1.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
        }
        

        // 第3-4天突發事件：神秘的訪客
        if(days == event2Day){
            StrangeVisitor event2;
            event2.showEvent();

            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;

            event2.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
        }

        // 第6-7天突發事件：拜訪鄰居
        if(days == event3Day){
            StrangeVisitor event3;
            event3.showEvent();

            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;

            event3.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
        }

        // 第8-9天突發事件：樓上的噪音
        if(days == event4Day){
            NoiseUpstairs event4;
            event4.showEvent();

            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;

            event4.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
        }


        // 突發事件5:恐怖生物
        if (days == event5Day) {
            if (creatureDay != 4 && creatureDay > 0) {    
                cout << "這生物還在附近徘徊，我們必須小心應對。" << "\n";
                cout << "(精神 -10)" << "\n";
                cindy.mentalChange(-10);
                chris.mentalChange(-10);
                creatureDay--;
            }
        }

        // 突發事件6:無線電訊號
        if (days == 5) { // 幫你改成event6
            RadioSignal event6;
            event6.showEvent();
            char choice = 'y'; // 預設選擇yes
            event6.makeChoice(choice, cindy, chris, playerPackage, days);
            cout << "----------------------------------------" << "\n";
        }
        else if (days == 14) {
            RadioSignal event6;
            event6.showEvent();
            char choice = 'n'; // 預設選擇no
            event6.makeChoice(choice, cindy, chris, playerPackage, days);
            cout << "----------------------------------------" << "\n";
        }
        

        // --- 玩家決策 (如果沒人在外面並且兩人都活著，可以派人) ---
        if (!myExpedition.isExpeditionActive() && cindy.isAliveStatus() && chris.isAliveStatus() 
            && !cindy.isInTheWild && !chris.isInTheWild && days >= 5 && days <= 10 && myExpedition.hadExpedition == false)
        {
            cout << "----------------------------------------" << endl;
            cout << "現在避難所全員都在。" << endl;
            cout << "要派人出去探險嗎嗎？ (y:是 / n:否): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') 
            {
                cout << "請輸入要派出的人名 (例如 Cindy/Chris): ";
                string name;
                cin >> name;
                if(name == "Cindy" && cindy.isAliveStatus())
                {
                    cindy.isInTheWild = true;
                    myExpedition.startExpedition(cindy, playerPackage);
                }
                else if(name == "Chris" && chris.isAliveStatus())
                {
                    chris.isInTheWild = true;
                    myExpedition.startExpedition(chris, playerPackage);
                }
                else
                {
                    cout << "輸入的名字無效，今天選擇不冒險" << endl;
                }
            }
            else
            {
                cout << "今天選擇不冒險";
            }
        } 



        if(myExpedition.getExpeditionName() == "Cindy")
            {
                myExpedition.updateDaily(cindy);
            }
        else if(myExpedition.getExpeditionName() == "Chris")
            {
                myExpedition.updateDaily(chris);;
            }


        cout << "this day ends\n";
        cout << "------------------------------\n";
        days++;
    }


    cout << "\n========================================\n";

    
    if(cindy.isAliveStatus() || chris.isAliveStatus()){
        cout << "恭喜！至少有一名倖存者活過了 15 天！\n";
        cout << ">> VICTORY <<\n";
    } 
    else{
        cout << "很遺憾，所有人都未能倖存...\n";
        cout << ">> DEFEAT <<\n";
    }


    return 0;
}
