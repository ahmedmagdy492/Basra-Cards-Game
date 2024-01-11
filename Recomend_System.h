#pragma once

#include "Card.h"
#include "Player.h"
#include "LinkedList.h"

enum ComputerPlayMode {
  EasyMode,
  HardMode
};

typedef enum ComputerPlayMode ComputerPlayMode;

Card* GetBestCard(Player* player, ComputerPlayMode play_mode, LinkedList* ground) {
  Node* head = GetFirstFromLL(&player->cur_set);
  Node* ptr = head;
  if(play_mode == EasyMode) {
    return head->card;
  }

  while(ptr != NULL) {
    if(ptr->card->value == 7 && ptr->card->type == diamond && CountLL(ground) > 1) {
      return ptr->card;
    }
    else if(ptr->card->value == 0) {
      if(ptr->card->type == jack && CountLL(ground) > 1) {
        return ptr->card;
      }
    }
    if(ground != NULL) {
      Node* ground_ptr = ground->head;

      while(ground_ptr != NULL) {
        if(ground_ptr->card->value == 0 && ptr->card->value == 0) {
          if(ground_ptr->card->type == ptr->card->type) {
            return ptr->card;
          }
        }
        else if(ground_ptr->card->value == ptr->card->value) {
          return ptr->card;
        }
        ground_ptr = ground_ptr->next;
      }
    }
    ptr = ptr->next;
  }

  return head->card;
}
