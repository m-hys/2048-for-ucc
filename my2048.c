#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define UP    0
#define DOWN  1
#define RIGHT 2
#define LEFT  3
int dx[4] = {  0, 0, 1, -1};
int dy[4] = { -1, 1, 0,  0};

int board[4][4];
int score;

void showBoard(){
  int i,j;
  printf("\033[2J");
  printf("\033[1;1H");
  for(i=0; i<4; i++){
    printf("+------+------+------+------+\n");
    printf("|      |      |      |      |\n");
    printf("| ");
    for(j=0; j<4; j++){
      if(board[i][j] != 0)
        printf("%4d | ", 1 << board[i][j]);
      else
        printf("     | ");
    }
    printf("\n");
    printf("|      |      |      |      |\n");
  }
  printf("+------+------+------+------+\n");
}

bool isValid(int x, int y){
  if(x < 0 || 4 <= x)
    return false;
  if(y < 0 || 4 <= y)
    return false;
  return true;
}

bool movable(int dir){
  int i,j;
  int ay,ax;
  for(i=0; i<4; i++){
    for(j=0; j<4; j++){
      ay = i+dy[dir]; ax = j+dx[dir];
      if(isValid(ax, ay) && board[i][j]!=0){
        if(board[ay][ax]==0 || board[ay][ax]==board[i][j]){
          return true;
        }
      }
    }
  }
  return false;
}

bool gameover(){
  int i,j;
  for(i=0; i<4; i++){
    for(j=0; j<4; j++){
      if(board[i][j] == 11)
        return true;
    }
  }
  for(i=0; i<4; i++){
    if(movable(i))
      return false;
  }
  return true;
}

void putNum(){
  int n, b;
  if(rand() <= RAND_MAX/10)
    n=2;
  else
    n=1;

  do{
    b = rand() % 16;
  } while(board[b%4][b/4] != 0);
  board[b%4][b/4] = n;
}

void init(){
  int i,j,b;
  for(i=0; i<4; i++)
    for(j=0; j<4; j++)
      board[i][j] = 0;

  score = 0;

  do{
    b = rand() % 16;
  } while(board[b%4][b/4] != 0);
  board[b%4][b/4] = 1;

  putNum();

  printf("\033[2J");
}

int c2dir(char c){
  switch(c){
  case 'w':
    return 0;
  case 's':
    return 1;
  case 'd':
    return 2;
  case 'a':
    return 3;
  default:
    return -1;
  }
}

void push(int d){
  bool f;
  int i,j,ay,ax;
  do{
    f=false;
    for(i=0; i<4; i++){
      for(j=0; j<4; j++){
        ay=i+dy[d]; ax=j+dx[d];
        if(isValid(ax,ay) && board[ay][ax]==0 && board[i][j]!=0){
          board[ay][ax] = board[i][j];
          board[i][j] = 0;
          f=true;
        }
      }
    }
  } while(f);
}

void merge(int d){
  int i,j;
  switch(d){
  case UP:
    for(j=0;j<4;j++){
      for(i=0;i<3;){
        if(board[i][j]==board[i+1][j] && board[i][j]!=0){
          board[i][j]++;
          score += 1 << board[i][j];
          board[i+1][j]=0;
          i+=2;
        } else {
          i++;
        }
      }
    }
    break;
  case DOWN:
    for(j=0;j<4;j++){
      for(i=3;i>0;){
        if(board[i][j]==board[i-1][j] && board[i][j]!=0){
          board[i][j]++;
          score += 1 << board[i][j];
          board[i-1][j]=0;
          i-=2;
        } else {
          i--;
        }
      }
    }
    break;
  case RIGHT:
    for(i=0;i<4;i++){
      for(j=3;j>0;){
        if(board[i][j]==board[i][j-1] && board[i][j]!=0){
          board[i][j]++;
          score += 1 << board[i][j];
          board[i][j-1]=0;
          j-=2;
        } else {
          j--;
        }
      }
    }
    break;
  case LEFT:
    for(i=0;i<4;i++){
      for(j=0;j<3;){
        if(board[i][j]==board[i][j+1] && board[i][j]!=0){
          board[i][j]++;
          score += 1 << board[i][j];
          board[i][j+1]=0;
          j+=2;
        } else {
          j++;
        }
      }
    }
    break;
  }
}

void Move(int d){
  push(d);
  merge(d);
  push(d);
}

int main(){
  int d;
  init();

  do{
    showBoard();
    printf("score: %d\n", score);
    do{
      printf("> ");
      d = c2dir(getchar());
    } while(d==-1 || !movable(d));
    Move(d);
    putNum();
  } while(!gameover());

  showBoard();
  printf("gameover...\n");
  printf("your score is: %d\n\n", score);

  return 0;
}
