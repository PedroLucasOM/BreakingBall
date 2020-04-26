#include<stdio.h>
#include<iso646.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<Windows.h>

#define ROW 8
#define COLUMN 11

void fill_array(char board[ROW][COLUMN]){
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
      if((i>0) and (i<4) and (j>1) and (j<9)){
        board[i][j] = '#';
      } else if((i == 7) and (j>2) and (j<8)){
        board[i][j] = '*';
      }else if((i == 6) and (j == 5)){
        board[i][j] = 'O';
      }else{
        board[i][j] = '.';
      }
    }
  }
}

void print_array(char board[ROW][COLUMN], int scores[1]){
  system("@cls||clear");
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
      if(j != 10){
        printf("%c", board[i][j]);
        printf(" ");
      }else{
        printf("%c\n", board[i][j]);
      }
    }
  }
  printf("\nScores: %d\n", scores[0]);
}

void search_position_pallet(char board[ROW][COLUMN], int position_pallet[5]){
	int n = 0;
	for(int i=0; i<COLUMN; i++){
		if(board[7][i] == '*'){
			position_pallet[n] = i;
			n++;
		}
	}
}

void modify_position_pallet(char board[ROW][COLUMN], int position_pallet[5], char key){
	if(key == 'A' or key == 'a'){
		int cont = 0;
		if(position_pallet[0] != 0){
			for(int i=0; i<5; i++){
				board[7][position_pallet[cont]] = '.';
				position_pallet[cont] = position_pallet[cont] - 1;
				board[7][position_pallet[cont]] = '*';
				cont++;
			}
		}
	}else if(key == 'D' or key == 'd'){
		int cont = 4;
		if(position_pallet[4] != 10){
			for(int i=0; i<5; i++){
        		board[7][position_pallet[cont]] = '.';
        		position_pallet[cont] = position_pallet[cont] + 1;
        		board[7][position_pallet[cont]] = '*';
        		cont--;
			}
		}			
	}
}

void search_positions_blocks(char board[ROW][COLUMN], int positons_blocks[ROW][COLUMN]){
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COLUMN; j++){
			if((board[i][j] == '#')){
				positons_blocks[i][j] = 1;
			}else{
				positons_blocks[i][j] = 0;
			}
		}
	}
}

int verify_pallet(int column_ball, int position_pallet[5]){
	int chek = 0;
	for(int i=0; i<5; i++){
		if(column_ball == position_pallet[i]){
			chek++;
		}
	}
	if(chek == 0){
		return 0;
	}else{
		return 1;
	}
}

void modify_array(char board[ROW][COLUMN], int position_ball[2], int position_pallet[5], int positons_blocks[ROW][COLUMN]){
  for(int i=0; i<ROW; i++){
    for(int j=0; j<COLUMN; j++){
		if((i == position_ball[0]) and (j == position_ball[1])){
			board[i][j] = 'O';
		}else if(positons_blocks[i][j] == 1){
			board[i][j] = '#';
		}else if((i == 7) and (j >= position_pallet[0] and j<= position_pallet[4])){
			board[i][j] = '*';
		}else{
        	board[i][j] = '.';
      	}
    }
  }
}

int choose_level(int default_scores[1], double velocity[1]){
  system("@cls||clear");
  printf("1 - Type for hard ~ 10 required points\n");
  printf("2 - Type for normal ~ 15 required points\n");
  printf("3 - Type for default ~ 21 required points\n");
  printf("Any other key for default game ~ 21 required points\n");
  printf("Choose your level: ");
  while(1){
    if(_kbhit()){
      char key;
      key = _getch();
      if(key == '1'){
        default_scores[0] = 10;
        velocity[0] = 400;
        break;
      }else if(key == '2'){
        default_scores[0] = 15;
        velocity[0] = 300;
        break;
      }else if(key == '3'){
        default_scores[0] = 21;
        velocity[0] = 200;
        break;
      }else{
        default_scores[0] = 21;
        velocity[0] = 400;
        break;
      }
    }
  }
}

int init(){
  system("@cls||clear");
  printf("WELCOME TO JJ'S BREAKING BALL!");
  sleep(5);
}

int keys_allowed(){
  char key;
  printf("\nKeys allowed: \n");
  printf(" Q ~ To quit the game;\n");
  printf(" A ~ To move the palette to the left;\n");
  printf(" D ~ To move the palette to the right;\n");
  printf(" Any other key to return to the game;\n");
  while(1){
    if(_kbhit()){
      key = _getch();
      if(key == 'Q' or key == 'q'){
        return 1; 
      }else{
        return 2;
      }
    }
  }
}

void run(char board[ROW][COLUMN], int position_pallet[5], int position_ball[2], int positons_blocks[ROW][COLUMN], int scores[1], int default_scores[1], double velocity[1]){
  	int row_ball = 6;
  	int column_ball = 5;

  	int previous_row_ball = row_ball;
  	int previous_column_ball = column_ball;

  	while(scores[0] != default_scores[0]){
    	char key;
    	if (_kbhit()){
    		key =_getch();
    		if(key == 'Q' or key == 'q'){
    			break;
    		}else if(key == 'A' or key == 'a' or key == 'D' or key == 'd'){
    			search_position_pallet(board, position_pallet);
    			modify_position_pallet(board, position_pallet, key);
    		}else if(keys_allowed() == 1){
    			break;
    		}
    	}

      //Verificação para a barra
    	if(row_ball == 6){
    		if(verify_pallet(column_ball, position_pallet) != 0){
    			if(column_ball == position_pallet[0]){
    				previous_row_ball = row_ball;
    				row_ball -= 1;
    				previous_column_ball = column_ball;
    				column_ball -= 1;
          }else if(column_ball == position_pallet[1]){
            previous_row_ball = row_ball;
            row_ball -= 1;
            if(column_ball % 2 != 0){
              previous_column_ball = column_ball;
              column_ball -= 1;
            }else{
              previous_column_ball = column_ball;
              column_ball = column_ball;
            }
    			}else if(column_ball == position_pallet[2]){
    				previous_row_ball = row_ball;
    				row_ball -= 1;
    				previous_column_ball = column_ball;
    				column_ball = column_ball;
    			}else if(column_ball == position_pallet[3]){
            previous_row_ball = row_ball;
            row_ball -= 1;
            if(column_ball % 2 == 0){
              previous_column_ball = column_ball;
              column_ball += 1;
            }else{
              previous_column_ball = column_ball;
              column_ball = column_ball;
            }
    			}else if(column_ball == position_pallet[4]){
            previous_row_ball = row_ball;
            row_ball -= 1;
            previous_column_ball = column_ball;
            column_ball += 1;
          }
    		}else{
          previous_row_ball = row_ball;
          row_ball += 1;
        }
    	}else if(row_ball == 7){ //CASO ULTRAPASSE A BARRA
        printf("\nYOU LOSE!\n");
        break;
      }else if(positons_blocks[row_ball][column_ball] != 0){ //VERIFICAÇÃO PARA OS BLOCOS E CONTAGEM DE SCORES
    		positons_blocks[row_ball][column_ball] = 0;
        scores[0] = scores[0] + 1;
    		if(previous_row_ball > row_ball){
    			previous_row_ball = row_ball;
    			row_ball += 1;
    		}else if(previous_row_ball < row_ball){
    			previous_row_ball = row_ball;
    			row_ball -= 1;
    		}
    		if(previous_column_ball > column_ball){
    			previous_column_ball = column_ball;
    			column_ball += 1;
    		}else if(previous_column_ball < column_ball){
    			previous_column_ball = column_ball;
    			column_ball -= 1;
    		}else if(previous_column_ball == column_ball){
    			if(previous_row_ball > row_ball){
    				previous_row_ball = row_ball;
    				row_ball -= 1;
    			}else{
    				previous_row_ball = row_ball;
    				row_ball += 1;
    			}
    		}
    	}else if(row_ball == 0){ //VERIFICAÇÃO PARA A BORDA SUPERIOR
    		if(row_ball == 0){
    			previous_row_ball = row_ball;
    			row_ball += 1;
    		}
    		if(column_ball == 0){
    			previous_column_ball = column_ball;
    			column_ball += 1;
    		}else if(column_ball == 10){
    			previous_column_ball = column_ball;
    			column_ball -= 1;
    		}else{
    			if(previous_column_ball > column_ball){
    				previous_column_ball = column_ball;
    				column_ball -= 1;
    			}else if(previous_column_ball < column_ball){
    				previous_column_ball = column_ball;
    				column_ball += 1;
    			}else{
    				previous_column_ball = column_ball;
    				column_ball -= 1;
    			}
    		}
    	}else if(column_ball == 0 or column_ball == 10){ //VERIFICAÇÃO PARA AS BORDAS LATERAIS
    		if(column_ball == 0){
    			previous_column_ball = column_ball;
    			column_ball += 1;
    		}else if(column_ball == 10){
    			previous_column_ball = column_ball;
    			column_ball -= 1;		
    		}
    		if(row_ball == 7){
    			printf("\nYOU LOSE!\n");
    			break;
    		}else{
    			if(previous_row_ball > row_ball){
    				previous_row_ball = row_ball;
    				row_ball -= 1;
    			}else if(previous_row_ball < row_ball){
    				previous_row_ball = row_ball;
    				row_ball += 1;
    			}else{
    				previous_row_ball = row_ball;
    				row_ball += 1;
    			}
    		}
    	}else{ //VERIFICAÇÃO PARA O RESTO DA MATRIZ
    		if(previous_column_ball == column_ball){
       			if(previous_row_ball < row_ball){
          			previous_row_ball = row_ball;
          			row_ball += 1;
        		}else{
        			previous_row_ball = row_ball;
          			row_ball -= 1;	
        		}
      		}else if(previous_column_ball < column_ball){
        		previous_column_ball = column_ball;
        		column_ball += 1;
        		if(previous_row_ball < row_ball){
          			previous_row_ball = row_ball;
          			row_ball += 1;
        		}else{
          			previous_row_ball = row_ball;
          			row_ball -= 1;
        		}
      		}else if(previous_column_ball > column_ball){
        		previous_column_ball = column_ball;
        		column_ball -= 1;
        		if(previous_row_ball < row_ball){
          			previous_row_ball = row_ball;
          			row_ball += 1;
        		}else{
          			previous_row_ball = row_ball;
          			row_ball -= 1;
        		}
      		}
    	}

    	position_ball[0] = row_ball;
    	position_ball[1] = column_ball;

    	modify_array(board, position_ball, position_pallet, positons_blocks);
    	print_array(board, scores);
      Sleep(velocity[0]);
  	}
    if(scores[0] == default_scores[0]){
      printf("\nCONGRATULATIONS! YOU WIN!\n");
    }
}

int main(void){
	char board[ROW][COLUMN];
	int positons_blocks[ROW][COLUMN];
	int position_pallet[5];
	int position_ball[2];
  int scores[1];
  int default_scores[1];
  double velocity[1];

  scores[0] = 0;
  default_scores[0] = 0;
  velocity[0] = 0;
  
  init();
  choose_level(default_scores, velocity);

	fill_array(board);
	search_positions_blocks(board, positons_blocks);
	search_position_pallet(board, position_pallet);

	print_array(board, scores);
	run(board, position_pallet, position_ball, positons_blocks, scores, default_scores, velocity); 	
}