#pragma once

#include <stdint.h>

#define CARD_NAME_LEN 100
#define CWIDTH 150
#define CHEIGHT 150

// hint: jack -> boy
typedef enum {
  blackheart, redheart, diamond, tree, jack, queen, king
} CardType;

struct Card {
  uint8_t value;
  CardType type;
  Image img;
  Texture texture;
  uint8_t selected;
  uint8_t is_basra;
  int x;
  int y;
  int width;
  int height;
};

static void GetCardName(CardType type, uint8_t value, char *output) {
  switch(type) {
  case blackheart: {
    sprintf(output, "resources/%s_%u.png", "blackheart", value);
    break;
  }
  case redheart: {
    sprintf(output, "resources/%s_%u.png", "redheart", value);
    break;
  }
  case diamond: {
    sprintf(output, "resources/%s_%u.png", "diamond", value);
    break;
  }
  case tree: {
    sprintf(output, "resources/%s_%u.png", "tree", value);
    break;
  }
  case jack: {
    sprintf(output, "resources/%s.png", "jack");
    break;
  }
  case queen: {
    sprintf(output, "resources/%s.png", "queen");
    break;
  }
  case king: {
    sprintf(output, "resources/%s.png", "king");
    break;
  }
  }
}

typedef struct Card Card;

Card* CreateCard(uint8_t value, CardType type) {
  Card* card = (Card*)malloc(sizeof(Card));
  card->is_basra = 0;
  card->x = 0;
  card->y = 0;
  card->value = value;
  card->type = type;
  char card_name[CARD_NAME_LEN];
  memset(card_name, 0, CARD_NAME_LEN);
  GetCardName(type, value, card_name);
  card->img = LoadImage(card_name);
  card->texture = LoadTextureFromImage(card->img);
  card->width = card->texture.width;
  card->height = card->texture.height;
  card->selected = 0;
  
  return card;
}

void DrawCard(Card* card) {
  if(card->selected) {
    DrawTexture(card->texture, card->x, card->y, WHITE);
  }
  else {
    DrawTexture(card->texture, card->x, card->y, CLITERAL(Color){ 255, 255, 255, 200 });
  }
}

void CleanCard(Card* card) {
  if(card != NULL) {
    UnloadImage(card->img);
    free(card);
  }
}
