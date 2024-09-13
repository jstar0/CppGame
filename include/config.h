#ifndef CONFIG_H
#define CONFIG_H

#include "gamemap.h"

namespace PlayerConfig {
    extern int currentX, currentY, currentRoom, speedX, speedY;
    extern int statePrintX, statePrintY, statePrintX2, statePrintY2;
}

namespace RoomConfig {
    extern int printX, printY, width, height;
}

namespace CardConfig {
    extern int selectPrintX, selectPrintY, selectPrintX2, selectPrintY2;
    extern std::vector<Card*> cards;
    extern std::vector<Card*> have, hand, used;
    extern int currentSelectCard;
}

namespace DescriptionConfig {
    extern int printX, printY, printX2, printY2;
}

namespace AttackConfig {
    extern int playerPrintX, playerPrintY, enemyPrintX, enemyPrintY;
}

namespace MessageConfig {
    extern int printX, printY, max, printX2, printY2;
}

namespace StoreConfig {
    extern int printX, printY;
    extern std::vector<Goods*> *currentGoods;
    extern int currentSelectGoods;
}

namespace GoodsConfig {
    extern int printX, pricePrintX, numberPrintX, printY;
}

namespace SmallMapConfig {
    extern int x, y, width, height;
}

namespace GameConfig {
    extern const int FPS;
    extern std::vector<Room> rooms;
    extern std::vector<Enemy> enemies;
    extern std::vector<Prop*> props;
    extern std::vector<EnemyIntention*> enemyIntentions;
    extern std::vector<std::string> story;
    extern Enemy *currentEnemy;
}

extern bool exitGame;

#endif // CONFIG_H