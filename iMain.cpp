# include "iGraphics.h"

#include <stdio.h>
#include <time.h>
#include <string.h>

int x = 500, y = 500, c = 1, l, m, count1, temp = 1, error = 0;
unsigned char ch;
int start = 0, ix, iy, letter_click = 0, temp1 = 0, temp2 = 1, temp3 = 1, music_temp = -1;
char words[980][50];
char categories[17][35] = {"", "COUNTRIES", "CRICKET", "CITIES", "ACTORS", "MOVIES", "FRUITS", "FLOWERS",
                           "ANIMALS", "FOOTBALL", "PROGRAMMING", "CHEMISTRY", "PHYSICS", "MATHEMATICS", "BIOLOGY",
                           "SUPERHEROES", "SCIENTISTS"
                          };
char random[50];
int letters[27][4];
int t[3];
int cat[17][4];
char now;
char score_string[10], highscore_string[10], let_rem[4], guess_rem[4];
int pos[100];
int arr[100];
int check[500] = {0};
char var[30][2] = {{0}};
int alpha[27];
int cat_pos = 0, finish = 0, score = 0, high_score = 0;

void hang();
void initial_state();
void generator();

void gettime(int t[])
{
    time_t ctime;
    struct tm * current;
    time ( &ctime );
    current = localtime ( &ctime );
    t[0] = current->tm_hour;
    t[1] = current->tm_min;
    t[2] = current->tm_sec;
};

void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);

}

void mouseOver(int mx, int my)
{
    //printf("%d %d\n", mx,my);
    int x = mx;
    int y = my;
//conditions for going to different pages or options
    if(start == 0 and x >= 490 && x <= 690 && y >= 330 && y <= 380)
    {
        start = 1;
    }

    if(start == 0 and x >= 490 && x <= 690 && y >= 70 && y <= 120)
    {
        exit(1); //to quit
    }
    if(start == 0 and x >= 490 && x <= 690 && y >= 160 && y <= 210)
    {
        start = 5; //to enter help page
    }
    if(start == 0 and x >= 490 && x <= 690 && y >= 250 && y <= 300)
    {
        start = 4; //to enter settings page
    }

    //go back conditions
    if(start == 1 and x >= 111 and x <= 235 and y >= 72 and y <= 117)
    {
        start = 0;
    }
    if(start == 2 and x >= 1108 and x <= 1230 and y >= 70 and y <= 117)
    {
        start = 1;
        initial_state();
    }
    if(start == 4 and x >= 1108 and x <= 1230 and y >= 70 and y <= 117)
    {
        start = 0;
        initial_state();
    }
    if(start == 5 and x >= 1108 and x <= 1230 and y >= 70 and y <= 117)
    {
        start = 0;
        initial_state();
    }
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        //place your codes here
        //	printf("x = %d, y= %d\n",mx,my);

    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        l = mx;
        m = my;

        //selecting the categories
        if(start == 1)
        {
            for(int i = 1; i <= 16; i++)
            {
                if(l >= cat[i][0] && l <= cat[i][1] && m >= cat[i][2] && m <= cat[i][3])
                {
                    cat_pos = i;
                    start = 2;
                    letter_click = 0; //variable to enable/disable click on letters
                    temp2 = 1; //variable to show "Click here to Start"
                }
            }
        }

        //enabling the letter click
        if(start == 2)
        {
            if(l >= 56 and l <= 305 and m >= 635 and m <= 675)
            {
                letter_click = 1;
                temp2 = 0;
            }
        }

        //click on the letters
        if(start == 2 and letter_click)
        {
            for(int i = 1; i <= 26; i++)
            {
                if(l >= letters[i][0] && l <= letters[i][1] && m >= letters[i][2] && m <= letters[i][3])
                {
                    now = 64 + i; //e.g. , for letter a, i=1, so now will be 65 or 'A'
                }
            }
        }

        if(start == 4 and l >= 750 && l <= 800 && m >= 370 && m <= 430)
        {
            music_temp = -music_temp; //music on-off
            if(music_temp == 1)
                PlaySound("files//music.wav", NULL, SND_ASYNC | SND_LOOP);
            else
                PlaySound(NULL, 0, 0);

        }


        //finish will be 1 if one round of guessing word is finished
        if(finish)
        {
            if(l >= 100 && l <= 310 && m >= 160 && m <= 200) //another word
            {
                initial_state();
                temp1 = score;
            }
            if(l >= 100 && l <= 310 && m >= 110 && m <= 150) //another category
            {
                start = 1;
                initial_state();
                temp1 = score;
            }
        }
    }
    //printf("%d %d\n",l,m);
    ix = mx;
    iy = my;
}

void iKeyboard(unsigned char key)
{

    //if(key=='s' and start==2) letter_click=1;

}

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }

}

void generator()
{
    if(temp == 1)
    {
        int k = rand() % 60 + (cat_pos - 1) * 60; //randomly generating the index of words array depending on the cat_pos which indicates the categories
        strcpy(random, words[k]); //The character array random holds the current word
    }
    temp = 0;
}

void settings_page()
{
    glClearColor(0.64, 0.168, 0.67, 1);
    iSetColor(255, 215, 0);
    iFilledRectangle(500, 370, 200, 60);
    iFilledCircle(720, 410, 7);
    iFilledCircle(720, 390, 7);
    iSetColor(0, 0, 0);
    iText(560, 400, "MUSIC", GLUT_BITMAP_HELVETICA_18);
    if(music_temp == -1)
    {
        iSetColor(255, 0, 0);
        iFilledRectangle(750, 370, 65, 60);
        iSetColor(0, 0, 0);
        iText(765, 400, "OFF", GLUT_BITMAP_HELVETICA_18);
    }
    else if(music_temp == 1)
    {
        iSetColor(0, 255, 0);
        iFilledRectangle(750, 370, 65, 60);
        iSetColor(0, 0, 0);
        iText(765, 400, "ON", GLUT_BITMAP_HELVETICA_18);
    }
    drawTexture(1000, 25, goback2);
}

void homepage()
{
    drawTexture(0, 0, pic2);
}

void show_categories()
{
    glClearColor(1.0, 1, 1, 1);
    int cx = 180, cy = 550;
    for(int i = 1; i <= 16; i++)
    {
        iSetColor(105, 0, 105);
        iFilledRectangle(cx, cy, 200, 100);
        cat[i][0] = cx; //storing the co-ordinate range of the category rectangles
        cat[i][1] = cx + 200;
        cat[i][2] = cy;
        cat[i][3] = cy + 100;
        iSetColor(255, 255, 255);
        iText(cx + 30, cy + 50, categories[i], GLUT_BITMAP_HELVETICA_18);
        if(i % 4 == 0)
        {
            cx = 180;
            cy -= 130;
        }
        else cx += 210;
    }
    drawTexture(0, 25, goback);
}

void play_again()
{
    iSetColor(255, 215, 0);
    iFilledRectangle(100, 160, 210, 40);
    iFilledRectangle(100, 110, 210, 40);
    iSetColor(0, 0, 0);
    iText(120, 175, "ANOTHER WORD", GLUT_BITMAP_HELVETICA_18);
    iText(105, 125, "ANOTHER CATEGORY", GLUT_BITMAP_HELVETICA_18);
}

void initial_state() //function to assign the initial values after a round finishes
{
    for(int i = 0; i < 26; i++) alpha[i] = 0;
    for(int i = 0; i < 100; i++) arr[i] = 0;
    finish = 0;
    temp = 1;
    memset(var, sizeof(var), 0);
    now = 0;
    letter_click = 1;
    //generator();
}

void gamepage()
{

    int i, x = 70, y = 500;
    char ch[27][2]; //2D array to make string of every letter of alphabet
    ch[1][0] = 'A';
    ch[1][1] = 0;
    error = 0;
    score = temp1;

    FILE* fpp = fopen("files//Highscores.txt", "r"); //reading the high score from file saved
    while(!feof(fpp))
    {
        if(!feof(fpp))
        {
            fscanf(fpp, "%d", &high_score);
        }
    }
    fclose(fpp);

    drawTexture(1000, 25, goback);

    glClearColor(1, 1, 1, 1);
    iSetColor(255, 0, 0);
    if(temp2) iFilledRectangle(55, 635, 250, 40);
    iSetColor(0, 0, 0);
    if(temp2) iText(75, 650, "CLICK HERE TO START", GLUT_BITMAP_HELVETICA_18);
    if(!temp2) iText(80, 550, "CLICK ON THE LETTERS", GLUT_BITMAP_HELVETICA_18);

    for(i = 1; i <= 26; i++)
    {
        if(alpha[i - 1] == 1) //if the letter is correctly guessed it will be green
        {
            iSetColor(100, 180, 100);
        }
        else if(alpha[i - 1] == -1) //if the letter is incorrectly guessed it will be red
        {
            iSetColor(240, 0, 10);
        }
        else iSetColor(20, 20, 200); //otherwise blue
        iFilledRectangle(x, y, 30, 30);

        letters[i][0] = x; //storing the position of each letters
        letters[i][1] = x + 30;
        letters[i][2] = y;
        letters[i][3] = y + 30;

        iSetColor(255, 255, 255);
        iText(x + 10, y + 10, ch[i]);
        x += 40;
        if(i % 6 == 0)
        {
            x = 70;
            y -= 40;
        }
        ch[i + 1][0] = ch[i][0] + 1; //next letter
        ch[i + 1][1] = 0;
    }

    int x1 = 380, y1 = 170, space = 0;
    generator();

    for(i = 0; i < strlen(random); i++)
    {
        iSetColor(0, 0, 0);
        if(random[i] == ' ') space++; //calculating the number of spaces
        else iFilledRectangle(x1, y1, 30, 3); //showing the rectangle for blanks
        pos[i] = x1 + 10;
        x1 += 40;
    }

    int flag = 0;

    for(i = 0; i < strlen(random); i++)
    {
        if(random[i] == now)
        {
            arr[i] = 1;
            alpha[(int)(now - 'A')] = 1;
            var[i][0] = random[i]; //to make string of each appeared letters of the words
            var[i][1] = 0;
            flag = 1;
        }
    }
    if(flag == 0) //the letter doesn't appear in the word
    {
        alpha[(int)(now - 'A')] = -1;
    }

    for(i = 0; i < 26; i++)
    {
        if(alpha[i] == -1) error++;
    }
    if(error >= 5) //If error count is 5, the user loses his/her streak
    {
        iSetColor(0, 0, 0);
        //iText(350,300,"WRONG!",GLUT_BITMAP_HELVETICA_18);
        drawTexture(400, 350, wrong);
        iText(300, 250, "THE CORRECT ANSWER IS :-", GLUT_BITMAP_HELVETICA_18);
        if(t[2] % 3) iSetColor(50, 205, 50);
        else iSetColor(210, 105, 30);
        iText(570, 250, random, GLUT_BITMAP_HELVETICA_18);
        finish = 1;
        play_again();
    }

    iSetColor(0, 0, 0);

    int right = 0;

    for(i = 0; i < strlen(random); i++)
    {
        if(arr[i] == 1)
        {
            if(t[2] % 2) iSetColor(255, 0, 0); //changing the color of the letters with respect to time
            else iSetColor(0, 0, 255);
            iText(pos[i], 175, var[i], GLUT_BITMAP_HELVETICA_18);
            right++;
        }
    }

    if(right == strlen(random) - space)
    {
        drawTexture(400, 350, correct);
        finish = 1;
        play_again();
    }

    if(error >= 5) score = 0;
    else if (right == strlen(random) - space) score = temp1 + 20 - error * 4;
    if(score >= high_score)
    {
        high_score = score;
        iSetColor(0, 255, 0);
        if(finish) iText(370, 100, "CONGRATULATIONS! NEW HIGH SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
        FILE* fpp = fopen("files//Highscores.txt", "w");
        fprintf(fpp, "%d", high_score);
        fclose(fpp);
    }

    itoa(score, score_string, 10);
    itoa(high_score, highscore_string, 10);
    itoa((5 - error), guess_rem, 10);
    itoa((strlen(random) - space - right), let_rem, 10);

    iSetColor(123, 123, 234);
    iText(1120, 650, "SCORE:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1210, 650, score_string, GLUT_BITMAP_TIMES_ROMAN_24);

    iText(1050, 600, "HIGH SCORE:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1210, 600, highscore_string, GLUT_BITMAP_TIMES_ROMAN_24);

    iText(400, 650, "TRIES REMAINING:", GLUT_BITMAP_9_BY_15);
    iText(400, 600, "LETTERS REMAINING:", GLUT_BITMAP_9_BY_15);
    iText(550, 650, guess_rem, GLUT_BITMAP_9_BY_15);
    iText(570, 600, let_rem, GLUT_BITMAP_9_BY_15);

    if(right == (strlen(random) - space) or error >= 5) letter_click = 0;
    hang();
}

void hang() //function for showing different hanging states of a man depending on the error count
{
    iSetColor(200, 250, 0);
    if(error == 0)
    {
        drawTexture(750, 385, hang0);
    }
    if(error == 1)
    {
        drawTexture(750, 385, hang1);
    }
    else if(error == 2)
    {
        drawTexture(750, 385, hang2);
    }
    else if(error == 3)
    {
        drawTexture(750, 385, hang3);
    }
    else if(error == 4)
    {
        drawTexture(750, 385, hang4);
    }
    else if(error >= 5)
    {
        drawTexture(750, 385, hang5);
    }
}

void iDraw()
{

    //place your drawing codes here

    iClear();
    gettime(t);

    mouseOver(ix, iy);
    if(start == 0)
    {
        homepage();
    }

    if(start == 1)
    {
        show_categories();
    }

    if(start == 2)
    {
        gamepage();
    }

    if(start == 4)
    {
        settings_page();
    }
    if(start == 5)
    {
        drawTexture(0, 0, help);
        drawTexture(1000, 25, goback2);
    }

}

int main()
{
    srand(time(NULL));
    FILE * fp;
    fp = fopen("files/database.txt", "r");


    int i = 0;

    while(!feof(fp))
    {
        if (!feof(fp))
        {
            fgets(words[i], 100, fp);
            words[i][strlen(words[i]) - 1] = 0;
        }
        i++;
    }

    iInitialize(1300, 720, "HANGMAN");
    return 0;
}
