
#include <stdio.h>
#define UNDER_LINE '_'
#define TWO 2
#define N 11
#define K 121
#define PLAYER_1 1
#define PLAYER_2 2
#define X 'X'
#define O 'O'
void print_tie();
void print_error();
void print_welcome();
void print_winner(int player_index);
void print_player_turn(int player_index);
void print_board(char board[N][N], int n);
int print_enter_board_size(char board[N][N]);
int check_win_row (char board[N][N] ,int board_size);
void initialize_board (char board[N][N],int board_size);
int check_win_column (char board[N][N] ,int board_size);
int check_win_diagonal (char board[N][N] ,int board_size);
int check_win_second_diagonal (char board[N][N] ,int board_size);
int check_legal_move (char board[N][N],int row ,int column,int size_of_board);
int check_final_win (char board[N][N], int size_of_board,int player_index,int number_of_turns);
void undo (char board [N][N] ,int index_history[TWO][K], int num_undo,int count_turns,int size_of_board);
int need_to_do_undo (char board[N][N] ,int index_history[TWO][K],int row , int count_turns,int size_of_board);
int receive_move (char board[N][N],int index_history[TWO][K],int player_index ,int size_of_board,int count_turns );
int actualize_move(int player_index,int index_history[TWO][K],int row,int column,char board[N][N],int size_of_board,int count_turns);

//10 lines
int main ( )
{
   int index_history[TWO][K]={{0}};
   char board [N][N];
   int count_turns = 0 , size_of_board = print_enter_board_size(board);
   for ( ; ;)
   {
       count_turns += receive_move(board,index_history,PLAYER_1,size_of_board,count_turns);
       if(check_final_win(board,size_of_board,PLAYER_2,count_turns))
       {
       return 0;
       }
       count_turns += receive_move(board,index_history,PLAYER_2,size_of_board,count_turns);
       if(check_final_win(board,size_of_board,PLAYER_1,count_turns))
       {
       return 0;
       }
   }
}
//Initalize the board----------------------------------
//3 lines
void initialize_board (char board[N][N],int board_size)
{
    for (int i = 0 ; i < board_size ; i++)
    {
        for (int j = 0 ; j < board_size ; j++)
            board[i][j]= UNDER_LINE;
    }
}


//------------------------------------------------------------------------
//Checks if the array is "empty"(='_') at a specific index
//3 lines
int check_empty (char board[N][N],int row , int column)
{
    if(board[row][column] == UNDER_LINE) return 1 ;
    return 0;
}
//------------------------------------------------------------------------
//receive a move from the player
//9 lines
int receive_move (char board[N][N],int index_history[TWO][K] ,int player_index ,int size_of_board,int count_turns )
{
    int row = 0 , column = 0;
    print_player_turn( player_index);
    for( ; ; )
    {

        if(scanf(" %d", &row) && need_to_do_undo(board,index_history,row,count_turns,size_of_board))
        {
            return row;
        }
       if( row >= 0)
        {
            if( actualize_move( player_index ,index_history,row,column,board,size_of_board,count_turns))
            {
               return 1;
            }
        }
        print_error();
    }
}

//------------------------------------------------------------------------
//checks if a player requested to do undo and actualize the undo
//4 lines
int need_to_do_undo (char board[N][N] ,int index_history[TWO][K],int row , int count_turns,int size_of_board)
{
    if ((row < 0) && (row % TWO != 0) && (row >= -count_turns))
    {
      undo(board,index_history,row,count_turns,size_of_board);
      return 1 ;
    }

    return 0 ;
}
//------------------------------------------------------------------------
//Actualize the move on the board, and save the moves whithin an array.
//11 lines
int actualize_move(int player_index,int index_history[TWO][K],int row,int column,char board[N][N],int size_of_board,int count_turns)
{
      scanf(" %d",&column);
      if(check_legal_move(board,row,column,size_of_board))
      {
         index_history[0][count_turns] = row-1;
         index_history[1][count_turns] = column-1;
         if(player_index == 1)
         {
             board[row-1][column-1] = X;
             print_board(board, size_of_board);
         }
         else
         {
            board[row-1][column-1] = O;
            print_board(board, size_of_board);
         }
      return 1;
      }
      return 0;
}
//------------------------------------------------------------------------
//checks if turn is legal
//3 lines
int check_legal_move (char board[N][N],int row ,int column,int size_of_board)
{
    if((row <= size_of_board) &&(column > 0 && column <= size_of_board) && (check_empty(board , row-1 , column-1)))
      {
       return 1;
      }
    return 0 ;
}

//------------------------------------------------------------------------
//Returns the board x turns back. (by order of the player)
//5 lines
void undo (char board [N][N],int index_history[TWO][K], int num_undo,int count_turns,int size_of_board)
{
while(num_undo < 0)
   {
     board [index_history[0][count_turns-1]][index_history[1][count_turns-1]] = UNDER_LINE;
     count_turns --;
     num_undo ++;

   }
   print_board(board, size_of_board);
}
//------------------------------------------------------------------------
//Checks if the indexes at the same row are identical
//8 lines
int check_win_column (char board[N][N] ,int board_size)
{
    int count_win_column = 0;
    for (int i = 0 ; i < board_size ; i++ )
    {

        for (int j = 0 ; j < board_size-1 ; j++)
        {
            if(board[i][j] != UNDER_LINE && board[i][0] == board[i][j+1] )
            {
              count_win_column++;
              if (count_win_column == board_size-1) return 1;
            }
        }
         count_win_column = 0;
    }
    return 0;
}

//----------------------------------------------------------------------
//Checks if the main diagonal indexes are identical
//5 lines
int check_win_diagonal(char board[N][N] ,int size_of_board )
{
  if(size_of_board == 1) return 1;
  for (int i = 0 ; i < size_of_board-1 ; i++ )
        {
            if(check_win_second_diagonal(board,size_of_board)) return 1;
            if(board[i][i] == UNDER_LINE || board[0][0] != board[i+1][i+1])
                return 0;
        }
        return 1;
}

//------------------------------------------------------------------------
//Checks if the second diagonal indexes are identical
//4 lines
int check_win_second_diagonal (char board[N][N] ,int board_size)
{
  for (int i = 0 ; i < board_size ; i++ )
        {
            if(board[i][board_size-1-i] == UNDER_LINE || board[0][board_size-1] != board[i][board_size-1-i])
                return 0;
        }
        return 1;
}
//------------------------------------------------------------------------
//Checks if the indexes at the same column are identical
//8 lines
int check_win_row (char board[N][N] ,int board_size)
{

  int count_win_row = 0;
  for (int i = 0 ; i < board_size ; i++ )
    {
        for (int j = 0; j < board_size-1; j++)
        {
             if(board[j][i] != UNDER_LINE && board[0][i] == board[j+1][i])
             {
                   count_win_row++;
                   if(count_win_row == board_size-1) return 1;
             }
        }
        count_win_row = 0;
    }
    return 0;
}
//------------------------------------------------------------------------
//Checks if all indexes at the same row/column/diagonal are the same
//7 lines
int check_final_win (char board[N][N], int size_of_board,int player_index,int number_of_turns)
{
int game_finished =(check_win_diagonal(board,size_of_board) + check_win_column(board,size_of_board)+check_win_row(board,size_of_board));
if(game_finished !=0)
       {
       print_winner(player_index);
       }
    else if(number_of_turns == size_of_board*size_of_board )
{
    print_tie();
    return 1;
}

return game_finished ;
}
/*------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size and recieves it
//7 lines
int print_enter_board_size(char board[N][N])
{
    print_welcome();
    int size_of_board ;
    printf("Please enter board size (1 to %d):\n", N);
    scanf(" %d", &size_of_board);
    initialize_board (board, size_of_board);
    print_board(board, size_of_board);
    return size_of_board ;

}
//------------------------------------------------------------------------
//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//------------------------------------------------------------------------
//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}
//------------------------------------------------------------------------
//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}
//------------------------------------------------------------------------
//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}
//------------------------------------------------------------------------
//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}

//------------------------------------------------------------------------
