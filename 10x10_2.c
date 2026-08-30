#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
void generate_random_walk(char walk[10][10]);
void print_array(char walk[10][10]);

int main(){

  char walk[10][10];

  generate_random_walk(walk);
  print_array(walk);

  return 0;
}

void generate_random_walk(char walk[10][10]){

  int i,j;

  srand((unsigned) time(NULL));

  for(i = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      walk[i][j] = 46;
    }
  }

  bool still = true;
  char ch = 'A';
  int move = 0;
  int o = 0, p = 0;

  walk[o][p] = ch;
  ch++;

  while(still){

    while(ch <= 'Z'){
      int random = rand() % 4;

    if(random == 3){
      move = 1;
    }else if(random == 2){                                   move = 2;
    }else if(random == 1){
      move = 3;
    }else {
      move = 0;
    }

      if((o >= 9 || walk[o + 1][p] != 46) && 
         (o <= 0 || walk[o - 1][p] != 46) &&
         (p >= 9 || walk[o][p + 1] != 46) &&
         (p <= 0 || walk[o][p - 1] != 46)){
          still = false;
          break;
         }


        if(move == 1){
          if(o + 1 >= 10 || walk[o + 1][p] != 46){
          continue;
          }
          o++;
        }else if(move == 2){
          if(o - 1 < 0 || walk[o - 1][p] != 46){
            continue;
          }
          o--;
        }else if(move == 3){

          if(p + 1 >= 10 || walk[o][p + 1] != 46){
            continue;
          }
          p++;
        }else if(move == 0){
          if(p - 1 < 0 || walk[o][p - 1] != 46){
            continue;
          }
          p--;
        }
        walk[o][p] = ch;
        ch++;
    }
    
  }
}


void print_array(char walk[10][10]){

  int i, j;

  for(i = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      printf("%c ", walk[i][j]);
    }
    printf("\n");
  }
}
