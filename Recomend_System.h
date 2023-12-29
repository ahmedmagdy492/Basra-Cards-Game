#pragma once

#include "Card.h"
#include "Player.h"
#include "LinkedList.h"

Card* GetBestCard(Player* player) {
  return GetFirstFromLL(&player->cur_set)->card;
}
