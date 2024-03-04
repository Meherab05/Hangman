#include "iGraphics.h"

#include <bits/stdc++.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm,lib")
using namespace std;
int wonflag = 0;

char wordlist[50][20] = {
    "BUBBLE", "GUITAR", "BEACH", "BOOK", "CAKE", "FLOWER", "MOON", "TREE", "SUN", "BIRD", "CLOUD", "STAR", "SMILE", "PIANO", "RIVER", "BOAT", "RAINBOW", "BUTTERFLY", "CANDLE", "MOUNTAIN", "ISLAND", "BRIDGE",
    "KEY", "LOCK", "MAP", "FISH", "HOME", "SHIP", "TRAIN", "CAR", "BIKE", "PLANE", "BUS", "HAT", "SHOE", "GLOVE", "SOCKS", "SHIRT", "PANTS", "DRESS", "COAT", "UMBRELLA", "GLASSES", "WATCH", "RING",
    "BRACELET", "NECKLACE", "EARRINGS"};
char hints[50][30] = {"FLOATS IN THE AIR", "MUSICAL INSTRUMENT", "SANDY AREA BY THE SEA", "CONTAINS STORIES", "SWEET BAKED DESSERT", "COLORFUL PLANT", "NATURAL SATELLITE", "TALL WOODY PLANT", "OUR CLOSEST STAR", "FEATHERED FLYER", "WHITE FLUFFY MASS", "LUMINOUS CELESTIAL BODY", "EXPRESSES HAPPINESS", "MUSICAL INSTRUMENT", "FLOWING BODY OF WATER", "VESSEL FOR TRAVELING", "COLORFUL ARC", "COLORFUL INSECT", "SOURCE OF LIGHT", "LARGE NATURAL ELEVATION", "LAND SURROUNDED BY WATER", "STRUCTURE OVER WATER", "OPENS OR CLOSES", "SECURES SOMETHING", "SHOWS GEOGRAPHY", "COLD-BLOODED AQUATIC ANIMAL", "PLACE OF LIVING", "LARGE BOAT", "RAILWAY VEHICLE", "PERSONAL TRANSPORTATION", "TWO-WHEELED TRANSPORT", "POWERED FLYING VEHICLE", "LARGE VEHICLE FOR PEOPLE", "HEAD COVERING", "FOOTWEAR", "HAND COVERING", "COVERINGS FOR FEET", "UPPER BODY GARMENT", "GARMENT FOR LEGS", "WOMEN'S CLOTHING", "OUTER GARMENT", "RAIN PROTECTION", "EYEWEAR", "WRIST TIMEPIECE", "FINGER ADORNMENT", "WRIST ORNAMENT", "NECK ADORNMENT", "EAR JEWELRY"};

int r;
int chances = 10;
string word = wordlist[r], hint = hints[r], word2 = "", hint2 = "";
char hangman[11][20] = {"", "bmp\\hangman10.bmp", "bmp\\hangman9.bmp", "bmp\\hangman8.bmp", "bmp\\hangman7.bmp", "bmp\\hangman6.bmp", "bmp\\hangman5.bmp", "bmp\\hangman4.bmp", "bmp\\hangman3.bmp", "bmp\\hangman2.bmp", "bmp\\hangman1.bmp"};
int game = 0;
string guess = "", playername = "";
int score = 0;
int sound = 1;
int sorry = 0;
int x = 0, y = 0, red = 255, g = 255, b = 255;
int wordinput = 1, hintinput = 0;
int counthint = 3;
int chintflag = 1, nameinput = 0;
typedef struct
{
    char name[20];
    int score;
} player;

player Players[3], player1;

void updateplayer(player Players[], player player1)
{
    for (int i = 0; i < 3; i++)
    {
        if (player1.score > Players[i].score)
        {
            for (int j = 2; j > i; j--)
            {
                Players[j].score = Players[j - 1].score;
                strcpy(Players[j].name, Players[j - 1].name);
            }
            Players[i].score = player1.score;
            strcpy(Players[i].name, player1.name);
            break;
        }
    }
}
bool name(player Players[], int score)
{
    for (int i = 0; i < 3; i++)
    {
        if (score > Players[i].score)
            return 1;
    }
    return 0;
}
void updateleaderboard(player Players[])
{
    FILE *file = fopen("leaderboard.txt", "w");
    for (int i = 0; i < 3; i++)
    {
        fprintf(file, "%s %d\n", Players[i].name, Players[i].score);
    }
    fclose(file);
}

void Showhint(string wor)
{
    if (counthint != 0 && chintflag)
        for (int i = 0;; i++)
        {
            if (guess.find(wor[i]) == string::npos)
            {
                guess += wor[i];

                counthint--;
                if (!counthint)
                    chintflag = 0;
                break;
            }
        }
}

string printavailableletters(string guessedword, char start, char end)
{
    string s;

    for (char i = start; i <= end; i++)
    {
        if (guessedword.find(i) == string::npos)
        {
            s += i;
            s += "    ";
        }
        else
            s += "     "s;
    }
    return s;
}
bool won(string word, string guess)
{
    int r = word.size();
    for (int i = 0; i < word.size(); i++)
    {
        if (guess.find(word[i]) == string::npos)
        {
            r--;
        }
    }
    return r == word.size();
}
string compareandprint(string word, string guessed)
{
    string s;
    for (int i = 0; i < word.size(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            s += "___   ";
        }
        else
        {
            int f = 1;
            if (i != word.size() - 2)
                for (int j = i + 1; j < word.size() - 1; j++)
                {
                    if (word[j] != word[j + 1])
                        f = 0;
                }
            if (f)
                chintflag = 0;
            s += word[i];
            s += "  ";
        }
    }
    return s;
}
int chancheck(string a, string b)
{
    int flag = 1;
    int n = b.size();
    if (a.find(b[n - 1]) == string::npos)
    {
        flag = 0;
    }
    return flag;
}

void iDraw()
{
    iClear();
    if (game == 0)
    {

        // iFilledRectangle(10, 30, 20, 20);
        if (sound)
            iShowBMP(0, 0, "bmp\\Home.bmp");
        else
            iShowBMP(0, 0, "bmp\\Homeo.bmp");
    }
    else if (game == 1)
    {
        iShowBMP(0, 0, "bmp\\back.bmp");
        iShowBMP2(685, 10, "bmp\\next.bmp", 255);

        iSetColor(0, 0, 0);
        word = wordlist[r];
        hint = hints[r];
        string compare = compareandprint(word, guess);
        float comparesize = compare.size() * 5.0;
        char arr2[compare.size() + 1];
        strcpy(arr2, compare.c_str());
        char arr3[hint.size() + 1];
        strcpy(arr3, hint.c_str());
        float hintsize = hint.size() * 5.0;

        if (!wonflag)
        {

            if (!sorry)
            {
                iShowBMP2(100, 200, hangman[chances], 255);
                iText(744 - hintsize, 250, arr3, GLUT_BITMAP_TIMES_ROMAN_24);
                iText(797 - comparesize, 200, arr2, GLUT_BITMAP_TIMES_ROMAN_24);
                string s = printavailableletters(guess, 'A', 'Z');
                char arr[s.size() + 1];
                strcpy(arr, s.c_str());
                iText(210, 100, arr, GLUT_BITMAP_TIMES_ROMAN_24);
                iShowBMP2(1200, 750, "bmp\\scorelogo.bmp", 255);
                char sscore[10];
                iSetColor(0, 0, 0);
                sprintf(sscore, "%d", score);
                iText(1252, 810, sscore, GLUT_BITMAP_TIMES_ROMAN_24);
                if (chintflag)
                {
                    iShowBMP2(1200, 640, "bmp\\Hint_logo.bmp", 255);
                }
            }
            else
            {

                char Wo[20];
                strcpy(Wo, word.c_str());
                iShowBMP(0, 0, "bmp\\gameover.bmp");
                iText(535, 205, "THE CORRECT WORD : ", GLUT_BITMAP_TIMES_ROMAN_24);

                iText(815, 205, Wo, GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }
        else
        {
            iShowBMP(0, 0, "bmp\\congratulations.bmp");
        }
        iShowBMP2(10, 770, "bmp\\homebutton.bmp", 0);
    }
    else if (game == 2)
    {
        iShowBMP(0, 0, "bmp\\back.bmp");
        iSetColor(0, 0, 0);
        if (wordinput == 1 || hintinput == 1)
        {
            iText(650, 700, "Enter the Word to Guess : ", GLUT_BITMAP_TIMES_ROMAN_24);
            float inputsize = word2.size() * 5.0;
            char wordarr[word2.size() + 1];
            strcpy(wordarr, word2.c_str());
            iText(750 - inputsize, 600, wordarr, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if (hintinput == 1)
        {
            iText(685, 500, "Enter the Hint : ", GLUT_BITMAP_TIMES_ROMAN_24);
            float hintsize = hint2.size() * 5.0;
            char hintarr[hint2.size() + 1];
            strcpy(hintarr, hint2.c_str());
            iText(750 - hintsize, 400, hintarr, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if (hintinput == 2)
        {

            string compare = compareandprint(word2, guess);
            float comparesize = compare.size() * 10 / 2.0;
            char arr2[compare.size() + 1];
            strcpy(arr2, compare.c_str());
            char arr3[hint2.size() + 1];
            strcpy(arr3, hint2.c_str());
            float hintsize = hint2.size() * 10 / 2.0;

            if (!wonflag)
            {

                if (!sorry)
                {
                    iShowBMP2(100, 200, hangman[chances], 255);
                    iText(750 - hintsize, 250, arr3, GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(780 - comparesize, 200, arr2, GLUT_BITMAP_TIMES_ROMAN_24);
                    string s = printavailableletters(guess, 'A', 'Z');
                    char arr[s.size() + 1];
                    strcpy(arr, s.c_str());
                    iText(210, 100, arr, GLUT_BITMAP_TIMES_ROMAN_24);
                    iShowBMP2(1200, 750, "bmp\\scorelogo.bmp", 255);
                    char sscore[10];
                    iSetColor(0, 0, 0);
                    sprintf(sscore, "%d", score);
                    iText(1252, 810, sscore, GLUT_BITMAP_TIMES_ROMAN_24);
                    if (chintflag)
                    {
                        iShowBMP2(1200, 640, "bmp\\Hint_logo.bmp", 255);
                    }
                }

                else
                {

                    char Wo2[20];
                    strcpy(Wo2, word2.c_str());
                    iShowBMP(0, 0, "bmp\\gameover.bmp");
                    iText(535, 205, "THE CORRECT WORD : ", GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(815, 205, Wo2, GLUT_BITMAP_TIMES_ROMAN_24);
                }
            }
            else
            {
                iShowBMP(0, 0, "bmp\\congratulations.bmp");
            }
        }
        iShowBMP2(10, 770, "bmp\\homebutton.bmp", 0);
    }
    if (game == 3)
        iShowBMP(0, 0, "bmp\\instruction.bmp");
    if (game == 4)
    {
        iShowBMP(0, 0, "bmp\\leaderboard.bmp");
        iSetColor(0, 0, 0);
        iText(434, 381, Players[0].name, GLUT_BITMAP_HELVETICA_18);
        iText(434, 284, Players[1].name, GLUT_BITMAP_HELVETICA_18);
        iText(434, 186, Players[2].name, GLUT_BITMAP_HELVETICA_18);
        char sscore1[10];
        sprintf(sscore1, "%d", Players[0].score);
        iText(835, 381, sscore1, GLUT_BITMAP_HELVETICA_18);
        char sscore2[10];
        sprintf(sscore2, "%d", Players[1].score);
        iText(835, 284, sscore2, GLUT_BITMAP_HELVETICA_18);
        char sscore3[10];
        sprintf(sscore3, "%d", Players[2].score);
        iText(835, 186, sscore3, GLUT_BITMAP_HELVETICA_18);
    }
    if (game == 5)
    {
        iShowBMP(0, 0, "bmp\\back.bmp");
        iSetColor(0, 0, 0);

        iText(670, 700, "Enter your name : ", GLUT_BITMAP_TIMES_ROMAN_24);
        float inputsize = playername.size() * 5.0;
        char wordarr[playername.size() + 1];
        strcpy(wordarr, playername.c_str());
        iText(750 - inputsize, 600, wordarr, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
    // place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if (sound)
            PlaySound("music\\mouse-click.wav", NULL, SND_ASYNC);
        printf("%d %d\n", mx, my);
        if (game == 0)
        {

            if (mx >= 1055 && mx <= 1484 && my >= 634 && my <= 707)
            {

                game = 1;
            }

            else if (mx >= 1050 && mx <= 1482 && my >= 536 && my <= 615)
            {

                game = 2;
            }
            else if (mx >= 1050 && mx <= 1486 && my >= 451 && my <= 521)
                game = 3;
            else if (mx >= 1050 && mx <= 1485 && my >= 372 && my <= 437)
                game = 4;
            else if (mx >= 1219 && mx <= 1318 && my >= 277 && my <= 354)
                sound = 1 ^ sound;
        }
        else if ((game == 1 || game == 2) && mx >= 10 && mx <= 80 && my >= 770 && my <= 840 && pow(mx - 45, 2) + pow(my - 805, 2) <= pow(35, 2))
        {
            if (name(Players, score))
                game = 5;
            else
            {
                game = 0;
                score = 0;
            }
            guess = "";
            wonflag = 0;
            sorry = 0;
            hint2 = "";
            wordinput = 1, hintinput = 0;
            word2 = "";
            chintflag = 1;
            counthint = 3;
        }

        else if ((game == 1) && mx >= 685 && mx <= 823 && my >= 10 && my <= 62)
        {
            chances = 10;
            sorry = 0;
            ++r;
            if (r > 47)
                r = 0;
            word = wordlist[r];
            hint = hints[r];
            guess = "";
            counthint = 3;
            chintflag = 1;
        }

        else if (mx >= 1200 && mx <= 1275 && my >= 640 && my <= 715 && !sorry && (game == 1 || (game == 2 && hintinput == 2)) && !wonflag)
        {
            if (game == 1)
                Showhint(word);
            else
                Showhint(word2);
        }

        else if (wonflag && mx >= 738 && mx <= 845 && my >= 127 && my <= 214)
        {
            if (game == 1)
            {

                ++r;
                if (r > 47)
                    r = 0;
                word = wordlist[r];
                hint = hints[r];
                chances = 10;
                wonflag = 0;
                guess = "";
                counthint = 3;
                chintflag = 1;
            }
            else if (game == 2 && hintinput == 2)
            {

                word2 = "";
                hint2 = "";
                chances = 10;
                wonflag = 0;
                guess = "";
                wordinput = 1;
                hintinput = 0;
                counthint = 3;
                chintflag = 1;
            }
        }
        else if (sorry && mx >= 719 && mx <= 846 && my >= 76 && my <= 173)
        {
            if (game == 1)
            {

                ++r;
                if (r > 47)
                    r = 0;
                word = wordlist[r];
                hint = hints[r];
                chances = 10;
                wonflag = 0;
                guess = "";
                counthint = 3;
                chintflag = 1;
                sorry = 0;
            }
            else if (game == 2 && hintinput == 2)
            {

                word2 = "";
                hint2 = "";
                chances = 10;
                wonflag = 0;
                guess = "";
                wordinput = 1;
                hintinput = 0;
                counthint = 3;
                chintflag = 1;
                sorry = 0;
            }
        }
        else if (game == 3 && mx >= 734 && mx <= 841 && my >= 44 && my <= 112)
            game = 0;
        else if (game == 4 && mx >= 711 && mx <= 853 && my >= 41 && my <= 98)
        {
            game = 0;
        }
        if (game == 5)
        {
            nameinput = 1;
        }
    }
}
void iKeyboard(unsigned char key)
{
    if ((key >= 65 && key <= 90) || key == 8 || key == 13 || (key >= 97 && key <= 122))
    {
        if (sound)
            PlaySound("music\\click.wav", NULL, SND_ASYNC);
        if (game == 1)
        {
            if (chances > 0)
            {

                guess += toupper(key);
                if (won(word, guess))
                {
                    if (sound)
                        PlaySound("music\\success.wav", NULL, SND_ASYNC);
                    wonflag = 1;
                    score += 1;
                }
                if (!chancheck(word, guess))
                    --chances;
            }
            if (chances == 0)
            {
                sorry = 1;
                if (sound)
                    PlaySound("music\\sorryh.wav", NULL, SND_ASYNC);
                if (score > 0)
                    score -= 1;
            }
        }
        else if (game == 2)
        {
            if (wordinput && (int)key != 13)
            {
                if (key == 8)
                {
                    if (word2.size())
                        word2.pop_back();
                }
                else
                    word2 += toupper(key);
            }
            else if (wordinput && (int)key == 13)
            {
                wordinput = 0;
                hintinput = 1;
            }
            else if (hintinput == 1 && (int)key != 13)
            {
                if (key == 8)
                {
                    if (hint2.size())
                        hint2.pop_back();
                }
                else
                    hint2 += toupper(key);
            }
            else if (hintinput == 1 && (int)key == 13)
            {
                hintinput = 2;
            }
            else if (hintinput == 2)
            {
                if (chances > 0)
                {
                    guess += toupper(key);
                    if (won(word2, guess))
                    {
                        wonflag = 1;

                        if (sound)
                            PlaySound("music\\success.wav", NULL, SND_ASYNC);
                        score += 1;
                    }
                    else
                    {
                        if (!chancheck(word2, guess))
                            --chances;
                        if (chances == 0)
                        {
                            sorry = 1;
                            if (sound)
                                PlaySound("music\\sorryh.wav", NULL, SND_ASYNC);
                            if (score > 0)
                                score -= 1;
                        }
                    }
                }
            }
        }
        else if (game == 5)
        {
            if (key == '\r')
            {
                strcpy(player1.name, playername.c_str());
                player1.score = score;
                updateplayer(Players, player1);
                updateleaderboard(Players);
                playername = "";
                game = 0;
                nameinput = 0;
                score = 0;
            }
            else
            {
                if (key == 8)
                {
                    if (playername.size())
                        playername.pop_back();
                }
                else
                    playername += toupper(key);
            }
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
}

int main()
{
    srand(time(NULL));
    r = rand() % 45;

    FILE *fil = fopen("leaderboard.txt", "r");

    for (int i = 0; i < 3; i++)
    {
        fscanf(fil, "%s %d", Players[i].name, &Players[i].score);
    }
    fclose(fil);

    iInitialize(1500, 850, "Hangman");
    return 0;
}
