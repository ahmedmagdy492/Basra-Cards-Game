#pragma once

#include "Card.h"
#include "Player.h"
#include "LinkedList.h"

enum GameRules
{
  GameRuleNone,
  TwoCardsMatch,
  TakeAllGroundCards,
  SumMatch,
  NoMatch,
  Basra
};

typedef enum GameRules GameRules;

int IsJackOr7Diamond(Card* card) {
  if (card->type == jack || (card->value == 7 && card->type == diamond))
  {
    return 1;
  }
  return 0;
}

GameRules DetermineGameRule(LinkedList *ground, Player *player, Card *ground_card, Card *card)
{
  int ground_count = 0;
  if ((ground_count = CountLL(ground)) == 0)
  {
    return NoMatch;
  }

  if (ground_card != NULL)
  {
    if (card->value == 0 && ground_card->value == 0)
    {
      if (card->type == ground_card->type)
      {
        if (ground_count == 1)
        {
          return Basra;
        }
        return TwoCardsMatch;
      }
    }
    else if (card->value == ground_card->value)
    {
      if (ground_count == 1)
      {
        return Basra;
      }
      return TwoCardsMatch;
    }
  }

  return NoMatch;
}

void GetGameRuleName(int player_turn, GameRules rule, char *out)
{
  memset(out, 0, strlen(out) + 1);
  switch (rule)
  {
  case TakeAllGroundCards:
  {
    if (player_turn == 0)
    {
      strncpy(out, "Good Move: You will take all cards", strlen("Good Move: You will take all cards"));
    }
    else
    {
      strncpy(out, "Computer will take all cards", strlen("Computer will take all cards"));
    }
  }
  break;
  case SumMatch: {
    if (player_turn == 0)
    {
      strncpy(out, "You Found a Sum Match", strlen("You Found a Sum Match"));
    }
    else
    {
      strncpy(out, "Computer Found a Sum Match", strlen("Computer Found a Sum Match"));
    }
  }
  break;
  case Basra:
  {
    if (player_turn == 0)
    {
      strncpy(out, "You won a Basra +10", strlen("You won a Basra +10"));
    }
    else
    {
      strncpy(out, "Computer won a Basra +10", strlen("Computer won a Basra +10"));
    }
  }
  break;
  case TwoCardsMatch:
  {
    if (player_turn == 0)
    {
      strncpy(out, "found a match for your card", strlen("found a match for your card"));
    }
    else
    {
      strncpy(out, "Computer found a match for his card", strlen("Computer found a match for his card"));
    }
  }
  break;
  case NoMatch:
  {
    if (player_turn == 0)
    {
      strncpy(out, "you will play this card", strlen("you will play this card"));
    }
    else
    {
      strncpy(out, "Computer will play this card", strlen("Computer will play this card"));
    }
  }
  break;
  }
}

// Actions
void TakeAllCards(LinkedList *ground, Player *player, Card *card)
{
  Node *ptr = ground->head;

  while (ptr != NULL)
  {
    Push(&player->pocket, ptr->card);
    printf("trying to remove card %d from ground\n", ptr->card->value);
    RemoveFromLL(ground, ptr->card);
    ptr = ptr->next;
  }
  // remove the card from the player's cur_set
  if (card != NULL)
  {
    RemoveFromLL(&player->cur_set, card);
  }
}
