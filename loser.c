// b.maherani@hotmail.com

#include "clui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
//clear_screen();
//delay(ms);
void Start_Menu();
void Signup_Menu();
void Login_Menu();
void Account_Menu();
void start_game();
void show_leaderboard();
void new_word();


int Randoms(int upper)
{
    int num = (rand() % (upper)) + 1;
    return num;   
}





void start_game(char usName[])
{
    delay(500);
    FILE* fWords;
    char randomWord[25]; // string that saves random word from words.txt
    fWords = fopen("words.txt" , "r");
    int tedadLine = 0; 
    while (fscanf(fWords , "%s" , randomWord) != EOF)
    {
        tedadLine++;
    }
    fclose(fWords);

    srand(time(0));
    int randomLine = Randoms(tedadLine); // generates random number.

    fWords = fopen("words.txt" , "r");
    for (int i = 1; i <= randomLine ; i++)
    {
        fscanf(fWords , "%s" , randomWord);
    }
    fclose(fWords);

    int endFlag = 0; // to determine when game is done.
    int charFlag = 2; // to determine when the guess is correct or wrong.
    int errors = 0; // number of allowed wrong guesses.
    const int len = strlen(randomWord); // lenght of randomword.
    char show_word [len]; // an array to show the hidden word for game.
    char chosen[35]; // an array to save the charachters that have been choosen.

    for (int i = 0; i < 35 ; i++)
    {
        chosen[i] = ' ';
    }

    int chosenFlag = 0; //used when a character had been used.
    int counter = 0; // a counter for chosen array.
    char guess; // users guess.
    char loser[5] = {'L' , 'O' , 'S' , 'E' , 'R'}; 
    strcpy(show_word , randomWord);
    for (int i = 0; i < len; i++)
    {
        show_word[i] = '-';
    }


    while (endFlag == 0)
    {
        if (guess != 10) // this if is for an unkwon error in programm.
        {
            for(int i = 0; i <= counter ; i++) // checking that if users guess is new.
            {
                if (chosen[i] == guess)
                {
                    chosenFlag = 1;
                }
            }
            if (chosenFlag != 1) // if the word is used twice!
            {
                chosen[counter] = guess;
                counter++;

                if (charFlag == 1 && guess != 10) // guess is correct!
                {
                    delay(1000);
                    clear_screen();
                    change_color_rgb (10 , 150 , 10);
                    printf(" *** Nice Guess ***\n\n");
                    reset_color();
                    charFlag = 2;
                }

                else if (charFlag == -1 && guess != 10) // guess is wrong!
                {
                    delay(1000);
                    clear_screen();
                    errors++;
                    change_color_rgb(150 , 10 , 10 );
                    printf(" !!! Bad Guess !!!\n\n");
                    reset_color();
                    charFlag = 2;
                }
                charFlag = -1;
                change_color_rgb(255, 251, 0);
                for(int i = 0; i < len; i++) // prints hidden word.
                {
                    delay(100);
                    printf(" %c" , show_word[i]);
                }
                reset_color();
                delay (1000);
                printf("\n\n");
                change_color_rgb(150 , 10 , 10);
                printf(" -> ");

                // prints The Word " L O S E R".
                if (len < 8)
                {
                    for(int i = 0 ; i < errors ;i++)
                    {
                        printf("%c" , loser[i]);
                    }
                }
                else if (len >= 8)
                {
                    for(int i = 0 ; i < errors/2 ;i++)
                    {
                        printf("%c" , loser[i]);
                    }
                }
                reset_color();
                //

                if ((len <8 && errors == 5) || (len >= 8 && errors == 10)) // gameover
                {
                    change_color_rgb(150 , 10 ,10);
                    printf("\n\n :(    !!! Game Over !!!     ):\n\n");
                    reset_color();
                    printf(" The Word Was ----> %s\n" , randomWord);
                    endFlag = -1;
                    delay(1000);
                    break;
                }

                if (strcmp (randomWord , show_word) == 0) // wining
                {
                    change_color_rgb(10 , 150 , 10);
                    printf("\n\n:)   *** You Won ***    (:\n\n");
                    reset_color();
                    printf(" The Word Was ----> %s\n" , randomWord);
                    printf(" Earned Score ----> %d\n" , len);
                    endFlag = 1;
                    delay(1000);
                    break;
                }
                delay(500);
            }


            else // age kalame tekrari bood!
            {
                printf(" You Already Used ----> ");
                for(int i = 0 ; i <= counter ; i++)
                {
                    printf("%c " , chosen[i]);
                }
            }
            printf("\n Type Your Guess In Lower Case ----> ");
        }

        scanf("%c" , &guess);

        for (int i = 0; i < len; i++) // check mikone ke hads karbar toye kalame hast ya na!?
        {
            if (randomWord[i] == guess)
            {
                show_word[i] = randomWord [i];
                charFlag = 1;
            }
        }
        chosenFlag = 0;
    }

    // Adding New Score //

    int score = 0; // Score
    char buf[25]; // string for reading each line in file.


    if (endFlag == 1) // if the player wins
    {
        int line = 0;
        int score = 0;
        char buf[25];
        FILE* rBoard;
        FILE* wBoard;
        rBoard = fopen("board.txt" , "r+");
        wBoard = fopen("temp.txt" , "w");
        while (fscanf(rBoard , "%s" , buf) != EOF)
        {        
            fprintf(wBoard , "%s\n" , buf);
            if (strcmp(buf , usName) == 0)
            {
                fscanf(rBoard , "%d" , &score); // previous score
                score += len; // new score
                fprintf(wBoard , "%d\n" , score); // adding new scores
            }
        }
        int v;
        fclose(wBoard);
        fclose(rBoard);

        // updating score file and temp file.
        v = rename("board.txt" , "tp.txt");
        v = rename("temp.txt", "board.txt");
        v = rename("tp.txt" , "temp.txt");
        //
    }

    printf("\n Loading LeaderBoard ...\n");
    delay(5000);
    show_leaderboard(usName);
}






void new_word(char usName[])
{
    delay(500);
    clear_screen();
    delay(1000);
    FILE* fWords;
    char buf[25]; // read every line in txt file.
    char getWord[25];
    short int flag = 0;
    change_color_rgb(255, 251, 0);
    printf(" ==================================\n\t *** New Word Menu ***\n\n");
    reset_color();
    while (flag == 0)
    {
        flag = 1;
        fWords = fopen("words.txt" , "r");
        delay(500);
        printf(" Type Your Word In Lower Case -----> ");
        scanf("%s" , getWord);

        while (fscanf(fWords ,"%s",buf) != EOF) // checking the word in database!!
        {
            if (strcmp(buf , getWord) == 0)
            {
                delay(750);
                change_color_rgb(150 , 10 , 10);
                printf(" !!! Error: Your Word Is Already In The DataBase !!!\n\n");
                reset_color();
                flag = 0;
                fclose(fWords);
            }
        }
    }
    fWords = fopen("words.txt" , "a");
    fprintf(fWords , "\n%s" , getWord); // adding the new word to the list.
    fclose(fWords);
    delay(1000);
    change_color_rgb(10 , 150 ,10);
    printf(" *** New Word Added Succesfully ***\n");
    reset_color();
    delay(3000);
    clear_screen();
    Account_Menu(usName);    
}





void show_leaderboard(char usName[])
{
    delay(500);
    clear_screen();
    delay(500);
    change_color_rgb(255, 251, 0);
    printf(" ==================================\n\t *** LeaderBoard ***\n\n");
    reset_color();
    FILE* fLeaderboard;
    fLeaderboard = fopen("board.txt" , "r");
    char buf [25];
    while (fscanf(fLeaderboard , "%s" , buf) != EOF)
    {
        if (strcmp (buf , usName) == 0) {change_color_rgb(255, 251, 0);}
        printf("  %s ............... " , buf);
        delay(100);
        fscanf(fLeaderboard , "%s" , buf);
        printf("%s\n" , buf);
        reset_color();
        delay(100);
    }
    fclose(fLeaderboard);
    int command = 1;
    printf("\n Back To Account Menu ----> 9\n Exit ----> 0\n");
    scanf ("%d" , &command);
    if (command == 9)
    {
        delay(1000);
        clear_screen();
        delay(500);
        Account_Menu(usName);
    }
    else if(command == 0)
    {
        exit;
    }    
}






void Account_Menu(char usName[])
{
    change_color_rgb(255, 251, 0);
    printf(" ==================================\n\t *** Account Menu ***\n\n");
    reset_color();
    delay(500);
    printf(" 1. Start Game\n 2. Show Leaderboard\n 3. New Word\n 4. Exit\n\n 0.SignOut\n\n\n");
    int command;
    scanf("%d" , &command);
    switch(command)
    {
        case 0:
            delay(500);
            printf(" Signing Out ...\n");
            delay(2000);
            clear_screen();
            Start_Menu();
            break;
        case 1:
            delay(500);
            printf(" Starting A Game ...\n");
            delay(2000);
            clear_screen();
            start_game(usName);
            break;
        case 2:
            show_leaderboard(usName);
            break;
        case 3:
            new_word(usName);
            break;
        case 4:
            exit;
            break;
    }
}





void Login_Menu()
{
    change_color_rgb(255, 251, 0);
    printf (" ==================================\n\t *** Login Menu ***\n\n *** Enter Your Acount Information ***\n");
    reset_color();
    delay(500);
    FILE* usInfo;
    char usName [25] = "@";
    char pass [25] = "#";
    char getPass [25];
    char getUsName [25];
    short int flag = 0;
    char buf[25];
    delay(500);
    while (flag == 0)
    {
        usInfo = fopen("UserInfo.txt" , "r");
        strcpy(usName , "@"); strcpy(pass , "#");
        printf(" Username: ");scanf("%s" , getUsName);
        printf(" Password: "); scanf("%s" , getPass);
        strcat(usName , getUsName); strcat(pass , getPass);
        while(fscanf(usInfo,"%s" , buf) != EOF)
        {
            if (buf[0] == '@' && strcmp (buf , usName) == 0)
            {
                fscanf(usInfo,"%s" , buf);
                if (buf[0] == '#' && strcmp (buf , pass) == 0)  
                {
                    flag = 1;
                    fclose(usInfo);
                    break;
                }
            }
        }
        if (flag == 0)
        {
            change_color_rgb (150 , 10 , 10);
            printf (" !!! Error: Username Or Password Is Worng !!!\n\n");
            reset_color();
        }
    }
    delay(1000);
    clear_screen();
    delay(1000);
    change_color_rgb(10 , 150 , 10);
    printf("\n *** Welcome To Your Account, %s ***\n\n" , getUsName);
    reset_color();
    delay(500);
    Account_Menu(getUsName);
}






void Signup_Menu()
{
    FILE* usInfo;
    usInfo = fopen("UserInfo.txt" , "r");
    char buf[25]; // array for reading each line in txt file.
    char getUsName[25];
    char getPass[25];
    char usName[25]="@"; // every username starts with "@" for saving in file.
    char pass[25]="#"; // every password starts with "#" for saving in file.
    change_color_rgb(255, 251, 0);
    printf(" ==================================\n\t *** SignUp Menu ***\n\n *** Enter Your Information ***\n\n");
    reset_color();

    short int usFlag = 0 , passFlag = 0;
    delay(500);
    while (usFlag == 0) //gets username and checks that the username isn't already used.
    {
        usInfo = fopen("UserInfo.txt" , "r");
        strcpy(usName , "@");
        printf(" Username: ");
        scanf("%s", getUsName); strcat(usName , getUsName);
        usFlag = 1;
        while(fscanf(usInfo,"%s" , buf) != EOF)
        {
            if (buf[0] == '@' && strcmp(buf , usName) == 0)
            {
                delay(500);
                change_color_rgb(150 , 10 ,10);
                printf(" !!! Error: Username already taken !!!\n");
                reset_color();
                usFlag = 0;
                fclose(usInfo);
                break;
            }
        }
        if (usFlag == 1)
        {
            fclose(usInfo);
        }
    }
    while (passFlag == 0)
    {
        delay(500);
        printf(" Password: ");
        scanf("%s" , getPass);
        short int A_Z = 0 , a_z = 0 ,numChar = 0 ,spChar = 0;
        for(int i = 0; i <25; i++)
        {
            char ch = getPass[i];
            if (a_z == 1 && A_Z == 1 && spChar == 1 && numChar == 1)
            {
                passFlag = 1;
                break;
            }
            if(ch == '\0') break; 
            if (ch >= 'a' && ch <= 'z')
            {
                a_z = 1;   
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                A_Z = 1;
            }
            else if(ch >= '0' && ch <= '9')
            {
                numChar = 1;
            }
            else 
            {
                spChar = 1;
            }
        }
        if (passFlag == 0 | strlen(getPass) < 8)
        {
            delay(500);
            change_color_rgb(150 , 10 , 10);
            printf("\n\n !!! Error: Your Password Must Contain a-z, A-Z , 0-9 and Special Characters And At Least 8 Characters !!!\n\n");
            reset_color();
            passFlag = 0;
        }    
    }
    usInfo = fopen("UserInfo.txt" , "a");
    fprintf(usInfo , "\n@%s\n#%s", getUsName , getPass);
    fclose(usInfo);
    usInfo = fopen ("board.txt" , "a");
    fprintf(usInfo ,"\n%s\n%d" , getUsName , 0 );
    fclose(usInfo);
    delay(500);
    change_color_rgb(10 , 150 ,10);
    printf(" *** Your Acount SignedUp Succesfully ***\n");
    reset_color();
    delay(3000);
    clear_screen();
    Start_Menu();
}





void Start_Menu()
{
    change_color_rgb(255, 251, 0);
    printf(" ==================================\n\t *** Start Menu ***\n\n");
    reset_color();
    delay(500);
    printf(" 1. Login \n 2. Signup \n 3. Exit\n");
    int command;
    scanf("%d" , &command);
    delay(1000);
    clear_screen(); delay(500);
    switch (command)
    {
    case 1:
        Login_Menu();
        break;
    case 2:
        Signup_Menu();
        break;
    case 3:
        exit;
        break;
    } 
}



int main()
{
    clear_screen();
    delay(500);
    change_color_rgb(255, 251, 0);
    printf(" *** Welcome To The Loser Game ***\n");
    reset_color();
    delay(1000);
    Start_Menu();
}
