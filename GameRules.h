#pragma once

#include "Card.h"
#include "Player.h"
#include "LinkedList.h"

enum GameRules {
  GameRuleNone,
  TwoCardsMatch,
  TakeAllGroundCards,
  NoMatch,
  Basra
};

typedef enum GameRules GameRules;

GameRules DetermineGameRule(LinkedList* ground, Player* player, Card* ground_card, Card* card) {
  if(CountLL(ground) == 0) {
    return NoMatch;
  }
  
  if(card->type == jack || (card->value == 7 && card->type == diamond)) {
    return TakeAllGroundCards;
  }
  
  if(ground_card != NULL) {
    if(card->value == 0 && ground_card->value == 0) {
      if(card->type == ground_card->type) {
	return TwoCardsMatch;
      }
    }
    else if(card->value == ground_card->value) {
      return TwoCardsMatch;
    }
  }

  return NoMatch;
}

void GetGameRuleName(int player_turn, GameRules rule, char* out) {
  memset(out, 0, strlen(out)+1);
  switch(rule) {
    case TakeAllGroundCards: {
      if(player_turn == 0) {
        strncpy(out, "Good Move: You will take all cards", strlen("Good Move: You will take all cards"));
      }
      else {
        strncpy(out, "Computer will take all cards", strlen("Computer will take all cards"));
      }
    }
    break;
    case NoMatch: {
      if(player_turn == 0) {
        strncpy(out, "you will play this card", strlen("you will play this card"));
      }
      else {
        strncpy(out, "Computer will play this card", strlen("Computer will play this card"));
      }
    }
    break;
  }
}

// Actions
void TakeAllCards(LinkedList* ground, Player* player, Card* card) {
  Node* ptr = ground->head;

  while(ptr != NULL) {
    Push(&player->pocket, ptr->card);
    printf("trying to remove card %d from ground\n", ptr->card->value);
    RemoveFromLL(ground, ptr->card);
    ptr = ptr->next;
  }
  // remove the card from the player's cur_set
  RemoveFromLL(&player->cur_set, card);
}
