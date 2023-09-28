#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/select.h>

// Function to check if a key has been pressed
// Note: This implementation is non-blocking, thus not preventing further process execution
int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

// Function to get the pressed key
char getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void displayWelcomeMessage()
{
    system("clear");
    printf("Welcome to the TERMTIME utility!\n");
    printf("           _________________________\n");
    printf("         ,'        _____            `.\n");
    printf("       ,'       _.'_____`._           `.\n");
    printf("      :       .'.-'  12 `-.`.           \\\n");
    printf("      |      /,' 11  .   1 `.\\           :\n");
    printf("      ;     // 10    |     2 \\\\          |\n");
    printf("    ,'     ::        |        ::         |\n");
    printf("  ,'       || 9   ---O      3 ||         |\n");
    printf(" /         ::                 ;;         |\n");
    printf(":           \\\\ 8           4 //          |\n");
    printf("|            \\`. 7       5 ,'/           |\n");
    printf("|             '.`-.__6__.-'.'            |\n");
    printf(":              ((-._____.-))             ;\n");
    printf(" \\             _))       ((_            /\n");
    printf("  `.          '--'       '--'         ,'\n");
    printf("    `.______________________________,'\n");
    printf("        ,-.                          \n");
    printf("        `-'                          \n");
    printf("           O                          \n");
    printf("            o                          \n");
    printf("             .     ____________        \n");
    printf("            ,('`)./____________`-.-,|\n");
    printf("           |'-----\\\\--------------| |\n");
    printf("           |_______^______________|,|\n");
    printf("           |                      |   \n");
    printf("\n\nPress Enter to view the live clock...\n");
}

int displayClock()
{
    char e[] = "!1`2!3`1!2`1!4`2!4`!1`!4`4!4`1!3`5!4`2!4`2!35^!`!]!1^`!}!}`1!]!1}`2!]!1}!}1!}!2}!`3}!2^!^!2}`3!1}!2^!`!]!2^!`!]!31`!}!}!}!}!1}!}!3*!}!2`1*!}!}!}1!}`!1}!}`1!3^!^`!6^!^!2}!)`*!}!}!)`*!}!2`1!`!`!`1!3`!`1!`!`1!4)`*}!}!}!}!1}!}!2^!^!2}`1!=!1}`1!2`}!}`2!]!1}!(`!]!4^!^!4?!`!=!2]`1-!}!1^!`a!}!(!1]!1}!(`!]!(!1]!4`!}!}`}!}!1}!}!1^!^`!2`2*!}!3}!}!3`2*!}!}!)`*!}!2^!^!4}!)`*!}!3^!^!2]`1-`}`}`}`}!}!/`1^`}`}`}!2)`*!]`2^!2}`}!}`3}!}`3^!4}`}!2}`3^!2]`2^!2^`^!6]`2^!3^`^!16}`}!14", l[] = "8578988998>?3", f[666], *q = f, *p = e, c, r;
    time_t z;
    time(&z);
    tm *u = localtime(&z);
    while (*p)
    {
        if (*p > 47 && *p < 58)
        {
            r = *p++ - 48;
            if (*p > 47 && *p < 58)
                r = r * 10 + *p++ - 48;
            while (r--)
                *q++ = c;
        }
        else
        {
            *q++ = c = *p++ == 94 ? 48 : p[-1];
        }
    }
    c = u->tm_hour;
    sprintf(e, "%02d<%02d%c", c % 12, u->tm_min, ':' + c / 12);
    for (int s, n, o, r = 0; r < 6; r++)
    {
        for (q = e; *q; q++)
        {
            o = r * 111;
            for (n = 0; n < *q - 48; n++)
                o += l[n] - 48;
            s = l[n] - 48;
            for (n = o; n < o + s; n++)
                putchar(f[n] - 1);
        }
        putchar('\n');
    }
    return 0;
}

int main()
{
    displayWelcomeMessage();
    while (true)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == '\n')
            { // Enter key
                while (true)
                {
                    system("clear");
                    displayClock();
                    sleep(1); // Wait for 1 second
                }
            }
        }
    }
    return 0;
}
