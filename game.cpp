#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "tetrominoes.cpp"
using namespace std;
int highscore=0;
tetrominoes T;
int level(char ch)
{
    int fallDelay;
    switch(ch)
    {
        case 'h': fallDelay=8;break;
        case 'e': fallDelay=18;break;
        case 'm': fallDelay=13;break;
    }
    return fallDelay;
}
int fallDelay;

class Grid {
private:
    vector<vector<int>> grid;
    int length = LENGTH;
    int width = WIDTH;

public:
    Grid() : grid(LENGTH, vector<int>(WIDTH, 0)) {}
    
    void render(node* currentShape, node* nextShape, HANDLE consoleHandle) {
        COORD pos = {0, 0};
        SetConsoleCursorPosition(consoleHandle, pos);
        
        for (int i = 0; i < LENGTH + 4; ++i) {
            for (int j = 0; j < WIDTH + 1; ++j) {
                bool isShape = false;
                node* temp = currentShape;
                if (j == 0 || j == WIDTH || i == LENGTH + 3) {
                    cout << "❌";
                    continue;
                }
                while (temp) {
                    if (temp->p.X == i && temp->p.Y == j) {
                        cout << T.v[T.k];
                        isShape = true;
                        break;
                    }
                    temp = temp->next;
                }
                if (!isShape) {
                    if (i >= 3 && i < LENGTH + 3 && j > 0 && j < WIDTH && grid[i - 3][j] == 1) {
                        cout << T.v[T.k];
                    } else {
                        cout << "  ";
                    }
                }
            }
            if (i >= 1 && i <= 5) {
                cout << "  ";
                for (int j = 0; j < 4; ++j) {
                    bool isNextShape = false;
                    node* nextTemp = nextShape;
                    while (nextTemp) {
                        if (nextTemp->p.X == i - 1 && nextTemp->p.Y - 4 == j) {
                            cout << T.v[T.next_k];
                            isNextShape = true;
                            break;
                        }
                        nextTemp = nextTemp->next;
                    }
                    if (!isNextShape) cout << "  ";
                }
            }
            cout << "\r\n";
        }
        COORD nextLabel = {static_cast<SHORT>(WIDTH * 2 + 2), 0};
        SetConsoleCursorPosition(consoleHandle, nextLabel);
        cout << "\t𝙉 𝙀 𝙓 𝙏";
    }

    void clearRows(int& score) {
        int linesCleared = 0;
        for (int i = LENGTH - 1; i >= 0; --i) {
            bool fullRow = true;
            for (int j = 1; j < WIDTH; ++j) {
                if (grid[i][j] == 0) {
                    fullRow = false;
                    break;
                }
            }
            if (fullRow) {
                linesCleared++;
                for (int k = i; k > 0; --k) {
                    for (int j = 1; j < WIDTH; ++j) {
                        grid[k][j] = grid[k - 1][j];
                    }
                }
                for (int j = 1; j < WIDTH; ++j) {
                    grid[0][j] = 0;
                }
                if(score%10==0 && score>=10)
                {
                    fallDelay-=2;
                }
            }
        }
        score += linesCleared * 10;
    }

    void lockPiece(node* currentShape) {
        node* temp = currentShape;
        while (temp) {
            if (temp->p.X >= 3 && temp->p.X < LENGTH + 3 && 
                temp->p.Y >= 1 && temp->p.Y <= WIDTH - 1) {
                grid[temp->p.X - 3][temp->p.Y] = 1;
            }
            temp = temp->next;
        }
    }

    vector<vector<int>>& getGrid() {
        return grid;
    }

    bool isGameOver() {
        for (int j = 1; j < WIDTH; ++j) {
            if (grid[0][j] == 1) return true;
        }
        return false;
    }
};

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void tutorial()

{

    cout << R"(Welcome to the Ultimate Tetromino Challenge!



Are you ready to test your reflexes and strategic thinking? This guide will teach you how to master the art of tetromino stacking and line-clearing! Let’s dive in.



### Basic Controls:

- ← Left Arrow: Move your tetromino to the left.

- → Right Arrow: Move your tetromino to the right.

- ↑ Up Arrow: Rotate your tetromino 90 degrees.

- ↓ Down Arrow: Soft drop to speed up the descent of the tetromino.

- Spacebar: Hard drop for an instant landing.

- ESC: Pause or Quit the game.



### Game Mechanics:

- A line clears when all blocks in a row are completely filled.

- Tetrominoes fall at a constant speed, but as you clear more lines, the speed increases!

- The game ends when tetrominoes stack up to the top of the screen.

- Each tetromino can rotate four times, allowing for multiple placement strategies.



### Pro Tips to Dominate the Game:

1. Plan Your Moves – Don’t just drop pieces randomly! Think ahead to create gaps that allow you to clear multiple lines at once.

2. Use the Hard Drop Wisely – The Spacebar can instantly place your tetromino, saving time, but be careful! Once it lands, there’s no going back.

3. Rotate for the Perfect Fit – Use the ↑ Up Arrow to rotate pieces strategically. A well-rotated piece can fit into tight spaces you might have missed!

4. Keep the Stack Low – Always try to keep your pile of tetrominoes low to give yourself more room to maneuver.

5. Speed is Key – As the game progresses, tetrominoes fall faster. Stay calm and react quickly to avoid stacking

Good luck, and happy stacking!

To continue press 'C':

Press Esc to exit :

)" << endl;

}

int main() {
    int game=1;
    while(game)
    {

    
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    Grid grid;
    int score = 0;
    int fallCounter = 0;
    system("cls");
    cout << "\033[1;32m"; 
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
     cout << R"(
     
                                            █████████████████████████████████████████████████████████████████████████████
                                            █─▄─▄─█▄─▄▄─█─▄─▄─█▄─▄▄▀█▄─▄█─▄▄▄▄███─▄─▄─██▀▄─██─▄▄▄─█─▄─▄─█▄─▄█─▄▄▄─█─▄▄▄▄█
                                            ███─████─▄█▀███─████─▄─▄██─██▄▄▄▄─█████─████─▀─██─███▀███─████─██─███▀█▄▄▄▄─█
                                            ▀▀▄▄▄▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▀▄▄▀▄▄▄▀▄▄▄▄▄▀▀▀▀▄▄▄▀▀▄▄▀▄▄▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀)";
    cout << "\033[0m\n";
    Sleep(3000); 
    system("cls");
    cout << "\033[1;34m"; 
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
     cout << R"(
     
    
                                            ██╗░░░░░███████╗████████╗██╗░██████╗  ██████╗░██╗░░░░░░█████╗░██╗░░░██╗
                                            ██║░░░░░██╔════╝╚══██╔══╝╚█║██╔════╝  ██╔══██╗██║░░░░░██╔══██╗╚██╗░██╔╝
                                            ██║░░░░░█████╗░░░░░██║░░░░╚╝╚█████╗░  ██████╔╝██║░░░░░███████║░╚████╔╝░
                                            ██║░░░░░██╔══╝░░░░░██║░░░░░░░╚═══██╗  ██╔═══╝░██║░░░░░██╔══██║░░╚██╔╝░░
                                            ███████╗███████╗░░░██║░░░░░░██████╔╝  ██║░░░░░███████╗██║░░██║░░░██║░░░
                                            ╚══════╝╚══════╝░░░╚═╝░░░░░░╚═════╝░  ╚═╝░░░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░
    )";
    cout << "\033[0m\n"; 
    cout << "\033[31m";
    cout <<"\t"<< R"(
                                                                    𝐏𝐑𝐄𝐒𝐒 𝐄𝐍𝐓𝐄𝐑 𝐓𝐎 𝐁𝐄𝐆𝐈𝐍 𝐓𝐇𝐄 𝐆𝐀𝐌𝐄 )";
    cout << "\033[0m\n"; 
    while(1)
    {
        if(kbhit())
        {
             char ch = getch();
            
            if( ch==13 || ch==10 ) break;
        }
    }
    system("cls");
    cout << R"(𝙋𝙍𝙀𝙎𝙎 𝙏 𝙏𝙊 𝙎𝙀𝙀 𝙏𝙐𝙏𝙊𝙍𝙄𝘼𝙇𝙎 𝘼𝙉𝘿 𝙍𝙐𝙇𝙀𝙎:)" << endl;
    cout << R"(𝙋𝙍𝙀𝙎𝙎 𝘾 𝙏𝙊 𝘾𝙊𝙉𝙏𝙄𝙉𝙐𝙀 𝙏𝙃𝙀 𝙂𝘼𝙈𝙀:)" << endl;
    cout << R"(𝙋𝙍𝙀𝙎𝙎 𝙀𝙎𝘾 𝙏𝙊 𝙀𝙓𝙄𝙏)" << endl;
     cout << "\033[0m\n";
    while(1)
    {
        if(kbhit())
        {
            char ch=getch();
            switch(ch)
            {
                case 't' : {tutorial();}
            }
            if(ch==27) exit(0);
            if(ch=='c') 
            {
                system("cls");
                break;
                }
        }
    }
    system("cls");
    cout << "\033[1;92m"; 
    cout<<R"(𝒞𝐻𝒪𝒪𝒮𝐸 𝐿𝐸𝒱𝐸𝐿: )"<<endl;
    cout<<R"(𝒫𝑅𝐸𝒮𝒮 '𝒽' 𝐹𝒪𝑅 𝐻𝒜𝑅𝒟.)"<<endl;
    cout<<R"(𝒫𝑅𝐸𝒮𝒮 '𝑒' 𝐹𝒪𝑅 𝐸𝒜𝒮𝒴.)"<<endl;
    cout<<R"(𝒫𝑅𝐸𝒮𝒮 '𝓂 ' 𝐹𝒪𝑅 𝑀𝐸𝒟𝐼𝒰𝑀.)"<<endl;
    cout << "\033[0m\n";
    while(1)
    {
        if(kbhit())
        {
            char c=getch();
            if(c=='h' || c=='e' || c=='m') 
            {
                cout<<c<<endl;
                fallDelay=level(c);
                Sleep(500);
                break;
            }
            else cout << endl << c  << endl << "Enter Again." << endl;
        }
    }
    system("cls");

    T.get_current_shape() = T.Shape();
    T.next_shape = T.Shape();
    while (T.k == T.next_k) {
        T.freeShape(T.next_shape);
        T.next_shape = T.Shape();
    }
    if (!T.canSpawn(grid.getGrid())) {
        system("cls");
        game=0;

        cout << "\033[1;95m"; 
        cout <<"\t\t\t\t"<< R"(
       
                                                ╭━━━┳━━━┳━╮╭━┳━━━╮╭━━━┳╮╱╱╭┳━━━┳━━━╮
                                                ┃╭━╮┃╭━╮┃┃╰╯┃┃╭━━╯┃╭━╮┃╰╮╭╯┃╭━━┫╭━╮┃
                                                ┃┃╱╰┫┃╱┃┃╭╮╭╮┃╰━━╮┃┃╱┃┣╮┃┃╭┫╰━━┫╰━╯┃
                                                ┃┃╭━┫╰━╯┃┃┃┃┃┃╭━━╯┃┃╱┃┃┃╰╯┃┃╭━━┫╭╮╭╯
                                                ┃╰┻━┃╭━╮┃┃┃┃┃┃╰━━╮┃╰━╯┃╰╮╭╯┃╰━━┫┃┃╰╮
                                                ╰━━━┻╯╱╰┻╯╰╯╰┻━━━╯╰━━━╯╱╰╯╱╰━━━┻╯╰━╯
       )";
       cout << "\033[0m\n";
       Sleep(2000);
       system("cls");
        Sleep(2000);
        return 0;
    }

    hideCursor();
    while (true) {
        grid.render(T.get_current_shape(), T.get_next_shape(), consoleHandle);
        COORD scorePos = {0, static_cast<SHORT>(LENGTH + 4)};
        SetConsoleCursorPosition(consoleHandle, scorePos);
        cout <<"\t\t\t\t"<< R"(𝗦𝗖𝗢𝗥𝗘:)"<<score;
        cout << "\033[0m\n";
        
        Sleep(10);
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': T.change_dir('a'); T.move(grid.getGrid()); break;
                case 75 : T.change_dir('a'); T.move(grid.getGrid()); break;
                case 'd' : T.change_dir('d'); T.move(grid.getGrid()); break;
                case 77 : T.change_dir('d'); T.move(grid.getGrid()); break;
                case 'w' : T.rotation(grid.getGrid()); break;
                case 72 : T.rotation(grid.getGrid()); break;
                case ' ': T.change_dir(' '); T.move(grid.getGrid()); break;
                case 'q' : return 0;
                case 27 : return 0;
            }
        }
        
        fallCounter++;
        if (fallCounter >= fallDelay) {
            T.move(grid.getGrid());
            fallCounter = 0;
        }
        
        if (T.collision(grid.getGrid())) {
            grid.lockPiece(T.get_current_shape());
            grid.clearRows(score);
            
            if (grid.isGameOver()) {
                grid.render(T.get_current_shape(), T.get_next_shape(), consoleHandle);
                SetConsoleCursorPosition(consoleHandle, scorePos);
                system("cls");
                game=0;
                if(score>highscore){
                    highscore=score;
                }
        cout << "\033[1;95m"; 
        cout <<"\t\t\t\t"<< R"(
       
                                                ╭━━━┳━━━┳━╮╭━┳━━━╮╭━━━┳╮╱╱╭┳━━━┳━━━╮
                                                ┃╭━╮┃╭━╮┃┃╰╯┃┃╭━━╯┃╭━╮┃╰╮╭╯┃╭━━┫╭━╮┃
                                                ┃┃╱╰┫┃╱┃┃╭╮╭╮┃╰━━╮┃┃╱┃┣╮┃┃╭┫╰━━┫╰━╯┃
                                                ┃┃╭━┫╰━╯┃┃┃┃┃┃╭━━╯┃┃╱┃┃┃╰╯┃┃╭━━┫╭╮╭╯
                                                ┃╰┻━┃╭━╮┃┃┃┃┃┃╰━━╮┃╰━╯┃╰╮╭╯┃╰━━┫┃┃╰╮
                                                ╰━━━┻╯╱╰┻╯╰╯╰┻━━━╯╰━━━╯╱╰╯╱╰━━━┻╯╰━╯
       )";
       cout << "\033[0m\n";
       cout << "\033[1;33m"; 
       cout << R"(                              𝗙𝗜𝗡𝗔𝗟 𝗦𝗖𝗢𝗥𝗘:)"<<score;
       cout << "\033[0m\n";
      cout << "\033[1;33m"; 
      cout << R"(                               𝗛𝗜𝗚𝗛 𝗦𝗖𝗢𝗥𝗘:)"<<highscore;
      cout << "\033[0m\n";
       cout << "\033[1;93m"; 
       cout<<R"(𝐏𝐑𝐄𝐒𝐒 '𝐑' 𝐅𝐎𝐑 𝐑𝐄𝐒𝐓𝐀𝐑𝐓 )"<<endl;
       cout<<R"( 𝐏𝐑𝐄𝐒𝐒 '𝐄' 𝐅𝐎𝐑 𝐄𝐗𝐈𝐓:)";
       cout << "\033[0m\n";
       while(1)
         {
             if(kbhit())
             {
                 char d=getch();
                 if (d=='r')
                 {
                     game=1;
                     break;
                 }
                 if(d==27) exit(0);
                 if(d=='e') 
                 {
                     system("cls");
                     break;
                 }
             }
         }
       system("cls");
                break;
            }
            
            T.freeShape(T.get_current_shape());
            T.get_current_shape() = T.get_next_shape();
            T.k = T.next_k;
            T.next_shape = T.Shape();
            while (T.k == T.next_k) {
                T.freeShape(T.next_shape);
                T.next_shape = T.Shape();
            }
            if (!T.canSpawn(grid.getGrid())) {
                grid.render(T.get_current_shape(), T.get_next_shape(), consoleHandle);
                SetConsoleCursorPosition(consoleHandle, scorePos);
                system("cls");
                game=0;
        cout << "\033[1;95m"; 
        cout <<"\t\t\t\t"<< R"(
       
                                                ╭━━━┳━━━┳━╮╭━┳━━━╮╭━━━┳╮╱╱╭┳━━━┳━━━╮
                                                ┃╭━╮┃╭━╮┃┃╰╯┃┃╭━━╯┃╭━╮┃╰╮╭╯┃╭━━┫╭━╮┃
                                                ┃┃╱╰┫┃╱┃┃╭╮╭╮┃╰━━╮┃┃╱┃┣╮┃┃╭┫╰━━┫╰━╯┃
                                                ┃┃╭━┫╰━╯┃┃┃┃┃┃╭━━╯┃┃╱┃┃┃╰╯┃┃╭━━┫╭╮╭╯
                                                ┃╰┻━┃╭━╮┃┃┃┃┃┃╰━━╮┃╰━╯┃╰╮╭╯┃╰━━┫┃┃╰╮
                                                ╰━━━┻╯╱╰┻╯╰╯╰┻━━━╯╰━━━╯╱╰╯╱╰━━━┻╯╰━╯
       )";
       cout << "\033[0m\n";
       cout << "\033[1;33m"; 
       cout <<"\t\t\t\t"<< R"(                              𝗙𝗜𝗡𝗔𝗟 𝗦𝗖𝗢𝗥𝗘:)"<<score;
      cout << "\033[0m\n";
      cout << "\033[1;33m"; 
      cout <<"\t\t\t\t"<< R"(                              𝗛𝗜𝗚𝗛 𝗦𝗖𝗢𝗥𝗘:)"<<highscore;
      cout << "\033[0m\n";
       cout << "\033[1;93m"; 
       cout<<R"(𝐏𝐑𝐄𝐒𝐒 '𝐑' 𝐅𝐎𝐑 𝐑𝐄𝐒𝐓𝐀𝐑𝐓 )"<<endl;
       cout<<R"( 𝐏𝐑𝐄𝐒𝐒 '𝐄' 𝐅𝐎𝐑 𝐄𝐗𝐈𝐓:)";
       cout << "\033[0m\n";
       while(1)
         {
             if(kbhit())
             {
                 char d=getch();
                 if (d=='r')
                 {
                     game=1;
                     break;
                 }
                 if(d==27) exit(0);
                 if(d=='e') 
                 {
                     system("cls");
                     break;
                 }
             }
         }
       system("cls");         
                break;
            }
        }
    }
}
    return 0;
}