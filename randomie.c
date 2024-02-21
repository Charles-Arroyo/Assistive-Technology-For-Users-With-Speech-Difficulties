/// Lab 09 DS4Talker Skeleton Code       

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#define WORDLENGTH 11
#define MAXWORDS 100
#define DEBUGM 1  
#define AVATAR '<'
// Set this to 0 to disable debug output
// gcc -o lab9-1 lab9-1.c -lncurses
//./ds4rd-real.exe -d 054c:05c4 -D DS4_USB -t - b -j -bt | ./lab9-1 wordslist-1.txt
void draw_character(int x, int y, char use);
// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char* WL[MAXWORDS], char* file_name);

// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* str);

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordcount;
	int i;
	int time;
	int triangleb, squareb, circleb, xb;
	int joyClickR, joyClickL;
	int R1, R2, L1, L2;
	int joy_lx;
	int joy_ly;
	int joy_rx;
	int joy_ry;
	int optionB;
	int shareB;
	int xGraph = 0;
	int yGraph = 0;
	int xTemp;
	int yTemp;
	int t = 0; 
	int holdValue = 5;
	char holdString[100] = {'\0'};
	char* prevWords[100];
	int currentWords = 0;
	int declarex = 0;
	wordcount = read_words(wordlist, argv[1]);
	if (DEBUGM) {
		printf("Read %d words from %s \n", wordcount, argv[1]);
		for (i = 0; i < wordcount; i++) {
			printf("%s,", wordlist[i]);
		}
		printf("\n");
	}
	initscr();
	//%d spaces, x and y is graph, wordslist[i] is the acess of the word list. 
	for(i = 0; i < wordcount; i++){
		mvprintw(yGraph,xGraph,"%15s",wordlist[i]);
		refresh();
		xGraph = xGraph + 15;	
		if(xGraph >= 75){
			yGraph++;
			xGraph = 0;
			}
		}
	int rows = 1;
	int columns = 16;
while(1){
	scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",&time,&triangleb,&circleb,&xb,&squareb,
		&joyClickR,&joyClickL,&optionB,&shareB,&R2,&L2,&R1,&L1,&joy_lx,&joy_ly,&joy_rx,&joy_ry);
	draw_character(rows, columns, AVATAR);
	
	
	if(time - t > 300){
	//This if statement moves the cursor right
	// it has a boundary at 76 to the right
	if(joy_rx >= 125 && columns != 76){
		draw_character(rows, columns, ' ');
		columns = columns + 15;
		holdValue = holdValue + 1;
	}

	//This if statement moves the cursor left
	// it has a boundary at 16 to the left
	if(joy_rx <= -125 && columns != 16){
		draw_character(rows, columns, ' ');
		columns = columns - 15;
		holdValue = holdValue - 1;
	}

	// This if statement moves the joystick up
	//it has a bounrday at zero 
	if(joy_ry <= -125 && rows != 0){
		draw_character(rows, columns, ' ');
		rows = rows - 1;
		holdValue = holdValue - 5;
	}

	//This if statement moves the cursor down
	// it has a boundary of 20 down.
	if(joy_ry >= 125 && rows != 20){
		draw_character(rows, columns, ' ');
		rows = rows + 1;
		holdValue = holdValue + 5;
	}

	/*

	for each of these if statements I have something called a holdValue, which keeps track, and holds the value of the arry based on where I move my joystick. It is intialzied
	5, I found this number by couting the array. Then, it will add one if moved right, and get rid of that added one everytime I do the oppisate, move left. I then counted from
	the first word(the) to the first word of the second row, I counted 5. So for moving down, it goes to up by 5, and going up removes that 5 so subtract 5. Then if you follow 
	my code to the mprintw you see that I print the hold value, where my cusor is.





	*/


		// if the square button is pressed then it will print on the line	
	if(squareb){
		prevWords[currentWords]= wordlist[holdValue];
		currentWords++;
		// strcat(holdString, wordlist[holdValue]);
	}

	if(triangleb){
		prevWords[currentWords] = strcat(strdup(wordlist[holdValue]), " ");
		currentWords++;
		// strcat(holdString, " ");
		// strcat(holdString, wordlist[holdValue]);
	}

	if (joyClickR == 1){
				declarex = 0;
				currentWords = 0;
				for (int i = 0; i < 200; i++){
					mvprintw(22, i, "%s", " ");
				}
			}

	if (xb == 1 && currentWords > 0){
	currentWords--;
	declarex -= strlen(prevWords[currentWords]);
		for(int i = 0; i < strlen(prevWords[currentWords]); i++){
		mvprintw(22, declarex, "%s", " ");
		declarex = declarex + 1;
		}

	}

	t = time;
	declarex = 0; 
	for (int i = 0; i < currentWords;  i++){
	mvprintw(22, declarex, "%s", prevWords[i]);
	declarex += strlen(prevWords[i]);
			}
		}	
	}
	mvprintw(22,0, "%s", holdString);
	return 0;
}
		

// DO NOT MODIFY THIS FUNCTION!
void trimws(char* str) {
	int length = strlen(str);
	int x;
	if (length == 0) return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0)) {
		str[x] = '\0';
		x -= 1;
	}
}


// DO NOT MODIFY THIS FUNCTION!
int read_words(char* WL[MAXWORDS], char* file_name)
{
	int numread = 0;
	char line[WORDLENGTH];
	char *p;
	FILE* fp = fopen(file_name, "r");
	while (!feof(fp)) {
		p = fgets(line, WORDLENGTH, fp);
		if (p != NULL) 
		{
			trimws(line);
			WL[numread] = (char *)malloc(strlen(line) + 1);
			strcpy(WL[numread], line);
			numread++;
		}
	}
	fclose(fp);
	return numread;
}

void draw_character(int x, int y, char use)
{
    mvaddch(x,y,use);
    refresh();
}
