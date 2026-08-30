/*
 * poker.c
 * Classifies a poker hand
 */

#include <stdbool.h>   /* C99 only */
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/* External variables */
int arr[5][2], num[5], i;  /* Pairs can be 0, 1, or 2 */

/* Prototypes */
void read_cards(void);
void analyze_hand(bool *, bool *, bool *, bool *, bool *, bool *, int *);
void sort(int n, int arr[n]);
void print_result(bool, bool, bool, bool, bool, bool, int);

/*
 * main: Calls read_cards, analyze_hand, and print_result repeatedly.
 */
int main(void)
{
  bool straight, flush, four, three, royal, ace_low;
  int pairs = 0;

  for (;;) {
      read_cards();
      analyze_hand(&straight, &flush, &four, &three, &royal, &ace_low, &pairs);
      print_result(straight, flush, four, three, royal, ace_low, pairs);
  }
}

/*
 * read_cards: Reads the cards into the external variables
 *             num_in_rank and num_in_suit; checks for bad
 *             cards and duplicate cards.
 */
void read_cards(void)
{
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card, duplicate;
    int cards_read = 0;


    while (cards_read < NUM_CARDS) {
        bad_card = false;
        duplicate = false;

        printf("Enter a card: ");

        rank_ch = getchar();
        switch (rank_ch) {
            case '0':       exit(EXIT_SUCCESS);
            case '2':           rank = 1;
                                num[cards_read] = 2;
                                    break;
            case '3':           rank = 2;
                                num[cards_read] = 3;
                                    break;
            case '4':           rank = 3;
                                num[cards_read] = 4;
                                    break;
            case '5':           rank = 4;
                                num[cards_read] = 5;
                                    break;
            case '6':           rank = 5;
                                num[cards_read] = 6;
                                    break;
            case '7':           rank = 6; 
                                num[cards_read] = 7;
                                    break;
            case '8':           rank = 7; 
                                num[cards_read] = 8;
                                    break;
            case '9':           rank = 8; 
                                num[cards_read] = 9;
                                    break;
            case 't': case 'T': rank = 9; 
                                num[cards_read] = 10;
                                    break;
            case 'j': case 'J': rank = 10; 
                                num[cards_read] = 11;
                                    break;
            case 'q': case 'Q': rank = 11; 
                                num[cards_read] = 12;
                                    break;
            case 'k': case 'K': rank = 12; 
                                num[cards_read] = 13;
                                    break;
            case 'a': case 'A': rank = 13; 
                                num[cards_read] = 1;
                                    break;
            default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit = 1; break;
            case 'd': case 'D': suit = 2; break;
            case 'h': case 'H': suit = 3; break;
            case 's': case 'S': suit = 4; break;
            default:            bad_card = true;
        }

        while ((ch = getchar()) != '\n')
            if (ch != ' ')
                bad_card = true;

        for(i = 0; i < 5; i++){
          if(arr[i][0] == rank && arr[i][1] == suit)
            duplicate = true;
        }

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (duplicate)
            printf("Duplicate card; ignored.\n");
        else {
            arr[cards_read][0] = rank;
            arr[cards_read][1] = suit;
            cards_read++;
        }
    }
}

/* This will sort an array*/

void sort(int n, int arr[n]){
  if(n <= 1)
    return;
  int largest = arr[0], in = 0;
  for(int i = 0; i < n; i++){
    if(arr[i] > largest){
      largest = arr[i];
      in = i;
    }
  }
  if(arr[n - 1] != largest){
  arr[in] = arr[n - 1];
  arr[n - 1] = largest;
  }
  sort(--n, arr);
}

/*
 * analyze_hand: Determines whether the hand contains a straight,
 *               a flush, four-of-a-kind, and/or three-of-a-kind;
 *               determines the number of pairs; stores the results
 *               into the external variables straight, flush, four,
 *               three, and pairs.
 */
void analyze_hand(bool *straight,
                  bool *flush, 
                  bool *four, 
                  bool *three, 
                  bool *royal,
                  bool *ace_low, int *pairs)
{
    int num_consec = 0;
    int rank, suit;

    *royal    = false;
    *ace_low  = false;
    *straight = false;
    *flush    = false;
    *four     = false;
    *three    = false;
    *pairs    = 0;

   int arr2[5] = {0};

   sort(5, num);

    int plus = 0;

    /* Check for ace-low */

    for(i = 0; i < 5; i++){
      plus += num[i];
    }

    if(plus == 15)
      *ace_low = true;

    /* Check for royal */

    plus = 0;

    for(i = 0; i < 5; i++){
      plus += arr[i][0];
    }
    if(plus == 55)
      *royal = true;

    /* Check for flush */
    for(i = 0; i < 4; i++){
      suit = arr[i][1];
      if(arr[i + 1][1] == suit){
        *flush = true;
      }else{
        *flush = false;
        break;
      }
    }

    /* Check for straight */
    for(i = 0; i < 4; i++){
      if(num[i + 1] == num[i] + 1 ){
        *straight = true;
      }else{
        *straight = false;
        break;
      }
    }
    /* Check for 4-of-a-kind, 3-of-a-kind, and pairs */
    int num_rank[NUM_RANKS] = {0};

    for(i = 0; i < NUM_CARDS; i++){
      int rank = arr[i][0];
      for(int j = 0; j < NUM_RANKS; j++){
        if(rank == j){
          num_rank[j]++;
        }
      }
    }


    for (i = 0; i < NUM_RANKS; i++) {
      rank = num_rank[i];
      if(rank == 4){
        *four = true;
      }else if(rank == 3){
        *three = true;
      }else if(rank == 2){
        *pairs++;
      }

    }
}

/*
 * print_result: Prints the classification of the hand, based on
 *               the values of the external variables straight,
 *               flush, four, three, and pairs.
 */
void print_result(bool straight,
                  bool flush,
                  bool four,
                  bool three,
                  bool royal,
                  bool ace_low, int pairs)
{   if (royal && flush)
        printf("ROYAL FLUSH!!!!");
    else if (ace_low && straight)
        printf("Ace low straight");
    else if (straight && flush)
        printf("Straight flush");
    else if (four)
        printf("Four of a kind");
    else if (three && pairs == 1)
        printf("Full house");
    else if (flush)
        printf("Flush");
    else if (straight)
        printf("Straight");
    else if (three)
        printf("Three of a kind");
    else if (pairs == 2)
        printf("Two pairs");
    else if (pairs == 1)
        printf("Pair");
    else
        printf("High card");

    printf("\n\n");
}
