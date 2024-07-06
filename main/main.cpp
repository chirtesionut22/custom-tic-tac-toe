#include <iostream>
#include <cstring>

using namespace std;

char choose[99999][4];
int dimension;

char get_mark(int pos)
{
    if(pos >= 100)
    {
        return choose[pos][1];
    }
    else
    {
        return choose[pos][0];
    }
}

void check()
{
    for(int i = 1; i <= dimension; i++)
    {
        bool allEqual = true;
        for(int j = 1; j < dimension; j++)
        {
            if(get_mark(i * dimension - j) != get_mark(i * dimension))
            {
                allEqual = false;
                break;
            }
        }
        if(allEqual && (get_mark(i * dimension) == 'X' || get_mark(i * dimension) == 'O'))
        {
            cout << "\n\n\n###########################\n";
            cout << "##       " << choose[i * dimension] << " HAS WON       ##\n";
            cout << "###########################\n\n";
            cout << "lines";
            exit(0);
        }
    }

    for(int i = 1; i <= dimension; i++)
    {
        bool allEqual = true;
        for(int j = 1; j < dimension; j++)
        {
            if(get_mark(i) != get_mark(j * dimension + i))
            {
                allEqual = false;
                break;
            }
        }
        if(allEqual && (get_mark(i) == 'X' || get_mark(i) == 'O'))
        {
            cout << "\n\n\n###########################\n";
            cout << "##       " << choose[i] << " HAS WON       ##\n";
            cout << "###########################\n\n";
            cout << "columns" ;
            exit(0);
        }
    }

    bool allEqual = true;
    for(int i = 1; i < dimension; i++)
    {
        if(get_mark(i * dimension + i + 1) != get_mark(1))
        {
            allEqual = false;
            break;
        }
    }
    if(allEqual && (get_mark(1) == 'X' || get_mark(1) == 'O'))
    {
        cout << "\n\n\n###########################\n";
        cout << "##       " << choose[1] << " HAS WON       ##\n";
        cout << "###########################\n\n";
        cout << "first diag";
        exit(0);
    }

    allEqual = true;
    for(int i = 1; i < dimension; i++)
    {
        if(get_mark(i * dimension - i + 1) != get_mark(dimension * (dimension - 1) + 1))
        {
            allEqual = false;
            break;
        }
    }
    if(allEqual && (get_mark(dimension) == 'X' || get_mark(dimension) == 'O'))
    {
        cout << "\n\n\n############################\n";
        cout << "##       " << choose[dimension] << " HAS WON        ##\n";
        cout << "############################\n\n";
        cout << "second diag";
        exit(0);
    }

    bool draw = true;
    for(int i=1; i<=dimension * dimension; i++)
    {
        if(get_mark(i) != 'X' && get_mark(i) != 'O')
            draw = false;
    }
    if(draw)
    {
        cout << "\n\n\n###########################\n";
        cout << "##          DRAW         ##\n";
        cout << "###########################\n\n";
        exit(0);
    }
}


void int_to_char(int num, char result[4])
{
    int temp = num;
    int len = 0;
    while(temp > 0)
    {
        len++;
        temp /= 10;
    }
    for(int i=len - 1; i>=0; i--)
    {
        result[i] = num % 10 + '0';
        num /= 10;
    }
    result[len] = '\0';
}

int main()
{
    int position;
    char turn[2] = {'X', 'O'};
    int switchh = 0;
    cout <<  "ENTER GRID DIMENSION (1 - 31): ";
    do{
        cin >> dimension;
        if(dimension < 1 || dimension > 31)
        {
            cout << "Invalid dimension! Try again!\n";
        }

    }while(dimension < 1 || dimension > 31);
    for(int i = 1; i <= dimension * dimension; i++)
    {
        char result[10];
        int_to_char(i, result);
        strcpy(choose[i], result);
    }

    bool play = true;
    while(play)
    {
        for(int i = 0; i <= dimension * 4; i++)
        {
            for(int j = 0; j <= dimension * 4; j++)
            {
                int idx = dimension * (i / 4) + j / 4 + 1;
                if(i % 4 == 0)
                    cout << '-';
                else if(j % 4 == 0)
                    cout << "|";
                else if(i % 4 == 2 && j % 4 == 2)
                    cout << choose[idx];
                else if(i % 4 == 1 || i % 4 == 3 || (i % 4 == 2 && idx < 100 && (idx < 10 || j % 4 == 1)))/// 1-right allign 3-left allign
                    cout << ' ';
            }
            if(i == dimension * 2)
            {
                cout << "    " << turn[switchh] << " TURN";
            }
            cout << '\n';
        }
        cout << "CHOOSE YOUR FREE POSITION (1-" << dimension * dimension << ") : ";
        cin >> position;
        if(position < 1 || position > dimension * dimension) {
            cout << "Invalid position. Try again." << endl;
            continue;
        }
        if(strcmp(choose[position], "X") == 0 || strcmp(choose[position], "O") == 0)
        {
            cout << "Position already taken. Try again." << endl;
            continue;
        }
        choose[position][0] = turn[switchh];
        if(position >=10 && position < 100) choose[position][1] = ' ';
        if(position >=100)
        {
            choose[position][0] = ' ';
            choose[position][1] = turn[switchh];
            choose[position][2] = ' ';
        }
        check();
        switchh = 1 - switchh;
    }
    return 0;
}
