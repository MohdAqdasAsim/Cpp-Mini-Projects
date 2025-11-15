#include <iostream>
#include <cctype>
#include <termios.h>
#include <unistd.h>

std::string asciiTitle = R"(
█████▄   ▄▄▄   ▄▄▄▄ ▄▄ ▄▄   █████▄  ▄▄▄  ▄▄▄▄  ▄▄▄▄▄ ▄▄▄▄    ▄█████  ▄▄▄▄ ▄▄  ▄▄▄▄  ▄▄▄▄  ▄▄▄  ▄▄▄▄  
██▄▄██▄ ██▀██ ██▀▀▀ ██▄█▀   ██▄▄█▀ ██▀██ ██▄█▀ ██▄▄  ██▄█▄   ▀▀▀▄▄▄ ██▀▀▀ ██ ███▄▄ ███▄▄ ██▀██ ██▄█▄ 
██   ██ ▀███▀ ▀████ ██ ██   ██     ██▀██ ██    ██▄▄▄ ██ ██   █████▀ ▀████ ██ ▄▄██▀ ▄▄██▀ ▀███▀ ██ ██ 
)";

std::string asciiArtAll = R"(
⠀⠀⠀⠀⠀⣠⡴⠖⠒⠲⠶⢤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡴⠖⠒⢶⣄⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢀⡾⠁⠀⣀⠔⠁⠀⠀⠈⠙⠷⣤⠦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠋⠀⠀⠀⢀⡿⠀⠀⠀⠀⠀⠀⠀
⣠⠞⠛⠛⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⠈⢿⡀⢠⡶⠒⠳⠶⣄⠀⠀⠀⠀⠀⣴⠟⠁⠀⠀⠀⣰⠏⠀⢀⣤⣤⣄⡀⠀⠀
⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠛⠛⠃⠸⡇⠈⣇⠸⡇⠀⠀⠀⠘⣇⠀⠀⣠⡾⠁⠀⠀⠀⢀⣾⣣⡴⠚⠉⠀⠀⠈⠹⡆⠀
⣹⡷⠤⠤⠤⠄⠀⠀⠀⠀⢠⣤⡤⠶⠖⠛⠀⣿⠀⣿⠀⢻⡄⠀⠀⠀⢻⣠⡾⠋⠀⠀⠀⠀⣠⡾⠋⠁⠀⠀⠀⠀⢀⣠⡾⠃⠀
⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡤⠖⠋⢀⣿⣠⠏⠀⠀⣿⠀⠀⠀⠘⠉⠀⠀⠀⠀⠀⡰⠋⠀⠀⠀⠀⠀⣠⠶⠋⠁⠀⠀⠀
⢿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠁⠀⠀⠠⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠁⠀⠀⠀⢀⣴⡿⠥⠶⠖⠛⠛⢶⡄
⠀⠉⢿⡋⠉⠉⠁⠀⠀⠀⠀⠀⢀⣠⠾⠋⠀⠀⠀⠀⢀⣰⡇⠀⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⢀⣠⠼⠃
⠀⠀⠈⠛⠶⠦⠤⠤⠤⠶⠶⠛⠋⠁⠀⠀⠀⠀⠀⠀⣿⠉⣇⠀⡴⠟⠁⣠⡾⠃⠀⠀⠀⠀⠀⠈⠀⠀⠀⣀⣤⠶⠛⠉⠀⠀⠀
⠀⠀⠀⠀⢀⣠⣤⣀⣠⣤⠶⠶⠒⠶⠶⣤⣀⠀⠀⠀⢻⡄⠹⣦⠀⠶⠛⢁⣠⡴⠀⠀⠀⠀⠀⠀⣠⡶⠛⠉⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢀⡴⠋⣠⠞⠋⠁⠀⠀⠀⠀⠙⣄⠀⠙⢷⡀⠀⠀⠻⣄⠈⢷⣄⠈⠉⠁⠀⠀⠀⢀⣠⡴⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⢀⡾⠁⣴⠋⠰⣤⣄⡀⠀⠀⠀⠀⠈⠳⢤⣼⣇⣀⣀⠀⠉⠳⢤⣭⡿⠒⠶⠶⠒⠚⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⢸⠃⢰⠇⠰⢦⣄⡈⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠛⠛⠓⠲⢦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠸⣧⣿⠀⠻⣤⡈⠛⠳⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠈⠹⣆⠀⠈⠛⠂⠀⠀⠀⠀⠀⠀⠈⠐⠒⠒⠶⣶⣶⠶⠤⠤⣤⣠⡼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠹⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠳⢦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠈⠻⣦⣀⠀⠀⠀⠀⠐⠲⠤⣤⣀⡀⠀⠀⠀⠀⠀⠉⢳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠶⠤⠤⠤⠶⠞⠋⠉⠙⠳⢦⣄⡀⠀⠀⠀⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠳⠦⠾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
)";

std::string asciiArts[] = {
    R"(
⠀⠀⠀⠀⠀⣠⡴⠖⠒⠲⠶⢤⣄⡀⠀⠀⠀⠀
⠀⠀⠀⢀⡾⠁⠀⣀⠔⠁⠀⠀⠈⠙⠷⣤⠦⣤⡀⠀⠀
⣠⠞⠛⠛⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⠈⢿⡀
⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠛⠛⠃⠸⡇⠈⣇
⣹⡷⠤⠤⠤⠄⠀⠀⠀⠀⢠⣤⡤⠶⠖⠛⠀⣿⠀⣿⠀
⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡤⠖⠋⢀⣿⣠⠏⠀
⢿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠁⠀
⠀⠉⢿⡋⠉⠉⠁⠀⠀⠀⠀⠀⢀⣠⠾⠋⠀⠀⠀
⠀⠀⠈⠛⠶⠦⠤⠤⠤⠶⠶⠛⠋⠁⠀
)",
    R"(
                  ⣠⡴⠖⠒⢶⣄⠀⠀⠀⠀⠀⠀⠀
                ⢀⡼⠋⠀⠀⠀⢀⡿⠀⠀⠀⠀⠀⠀⠀
    ⢠⡶⠒⠳⠶⣄⠀⠀⠀⠀⠀⣴⠟⠁⠀⠀⠀⣰⠏⠀⢀⣤⣤⣄⡀⠀⠀
    ⠸⡇⠀⠀⠀⠘⣇⠀⠀⣠⡾⠁⠀⠀⠀⢀⣾⣣⡴⠚⠉⠀⠀⠈⠹⡆⠀
    ⢻⡄⠀⠀⠀⢻⣠⡾⠋⠀⠀⠀⠀⣠⡾⠋⠁⠀⠀⠀⠀⢀⣠⡾⠃⠀
    ⣿⠀⠀⠀⠘⠉⠀⠀⠀⠀⠀⡰⠋⠀⠀⠀⠀⠀⣠⠶⠋⠁⠀⠀⠀
  ⠠⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠁⠀⠀⠀⢀⣴⡿⠥⠶⠖⠛⠛⢶⡄
⢀⣰⡇⠀⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⢀⣠⠼⠃
⣿⠉⣇⠀⡴⠟⠁⣠⡾⠃⠀⠀⠀⠀⠀⠈⠀⠀⠀⣀⣤⠶⠛⠉⠀⠀⠀
⠀⢻⡄⠹⣦⠀⠶⠛⢁⣠⡴⠀⠀⠀⠀⠀⠀⣠⡶⠛⠉⠀⠀⠀⠀⠀⠀⠀
  ⠻⣄⠈⢷⣄⠈⠉⠁⠀⠀⠀⢀⣠⡴⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠉⠳⢤⣭⡿⠒⠶⠶⠒⠚⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
)",
    R"(
⠀⠀⠀⠀⢀⣠⣤⣀⣠⣤⠶⠶⠒⠶⠶⣤⣀⠀
⠀⠀⢀⡴⠋⣠⠞⠋⠁⠀⠀⠀⠀⠙⣄⠀⠙⢷⡀
⠀⢀⡾⠁⣴⠋⠰⣤⣄⡀⠀⠀⠀⠀⠈⠳⢤⣼⣇⣀⣀
⠀⢸⠃⢰⠇⠰⢦⣄⡈⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠛⠛⠓⠲⢦⣄⠀⠀
⠀⠸⣧⣿⠀⠻⣤⡈⠛⠳⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡆⠀⠀
⠀⠀⠈⠹⣆⠀⠈⠛⠂⠀⠀⠀⠀⠀⠀⠈⠐⠒⠒⠶⣶⣶⠶⠤⠤⣤⣠⡼⠃⠀⠀⠀
⠀⠀⠀⠀⠹⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠳⢦⣀⠀⠀⠀
⠀⠀⠀⠀⠀⠈⠻⣦⣀⠀⠀⠀⠀⠐⠲⠤⣤⣀⡀⠀⠀⠀⠀⠀⠉⢳⡄
⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠶⠤⠤⠤⠶⠞⠋⠉⠙⠳⢦⣄⡀⠀⠀⠀⡷
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠳⠦⠾⠃
)"};

const int KEY_LEFT = -1;
const int KEY_RIGHT = -2;
const int KEY_UP = -3;
const int KEY_DOWN = -4;

// Read one key press (normal or arrow)
int getch_all()
{
    char c = 0;
    termios old{}, raw{};

    tcgetattr(STDIN_FILENO, &old);
    raw = old;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    read(STDIN_FILENO, &c, 1);

    // Check for escape sequence (arrow keys)
    if (c == '\x1b')
    {
        char c1 = 0, c2 = 0;

        if (read(STDIN_FILENO, &c1, 1) == 0)
            return 0;
        if (read(STDIN_FILENO, &c2, 1) == 0)
            return 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &old);

        if (c1 == '[')
        {
            switch (c2)
            {
            case 'A':
                return KEY_UP;
            case 'B':
                return KEY_DOWN;
            case 'C':
                return KEY_RIGHT;
            case 'D':
                return KEY_LEFT;
            }
        }
        return 0;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return c;
}

void showHelp()
{
    system("clear");

    std::cout << "================= HELP MENU =================\n";
    std::cout << "        Welcome to the Legendary Guide!\n";
    std::cout << "=============================================\n\n";

    std::cout << " HOW TO PLAY:\n";
    std::cout << " -------------------------------------------\n";
    std::cout << " • Use the UP and DOWN arrow keys to\n";
    std::cout << "   switch between Rock, Paper, and Scissors.\n\n";

    std::cout << " • Press ENTER to lock in your choice.\n\n";

    std::cout << " • Rock beats Scissors\n";
    std::cout << " • Scissors beats Paper\n";
    std::cout << " • Paper beats Rock\n\n";

    std::cout << " -------------------------------------------\n";
    std::cout << " TIP: Trust your instincts, warrior.\n";
    std::cout << " -------------------------------------------\n\n";

    std::cout << " Press any key to return to the main menu...\n";

    getch_all();
}

void startGame()
{
    int userChoice = 0;
    std::string choices[3] = {"rock", "paper", "scissors"};

    while (true)
    {
        system("clear");

        std::cout << "Use ↑ ↓ to choose, press Enter to confirm.\n\n";
        std::cout << asciiArts[userChoice] << "\n\n";

        for (int i = 0; i < 3; ++i)
        {
            choices[i][0] = static_cast<char>(toupper(choices[i][0]));
            std::cout << (userChoice == i ? "> " : "  ") << choices[i] << "\n";
        }

        int key = getch_all();

        if (key == KEY_UP || key == KEY_LEFT)
            userChoice = (userChoice + 2) % 3;
        else if (key == KEY_DOWN || key == KEY_RIGHT)
            userChoice = (userChoice + 1) % 3;
        else if (key == '\n')
        {
            system("clear");
            srand(time(NULL));

            int computerChoice = rand() % 3;

            std::cout << "Your mighty choice: " << choices[userChoice] << "!\n";
            std::cout << asciiArts[userChoice] << "\n\n";

            std::cout << "The challenger enters the arena with: " << choices[computerChoice] << "!\n";
            std::cout << asciiArts[computerChoice] << "\n\n";

            // determine the winner
            if (userChoice == computerChoice)
            {
                std::cout << "It's a draw!\n\n";
            }
            else if (
                (userChoice == 0 && computerChoice == 2) || // Rock beats Scissors
                (userChoice == 1 && computerChoice == 0) || // Paper beats Rock
                (userChoice == 2 && computerChoice == 1)    // Scissors beats Paper
            )
            {
                std::cout << "Nice! You actually won. Didn’t expect that.\n\n";
            }
            else
            {
                std::cout << "Yikes. You lost. Maybe try next time?\n\n";
            }

            system("sleep 3");
            system("clear");

            // Flush any leftover input so the selector doesn't immediately act
            tcflush(STDIN_FILENO, TCIFLUSH);

            int againChoice = 0;
            while (true)
            {
                system("clear");
                std::cout << "Use ← → (or ↑ ↓) to choose, Enter to confirm.\n";
                std::cout << asciiArtAll << "\n\n";
                std::cout << "=============================================\n";
                std::cout << "  Rematch? Or are we packing up the gloves?\n";
                std::cout << "=============================================\n\n";
                std::cout << (againChoice == 0 ? "> " : "  ") << "Yes\n";
                std::cout << (againChoice == 1 ? "> " : "  ") << "No\n\n";

                int k = getch_all();
                if (k == KEY_LEFT || k == KEY_UP)
                    againChoice = (againChoice + 1) % 2;
                else if (k == KEY_RIGHT || k == KEY_DOWN)
                    againChoice = (againChoice + 1) % 2;
                else if (k == '\n' || k == '\r' || k == 10 || k == 13)
                {
                    if (againChoice == 0)
                    {
                        break;
                    }
                    else
                    {
                        return;
                    }
                }
            }
        }
    }
}

int main()
{
    while (true)
    {
        system("clear");

        std::cout << asciiTitle << "\n";
        std::cout << "=============================================\n";
        std::cout << "     Welcome to the Ultimate RPS Arena!\n";
        std::cout << "    Sharpen your hands... destiny awaits. \n";
        std::cout << "=============================================\n\n";

        std::cout << "   [S] Start Game  →  Begin your journey\n";
        std::cout << "   [H] Help        →  How to play\n";
        std::cout << "   [Q] Quit        →  Escape the arena\n\n";

        int c = getch_all();
        c = tolower(c);

        switch (c)
        {
        case 'h':
            showHelp();
            break;
        case 'q':
            system("clear");
            std::cout << "Exiting the arena… see you again, challenger.\n";
            return 0;
        case 's':
        default:
            startGame();
            break;
        }
    }

    return 0;
}
