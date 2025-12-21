#include <iostream>
#include <limits>   
#include "Character.h"
#include "Item.h"
#include "event.h"
using namespace std;


void pressEnterToContinue();
int getValidInt();


int main()
{

    srand(time(0)); // 設定隨機種子

    // --- 遊戲開頭介紹 ---
    cout << "\n=======================================================\n";
    cout << "               末日生存 (Survival Game)               \n";
    cout << "=======================================================\n\n";
    
    cout << "外面世界因為某種因素從此改變了。\n";
    cout << "目前外面已不適合人類出去。\n";
    cout << "幸運的是，你們（Cindy Chris）及時躲進了地下避難所。\n";
    cout << "不幸的是，避難所裡的物資非常有限，而救援遙遙無期。\n\n";
    
    cout << "現在，你必須操控兩位倖存者：\n";
    
    cout << "你的目標是讓至少一人在險惡的末日環境中存活 15 天。\n";
    cout << "你需要精打細算每一滴水、每一口食物，並面對突如其來的危機。\n";
    cout << "無論是來自外部的威脅，還是內心的崩潰，都將考驗著你們...\n";

    pressEnterToContinue();

    // 介紹各種物品
    cout << "\n[初期物資分配]\n";
    cout << "避難所的空間是有限的，背包最大容量只有 100 單位。\n";
    cout << "請參考下方物資的重量表，明智地分配你們的初始裝備。\n";
    cout << "有些物品能保命，有些能安撫心靈，而有些則是探險必備。\n";
    cout << "----------------------------------------" << "\n";

    cout << " [消耗品] (可攜帶多個)\n";
    cout << " - Water (水): " << waterWeight << " (解渴與生存之源)\n";
    cout << " - Food (食物): " << foodWeight << " (止飢與體力來源)\n";
    
    cout << "\n [裝備] (只能攜帶 0 或 1 個)\n";
    cout << " - Axe (斧頭): " << axeWeight << " (防身與破門工具)\n";
    cout << " - Pistol (手槍): " << pistolWeight << " (強大的遠程武器)\n";
    cout << " - GasMask (防毒面具): " << gasMaskWeight << " (外出探險必備，防止輻射病)\n";
    cout << " - Map (地圖): " << mapWeight << " (降低外出探險迷路的風險)\n";
    cout << " - Medkit (急救包): " << medkitWeight << " (能治癒疾病與重傷，極其珍貴)\n";

    cout << "\n [娛樂] (只能攜帶 0 或 1 個，可回復精神)\n";
    cout << " - Game (遊戲): " << gameWeight << "\n";
    cout << " - Book (書本): " << bookWeight << "\n";
    cout << " - Saxophone (薩克斯風): " << saxophoneWeight << "\n";
    cout << " - Radio (收音機): " << radioWeight << " (不僅是娛樂，或許還能接收外界訊號...)\n";
    
    cout << "----------------------------------------" << "\n";

    int initials[11] = {0};

    // --- 初始物資分配迴圈 ---
    while (true)
    {   
        int total = 0;
        cout << "\n>>> 請開始分配物資 (輸入數量):\n";
        
        for (int i = 0; i < 11; i++)
        {
            // 若當前背包超過總額，就重新分配
            if (total > packageCapacity)
            {
                cout << "!!! 警告：總重量超過負重限制 (100) !!!\n"; 
                cout << "請重新開始分配。\n";
                break;
            }

            cout << "剩餘負重: " << packageCapacity - total << endl;
            
            if (i == 0){
                cout << "Water : " ; 
                initials[i] = getValidInt();
                total += initials[i] * waterWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * waterWeight;
                    i--;
                    continue;
                }  
            }

            else if (i == 1){
                cout << "Food : " ; 
                initials[i] = getValidInt();
                total += initials[i] * foodWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * foodWeight;
                    i--;
                    continue;
                }   
            }
            else if (i == 2){
                cout << "Axe : " ; 
                initials[i] = getValidInt();
                total += initials[i] * axeWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * axeWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * axeWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 3){
                cout << "Pistol : " ; 
                initials[i] = getValidInt();
                total += initials[i] * pistolWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * pistolWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * pistolWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 4){
                cout << "Game : " ; 
                initials[i] = getValidInt();
                total += initials[i] * gameWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * gameWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * gameWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 5){
                cout << "Book : " ; 
                initials[i] = getValidInt();
                total += initials[i] * bookWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * bookWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * bookWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 6){
                cout << "GasMask : " ; 
                initials[i] = getValidInt();
                total += initials[i] * gasMaskWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * gasMaskWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * gasMaskWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 7){
                cout << "Map : " ; 
                initials[i] = getValidInt();
                total += initials[i] * mapWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * mapWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * mapWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 8){
                cout << "Saxophone : " ; 
                initials[i] = getValidInt();
                total += initials[i] * saxophoneWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * saxophoneWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * saxophoneWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 9){
                cout << "Radio : " ;
                initials[i] = getValidInt();
                total += initials[i] * radioWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * radioWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * radioWeight;
                    i--;
                    continue;
                }
            }
            else if (i == 10){
                cout << "Medkit : " ; 
                initials[i] = getValidInt();
                total += initials[i] * medkitWeight;
                if(initials[i] < 0) //不可為負
                {
                    cout << "無效輸入！數量不能為負。" << endl;
                    total -= initials[i] * medkitWeight;
                    i--;
                    continue;
                }
                else if(initials[i] > 1) // 不可超過1
                {
                    cout << "無效輸入！不可超過1。" << endl;
                    total -= initials[i] * medkitWeight;
                    i--;
                    continue;
                }
            }
        }
        if (total <= packageCapacity && total > 0)
        {
            cout << "\n>>> 分配完成！總重量: " << total << "/100\n";
            cout << "避難所的大門緩緩關閉，生存挑戰正式開始...\n";
            pressEnterToContinue();
            break;
        } 
        else if (total == 0) {
             cout << "!!! 你什麼都沒帶？這跟自殺沒兩樣，請重新分配 !!!\n";
        } 
    }   
  

    // 初始化遊戲物件
    Package playerPackage("Player Package", initials[0], initials[1], initials[2], initials[3], initials[4],initials[5], 
                      initials[6], initials[7], initials[8], initials[9], initials[10]);

    
   
    Cindy cindy;
    Chris chris;
    ExpeditionSystem myExpedition;


    int days = 1;
    int nextNeverBackMsg = 0;
    
    // 設定突發事件發生的日期
    int event1Day = rand() % 1 + 2; // 突發事件開始日（2)
    int event2Day = rand() % 1 + 4; // 突發事件開始日 (4)
    int event3Day = rand() % 2 + 6; // 突發事件開始日 (6-7)
    int event4Day = rand() % 2 + 9; // 突發事件開始日 (9-10)
    int event5Day = rand() % 2 + 12; // 突發事件開始日 (12-13)

    // --- 遊戲主迴圈 ---
    while(days <= 15)
    {   
        // 檢查是否所有人都死亡
        if(!cindy.isAliveStatus() && !chris.isAliveStatus() || (cindy.isInTheWild == true && !chris.isAliveStatus()) 
        || (chris.isInTheWild == true && !cindy.isAliveStatus())){
            cout << "\n========= GAME OVER =========\n";
            cout << "所有人都不幸身亡或是無人處於地下室..." << "\n";
            cout << "生存天數: " << days - 1 << " 天\n";

            pressEnterToContinue();

            break;
        }


        cout << "\n========================================\n";
        cout << " [ Day " << days << " ]\n";
        cout << "========================================\n";


        // 計算本日娛樂精神加成
        int mentalBonus  = playerPackage.entertainmentMentalBonus();
        if(mentalBonus > 0){
            cout << ">>> 娛樂道具發揮作用，本日精神回復\n";
        }

        if(cindy.isInTheWild) {
            // 如果是 Cindy 出去，且已經被判定死亡
            if (myExpedition.getExpeditionName() == "Cindy" && myExpedition.isDead) 
            {
                cout << ">>> Cindy 毫無音訊... 不知道他在外面過得如何。" << "\n";
                nextNeverBackMsg++;
            }
            else if(myExpedition.getExpeditionName() == "Cindy" && myExpedition.isDead && nextNeverBackMsg >= 2)
            {
                cout << ">>> Cindy 似乎永遠不會回來了吧..." << "\n";
            }
            else 
            {
                cout << ">> Cindy 目前正在外面探險" << "\n";
            }
        }
        else if(!cindy.isAliveStatus() && !cindy.isInTheWild){
            cout << ">>> Cindy已死亡" << "\n";
        }

        if(chris.isInTheWild) {
            // 如果是 Chris 出去，且已經被判定死亡
            if (myExpedition.getExpeditionName() == "Chris" && myExpedition.isDead && nextNeverBackMsg < 2) 
            {
                cout << ">>> Chris 毫無音訊... 不知道他在外面過得如何。" << "\n";
                nextNeverBackMsg++;
            } 
            else if(myExpedition.getExpeditionName() == "Chris" && myExpedition.isDead && nextNeverBackMsg >= 2)
            {
                cout << ">>> Chris 似乎永遠不會回來了吧..." << "\n";
            }
            else 
            {
                cout << ">>> Chris 目前正在外面探險" << "\n";
            }
        }
        else if(!chris.isAliveStatus() && !chris.isInTheWild){
            cout << ">>> Chris已死亡" << "\n";
        }


        // 冒險部分
        if (myExpedition.checkReturn()) 
        {
            myExpedition.resolveReturn(playerPackage, cindy, chris);
            if(myExpedition.getExpeditionName() == "Cindy" && !myExpedition.neverBack && !myExpedition.neverBack)
            {
                cindy.isInTheWild = false;
            }
            if(myExpedition.getExpeditionName() == "Chris" && !myExpedition.neverBack && !myExpedition.neverBack)
            {
                chris.isInTheWild = false;
            }
        }
        // Cindy回合
        if(cindy.isAliveStatus()){
            if(!cindy.isInTheWild){  
                cindy.showStatus();
                if(cindy.isSickStatus()){ // 生病檢查
                    int kits = playerPackage.showItemQuantity("medkit");
                    if(kits > 0){
                        cout << "!!! Cindy 生病了 (背包擁有 Medkit:" << kits << ") !!!\n";
                        cout << "要使用急救包醫治嗎? (y/n): ";
                        char choice;
                        cin >> choice;
                        if(choice == 'y' || choice == 'Y') {
                            playerPackage.useItem("medkit", 1, cindy);
                            cout << ">> Cindy 使用了急救包，恢復健康！\n";
                        }
                    }
                    else{
                        cout << "!!! Cindy 生病了，但已無急救包可用 (若持續 3 天將死亡)。\n";
                    }
                }
                if(cindy.getMental() < 25){
                    cout << "⚠️ Cindy 的精神狀態極差！\n";
                    cout << "要使用特殊能力【樂觀幻想】嗎? (精神+20 / 飽食飲水-10) (y/n): ";
                    char abilityChoice;
                    cin >> abilityChoice;
                    if(abilityChoice == 'y' || abilityChoice == 'Y'){
                        cindy.specialAbility();
                        cindy.showStatus(); // 更新顯示數值
                    }
                }
                // 補給
                playerPackage.displayItems();
                cout << "分配給 Cindy -> 水: ";
                int w;
                w = getValidInt();
                cout << "             -> 食物: ";
                int f;
                f = getValidInt();
                if(w > 0){
                    playerPackage.useItem("bottled water", w, cindy);
                }
                if(f > 0){
                    playerPackage.useItem("can", f, cindy);
                }
            }
        }
        

        cout << "----------------------------------------\n";


        // Chris回合
        if(chris.isAliveStatus()){
            if(!chris.isInTheWild){
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
                if (chris.getThirst() < 20 || chris.getHunger() < 20) {
                    cout << "⚠️ Chris 的生理狀態極差！\n";
                    cout << "要使用特殊能力【極限搜尋】嗎? (飢渴飢餓+10 / 精神-15) (y/n): ";
                    char abilityChoice;
                    cin >> abilityChoice;
                    if(abilityChoice == 'y' || abilityChoice == 'Y'){
                        chris.specialAbility();
                        chris.showStatus(); // 更新顯示數值
                    }
                }
                // 補給
                playerPackage.displayItems();
                cout << "分配給 Chris -> 水: ";
                int w;
                w = getValidInt();
                cout << "             -> 食物: ";
                int f;
                f = getValidInt();
                if(w > 0){
                    playerPackage.useItem("bottled water", w, chris);
                }
                if(f > 0){
                    playerPackage.useItem("can", f, chris);
                }
            }
        }

        // 過一天
        if(cindy.isAliveStatus() && !cindy.isInTheWild)
        {
            cindy.passDay(mentalBonus);
        }

        if(chris.isAliveStatus() && !chris.isInTheWild)
        {
            chris.passDay(mentalBonus);
        }

        if(!cindy.isAliveStatus() && !chris.isAliveStatus())
        {
            continue;
        }

        // ====================
        // 第2天突發事件：神秘皮箱
        if(days == event1Day){
            MysteryCase event1;
            event1.showEvent();


            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;


            event1.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
            pressEnterToContinue();
        }


        // 第4天突發事件：神秘的訪客
        if(days == event2Day){
            StrangeVisitor event2;
            event2.showEvent();

            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;

            event2.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
            pressEnterToContinue();
        }

        // 第6-7天突發事件：拜訪鄰居
        if(days == event3Day){
            VisitNeighbor event3;
            event3.showEvent();

            char choice;
            cout << "請輸入決策 (y/n): ";
            cin >> choice;

            event3.makeChoice(choice, cindy, chris, playerPackage, days);

            cout << "----------------------------------------" << "\n";
            pressEnterToContinue();
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
            pressEnterToContinue();
        }

        
        // 突發事件5:恐怖生物 (可能觸發多次)
        if (creatureDay != 4 && creatureDay > 0) {    
            cout << "這生物還在附近徘徊，我們必須小心應對。" << "\n";
            cout << "(精神 -10)" << "\n";
            cindy.mentalChange(-10);
            chris.mentalChange(-10);
            creatureDay--;
        };
        // 突發事件5:恐怖生物
        if (days == event5Day) {
            HorrificCreature event5;
            event5.showEvent();
            if (initials[4] == 1 || initials[5]== 1 || initials[7] == 1) { // 有可供犧牲的物品
                char choice = 'y'; // 預設選擇yes
                event5.makeChoice(choice, cindy, chris, playerPackage, days);
            } else {
                cout << "沒有可供犧牲的物品，只能選擇面對它。" << "\n";
                char choice = 'n'; // 預設選擇no
                event5.makeChoice(choice, cindy, chris, playerPackage, days);
            }
            cout << "----------------------------------------" << "\n";
            pressEnterToContinue();
        }

        // 突發事件6:無線電訊號
        if (days == 5) { 
            if (initials[9] != 0){
                RadioSignal event6;
                event6.showEvent();
                char choice = 'y'; // 預設選擇yes
                event6.makeChoice(choice, cindy, chris, playerPackage, days);
                cout << "----------------------------------------" << "\n";
                pressEnterToContinue();
            }
        }
        else if (days == 14) {
            if (initials[9] != 0){
                RadioSignal event6;
                event6.showEvent();
                char choice = 'n'; // 預設選擇no
                event6.makeChoice(choice, cindy, chris, playerPackage, days);
                cout << "----------------------------------------" << "\n";
                pressEnterToContinue();
            }
        }
        

        // --- 玩家決策 (如果沒人在外面並且兩人都活著，可以派人) ---
        if (!myExpedition.isExpeditionActive() && cindy.isAliveStatus() && chris.isAliveStatus() 
            && !cindy.isInTheWild && !chris.isInTheWild && days >= 5 && days <= 9 && myExpedition.hadExpedition == false)
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


        cout << "\nthis day ends\n";
        cout << "------------------------------\n";
        pressEnterToContinue();
        days++;
    }


    cout << "\n========================================\n";

    
    if(cindy.isAliveStatus() || chris.isAliveStatus()){
        cout << "恭喜！至少有一名倖存者活過了 15 天！\n";
        cout << ">>>>>>>>>>>>>>> VICTORY <<<<<<<<<<<<<<<\n";
    } 
    else{
        cout << "很遺憾，所有人都未能倖存...\n";
        cout << ">>>>>>>>>>>>>>>> DEFEAT <<<<<<<<<<<<<<<<\n";
    }


    return 0;
}


void pressEnterToContinue() { // 函數用於分段輸出
    cout << "\n >> Press Enter to Continue... ";
    
    if (cin.rdbuf()->in_avail() > 0) { // 緩衝區有東西時，清理換行符號
        if (cin.peek() == '\n') { 
            cin.ignore(); 
        }
    }
    
    cin.get(); // 讀取Enter
}

int getValidInt(){
    int value;
    cin.exceptions(ios::failbit | ios::badbit);
    while(true){
        try {
            // 嘗試讀取輸入
            // 如果輸入文字，會直接拋出ios_base::failure
            if (cin >> value) {
                return value; // 成功讀取，回傳數值
            }
        }
        catch (const ios_base::failure& e) {
            // 捕捉到錯誤 (輸入了文字)
            cout << "無效輸入！請輸入數字: ";
            
            cin.clear(); // 解除錯誤狀態
            
            // 清空緩衝區
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}