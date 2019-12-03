#include<bits/stdc++.h>
using namespace std;

const int COUNT_BITS = 22;

vector < int > accumulater(COUNT_BITS);
vector < int > register1(COUNT_BITS);
/*
vector < int > getAddCode(vector < int > operand)
{
    vector < int > result;
    result.resize(COUNT_BITS);

    for(int i = 0; i < COUNT_BITS; i++)
    {
        if(operand[i] == 0)
        {
            result[i] = 1;
        }else
        {
            result[i] = 0;
        }
    }

    result[0]++;

    for(int i = 0; i < COUNT_BITS; i++)
    {
        if(result[i] == 2)
        {
            result[i] = 0;

            if(i + 1 < COUNT_BITS)
            {
                result[i+1]++;
            }
        }
    }

    cout << "\n\n";

    for(int i = COUNT_BITS; i; i--)
    {
        cout << operand[i-1];
    }

    cout << " --> ";

    for(int i = COUNT_BITS; i; i--)
    {
        cout << result[i-1];
    }

    cout << "\n\n";

    return result;
}
*/
vector < int > getValue(int operand)
{
    vector < int > result;
    result.resize(COUNT_BITS);

    for(int i = 0; i < COUNT_BITS-1; i++)
    {
        if(operand & (1 << i))
        {
            result[i] = 1;
        }
    }

    if(operand < 0)
    {
        result[COUNT_BITS-1] = 1;
    }

    return result;
}

void write(string operation, vector < int > & operandsBits, bool beforeOperation, int operationNumber)
{
    if(beforeOperation)
    {
        cout << "-----------------------\n\n";
    }

    cout << "Ins = " << operation << " | ";

    for(int i = COUNT_BITS; i;  i--)
    {
        cout << operandsBits[i-1];
    }

    cout << "\n";

    cout << "PC = " << operationNumber << ", TC = " << 2 - (int)(beforeOperation) << ", PS == ";
    cout << (accumulater[COUNT_BITS-1] == 1 ? "-" : "+") << "\n";
    cout << "Accumulater = ";

    for(int i = COUNT_BITS; i; i--)
    {
        cout << accumulater[i-1];
    }

    cout << "\n\n";
}

void sub(int operand, int operationNumber)
{
    operand *= -1;

    vector < int > operandsBits = getValue(operand);

    write("sub", operandsBits, 1, operationNumber);

    int movingOne = 0;

    for(int i = 0; i < COUNT_BITS; i++)
    {
        accumulater[i] += movingOne + operandsBits[i];

        movingOne = accumulater[i] / 2;
        accumulater[i] %= 2;
    }

    write("sub", operandsBits, 0, operationNumber);
}

void mov(int operand, int operationNumber)
{
    vector < int > operandsBits = getValue(operand);

    write("mov", operandsBits, 1, operationNumber);

    accumulater = operandsBits;

    write("mov", operandsBits, 0, operationNumber);
}

void process(string textFile)
{
    ifstream in;
    in.open(textFile);

    string operationName;
    int operand;
    int operationNumber = 0;

    while(in >> operationName)
    {
        operationNumber ++;

        in >> operand;

        if(operationName == "mov")
        {
            mov(operand, operationNumber);
        }else
        {
            sub(operand, operationNumber);
        }
    }

    return;
}

main()
{
    process("input.txt");
}
