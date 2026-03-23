#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <string>
using namespace std;
string setcolor(unsigned short color);
string login(string, string);
void saveData();
void loadData();
int choice(int);
void mainInterface();
bool signUp(string, string, string);
void printMenuHeader(string, string);
void exit();
void menu();
void header();
void clearScreen();
void adminInterface();
void userInterface();
void partyModule();
void partyMenu();
void employeeModule();
void employeeMenu();
void summaryModule();
void factoryExpenses();
void weeklyRecords();
void enterDailyWork(string);
void materialUsage();
void enterMaterialUsed(string);
void viewWeeklyProgress(string);
void updateProfile(string);
void showPartiesList();
int getEmployeeIndex(string);
int getUserIndex(string);
void generateFinancialReport();
void markAttendance();
void viewAttendance();

// DATA FOR LOGIN

const int size = 100;
string nameArray[size] = {"Behzad"};
string passwordArray[size] = {"1234"};
string roleArray[size] = {"Admin"};
int userCount = 1;
// DATA FOR PARTIES
const int maxParties = 10;
string partyName[maxParties] = {"BUTT BROTHERS", "BILAL THREADS", "AMAN TRADERS"};
int bundlePrice[maxParties] = {400, 350, 200};
int bundlesGiven[maxParties] = {50, 100, 23};
int partyIndex = 3;
// DATA FOR EMPLOYEES
const int maxEmployees = 20;
string employeeName[maxEmployees] = {"Ali", "Awais", "Hamza"};
string employeeCNIC[maxEmployees] = {"35202-1081-718-5", "35202-3678-607-9", "35240-3456-876-6"};
int employeeRate[maxEmployees] = {30, 40, 50};
int employeeIndex = 3;

// USER DAILY WORK  [employee][party][day]
const int totalWeeks = 10;
int dailyWork[maxEmployees][maxParties][32] = {0};

// MATERIAL USED BY USER  [employee][day]
int dyeUsed[maxEmployees][31] = {0};
int woodUsed[maxEmployees][31] = {0};
int waterUsed[maxEmployees][31] = {0};

// UPGRADED FACTORY EXPENSES
const int maxExpenses = 100;
string expenseType[maxExpenses];     // e.g., "Electricity Bill"
string expenseCategory[maxExpenses]; // e.g., "Utilities"
string expenseDate[maxExpenses];     // e.g., "2023-10-25"
int expenseAmount[maxExpenses];
int expenseIndex = 0;

// Attendence track
int attendance[maxEmployees][32] = {0};
int absentPenalty = 200; // Amount to cut per absent day

int main()
{
    loadData();
    int op = 0;
    while (op != 3)
    {
        system("cls");
        header();
        mainInterface();
        op = choice(op);

        if (op == 1)
        {
            clearScreen();
            printMenuHeader("Main menu", "Sign Up");
            string uN, uP, uR;
            cout << "Enter Username: ";
            cin >> uN;
            cout << "Create Password: ";
            cin >> uP;

            uR = "User";

            bool check = signUp(uN, uP, uR);
            saveData();
            if (check)
            {
                cout << "SignUp successful! You are registered as a Worker/User." << endl;
                Sleep(1000);
            }
            else
            {
                cout << "SignUp Failed! Username might already exist." << endl;
            }
        }
        else if (op == 2)
        {
            clearScreen();
            printMenuHeader("Main menu", "Login");
            string uN, uP, uR;
            cout << "Enter Name: ";
            cin >> uN;
            cout << "Enter password: ";
            cin >> uP;
            uR = login(uN, uP);

            if (uR != "undefined")
            {
                if (uR == "Admin")
                {
                    int opAdmin = -1;
                    while (opAdmin != 0)
                    {
                        clearScreen();
                        printMenuHeader("Main menu > Login", "Admin Panel");
                        adminInterface();
                        opAdmin = choice(opAdmin);

                        if (opAdmin == 1)
                        {
                            partyModule();
                        }
                        else if (opAdmin == 2)
                        {
                            employeeModule();
                        }
                        else if (opAdmin == 3)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "Weekly Records");
                            weeklyRecords();
                        }
                        else if (opAdmin == 4)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "Production and Earning Summary");
                            summaryModule();
                        }
                        else if (opAdmin == 5)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "Material Usage");
                            materialUsage();
                        }
                        else if (opAdmin == 6)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "Factory Expenses");
                            factoryExpenses();
                        }
                        else if (opAdmin == 7)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "Generate Bill");
                            generateFinancialReport();
                        }
                        else if (opAdmin == 8)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "Mark Attendance");
                            markAttendance();
                        }
                        else if (opAdmin == 9)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > Admin Panel", "View Attendance");
                            viewAttendance();
                        }
                    }
                }
                if (uR == "User")
                {
                    int opUser = -1;
                    while (opUser != 0)
                    {
                        clearScreen();
                        printMenuHeader("Main menu > Login > User Panel", uN + " (User)");
                        userInterface();
                        opUser = choice(opUser);

                        if (opUser == 1)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > User Panel ", "Enter Daily Work");
                            enterDailyWork(uN);
                        }
                        else if (opUser == 2)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > User Panel ", "Enter Material Usage");
                            enterMaterialUsed(uN);
                        }
                        else if (opUser == 3)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > User Panel ", "View Weekly Progress");
                            viewWeeklyProgress(uN);
                        }
                        else if (opUser == 4)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > User Panel ", "View Available Parties");
                            showPartiesList();
                        }
                        else if (opUser == 5)
                        {
                            clearScreen();
                            printMenuHeader("Main menu > Login > User Panel ", "Update Profile");
                            updateProfile(uN);
                        }
                    }
                }
            }
            else
            {
                cout << "No User found :(" << endl;
                Sleep(1000);
            }
        }
    }

    return 0;
}
void header()
{
    setcolor(11);
    const char *art[] =
        {
            R"(/*\ */*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/ /*\)",
            R"(/*\  _____  _    _  ____   _____    _     ____        ____   _   _  _____ ___  _   _   ____  /*\)",
            R"(/*\ |_   _|| |  | ||  _ \ | ____|  / \   | |  \\     | |  \\\ \ / /| ____|_ _|| \ | | / ___| /*\)",
            R"(/*\   | |  | |__| || |_)  |  _|   / _ \  | |   ||    | |   ||\ V / |  _|  | | |  \| || |  _  /*\)",
            R"(/*\   | |  | |  | ||  _ < | |___ / ___ \ | |   ||    | |   || | |  | |___ | | | |\  |\ |_| | /*\)",
            R"(/*\   |_|  |_|  |_||_| \_\|_____/_/   \_\| |__//     | |__//  |_|  |_____|___||_| \_| \____| /*\)",
            R"(/*\                 __  __    _    _   _    _    ____ __  __ _____ _   _ _____               /*\)",
            R"(/*\                |  \/  |  / \  | \ | |  / \  / ___|  \/  | ____| \ | |_   _|              /*\)",
            R"(/*\                | |\/| | / _ \ |  \| | / _ \| |  _| |\/| |  _| |  \| | | |                /*\)",
            R"(/*\                | |  | |/ ___ \| |\  |/ ___ \ |_| | |  | | |___| |\  | | |                /*\)",
            R"(/*\                |_|  |_/_/   \_\_| \_/_/   \_\____|_|  |_|_____|_| \_| |_|                /*\)",
            R"(/*\                         ______   ______ _____ _____ __  __                               /*\)",
            R"(/*\                        / ___\ \ / / ___|_   _| ____|  \/  |                              /*\)",
            R"(/*\                        \___ \\ V /\___ \ | | |  _| | |\/| |                              /*\)",
            R"(/*\                         ___) || |  ___) || | | |___| |  | |                              /*\)",
            R"(/*\                        |____/ |_| |____/ |_| |_____|_|  |_|                              /*\)",
            R"(/*\                                                                                          /*\)",
            R"(/*\ */*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/ /*\)"};
    for (int i = 0; i < 18; i++)
    {
        cout << art[i] << endl;
        Sleep(60);
    }
    cout << endl;
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
void mainInterface()
{
    setcolor(2);
    cout << "|*|*********************************************************************************************|*|" << endl;
    cout << "|*|                                        _   _  _      _                                      |*|" << endl;
    cout << R"(|*|                                   |  ||_| |  | ||\/||_                                      |*|)" << endl;
    cout << R"(|*|                                   |/\||_|_|_ |_||  ||_                                      |*|)" << endl;
    cout << R"(|*|                                                                                             |*|)" << endl;
    cout << R"(|*|                                                                                             |*|)" << endl;
    cout << R"(|*|               __ ___  __  _  _     _  _ ____                                                |*|)" << endl;
    cout << R"(|*|   /|         |__  |  | __ |\ |     |  | |__|                                                |*|)" << endl;
    cout << R"(|*|   _|_ o       __|_|_ |__| | \|     |__| |                                                   |*|)" << endl;
    cout << "|*|                                                                                             |*|" << endl;
    cout << R"(|*|   __              __  __ ___ _  _                                                           |*|)" << endl;
    cout << R"(|*|   __|        |   |  || __ |  |\ |                                                           |*|)" << endl;
    cout << R"(|*|  |__ o       |__ |__||__|_|_ | \|                                                           |*|)" << endl;
    cout << "|*|                                                                                             |*|" << endl;
    cout << R"(|*|   __          __ _  _ ___ ___                                                               |*|)" << endl;
    cout << R"(|*|   __|        |_   \/   |   |                                                                |*|)" << endl;
    cout << R"(|*|   __| o      |__ _/\_ _|_  |                                                                |*|)" << endl;
    cout << "|*|                                                                                             |*|" << endl;
    cout << "|*|*********************************************************************************************|*|" << endl;
}
int choice(int op)
{
    cout << "Enter your Choice...";
    cin >> op;
    while (true)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
            cout << "Invalid Option entered." << endl;
            cout << "Enter your Choice...";
            cin >> op;
        }
        if (!cin.fail())
        {
            break;
        }
    }
    return op;
}
bool signUp(string uN, string uP, string uR)
{
    if (userCount < size)
    {
        for (int i = 0; i < userCount; i++)
        {
            if (nameArray[i] == uN && passwordArray[i] == uP)
            {
                return false;
            }
        }
        nameArray[userCount] = uN;
        passwordArray[userCount] = uP;
        roleArray[userCount] = uR;
        userCount++;

        return true;
    }
    return false;
}
string login(string uN, string uP)
{
    for (int i = 0; i < userCount; i++)
    {
        if (nameArray[i] == uN && passwordArray[i] == uP)
        {
            return roleArray[i];
        }
    }
    return "undefined";
}
void printMenuHeader(string mainMenu, string subMenu)
{
    setcolor(6);
    string msg = mainMenu + " > " + subMenu;
    cout << R"(|----------------------------------------------------------------------------------------------)" << endl;
    cout << "|\t" << msg << endl;
    cout << R"(|----------------------------------------------------------------------------------------------)" << endl;
}
void clearScreen()
{
    cout << "Press Any Key to Continue..";
    getch();
    system("cls");
    header();
}
void adminInterface()
{
    setcolor(10);
    cout << "                                                                                               " << endl;
    cout << "                                                                                               " << endl;
    cout << R"(|*|.......~~~~~~~~~~___~_~_~_~_~_/\/\/\( ADMIN PANEL )/\/\/\_~_~_~_~_~___~~~~~~~~~~~........|*|)" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|    1. PARTY MANAGEMENT MODULE                                                           |*|" << endl;
    cout << "|*|    2. EMPLOYEE MANAGEMENT MODULE                                                        |*|" << endl;
    cout << "|*|    3. WEEKLY PRODUCTION REPORT                                                          |*|" << endl;
    cout << "|*|    4. PRODUCTION AND EARNING SUMMARY REPORT                                             |*|" << endl;
    cout << "|*|    5. MATERIAL USAGE                                                                    |*|" << endl;
    cout << "|*|    6. FACTORY EXPENSE TRACKER                                                           |*|" << endl;
    cout << "|*|    7. GENERATE FINANCIAL BILL (PAYMENTS AND SALARIES)                                   |*|" << endl;
    cout << "|*|    8. MARK ATTENDANCE                                                                   |*|" << endl;
    cout << "|*|    9. VIEW ATTENDANCE                                                                   |*|" << endl;
    cout << "|*|    0. LOGOUT                                                                            |*|" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|       ENTER YOUR CHOICE...                                                              |*|" << endl;
    cout << "|*|_________________________________________________________________________________________|*|" << endl;
}
void partyModule()
{
    int pChoice = -1;
    while (pChoice != 0)
    {
        clearScreen();
        printMenuHeader("Main menu > Login > Admin Panel", "Party Management");
        partyMenu();
        pChoice = choice(pChoice);
        //---------ADD PARTY---------//
        if (pChoice == 1)
        {
            if (partyIndex < maxParties)
            {
                cin.ignore();
                cout << "Enter Party Name: ";
                getline(cin, partyName[partyIndex]);
                cout << "Enter Price per bundle: ";
                cin >> bundlePrice[partyIndex];
                cout << "Enter Total bundles given: ";
                cin >> bundlesGiven[partyIndex];
                partyIndex++;
                saveData();
                cout << "Party Added Successfully!" << endl;
            }
            else
            {
                cout << "Max Limit reached!\n";
                continue;
            }
        }
        else if (pChoice == 2)
        {
            if (partyIndex == 0)
            {
                cout << "No Parties available!\n";
                continue;
            }
            string pSearch;
            cout << "Enter Party Name to search: ";
            cin.ignore();
            getline(cin, pSearch);
            bool isFound = false;
            for (int i = 0; i < partyIndex; i++)
            {
                if (partyName[i] == pSearch)
                {
                    cout << "Party found : " << partyName[i];
                    cout << " | Price : " << bundlePrice[i];
                    cout << " | Bundles: " << bundlesGiven[i] << endl;
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
                cout << "Party not found!" << endl;
        }
        else if (pChoice == 3)
        {
            if (partyIndex == 0)
            {
                cout << "No Parties available!\n";
                continue;
            }

            string pSearch;
            cout << "Enter party name to update: ";
            cin.ignore();
            getline(cin, pSearch);
            bool isFound = false;
            for (int i = 0; i < partyIndex; i++)
            {
                if (partyName[i] == pSearch)
                {
                    cout << "New Name: ";
                    getline(cin, partyName[i]);
                    cout << "New Price: ";
                    cin >> bundlePrice[i];
                    cout << "New Total bundles given: ";
                    cin >> bundlesGiven[i];
                    cout << "Party Updated Successfully!\n";
                    saveData();
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
                cout << "No party found.\n";
        }
        else if (pChoice == 4)
        {
            if (partyIndex == 0)
            {
                cout << "No Parties available!\n";
                continue;
            }
            string pSearch;
            cout << "Enter Party Name to delete: ";
            cin.ignore();
            getline(cin, pSearch);
            bool isFound = false;
            for (int i = 0; i < partyIndex; i++)
            {
                if (partyName[i] == pSearch)
                {
                    for (int j = i; j < partyIndex - 1; j++)
                    {
                        partyName[j] = partyName[j + 1];
                        bundlePrice[j] = bundlePrice[j + 1];
                        bundlesGiven[j] = bundlesGiven[j + 1];
                    }
                    partyName[partyIndex - 1] = "";
                    bundlePrice[partyIndex - 1] = 0;
                    bundlesGiven[partyIndex - 1] = 0;

                    partyIndex--;
                    cout << "Party Deleted Successfully!\n";
                    saveData();
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
                cout << "Party Not Found!\n";
        }
    }
}
void partyMenu()
{
    setcolor(8);
    cout << "                                                                                               " << endl;
    cout << "                                                                                               " << endl;
    cout << R"(|*|......~~~~~~~~___~_~_~_/\/\/\( Party Management Module )/\/\/\_~_~_~_~___~~~~~~~~~.......|*|)" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|    1. ADD A PARTY                                                                       |*|" << endl;
    cout << "|*|    2. SEARCH A PARTY                                                                    |*|" << endl;
    cout << "|*|    3. UPDATE A PARTY                                                                    |*|" << endl;
    cout << "|*|    4. DELETE A PARTY                                                                    |*|" << endl;
    cout << "|*|    0. EXIT                                                                              |*|" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|       ENTER YOUR CHOICE...                                                              |*|" << endl;
    cout << "|*|_________________________________________________________________________________________|*|" << endl;
}
void employeeModule()
{
    int eChoice = -1;
    while (eChoice != 0)
    {
        clearScreen();
        printMenuHeader("Main menu > Login > Admin Panel", "Employee Management");
        employeeMenu();
        eChoice = choice(eChoice);
        if (eChoice == 1)
        {
            if (employeeIndex < maxEmployees)
            {
                cin.ignore();
                cout << "Enter employee name: ";
                getline(cin, employeeName[employeeIndex]);
                cout << "Enter his CNIC: ";
                getline(cin, employeeCNIC[employeeIndex]);
                cout << "Enter rate (Rs./Bundle): ";
                cin >> employeeRate[employeeIndex];
                employeeIndex++;
                saveData();
                cout << "Employee added successfully!\n";
            }
            else
            {
                cout << "Max Employees added.\n";
                continue;
            }
        }
        else if (eChoice == 2)
        {
            if (employeeIndex == 0)
            {
                cout << "No employee available.\n";
                continue;
            }
            string eSearch;
            cout << "Enter employee name to search: ";
            cin.ignore();
            getline(cin, eSearch);
            bool isFound = false;
            for (int i = 0; i < employeeIndex; i++)
            {
                if (employeeName[i] == eSearch)
                {
                    cout << "Employee found! ";
                    cout << "Name: " << employeeName[i] << endl;
                    cout << "CNIC: " << employeeCNIC[i] << endl;
                    cout << "Rate (Rs./Bundle): " << employeeRate[i] << endl;
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
            {
                cout << "No such employee found.\n";
            }
        }
        else if (eChoice == 3)
        {
            if (employeeIndex == 0)
            {
                cout << "No employees to update!\n";
                continue;
            }
            string eSearch;
            cout << "Enter Employee Name to Update: ";
            cin.ignore();
            getline(cin, eSearch);
            bool found = false;
            for (int i = 0; i < employeeIndex; i++)
            {
                if (employeeName[i] == eSearch)
                {
                    cout << "Enter New Name: ";
                    getline(cin, employeeName[i]);
                    cout << "Enter New CNIC: ";
                    getline(cin, employeeCNIC[i]);
                    cout << "Enter New Rate (Rs./Bundle): ";
                    cin >> employeeRate[i];
                    cout << "Employee Updated Successfully!\n";
                    saveData();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Employee Not Found!\n";
        }
        else if (eChoice == 4)
        {
            if (employeeIndex == 0)
            {
                cout << "No employees to update!\n";
                continue;
            }
            string eSearch;
            cout << "Enter Employee Name to Delete: ";
            cin.ignore();
            getline(cin, eSearch);
            bool isFound = false;
            for (int i = 0; i < employeeIndex; i++)
            {
                if (employeeName[i] == eSearch)
                {
                    for (int j = i; j < employeeIndex - 1; j++)
                    {
                        employeeName[j] = employeeName[j + 1];
                        employeeCNIC[j] = employeeCNIC[j + 1];
                        employeeRate[j] = employeeRate[j + 1];
                    }
                    employeeName[employeeIndex - 1] = "";
                    employeeCNIC[employeeIndex - 1] = "";
                    employeeRate[employeeIndex - 1] = 0;
                    employeeIndex--;
                    cout << "Employee deleted Successfully!\n";
                    saveData();
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
                cout << "No employee found.\n";
        }
    }
}
void employeeMenu()
{
    setcolor(8);
    cout << "                                                                                               " << endl;
    cout << "                                                                                               " << endl;
    cout << R"(|*|......~~~~~~~__~_~_~_/\/\/\( Employee Management Module )/\/\/\_~_~_~_~__~~~~~~~~~.......|*|)" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|    1. ADD AN EMPLOYEE                                                                   |*|" << endl;
    cout << "|*|    2. SEARCH AN EMPLOYEE                                                                |*|" << endl;
    cout << "|*|    3. UPDATE AN EMPLOYEE                                                                |*|" << endl;
    cout << "|*|    4. DELETE AN EMPLOYEE                                                                |*|" << endl;
    cout << "|*|    0. EXIT                                                                              |*|" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|       ENTER YOUR CHOICE...                                                              |*|" << endl;
    cout << "|*|_________________________________________________________________________________________|*|" << endl;
}
void weeklyRecords()
{
    cout << "Weekly Production Summary\n";
    cout << "-------------------------------------\n";

    for (int p = 0; p < partyIndex; p++)
    {
        int total = 0;

        for (int e = 0; e < employeeIndex; e++)
        {
            for (int d = 1; d <= 7; d++)
                total += dailyWork[e][p][d];
        }

        cout << partyName[p] << ": " << total << " bundles dyed\n";
    }

    Sleep(3000);
}
void materialUsage()
{
    int totalDye = 0, totalWood = 0, totalWater = 0;

    for (int e = 0; e < employeeIndex; e++)
    {
        for (int d = 1; d <= 31; d++)
        {
            totalDye += dyeUsed[e][d];
            totalWood += woodUsed[e][d];
            totalWater += waterUsed[e][d];
        }
    }

    cout << "Material Usage Summary:\n";
    cout << "Dye Used: " << totalDye << " grams\n";
    cout << "Wood Used: " << totalWood << " kg\n";
    cout << "Water Used: " << totalWater << " liters\n";

    Sleep(3000);
}

void summaryModule()
{
    cout << "\n=========== PRODUCTION & EARNING SUMMARY ===========\n";

    for (int p = 0; p < partyIndex; p++)
    {
        cout << "\nParty: " << partyName[p] << endl;
        cout << "Bundles Given: " << bundlesGiven[p] << endl;
        cout << "Price per Bundle: Rs. " << bundlePrice[p] << endl;

        int totalDyed = 0;

        for (int e = 0; e < employeeIndex; e++)
        {
            int empDyed = 0;

            for (int d = 1; d < 31; d++)
            {
                empDyed += dailyWork[e][p][d];
            }

            if (empDyed > 0)
            {
                cout << "  Employee: " << employeeName[e]
                     << " | Bundles Dyed: " << empDyed
                     << " | Rate: " << employeeRate[e] << endl;
            }

            totalDyed += empDyed;
        }

        cout << "Total Dyed Bundles: " << totalDyed << endl;
        cout << "Remaining Bundles: " << (bundlesGiven[p] - totalDyed) << endl;

        int revenue = totalDyed * bundlePrice[p];
        cout << "Total Revenue from this Party: Rs. " << revenue << endl;
        cout << "------------------------------------------------\n";
    }
}
void factoryExpenses()
{
    int choice = -1;
    while (choice != 0)
    {
        system("cls");
        printMenuHeader("Admin Panel", "Factory Expense Tracker");
        cout << "\n1. Add New Expense\n2. View Detailed Log\n3. View Category Summary\n0. Back\n";
        choice = ::choice(choice); // Using your global choice function

        if (choice == 1)
        {
            if (expenseIndex < maxExpenses)
            {
                cin.ignore();
                cout << "Description (e.g. Rent): ";
                getline(cin, expenseType[expenseIndex]);
                cout << "Category (Utility/Material/Salary): ";
                getline(cin, expenseCategory[expenseIndex]);
                cout << "Date (DD/MM): ";
                getline(cin, expenseDate[expenseIndex]);
                cout << "Amount: ";
                cin >> expenseAmount[expenseIndex];

                expenseIndex++;
                saveData();
                cout << "Expense logged successfully!";
                Sleep(1000);
            }
        }
        else if (choice == 2)
        {
            cout << left << setw(15) << "Date" << setw(20) << "Category" << setw(20) << "Description" << "Amount" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            for (int i = 0; i < expenseIndex; i++)
            {
                cout << left << setw(15) << expenseDate[i] << setw(20) << expenseCategory[i]
                     << setw(20) << expenseType[i] << "Rs. " << expenseAmount[i] << endl;
            }
            getch();
        }
    }
}
void generateFinancialReport()
{
    int startDay, endDay;
    cout << "Enter Start Day for the week (e.g., 1): ";
    cin >> startDay;
    cout << "Enter End Day for the week (e.g., 7): ";
    cin >> endDay;

    ofstream bill("Weekly_Financial_Report.html");

    // LOGIC: Initialize totals
    int totalRevenue = 0;
    int totalSalaries = 0;
    int totalExpenses = 0;

    // 1. Calculate Total Revenue for the selected period
    for (int p = 0; p < partyIndex; p++)
    {
        int pDyed = 0;
        for (int e = 0; e < employeeIndex; e++)
        {
            for (int d = startDay; d <= endDay; d++)
                pDyed += dailyWork[e][p][d];
        }
        totalRevenue += (pDyed * bundlePrice[p]);
    }

    // 2. Calculate Total Expenses (Current logic shows all, you can filter if needed)
    for (int i = 0; i < expenseIndex; i++)
        totalExpenses += expenseAmount[i];

    // HTML Header and Styles
    bill << "<html><head><style>"
         << "body{font-family: 'Segoe UI', Tahoma, sans-serif; margin: 40px; color: #333;}"
         << "h1{text-align: center; color: #2c3e50; border-bottom: 2px solid #2c3e50; padding-bottom: 10px;}"
         << "h2{color: #2980b9; margin-top: 30px; border-left: 5px solid #2980b9; padding-left: 10px;}"
         << "table{border-collapse: collapse; width: 100%; margin-top: 10px;}"
         << "th, td{border: 1px solid #ddd; padding: 12px; text-align: left;}"
         << "th{background-color: #2c3e50; color: white;}"
         << "tr:nth-child(even){background-color: #f9f9f9;}"
         << ".summary-box{margin-top: 30px; padding: 20px; border: 2px solid #2c3e50; background: #ecf0f1; font-size: 1.2em;}"
         << ".profit{color: green; font-weight: bold;} .loss{color: red; font-weight: bold;}"
         << "</style></head><body>"
         << "<h1>Textile Factory Financial Report</h1>"
         << "<p style='text-align:center;'>Reporting Period: Day " << startDay << " to Day " << endDay << "</p>";

    // Table 1: Employee Salaries
    bill << "<h2>Employee Payroll (with Attendance Penalty)</h2>";
    bill << "<table><tr><th>Name</th><th>Bundles</th><th>Absents</th><th>Penalty</th><th>Net Salary</th></tr>";

    for (int e = 0; e < employeeIndex; e++)
    {
        int totalBundles = 0;
        int absentDays = 0;

        for (int d = startDay; d <= endDay; d++)
        {
            for (int p = 0; p < partyIndex; p++)
            {
                totalBundles += dailyWork[e][p][d];
            }
            if (attendance[e][d] == 0) // If absent on that day
                absentDays++;
        }

        int grossSalary = totalBundles * employeeRate[e];
        int totalPenalty = absentDays * absentPenalty;
        int netSalary = grossSalary - totalPenalty;
        if (netSalary < 0)
            netSalary = 0;

        bill << "<tr><td>" << employeeName[e] << "</td><td>" << totalBundles
             << "</td><td>" << absentDays << "</td><td>Rs. " << totalPenalty
             << "</td><td>Rs. " << netSalary << "</td></tr>";

        // ADD TO TOTAL SALARIES HERE (The correct way)
        totalSalaries += netSalary;
    }
    bill << "</table>";

    // Table 2: Party Invoices
    bill << "<h2>Party Invoices</h2><table><tr><th>Party Name</th><th>Bundles Dyed</th><th>Price/Bundle</th><th>Total Amount</th></tr>";
    for (int p = 0; p < partyIndex; p++)
    {
        int totalDyed = 0;
        for (int e = 0; e < employeeIndex; e++)
        {
            for (int d = startDay; d <= endDay; d++)
                totalDyed += dailyWork[e][p][d];
        }
        bill << "<tr><td>" << partyName[p] << "</td><td>" << totalDyed << "</td><td>" << bundlePrice[p] << "</td><td>Rs. " << (totalDyed * bundlePrice[p]) << "</td></tr>";
    }
    bill << "</table>";

    // Table 3: Expenses
    bill << "<h2>Factory Expense Breakdown</h2><table><tr><th>Date</th><th>Category</th><th>Description</th><th>Amount</th></tr>";
    for (int i = 0; i < expenseIndex; i++)
    {
        bill << "<tr><td>" << expenseDate[i] << "</td><td>" << expenseCategory[i] << "</td><td>"
             << expenseType[i] << "</td><td>Rs. " << expenseAmount[i] << "</td></tr>";
    }
    bill << "</table>";

    // FINAL STEP: Calculate Net Profit AFTER all sums are finished
    int netProfit = totalRevenue - totalSalaries - totalExpenses;

    bill << "<div class='summary-box'>"
         << "<strong>Total Revenue:</strong> Rs. " << totalRevenue << "<br>"
         << "<strong>Total Salaries (After Penalties):</strong> Rs. " << totalSalaries << "<br>"
         << "<strong>Factory Expenses:</strong> Rs. " << totalExpenses << "<br><hr>"
         << "<strong>Net Business Profit: </strong>"
         << "<span class='" << (netProfit >= 0 ? "profit" : "loss") << "'>Rs. " << netProfit << "</span>"
         << "</div></body></html>";

    bill.close();
    cout << "\nReport updated successfully for Days " << startDay << "-" << endDay << "!";
    ShellExecute(NULL, "open", "Weekly_Financial_Report.html", NULL, NULL, SW_SHOWNORMAL);
}
void markAttendance()
{
    int day;
    cout << "Enter Day to mark attendance (1-31): ";
    cin >> day;

    if (day < 1 || day > 31) {
        cout << "Invalid day!";
        return;
    }

    for (int i = 0; i < employeeIndex; i++)
    {
        char status;
        // Instruction for the Admin
        cout << "Employee: " << employeeName[i] << " | Enter Status (P=Present, A=Absent, S=Skip): ";
        cin >> status;

        if (status == 'p' || status == 'P')
        {
            attendance[i][day] = 1; // 1 represents Present
        }
        else if (status == 'a' || status == 'A')
        {
            attendance[i][day] = 2; // 2 represents Absent
        }
        else
        {
            // If they press 's' or any other key, it stays 0 (Unmarked)
            cout << "Skipped. (Remains unmarked)" << endl;
        }
    }
    saveData();
    cout << "\nAttendance processed successfully!";
    Sleep(1000);
}
void viewAttendance()
{
    system("cls");
    cout << "=====================================================================================================" << endl;
    cout << "                                   MONTHLY ATTENDANCE RECORD                                         " << endl;
    cout << "=====================================================================================================" << endl;
    
    cout << left << setw(15) << "Employee";
    for (int d = 1; d <= 31; d++) cout << setw(3) << d;
    cout << " | " << "P" << " | " << "A"; 
    cout << endl << string(120, '-') << endl;

    for (int i = 0; i < employeeIndex; i++) {
        int pCount = 0;
        int aCount = 0;
        cout << left << setw(15) << employeeName[i];
        
        for (int d = 1; d <= 31; d++) {
            if (attendance[i][d] == 1) {
                cout << setw(3) << "P";
                pCount++;
            }
            else if (attendance[i][d] == 2) {
                cout << setw(3) << "A"; // NEW: Show A for Absent
                aCount++;
            }
            else {
                cout << setw(3) << "."; // Show . for Unmarked (0)
            }
        }
        
        cout << " | " << setw(2) << pCount << " | " << setw(2) << aCount; 
        cout << endl;
    }
    cout << "\nPress any key to return...";
    getch();
}
void userInterface()
{
    setcolor(10);
    cout << "                                                                                               " << endl;
    cout << "                                                                                               " << endl;
    cout << R"(|*|.......~~~~~~~~~~___~_~_~_~_~_/\/\/\( USER PANEL )/\/\/\_~_~_~_~_~___~~~~~~~~~~~........|*|)" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|    1. ENTER DAILY WORK                                                                  |*|" << endl;
    cout << "|*|    2. ENTER MATERIAL USED                                                               |*|" << endl;
    cout << "|*|    3. VIEW WEEKLY PROGRESS                                                              |*|" << endl;
    cout << "|*|    4. VIEW AVAILABLE PARTIES                                                            |*|" << endl;
    cout << "|*|    5. UPDATE PROFILE                                                                    |*|" << endl;
    cout << "|*|    0. LOGOUT                                                                            |*|" << endl;
    cout << "|*|                                                                                         |*|" << endl;
    cout << "|*|       ENTER YOUR CHOICE...                                                              |*|" << endl;
    cout << "|*|_________________________________________________________________________________________|*|" << endl;
}
int getEmployeeIndex(string username)
{
    for (int i = 0; i < employeeIndex; i++)
    {
        if (employeeName[i] == username)
            return i;
    }
    return -1;
}
void enterDailyWork(string username)
{
    int eIndex = getEmployeeIndex(username);
    if (eIndex == -1)
    {
        cout << "No employee found";
        return;
    }
    cout << "----Select party---- " << endl;
    for (int i = 0; i < partyIndex; i++)
        cout << i << ". " << partyName[i] << endl;

    int p;
    cout << "Enter party number: ";
    cin >> p;
    if (p < 0 || p >= partyIndex)
    {
        cout << "Invalid Party\n";
        return;
    }
    int day, bundles;
    cout << "Enter Day(1-31): ";
    cin >> day;
    if (attendance[eIndex][day] == 0)
    {
        cout << "Error: Employee was marked ABSENT on this day. Cannot enter work!";
        return;
    }
    cout << "Enter Bundles dyed: ";
    cin >> bundles;
    int alreadyDyed = 0;
    for (int i = 0; i < employeeIndex; i++)
    {
        for (int d = 1; d <= 31; d++)
        {
            alreadyDyed += dailyWork[i][p][d];
        }
    }

    int available = bundlesGiven[p] - alreadyDyed;

    if (available <= 0) 
    {
        cout << "Error: This party's order is already 100% completed!";
        return;
    }

    if (bundles > available)
    {
        cout << "Error: Only " << available << " bundles remaining for this party!";
        return; // Stop the entry
    }
    dailyWork[eIndex][p][day] += bundles;
    saveData();
    cout << "Work Saved Successfully.";
    Sleep(1000);
}
void enterMaterialUsed(string username)
{

    int eIndex = getEmployeeIndex(username);
    if (eIndex == -1)
    {
        cout << "No employee found";
        return;
    }
    int day;
    cout << "Enter Day(1-31): ";
    cin >> day;

    cout << "Dye used (grams): ";
    cin >> dyeUsed[eIndex][day];
    cout << "Wood burnt (kg): ";
    cin >> woodUsed[eIndex][day];
    cout << "Water used (liters): ";
    cin >> waterUsed[eIndex][day];

    cout << "Material entry saved!";
    Sleep(1000);
}
void viewWeeklyProgress(string username)
{
    int eIndex = getEmployeeIndex(username);

    if (eIndex == -1)
    {
        cout << "No employee found";
        return;
    }

    int total = 0;

    cout << "Weekly progress for " << username << endl;
    cout << "----------------------------";
    for (int p = 0; p < partyIndex; p++)
    {
        int partyTotal = 0;
        for (int d = 1; d <= 7; d++)
        {
            partyTotal += dailyWork[eIndex][p][d];
        }
        if (partyTotal > 0)
            cout << partyName[p] << ": " << partyTotal << " bundles" << endl;

        total += partyTotal;
    }
    cout << "\nTotal bundles dyed this week: " << total << endl;
    Sleep(2000);
}
void showPartiesList()
{
    cout << "Available parties: ";
    for (int p = 0; p < partyIndex; p++)
    {
        cout << p << ". " << partyName[p];
        cout << " | Bundles : " << bundlesGiven[p];
        cout << " | Rate: " << bundlePrice[p] << endl
             << "----------------------------";
    }
    Sleep(2000);
}
int getUserIndex(string username)
{
    for (int i = 0; i < userCount; i++)
    {
        if (nameArray[i] == username)
            return i;
    }
    return -1;
}
void updateProfile(string username)
{
    int uIndex = getUserIndex(username);
    int eIndex = getEmployeeIndex(username);

    if (uIndex == -1)
    {
        cout << "User not found!";
        return;
    }
    string newName, newPass;
    cin.ignore(100, '\n');
    cout << "Enter New Username: ";

    getline(cin, newName);
    nameArray[uIndex] = newName;
    if (eIndex != -1)
        employeeName[eIndex] = newName;
    cout << "Enter New password: ";
    getline(cin, newPass);
    passwordArray[uIndex] = newPass;
    saveData();
    cout << "Updated successfully! Please re-login with new credentials.";
    Sleep(1000);
}
void saveData()
{
    // 1. Save Users
    ofstream userWrite("users.txt");
    if (userWrite)
    {
        for (int i = 0; i < userCount; i++)
        {

            userWrite << nameArray[i] << " " << passwordArray[i] << " " << roleArray[i] << endl;
        }
        userWrite.close();
    }
    // 2. Save Parties
    ofstream partyFile("parties.txt");
    for (int i = 0; i < partyIndex; i++)
    {
        partyFile << partyName[i] << "," << bundlePrice[i] << "," << bundlesGiven[i] << endl;
    }
    partyFile.close();

    // 3. Save Employees
    ofstream empWrite("employees.txt");
    if (empWrite)
    {
        for (int i = 0; i < employeeIndex; i++)
        {
            empWrite << employeeName[i] << "," << employeeCNIC[i] << "," << employeeRate[i] << endl;
        }
        empWrite.close();
    }

    // 4. Save Daily Work Production
    ofstream workFile("work.txt");
    for (int e = 0; e < employeeIndex; e++)
    {
        for (int p = 0; p < partyIndex; p++)
        {
            for (int d = 0; d < 32; d++)
            {
                workFile << dailyWork[e][p][d] << " ";
            }
            workFile << endl;
        }
    }
    workFile.close();
    // 5. Save Factory Expenses
    ofstream expFile("expenses.txt");
    for (int i = 0; i < expenseIndex; i++)
    {
        expFile << expenseType[i] << "," << expenseCategory[i] << ","
                << expenseDate[i] << "," << expenseAmount[i] << endl;
    }
    expFile.close();
    ofstream attFile("attendance.txt");
    for (int e = 0; e < employeeIndex; e++)
    {
        for (int d = 0; d < 32; d++)
        {
            attFile << attendance[e][d] << " ";
        }
        attFile << endl;
    }
    attFile.close();
}

void loadData()
{
    // 1. Load Users
    ifstream userFile("users.txt");
    if (userFile)
    {
        userCount = 0;
        // The check is built into the while condition
        while (userFile >> nameArray[userCount] >> passwordArray[userCount] >> roleArray[userCount])
        {
            userCount++;
        }
        userFile.close();
    }

    // 2. Load Parties
    ifstream partyFile("parties.txt");
    if (partyFile)
    {
        partyIndex = 0;
        string price, bundles, name;
        // The check: Read the name first, then check if it's not empty
        while (getline(partyFile, name, ','))
        {
            if (!name.empty())
            { // <--- THE CHECK LOGIC
                partyName[partyIndex] = name;
                getline(partyFile, price, ',');
                getline(partyFile, bundles);

                bundlePrice[partyIndex] = stoi(price);
                bundlesGiven[partyIndex] = stoi(bundles);
                partyIndex++;
            }
        }
        partyFile.close();
    }

    // 3. Load Employees
    ifstream empFile("employees.txt");
    if (empFile)
    {
        employeeIndex = 0;
        string name, cnic, rate;
        while (getline(empFile, name, ','))
        {
            if (!name.empty())
            {
                employeeName[employeeIndex] = name;
                getline(empFile, cnic, ',');
                getline(empFile, rate);

                employeeRate[employeeIndex] = stoi(rate);
                employeeIndex++;
            }
        }
        empFile.close();
    }
    // 4. Load Daily Work Production
    ifstream workFile("work.txt");
    if (workFile)
    {
        // Synchronize with saveData by using actual indices
        for (int e = 0; e < employeeIndex; e++)
        {
            for (int p = 0; p < partyIndex; p++)
            {
                for (int d = 0; d < 32; d++)
                {
                    workFile >> dailyWork[e][p][d];
                }
            }
        }
        workFile.close();
    }
    ifstream expFile("expenses.txt");
    if (expFile)
    {
        expenseIndex = 0;
        string t, c, d, a;
        while (getline(expFile, t, ','))
        {
            getline(expFile, c, ',');
            getline(expFile, d, ',');
            getline(expFile, a);
            expenseType[expenseIndex] = t;
            expenseCategory[expenseIndex] = c;
            expenseDate[expenseIndex] = d;
            expenseAmount[expenseIndex] = stoi(a);
            expenseIndex++;
        }
    }
    ifstream attFile("attendance.txt");
    if (attFile)
    {
        for (int e = 0; e < maxEmployees; e++)
        {
            for (int d = 0; d < 32; d++)
            {
                attFile >> attendance[e][d];
            }
        }
    }
}