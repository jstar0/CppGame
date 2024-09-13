#include <vector>
#include "gamemap.h"
#include "config.h"

namespace PlayerConfig {
    int currentX = 24, currentY = 20, currentRoom = 14, speedX = 2, speedY = 1;
    int statePrintX = 61, statePrintY = 36, statePrintX2 = 99, statePrintY2 = 40;
}

namespace RoomConfig {
    int printX = 5, printY = 4, width = 50, height = 23;
}

namespace CardConfig {
    int selectPrintX = 1, selectPrintY = 31, selectPrintX2 = 29, selectPrintY2 = 39;
    std::vector<Card*> cards(1000);
    std::vector<Card*> have, hand, used;
    int currentSelectCard;
}

namespace DescriptionConfig {
    int printX = 38, printY = 32, printX2 = 51, printY2 = 39;
}

namespace AttackConfig {
    int playerPrintX = 15, playerPrintY = 10, enemyPrintX = 40, enemyPrintY = 10;
}

namespace MessageConfig {
    int printX = 61, printY = 16, max = 19, printX2 = 99, printY2 = 34;
}

namespace StoreConfig {
    int printX = 5 + 50 / 2 - 2, printY = 4;
    std::vector<Goods*> *currentGoods = nullptr;
    int currentSelectGoods;
}

namespace GoodsConfig {
    int printX = 5, pricePrintX = 40, numberPrintX = 48, printY = 7;
}

namespace SmallMapConfig {
    int x = 61, y = 1, width = 39, height = 14;
}

namespace GameConfig {
    const int FPS = 30;
    std::vector<Room> rooms;
    std::vector<Enemy> enemies(100);
    std::vector<Prop*> props(100);
    std::vector<EnemyIntention*> enemyIntentions(100);
    std::vector<std::string> story(100);
    Enemy *currentEnemy = nullptr;
}