/*
Noah Yacoub
11/7/2021
ITCS 2530
Week 03 Programming Assignment

Assignment Description:
Write a Item Shipping Calculator program that does the following:
    
    Prompt and retrieve the following input from the user (through the console):
        - Item name
        - Is the item fragile (add in $2.00 if the item is fragile)
        - The order total (without shipping)
        - The destination to which the item will be shipped (USA, Canada, Australia)

    Accurately reverse engineer given example .exe file
*/

#include <iostream>
//adds format manipulators
#include <iomanip>
//includes to_string()
#include <string>
//allows for transforming strings to uppercase easily
#include <algorithm>
//allows creation of .txt output file
#include <fstream>

using namespace std;

int main()
{
    //constant variables
    double finalprice = 0.00;
    double fragiletax = 2.00;
    double addoncost = 0.00;
    double linelength = 50; //want to use int but it gave me green underlines and told me to cast to wider type to avoid overflow, tried float and had same issue, tried double it fixed the issue.
    char char1 = '.';
    char char2 = '-';
    char char3 = ':';
    char char4 = '$';
    string title = "ITCS 2530 - Programming Assignment for week #3";
    ofstream file1 ("Orders.txt");

    //dont know if this was required but wanted to challenge myself - multidimensional-array for holding table of values for shipping
    double shippingval [4][3]; //table is 4x3
    //usa column 0
    shippingval[0][0] = 6.00;
    shippingval[1][0] = 9.00;
    shippingval[2][0] = 12.00;
    shippingval[3][0] = 0.00;
    //can column 1
    shippingval[0][1] = 8.00;
    shippingval[1][1] = 12.00;
    shippingval[2][1] = 15.00;
    shippingval[3][1] = 0.00;
    //aus column 2
    shippingval[0][2] = 10.00;
    shippingval[1][2] = 14.00;
    shippingval[2][2] = 17.00;
    shippingval[3][2] = 0.00;

    //multidimensional array to have a total of 6 different changable numbers for the shipping calculator
    /*
    in this case our constants looks like this as a visual. note: zeros will be ignored
    [0,50]
    [50.01,100.00]
    [100.01,150.00]
    [150.00, 0]
    */
    double ordertotalprice[4][2];
    ordertotalprice[0][1] = 50;
    ordertotalprice[1][0] = 50.01;
    ordertotalprice[1][1] = 100.00;
    ordertotalprice[2][0] = 100.01;
    ordertotalprice[2][1] = 150.00;
    ordertotalprice[3][0] = 150.00;

    //undefined variables
    char yorn;
    double preshipprice;
    string itemname, receivingcountry;

    //line one (stream manipulator dependant)
    cout << setfill(char1) << left << setw(linelength - 1);
    cout << char1 << '\n';
    file1 << setfill(char1) << left << setw(linelength - 1);
    file1 << char1 << '\n';
    //line two
    cout << title;
    file1 << title;
    //line three (stream manipulator dependant)
    cout << setfill(char1) << left << setw(linelength - 1) << endl;
    cout << char1 << '\n' << '\n';
    file1 << setfill(char1) << left << setw(linelength - 1) << endl;
    file1 << char1 << '\n' << '\n';

    //1      get itemname written with stream mani and constant variable dependancies
    cout << setfill(char1) << left << setw(linelength - 1) << "What is your item's name?(No spaces please)" << right << char3;
    file1 << setfill(char1) << left << setw(linelength - 1) << "What is your item's name?(No spaces please)" << right << char3;
    cin >> itemname;
    file1 << itemname << '\n';
    //2      get fragile status written with stream mani and constant variable dependancies
    cout << setfill(char1) << left << setw(linelength - 1) << "Does your package need fragile care?(y/n)" << right << char3;
    file1 << setfill(char1) << left << setw(linelength - 1) << "Does your package need fragile care?(y/n)" << right << char3;
    cin >> yorn;
    file1 << yorn << '\n';
    //Y or N is converted to y or n
    yorn = tolower(yorn);

    //check fragile input add potentially add +2 to unset price
    if (yorn == 'y')
    {
        addoncost = fragiletax;
    }
    else if (yorn == 'n')
    {
        addoncost = 0.00;
    }
    else
    {
        cout << "In valid response! Please only answer with y or n! Exiting...";
        file1 << "In valid response! Please only answer with y or n! Exiting...";
        return 0;
    }

    //3      get itemprice written with stream mani and constant variable dependancies
    cout << setfill(char1) << left << setw(linelength - 1) << "Enter order total(Before shipping cost)" << right << char3;
    file1 << setfill(char1) << left << setw(linelength - 1) << "Enter order total(Before shipping cost)" << right << char3;
    cin >> preshipprice;
    file1 << preshipprice << '\n';
    //4      get receivingcountry written with stream mani and constant variable dependancies
    cout << setfill(char1) << left << setw(linelength - 1) << "Where shipped to?(Valid Ans: USA/CAN/AUS)" << right << char3;
    file1 << setfill(char1) << left << setw(linelength - 1) << "Where shipped to?(Valid Ans: USA/CAN/AUS)" << right << char3;
    cin >> receivingcountry;
    file1 << receivingcountry << '\n';
    //wanted to use tolower here found i can just pass variable into function without getting error "no suitable conversion function from to exists"
    
    //shipping calculator gets addoncost which is our table value, and if theres a fragile tax added together 
    if (receivingcountry == "USA" || receivingcountry == "usa" || receivingcountry == "US" || receivingcountry == "us")
    {
        if (preshipprice < ordertotalprice[0][1])
        {
            addoncost = addoncost + shippingval[0][0];
        }
        else if (preshipprice > ordertotalprice[1][0] || preshipprice <= ordertotalprice[1][1])
        {
            addoncost = addoncost + shippingval[1][0];
        }
        else if (preshipprice > ordertotalprice[2][0] || preshipprice <= ordertotalprice[2][1])
        {
            addoncost = addoncost + shippingval[2][0];
        }
        else if (preshipprice > ordertotalprice[3][0])
        {
            addoncost = addoncost + shippingval[3][0];
        }
        else
        {
            cout << "FATAL ERROR, exiting...";
            file1 << "FATAL ERROR, exiting...";
            return 0;
        }
    }
    else if (receivingcountry == "CAN" || receivingcountry == "can" || receivingcountry == "CN" || receivingcountry == "cn")
    {
        if (preshipprice < ordertotalprice[0][1])
        {
            addoncost = addoncost + shippingval[0][1];
        }
        else if (preshipprice > ordertotalprice[1][0] || preshipprice <= ordertotalprice[1][1])
        {
            addoncost = addoncost + shippingval[1][1];
        }
        else if (preshipprice > ordertotalprice[2][0] || preshipprice <= ordertotalprice[2][1])
        {
            addoncost = addoncost + shippingval[2][1];
        }
        else if (preshipprice > ordertotalprice[3][0])
        {
            addoncost = addoncost + shippingval[3][1];
        }
        else
        {
            cout << "FATAL ERROR, exiting...";
            file1 << "FATAL ERROR, exiting...";
            return 0;
        }
    }
    else if (receivingcountry == "AUS" || receivingcountry == "aus" || receivingcountry == "AU" || receivingcountry == "au")
    {
        if (preshipprice < ordertotalprice[0][1])
        {
            addoncost = addoncost + shippingval[0][2];
        }
        else if (preshipprice > ordertotalprice[1][0] || preshipprice <= ordertotalprice[1][1])
        {
            addoncost = addoncost + shippingval[1][2];
        }
        else if (preshipprice > ordertotalprice[2][0] || preshipprice <= ordertotalprice[2][1])
        {
            addoncost = addoncost + shippingval[2][2];
        }
        else if (preshipprice > ordertotalprice[3][0])
        {
            addoncost = addoncost + shippingval[3][2];
        }
        else
        {
            cout << "FATAL ERROR, exiting...";
            file1 << "FATAL ERROR, exiting...";
            return 0;
        }
    }
    else
    {
        cout << "In valid response! Please only answer with USA CAN or AUS! Exiting...";
        file1 << "In valid response! Please only answer with USA CAN or AUS! Exiting...";
        return 0;
    }

    //finally add our calculated shipping price  along with preshipping price
    finalprice = addoncost + preshipprice;

    //best solution I found online to getting string value to upper case
    transform(itemname.begin(), itemname.end(), itemname.begin(), toupper);
    transform(receivingcountry.begin(), receivingcountry.end(), receivingcountry.begin(), toupper);
    
    //outputs of itemanme, addoncost, receivingcountry, and finalprice all using stream manipulators.
    cout << endl;
    file1 << endl;
    cout << setfill(char1) << left << setw(linelength - 10) << "Item name" << right << itemname << endl;
    file1 << setfill(char1) << left << setw(linelength - 10) << "Item name" << right << itemname << endl;
    cout << setfill(char1) << left << setw(linelength - 10) << "Add on costs" << right << char4 << addoncost << endl;
    file1 << setfill(char1) << left << setw(linelength - 10) << "Add on costs" << right << char4 << addoncost << endl;
    cout << setfill(char1) << left << setw(linelength - 10) << "Shipping to" << right << receivingcountry << endl;
    file1 << setfill(char1) << left << setw(linelength - 10) << "Shipping to" << right << receivingcountry << endl;
    cout << setfill(char1) << left << setw(linelength - 10) << "Total shipping cost" << right << char4 << finalprice << endl;
    file1 << setfill(char1) << left << setw(linelength - 10) << "Total shipping cost" << right << char4 << finalprice << endl;

    return 0;
}

/* removed code
    int linelength = 50;
    float linelength = 50;

    //replaced ALOT of numbers with variables.
    
    //debugging statements
    cout << receivingcountry << '\n';
    cout << preshipprice << " " << addoncost << "=" << finalprice << '\n';
    cout << itemname << '\n' << yorn;
*/