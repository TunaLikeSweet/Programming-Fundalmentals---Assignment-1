#include "study_in_pink1.h"
bool readFile(
    const string &filename,
    int &HP1,
    int &HP2,
    int &EXP1,
    int &EXP2,
    int &M1,
    int &M2,
    int &E1,
    int &E2,
    int &E3)
{
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open())
    {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    }
    else
    {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Macros
#define ceil(double) ceil(float(double))
// Function
int nearestSquare(int &n)
{
    float m = round(sqrt(n));
    return m * m;
}

// Set limit for stats: HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3
int limit_HP(int &HP) { return min(max(0, HP), 666); }
int limit_EXP(int &EXP) { return min(max(0, EXP), 600); }
int limit_M(int &M) { return min(max(0, M), 3000); }

// Sum of digits - Task 3
int sumDigits(int &num)
{
    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    if (sum >= 10)
        return sumDigits(sum);
    else
        return sum;
}

// Start:
// Task 1
int firstMeet(int &exp1, int &exp2, int e1)
{
    // TODO: Complete this function
    if (e1 < 0 || e1 > 99)
        return -99;
    else
    {
        exp1 = limit_EXP(exp1);
        exp2 = limit_EXP(exp2);
        int D;
        if (e1 >= 0 && e1 <= 3) // Case 1
        {
            if (e1 == 0)
                exp2 += 29;
            if (e1 == 1)
                exp2 += 45;
            if (e1 == 2)
                exp2 += 75;
            if (e1 == 3)
                exp2 += 29 + 45 + 75;
            D = e1 * 3 + exp1 * 7;
            if (D % 2 == 0)
                exp1 = ceil(exp1 + D / 200.0);
            else
                exp1 = ceil(exp1 - D / 100.0);
        }

        else if (e1 >= 4 && e1 <= 99) // Case 2
        {
            if (e1 >= 4 && e1 <= 19)
                exp2 = ceil(exp2 + e1 / 4.0 + 19);
            if (e1 >= 20 && e1 <= 49)
                exp2 = ceil(exp2 + e1 / 9.0 + 21);
            if (e1 >= 50 && e1 <= 65)
                exp2 = ceil(exp2 + e1 / 16.0 + 17);
            if (e1 >= 66 && e1 <= 79)
            {
                exp2 = ceil(exp2 + e1 / 4.0 + 19);
                if (exp2 > 200)
                    exp2 = ceil(exp2 + e1 / 9.0 + 21);
            }
            if (e1 >= 80 && e1 <= 99)
            {
                exp2 = ceil(exp2 + e1 / 4.0 + 19);
                exp2 = ceil(exp2 + e1 / 9.0 + 21);
                if (exp2 > 400)
                {
                    exp2 = ceil(exp2 + e1 / 16.0 + 17);
                    exp2 = ceil(exp2 * 1.15);
                }
            }
            exp1 = limit_EXP(exp1);
            exp2 = limit_EXP(exp2);
            exp1 -= e1;
        }
        exp1 = limit_EXP(exp1);
        exp2 = limit_EXP(exp2);
    }
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int &HP1, int &EXP1, int &M1, int E2)
{
    // TODO: Complete this function
    // Declared variables
    int P1, P2, P3;
    int S1 = nearestSquare(EXP1);
    // Set limit for E2
    if (E2 < 0 || E2 > 99)
        return -99;
    else
    {
        HP1 = limit_HP(HP1);
        EXP1 = limit_EXP(EXP1);
        M1 = limit_M(M1);
        const int originalM1 = M1;
        // First way
        (EXP1 >= S1) ? P1 = 100 : P1 = 100.0 * (EXP1 / S1 + 80.0) / 123;
        // Second way
        if (E2 % 2 == 1 && M1 > 0)
        {
            while (M1 >= 0.5 * originalM1)
            {
                HP1 = limit_HP(HP1);
                EXP1 = limit_EXP(EXP1);
                M1 = limit_M(M1);
                if (HP1 < 200)
                {
                    HP1 = ceil(HP1 * 1.3);
                    M1 -= 150;
                    HP1 = limit_HP(HP1);
                    M1 = limit_M(M1);
                    if (M1 < 0.5 * originalM1)
                        break;
                }
                else
                {
                    HP1 = ceil(HP1 * 1.1);
                    M1 -= 70;
                    HP1 = limit_HP(HP1);
                    M1 = limit_M(M1);
                    if (M1 < 0.5 * originalM1)
                        break;
                }
                if (EXP1 < 400)
                {
                    M1 -= 200;
                    EXP1 = ceil(EXP1 * 1.13);
                    EXP1 = limit_EXP(EXP1);
                    M1 = limit_M(M1);
                    EXP1 = limit_EXP(EXP1);
                    if (M1 < 0.5 * originalM1)
                        break;
                }
                else
                {
                    M1 -= 120;
                    EXP1 = ceil(EXP1 * 1.13);
                    EXP1 = limit_EXP(EXP1);
                    M1 = limit_M(M1);
                    EXP1 = limit_EXP(EXP1);
                    if (M1 < 0.5 * originalM1)
                        break;
                }
                if (EXP1 < 300)
                {
                    M1 -= 100;
                    EXP1 = ceil(EXP1 * 0.9);
                    EXP1 = limit_EXP(EXP1);
                    M1 = limit_M(M1);
                    if (M1 < 0.5 * originalM1)
                        break;
                }
                else
                {
                    M1 -= 120;
                    EXP1 = ceil(EXP1 * 0.9);
                    EXP1 = limit_EXP(EXP1);
                    M1 = limit_M(M1);
                    if (M1 < 0.5 * originalM1)
                        break;
                }
            }
        }
        else if (E2 % 2 == 0)
        {
            HP1 = limit_HP(HP1);
            EXP1 = limit_EXP(EXP1);
            M1 = limit_M(M1);
            int t = 1;
            while (M1 > 0 && t == 1)
            {
                t--;
                HP1 = limit_HP(HP1);
                EXP1 = limit_EXP(EXP1);
                M1 = limit_M(M1);
                if (HP1 < 200)
                {
                    if (M1 <= 0)
                    {
                        M1 = limit_M(M1);
                        break;
                    }
                    HP1 = ceil(HP1 * 1.3);
                    M1 -= 150;
                    HP1 = limit_HP(HP1);
                }
                else
                {
                    if (M1 <= 0)
                    {
                        M1 = limit_M(M1);
                        break;
                    }
                    HP1 = ceil(HP1 * 1.1);
                    M1 -= 70;
                    HP1 = limit_HP(HP1);
                }
                if (EXP1 < 400)
                {
                    if (M1 <= 0)
                    {
                        M1 = limit_M(M1);
                        break;
                    }
                    M1 -= 200;
                    EXP1 = ceil(EXP1 * 1.13);
                    EXP1 = limit_EXP(EXP1);
                }
                else
                {
                    if (M1 <= 0)
                    {
                        M1 = limit_M(M1);
                        break;
                    }
                    M1 -= 120;
                    EXP1 = ceil(EXP1 * 1.13);
                    EXP1 = limit_EXP(EXP1);
                }
                if (EXP1 < 300)
                {
                    if (M1 <= 0)
                    {
                        M1 = limit_M(M1);
                        break;
                    }
                    M1 -= 100;
                    EXP1 = ceil(EXP1 * 0.9);
                    EXP1 = limit_EXP(EXP1);
                }
                else
                {
                    if (M1 <= 0)
                    {
                        M1 = limit_M(M1);
                        break;
                    }
                    M1 -= 120;
                    EXP1 = ceil(EXP1 * 0.9);
                    EXP1 = limit_EXP(EXP1);
                }
            }
        }
        EXP1 = ceil(EXP1 * 1.17);
        HP1 = ceil(HP1 * 0.83);
        EXP1 = limit_EXP(EXP1);
        HP1 = limit_HP(HP1);
        int S2 = nearestSquare(EXP1);
        (EXP1 >= S2) ? P2 = 100 : P2 = 100.0 * (EXP1 / S2 + 80.0) / 123;
        // Debug may hom met qua :(
        // Third way
        HP1 = limit_HP(HP1);
        EXP1 = limit_EXP(EXP1);
        M1 = limit_M(M1);
        int P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
        (E2 <= 9 && E2 >= 0) ? P3 = P[E2] : P3 = P[(E2 / 10 + E2 % 10) % 10];
        int Average = (P1 + P2 + P3) / 3.0;
        if (P1 == 100 && P2 == 100 && P3 == 100)
        {
            EXP1 = ceil(EXP1 * 0.75);
        }
        else if (Average < 50)
        {
            HP1 = ceil(HP1 * 0.85);
            EXP1 = ceil(EXP1 * 1.15);
        }
        else
        {
            HP1 = ceil(HP1 * 0.9);
            EXP1 = ceil(EXP1 * 1.2);
        }
        HP1 = limit_HP(HP1);
        EXP1 = limit_EXP(EXP1);
    }
    return HP1 + EXP1 + M1;
}
// Task 3
int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    // TODO: Complete this function
    int count_x = 0;
    int count_y = 0;
    int a = 0, b = 0, c = 0, d = 0; // left top, left bottom, right top, right bottom
    int matrix[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrix[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            if (matrix[i][j] > 2 * E3)
                count_x++;
            if (matrix[i][j] < (-E3))
                count_y++;
        }
    }
    int x = sumDigits(count_x);
    int y = sumDigits(count_y);
    int taxiPoint = matrix[x][y];
    int i = x, j = y;
    while (i < 10 && j >= 0)
    {
        a = max(a, matrix[i][j]);
        i++;
        j--;
    }
    i = x, j = y;
    while (i >= 0 && j < 10)
    {
        b = max(b, matrix[i][j]);
        i--;
        j++;
    }
    i = x, j = y;
    while (i < 10 && j < 10)
    {
        c = max(c, matrix[i][j]);
        i++;
        j++;
    }
    i = x, j = y;
    while (i >= 0 && j >= 0)
    {
        d = max(d, matrix[i][j]);
        i--;
        j--;
    }
    int detectivePoint = max(max(a, b), max(c, d));
    if (E3 < 0 || E3 > 99)
    {
        return -99;
    }
    else
    {
        limit_EXP(EXP1);
        limit_EXP(EXP2);
        limit_HP(HP1);
        limit_HP(HP2);
        if (detectivePoint >= abs(taxiPoint))
        {
            HP1 = ceil(HP1 * 1.1);
            HP2 = ceil(HP2 * 1.1);
            EXP1 = ceil(EXP1 * 1.12);
            EXP2 = ceil(EXP2 * 1.12);
        }
        else
        {
            HP1 = ceil(HP1 * 0.9);
            HP2 = ceil(HP2 * 0.9);
            EXP1 = ceil(EXP1 * 0.88);
            EXP2 = ceil(EXP2 * 0.88);
        }
        EXP1 = limit_EXP(EXP1);
        EXP2 = limit_EXP(EXP2);
        HP1 = limit_HP(HP1);
        HP2 = limit_HP(HP2);
    }
    return (abs(taxiPoint) > detectivePoint) ? taxiPoint : detectivePoint;
}
// Task 4
int checkPassword(const char *s, const char *email)
{
    // TODO: Complete this function
    char se[101];
    int i = 0;
    while (*email != '@')
    {
        se[i++] = *email++;
    }
    se[i] = '\0';

    int length = strlen(s);
    if (length < 8)
        return -1;
    if (length > 20)
        return -2;
    if (strstr(s, se))
    {
        string str(s);
        return -(300 + str.find(se));
    }
    for (int i = 0; i < length - 1; i++)
    {
        if (i < length - 2 && s[i] == s[i + 1] && s[i] == s[i + 2])
            return -(400 + i);
    }
    bool hasSpecial = false;
    char special[] = "!@#$%";
    for (int i = 0; i < length; i++)
    {
        if (strchr(special, s[i]) != NULL)
        {
            hasSpecial = true;
            break;
        }
    }
    if (!hasSpecial)
        return -5;
    bool isNormal = false;
    for (int i = 0; i < length; i++)
    {
        if (s[i] >= 48 && s[i] <= 57 || s[i] >= 65 && s[i] <= 90 || s[i] >= 97 && s[i] <= 122)
        {
            isNormal = true;
            break;
        }
    }
    if (!isNormal)
    {
        return -10;
    }
    char another[] = {'&', '*', '(', ')', '-', '+', '=', '_', '{', '}', '[', ']', ':', ';', '"', '\'', '<', '>', ',', '.', '?', '/', '|', '\\', '~', '`', '^', '\0'};
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            if (another[j] == s[i])
                return i;
        }
    }
    return -10;
}

struct PasswordInfo
{
    char password[100];
    int count;
    int length;
    int originalIndex;
};
#define num num_of_diff_pwd
// Task 5
int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    PasswordInfo *pwd = new PasswordInfo[30];
    int num_of_diff_pwd = 0;
    for (int i = 0; i < num_pwds; i++)
    {
        bool founded = false;
        for (int j = 0; j < num; j++)
        {
            if (strcmp(pwd[j].password, arr_pwds[i]) == 0)
            {
                pwd[j].count++;
                founded = true;
                break;
            }
        }
        if (!founded)
        {
            strcpy(pwd[num].password, arr_pwds[i]);
            pwd[num].count = 1;
            pwd[num].length = strlen(arr_pwds[i]);
            pwd[num].originalIndex = i;
            num++;
        }
    }
    int max_count = 0, max_length = 0, index = -1; // If not found any correct pwd, index = -1 -> return -1
    for (int i = 0; i < num; i++)
    {
        if (pwd[i].count > max_count || (pwd[i].count == max_count && pwd[i].length > max_length))
        {
            max_count = pwd[i].count;
            max_length = pwd[i].length;
            index = pwd[i].originalIndex;
        }
    }
    delete[] pwd;
    return index;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////