#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool read_conf();               //complete
bool valid_router(ipAddress);   //complete
bool in_range(ipAddress);       //complete
bool valid_rassword(password);  //complete
void first_startup();
void main_menu();
void staticAddress_menu();
void dns_menu();
void dhcp_menu();
void user_management();
void reset_system();

//this struct will define the format of a given user
class User {
    string username;
    string password;
    int privilege;
};

int main()
{
    //call the read_conf function to get the first startup variable
    bool isFirstStartup = read_conf();

    //if the conf file does not exist of contains true the first startup function will be called
    if (isFirstStartup)
    {
        first_startup();
    }

    //will run after first startup or if the program is opened again
    main_menu();
    return 0;
}

bool read_conf()
{
    //init first startup bool and declare as true
    bool isFirstStarup = true;

    //checks if the startup config file exists and creates it if it doesnt
    string confFile {"startup.conf"};
    string confString;
    ifstream inFile {confFile};

    if (!inFile)
    {
        ofstream outFile {confFile};
        outFile << "false";
        isFirstStarup = true;
    }
    //if it does exist, we get the value of the first line that defines the value for a bool isFirstStartup
    else
    {
        inFile >> confString;

        isFirstStarup = (confString == "true") ? true : false;

        if (isFirstStarup)
        {
            ofstream outFile {confFile};    //overwrite conf file after bool value was received
            outFile << "false";             //change the conf file's contents to false
        }

    }

    //return the value read from the file
    //if the text value is true it will return true, if it's false it will return false
    return isFirstStarup;
}

bool isValidRouter(ipAddress)
{
    /*initializes a stream and array that will be used to
     *compactly process and store the blocks of the given ip address*/
    stringstream ss(ipAddress);
    string block, blocks[4];

    //count the number of delimiters to determine of the ip address is valid
    // (ip addresses have 4 blocks, ie 3 delimiters
    int numSeps = 0;
    for (char ch : ipAddress)
    {
        if (ch == '.')
        {
            numSeps++;
        }
    }
    if (numSeps != 3)
    {
        return false;
    }

    //initialize index variable to determine blocks of ip address
    int index = 0;
    while (getline(ss, block, '.') && index < 4)
    {
        blocks[index] = block;
        index++;
    }

    //convert each block to an integer and check if it is less 255 (max value for an ip address block)
    for (int i = 0; i < 4; i++)
    {
        if (stoi(blocks[i]) > 255)
        {
            return false;
        }
    }

    //if all conditions are met the ip address is valid
    return true;
{
bool isInRange(const string &ipAddress, const string &routerAddress)
{
    //initialize a stream and array for both addresses
    //also initialize iblock --> user input ip address blocks
    //            and rblock --> router ip address blocks
    stringstream ssIP(ipAddress);
    stringstream ssRT(routerAddress);
    string iblock, rblock, iblocks[4], rblocks[4];
    int index = 0;

    //separate the blocks of the addresses and compare them
    //return false if the first 3 don't match
    while(getline(ssIP, iblock, '.'))
    {
        iblocks[index] = iblock;
        index++;
    }
    index = 0;
    while (getline(ssRT, rblock, '.'))
    {
        rblocks[index] = rblock;
        index++;
    }
    for (int i = 0; i < 3; i++)
    {
        if (iblocks[i] != rblocks[i])
        {
            return false;
        }
    }

    //return false if the user input ip address is over 255
    if (stoi(iblocks[3]) > 255)
    {
        return false;
    }

    //if all conditions are met the ip address is valid
    return true;
}

bool validPassword(const string &password)
{
    /* the password must have the following:
     * 1 uppercase character
     * 1 lowercase character
     * 1 digit
     * 1 special character as defined below
     * must be at least 8 characters long    */

    //specify the special character and initialaze the condition booleans
    const string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    bool hasUpper, hasLower, hasDigit, hasSpecial;

    //check if the password string contains all requirements and changes bools accordingly
    for (char ch : password)
    {
        if (isupper(ch))
        {
            hasUpper = true;
        }
        if (islower(ch))
        {
            hasLower = true;
        }
        if (isdigit(ch))
        {
            hasDigit = true;
        }
        if (specialChars.find(ch) != string::npos)
        {
            hasSpecial = true;
        }
    }

    // if all bools are true the function will return true and the password is valid
    // length check is done at the end of the function to avoid a while loop with counter variable
    return hasUpper && hasLower && hasDigit && hasSpecial && (password.length() >= 8);
}


void first_startup()
{
    cout << "Initial Setup Screen" << endl;
}


/*this function displays the menu options to the user
     *and handles their choice using a switch-case
     *each case leads to a defined function and returns back to a while loop*/
void main_menu()
{
    //declare user option
    int option;

    //post-test loop to handle returns to the main menu and exit condition
    do
    {
        //below code prints out the interface of the router cli and the menu options
        printf("--------------------------------------------------------------------------\n"
               "                              Router Simulator                            \n"
               "--------------------------------------------------------------------------\n\n"

               "Network Settings\n"
               "  1. DNS Server\n"
               "  2. DHCP Server\n"
               "  3. Static Addresses\n\n"

               "ADMIN ONLY\n"
               "  4. User Management\n"
               "  5. Reset Router\n\n"

               "0 TO EXIT\n"
               "--------------------------------------------------------------------------\n\n");

        //get input from user using cout and cin
        cout << "Enter menu option: ";
        cin >> option;

        //clear the screen (windows powershell command)
        system("cls");

        //switch statement handles users selected menu option
        switch (option)
        {
            case 0:
                break;
            case 1:
                dns_menu();
                break;
            case 2:
                dhcp_menu();
                break;
            case 3:
                staticAddress_menu();
                break;
            case 4:
                user_management();
                break;
            case 5:
                reset_system();
                break;
            default:
                printf("!! Please select a valid option !!\n");
                break;
        }
    }while (option != 0);

}

void staticAddress_menu()
{

}

void dns_menu() {

}

void dhcp_menu() {

}

void user_management() {

}

void reset_system() {

}

