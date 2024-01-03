#pragma once

#include "Card.h"
#include "Player.h"
#include "LinkedList.h"

enum ComputerPlayMode {
  EasyMode,
  HardMode
};

typedef enum ComputerPlayMode ComputerPlayMode;

Card* GetBestCard(Player* player, ComputerPlayMode playMode) {
  return GetFirstFromLL(&player->cur_set)->card;
}
