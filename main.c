#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <raylib.h>
#include <limits.h>

#include "Utils.h"
#include "constants.h"
#include "Card.h"
#include "Stack.h"
#include "Pile.h"
#include "LinkedList.h"
#include "Player.h"
#include "Ground.h"
#include "GameRules.h"
#include "Button.h"

#include "Recomend_System.h"

// Game State
uint8_t show_dialog = 0;
uint8_t is_playing = 0;
uint8_t is_dimmed = 0;
uint8_t current_player = 0;
uint8_t someone_won = 0;
uint32_t frames_counter = 0;
Card *cur_selected_card = NULL;
GameRules cur_play_rule = GameRuleNone;

Player player1, computer;
Stack pile;
LinkedList ground = {0};

// drawing section

// drawing dialogs
int cards_to_show_no = 1;
Card *cards_to_show[3];
char text_to_show[100];
Font font;
void DrawFullScreenDialog()
{
  DrawRectangle(0, 0, WIDTH, HEIGHT, CLITERAL(Color){0, 0, 0, 200});
  int i;
  for (i = 0; i < cards_to_show_no; ++i)
  {
    if (cards_to_show[i] != NULL)
    {
      int x = cards_to_show[i]->texture.width * i + 40;
      DrawTexture(cards_to_show[i]->texture, x, 40, WHITE);
    }
  }

  Vector2 size = MeasureTextEx(font, text_to_show, 60, 0);
  DrawTextEx(font, text_to_show, (Vector2){(WIDTH - size.x) / 2, (HEIGHT - 60) / 2}, 60, 0, WHITE);

  DrawOkDialogButton(&font);
}
void CloseDialog()
{
  show_dialog = 0;
  is_dimmed = 0;
}

// drawing turn and score
void DrawGameText()
{
  if (current_player == 0)
  {
    // player1
    DrawTextEx(font, "Turn: Player1", (Vector2){5, 5}, 40, 0, WHITE);
  }
  else
  {
    // computer
    DrawTextEx(font, "Turn: Computer", (Vector2){5, 5}, 40, 0, WHITE);
  }

  // drawing pocket count
  DrawTextEx(font, TextFormat("your pocket: %i", StackCountWithBasra(&player1.pocket)), (Vector2){10, HEIGHT - 40}, 40, 0, WHITE);
  DrawTextEx(font, TextFormat("Com pocket: %i, Cards Left: %i", StackCountWithBasra(&computer.pocket), CountLL(&computer.cur_set)), (Vector2){(WIDTH / 2 - 150), 10}, 40, 0, WHITE);
}

// handling ground staff
void DrawGroundBG()
{
  DrawRectangleLines(0, GROUND_X_START, WIDTH, HEIGHT - 200 - GROUND_X_START, WHITE);
  DrawTextEx(font, "Ground", (Vector2){WIDTH / 2 - 40, HEIGHT / 2 - 30}, 40, 0, WHITE);
}

void DrawGroundCards()
{
  int i = 0;
  Node *ptr = ground.head;
  while (ptr != NULL)
  {
    Card *card = ptr->card;
    if (card != NULL)
    {
      card->x = i * card->width + GROUND_X_START;
      card->y = GROUND_X_START;
      DrawCard(card);
      ++i;
    }
    ptr = ptr->next;
  }
}

void Init()
{
  pile.top = 0;
  CreateThePile(&pile);
  ShuffleThePile(&pile);

  // creating the players
  player1.score = computer.score = 0;
  player1.basra_count = computer.basra_count = 0;
  memset(&player1.cur_set, 0, sizeof(sizeof(LinkedList)));
  memset(&computer.cur_set, 0, sizeof(sizeof(LinkedList)));

  // distributing 4 cards to each player
  DistributeCards(&pile, &player1, &computer);

  // disteribute 4 cards to the ground
  int i;
  for (i = 0; i < 4; ++i)
  {
    Card *card = Pop(&pile);
    AppendToLL(&ground, card);
  }

  is_playing = 1;
  current_player = 0;
}

Card *GetClickedCard(Vector2 *mouse_pos, int *from_ground)
{
  Card *card = NULL;

  // checking cards on the ground
  Node *ptr = ground.head;

  while (ptr != NULL)
  {
    if ((mouse_pos->x >= ptr->card->x && mouse_pos->x < (ptr->card->x + ptr->card->width)) && (mouse_pos->y >= ptr->card->y && mouse_pos->y < (ptr->card->y + ptr->card->height)))
    {
      card = ptr->card;
      *from_ground = 1;
      return card;
    }
    ptr = ptr->next;
  }

  // checking player1's cards
  ptr = player1.cur_set.head;

  while (ptr != NULL)
  {
    if ((mouse_pos->x >= ptr->card->x && mouse_pos->x < (ptr->card->x + ptr->card->width)) && (mouse_pos->y >= ptr->card->y && mouse_pos->y < (ptr->card->y + ptr->card->height)))
    {
      card = ptr->card;
      *from_ground = 0;
      return card;
    }
    ptr = ptr->next;
  }

  return card;
}

void PerformAction(GameRules game_rule)
{
  Player *player = current_player == 0 ? &player1 : &computer;
  cur_selected_card->selected = 0;

  switch (game_rule)
  {
  case Basra:
  case TwoCardsMatch:
  {
    printf("Player No %d: Two Cards Match\n", current_player);
    printf("Remove from my curset\n");
    if(game_rule == Basra) {
      printf("Basra won\n");
      cur_selected_card->is_basra = 1;
    }
    RemoveFromLL(&player->cur_set, cur_selected_card);
    Card* matching_card = FindAMatchFromGround(&ground, cur_selected_card);
    printf("matching card ptr = %p, selected card ptr = %p\n", matching_card, cur_selected_card);
    RemoveFromLL(&ground, matching_card);
    Push(&player->pocket, cur_selected_card);
    Push(&player->pocket, matching_card);
  }
  break;
  case TakeAllGroundCards:
  {
    TakeAllCards(&ground, player, cur_selected_card);
  }
  break;
  case NoMatch:
  {
    RemoveFromLL(&player->cur_set, cur_selected_card);
    AppendToLL(&ground, cur_selected_card);
  }
  break;
  }
}

int GetWhoWon() {
  return StackCountWithBasra(&player1.pocket) > StackCountWithBasra(&computer.pocket) ? 0 : 1;
}

#define SWITCH_PLAYER() (current_player = current_player == 0 ? 1 : 0)

int main()
{
  InitWindow(WIDTH, HEIGHT, GAME_NAME);

  InitAudioDevice();

  SetTargetFPS(60);

  font = LoadFont("resources/fonts/OleoScriptBold-1eRg.ttf");

  // loading screen
  BeginDrawing();
  Vector2 loading_txt_size = MeasureTextEx(font, "Loading...", 40, 0);
  DrawTextEx(font, "Loading...", (Vector2){(WIDTH-loading_txt_size.x)/2, (HEIGHT-loading_txt_size.y)/2}, 40, 0, WHITE);
  EndDrawing();
  
  Sound sound = LoadSound("resources/sound/gameplay.ogg");

  Init();

  SetExitKey(0);

  PlaySound(sound);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(DARKGREEN);

    if(!IsSoundPlaying(sound)) {
      PlaySound(sound);
    }

    if (is_playing)
    {
      DrawGroundBG();
      DrawGroundCards();
      DrawGameText();
      DrawPlayerCards(&player1);

      if (IsKeyPressed(KEY_ESCAPE))
      {
        CloseDialog();
      }

      if (!is_dimmed)
      {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
          if (current_player == 0)
          {
            int from_ground = 0;
            Vector2 mouse_pos = GetMousePosition();
            Card *card = GetClickedCard(&mouse_pos, &from_ground);

            if (!from_ground && card != NULL)
            {
              if (cur_selected_card != card)
              {
                card->selected = 1;
                if (cur_selected_card != NULL) {
                  cur_selected_card->selected = 0;
                }
                cur_selected_card = card;
              }
              else
              {
                Card *ground_card = FindAMatchFromGround(&ground, card);
                cur_play_rule = DetermineGameRule(&ground, &player1, ground_card, card);
                cards_to_show[0] = cur_selected_card;
                cards_to_show_no = 1;
                GetGameRuleName(current_player, cur_play_rule, text_to_show);
                show_dialog = 1;
                is_dimmed = 1;
              }
            }
          }
        }
      }

      if (current_player == 1) // computer's turn
      {
        Card *card = GetBestCard(&computer);
        if (CountLL(&computer.cur_set) > 0)
        {
	  Card* matching_card = FindAMatchFromGround(&ground, card);
          cur_play_rule = DetermineGameRule(&ground, &computer, matching_card, card);
          cur_selected_card = card;

          cards_to_show[0] = card;
          cards_to_show_no = 1;
          GetGameRuleName(current_player, cur_play_rule, text_to_show);
          show_dialog = 1;
	  is_dimmed = 1;
        }
      }
    }

    if (show_dialog)
    {
      DrawFullScreenDialog();

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        if (IsOkDialogButtonClicked())
        {
          CloseDialog();
          PerformAction(cur_play_rule);
          SWITCH_PLAYER();
        }
      }
    }
    else {
      // check if the both players card sets are empty
      if(StackCount(&pile) > 0) {
	if(CountLL(&player1.cur_set) == 0 && CountLL(&computer.cur_set) == 0) {
	  // TODO: ensure that the left in the pile is enough for each player
	  // TODO: distribute 4 cards for each player
	  printf("Distributing cards to players...\n");
	  DistributeCards(&pile, &player1, &computer);
	}
      }
      else if(StackCount(&pile) == 0 && CountLL(&player1.cur_set) == 0 && CountLL(&computer.cur_set) == 0) {
        cards_to_show_no = 0;
	memset(text_to_show, 0, 100);
	int who_won = GetWhoWon();
	if(who_won == 0) {
	  strncpy(text_to_show, "Congrats You Won", strlen("Congrats You Won"));
	}
	else {
	  strncpy(text_to_show, "Computer Won", strlen("Computer Won"));
	}
        show_dialog = 1;
	is_dimmed = 1;
	someone_won = 1;
      }
    }

    EndDrawing();

    if(frames_counter < INT_MAX) {
      ++frames_counter;
    }
    else {
      frames_counter = 0;
    }
  
  }

  CleanupLL(&ground);
  CleanThePile(&pile);

  UnloadSound(sound);
  UnloadFont(font);

  CloseAudioDevice();

  CloseWindow();
  return 0;
}
