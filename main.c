#include<stdio.h>
#include<string.h>

int color( char a )
{
    if ( a == 'S' ) return 0;
    if ( a == 'H' ) return 1;
    if ( a == 'D' ) return 2;
    if ( a == 'C' ) return 3;
}

int value( char a )
{
    if ( a == 'T' ) return 8;
    if ( a == 'J' ) return 9;
    if ( a == 'Q' ) return 10;
    if ( a == 'K' ) return 11;
    if ( a == 'A' ) return 12;
    return a - '2';
}

int compare(char cards[][3]) 
{

    for (int i = 5; i > 1; i--){  // make the cards in a order
        for (int j = 1; j < i; j++){
            if (cards[j-1][0] > cards[j][0]) {

                int temp = cards[j-1][0];
                cards[j-1][0] = cards[j][0];
                cards[j][0] = temp;

                int temp2 = cards[j-1][1];
                cards[j-1][1] = cards[j][1];
                cards[j][1] = temp2;

            }
        }

    }


    int maps[5][13];

    memset(maps, 0, sizeof(maps));

    for (int i = 0; i < 5; i++) {  //if get card in that position it fill with 1
        maps[color(cards[i][1])][value(cards[i][0])] ++;
        maps[4][value(cards[i][0])] ++;
    }

    //royal-flush | straight-flush
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 9; j++){
            if (maps[i][j]&maps[i][j+1]&maps[i][j+2]&maps[i][j+3]&maps[i][j+4]){
                return 13*13*13*13*13+40+j;
            }

        }

    }

    //four-of-a-kind
    for (int i = 0; i < 13; i++){
        if (maps[4][i] >= 4) {
            return 13*13*13*13*13+20+i;
        }
    }


    //full-house
    int three = 0;
    int two = 0;
    for (int i = 12; i >= 0; i--) {
        if (maps[4][i] == 2){
            two = two*15+i+1;
        }

        if (maps[4][i] == 3){
            three = i+1;
        }

    }

    if (two && three){
        return 13*13*13*13*13+three+1;
    }

    //flush
    for (int i = 0; i < 4; i++) {
        int count = 0;
        int number = 0;
        for (int j = 12; j >= 0; j--){
            for (int k = 0; k < maps[i][j]; k++) {
                count++;
                number = number*13+j;
            }
        }

        if (count == 5){
            return number;
        }
    }
    //straight
    for (int i = 0; i < 9; i++){
        if (maps[4][i]&maps[4][i+1]&maps[4][i+2]&maps[4][i+3]&maps[4][i+4]){
            return i-20;
        }
    }

    //three-of-a-kind
    if (three){
        return three-40;
    }

    int ans = 0;
    for (int i = 12; i >= 0; i--){
        if (maps[4][i] == 1){
            ans = ans*13+i;
        }
    }

    //two-pairs
    if (two >= 15){
        two*15+ans-8000;
    }
    //one-pair
    if (two){
        return two*13*13*13+ans-13*13*13*13*30;
    }
    //high-card
    return ans-13*13*13*13*50;
}

int main()
{
    char w[5][3];
    char b[5][3];
    while ( scanf("%s",b[0]) == 1 ) {

        for (int i = 1; i < 5; i++){
            scanf("%s",b[i]);
        }

        for (int i = 0; i < 5; i++){
            scanf("%s",w[i]);
        }

        int result = compare(b)-compare(w);

        if (result < 0){
            printf("White wins.\n");
        }

        else if (result > 0){
            printf("Black wins.\n");
        }

        else {
            printf("Tie.\n");
        }
    }
    return 0;
}
