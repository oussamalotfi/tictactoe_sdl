#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define pi 3.14159265359
#define title "tic tac toe"
#define width 600
#define height 600

typedef enum cell_content { empty, has_x, has_o } cell_content;

typedef enum game_state { runningon, winner_x, winner_o, tie } game_state;


void drawx(SDL_Renderer * renderer, int i, int j) {
  //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, 20 + (width / 3) * j, 20 + (height / 3) * i,
                     180 + (width / 3) * j, 180 + (height / 3) * i);
  SDL_RenderDrawLine(renderer, 20 + (width / 3) * j, 180 + (height / 3) * i,
                     180 + (width / 3) * j, 20 + (height / 3) * i);
}
void drawo(SDL_Renderer * renderer, int i, int j) {
  //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  int ci = height / 6;
  int cj = width / 6;
  int stepi = i * height / 3;
  int stepj = j * width / 3;
  int r = 80;
  for (int i = 0; i < 360; i++) {
    SDL_RenderDrawPoint(renderer, r * cos(i * pi / 180) + (cj + stepj), r * sin(i * pi / 180) + (ci + stepi));
    SDL_RenderDrawLine(renderer, r * cos(i * pi / 180) + (cj + stepj),
                       r * sin(i * pi / 180) + (ci + stepi),
                       r * cos((i+1)* pi / 180) + (cj + stepj),
                       r * sin((i+1) * pi / 180) + (ci + stepi));
  }
}


void getmouseinput(SDL_Renderer * renderer, int *turntoplay, cell_content ** board){
  // mouse input
  int x, y;
  Uint32 buttons;
  SDL_PumpEvents();
  buttons = SDL_GetMouseState(&x, &y);
  

  // check if square is empty and fill square
  int i = (int)(y) / (width / 3), j = (int)(x) / (width / 3);
  if (board[i][j] == empty && (buttons & SDL_BUTTON_LMASK) != 0) {
    switch (*turntoplay) {
    case 0: // x to play
      board[i][j] = has_x;
      *turntoplay = 1 ;
      break;
    case 1: // o to play
      board[i][j] = has_o;
      *turntoplay = 0;
      break;
    }
  }
}
void draw(SDL_Renderer * renderer,  cell_content (board[3][3]) ,game_state state){
  // draw grid
  switch (state) {
  case runningon:
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    break;
  case winner_x:
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    break;
  case winner_o:
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    break;
  case tie:
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    break;
  }



  for (int i = 1; i < 3; i++) {
    SDL_RenderDrawLine(renderer, i * (width / 3), 0, i * (width / 3), height);
    SDL_RenderDrawLine(renderer, 0, i * (height / 3), width,
                       i * (height / 3));
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      switch (board[i][j]) {
      case has_x: drawx(renderer,i,j);break;
      case has_o: drawo(renderer,i,j);break;
      case empty:break;
      }
    }
  }
}









int main(int argc, char *argv[]) {
  // init sdl
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_OPENGL);
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_Event event;
  bool running = true;

 restart_game:
  ;
  // game variables

  cell_content board[3][3] = {
    {empty, empty, empty},
    {empty, empty, empty},
    {empty, empty, empty}
  };

  int turntoplay = 0; // 0 means x is playing while 1 means o is playing
  game_state state = runningon;

  /* for (int i = 0; i < 3; i++) { */
  /*   for (int j = 0; j < 3; j++) { */
  /*     printf("%d \t", board[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  // printf("%d",board[1][1]);


  while (running) {
    while (SDL_PollEvent(&event))
      if (event.type == SDL_QUIT)
        running = false;

    // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);




    // restart game
    const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
    if (state != 0) {

      if (keyboardstate[SDL_SCANCODE_R]) {
        goto restart_game;
      }
    }

    //logic


    // check for win in rows and columns
    printf("state = %d\n",state);
        for(int j = 0; j < 3 ; j++){

          if (board[0][j] == board[1][j] && board[1][j] == board[2][j] &&
              board[0][j] != empty) {
            if(board[0][j] == has_o) {state = winner_o;goto continue_program;}
            
            else if(board[0][j] == has_x) {state = winner_x;;goto continue_program;}
          }
            /* switch (board[0][j]) { */
            /* case has_o: */
            /*   state = winner_o; */
            /*   break; */
            /* case has_x: */
            /*   state = winner_x; */
            /*   break; */
            /* case empty: */
            /*   state = runningon; */
            /*   break; */
            /* } */

            if (board[j][0] == board[j][1] && board[j][1] == board[j][2] &&
                board[j][0] != empty) {
              if(board[j][0] == has_o){ state = winner_o;goto continue_program;}
              else if(board[j][0] == has_x) {state = winner_x;goto continue_program;}
            }

              /* switch (board[j][0]) { */
              /* case has_o: */
              /*   state = winner_o; */
              /*   break; */
              /* case has_x: */
              /*   state = winner_x; */
              /*   break; */
              /* case empty: */
              /*   state = runningon; */
              /*   break; */

              /* } */
            if(board [0][0] == board[1][1] && board[1][1] == board[2][2] && board [0][0] != empty){
              if (board[0][0] == has_o){
                state = winner_o;
                goto continue_program;
              }
              else if (board[0][0] == has_x){
                state = winner_x;
                goto continue_program;
              }

            }


            }


        // check for tie

        for(int i = 0; i< 3 ; i++){
          for(int j = 0; j < 3 ; j++){
            if(board[i][j] == empty){
              goto continue_program;
            }
          }
        }


        state = tie;
  continue_program:


        //draw
    draw(renderer, board, state);
    if(state == runningon){
    cell_content *boardrows[3] = {board[0], board[1], board[2]};

    getmouseinput(renderer, &turntoplay, boardrows);

    // printf("turn to play: %d\n", turntoplay);

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        printf("%d \t", board[i][j]);
      }
      printf("\n");
    }
    }


    // show
    SDL_RenderPresent(renderer);
  }






  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return (0);
}
