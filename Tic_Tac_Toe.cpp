#include <iostream>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char player[2];
char usedslot[9] = {};
int currentplayer;

void setcolor(const string& color_no)
{
    cout << "\033["<<color_no<<"m";
}


void drawboard()
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout<<" ";
            if(board[i][j] == 'X')
                setcolor("31");
            else if(board[i][j] =='O')
                setcolor("32");
            else
                setcolor("0");
            
            cout<< board[i][j];
            setcolor("0");

            if (j < 2)
                cout << " |";
            
        }
        cout << endl;

        if (i < 2)
            cout << "---+---+---" << endl;
    }

    cout << endl;
}

void changeplayer()
{
    if (currentplayer == 1)
        currentplayer = 0;
    else
        currentplayer = 1;
}

int valid_slot(int slot)
{
    int j = 1;
    for (int i = 1; i <= 9; i++)
    {
        if (i == slot)
            j = 0;
    }

    if (j == 1)
        return 1;

    for (int i = 0; usedslot[i] != '\0'; i++)
    {
        if (usedslot[i] == slot+48)
            return 2;
    }

    if (j == 0)
        return 0;
}

void update_board(int pos, char sign)
{
    pos--;
    board[pos / 3][pos % 3] = sign;
}

int check_winner()
{
    for(int i=0;i<3;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
            return 1;
        if (board[0][i]==board[1][i] && board[1][i]==board[2][i])
            return 1; 
    }

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
        return 1;
    else if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
        return 1;
    else   
        return 0;
}

void game()
{
    int slot;
    int error;
    int i,j = 0;
    cout << "Player 1  --  " << player[0] << endl;
    cout << "Player 2  --  " << player[1] << endl;

    drawboard();

    for ( i = 0; i < 9; i++)
    {
        while (1)
        {
            cout << "Player " << currentplayer + 1 << " Enter your move : ";
            cin >> slot;

            error = valid_slot(slot);
            if (error == 1)
            {
                cout << "Invalid input , Enter a number in [1-9] : ";
                continue;
            }
            else if (error == 2)
            {
                cout << "Invalid input , Do not repeat any number : ";
                continue;
            }
            else
            {
                usedslot[j++] = slot+48;
                update_board(slot, player[currentplayer]);
                break;
            }
        }
        
        

        drawboard();

        if(check_winner())
        {
            cout<<"Winner is Player "<<currentplayer+1<<endl;
            break;
        }

        changeplayer();
    }

    if(i==9)
        cout<<"It's a draw"<<endl;
}

int main()
{

    while (1)
    {
        cout << "Who will start the Game - [ 1 , 2 ] : ";
        cin >> currentplayer;

        if (currentplayer != 1 && currentplayer != 2)
        {
            cout << "Invalid input " << endl;
            continue;
        }

        currentplayer--;

        while (1)
        {
            cout << "Player " << currentplayer + 1 << " choose your sign - [ X , O ] : ";
            cin >> player[currentplayer];

            player[currentplayer] = toupper(player[currentplayer]);

            if (player[currentplayer] == 'X')
            {
                changeplayer();
                player[currentplayer] = 'O';
                break;
            }
            else if (player[currentplayer] == 'O')
            {
                changeplayer();
                player[currentplayer] = 'X';
                break;
            }
            else
            {
                cout << "Invalid input " << endl;
                continue;
            }
        }
        changeplayer();
        break;
    }

    game();

    return 0;
}