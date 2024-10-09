#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

//this struct will define the format of a given user
class User {
    public:
    string username;
    string password;
    int privilege;
};

bool read_files(User arrUsers[], int &numUsers, string arrAddresses[], int &numAddresses)
{
    //init first startup bool and declare as true
    bool isFirstStartup = true;

    //checks if the startup config file exists and creates it if it doesnt
    string confFile {"startup.conf"};
    string confString;
    ifstream inFile {confFile};

    if (!inFile)
    {
        ofstream outFile {confFile};
        outFile << "false";
        isFirstStartup = true;
    }
    //if it does exist, we get the value of the first line that defines the value for a bool isFirstStartup
    else
    {
        inFile >> confString;

        //will set isFirstStartup to false if the condition is false
        isFirstStartup = (confString == "true");

        if (isFirstStartup)
        {
            ofstream outFile {confFile};    //overwrite conf file after bool value was received
            outFile << "false";             //change the conf file's contents to false
        }

    }

    //create the users.txt file that stores added users and add them to an array defined by the User class
    ifstream inUsers {"users.txt"};
    ifstream inAddresses {"addresses.txt"};
    string userString, ipString;

    //read contents of user.txt and add them to arrUsers array if file is accessible
    if (!inUsers.is_open())
    {
        cout << "users.txt could not be opened. Previously created users will not be displayed." << endl;
    }
    else
    {
        //get user details per line using getline method
        for(int i = 0; getline(inUsers, userString); i++)
        {
            stringstream ss(userString);
            string privilegeString;

            //fetch each value of user details and store in array
            //!!privilege is incompattible with with array and is converted after fetching
            getline(ss, arrUsers[i].username, ',');
            getline(ss, arrUsers[i].password, ',');
            getline(ss, privilegeString);

            //converts privilege received from file to int and store in array
            arrUsers[i].privilege = stoi(privilegeString);
            //increase number of users with 1
            numUsers++;
        }
        inUsers.close();
    }
    //read contents of addresses.txt and add them to arrAddresses if file is accessible
    if (!inAddresses.is_open())
    {
        cout << "addresses.txt could not be opened. Previously configured static addresses will not be displayed" << endl;
    }
    else
    {
        for(int i = 0; getline(inAddresses, ipString); i++)
        {
            arrAddresses[i] = ipString;
            //increase number of addresses with 1
            numAddresses++;
        }

        inAddresses.close();
    }



    //close file
    inFile.close();

    //return the value read from the conf file
    //if the text value is true it will return true, if it's false it will return false
    return isFirstStartup;
}

//gets users from users.txt and adds to arrUsers object
void get_users(User arrUsers[], int& numUsers) {
    //declare filename
    string filename = "users.txt";

    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening file.";
        return;
    }

    for (int i = 0; i < numUsers; ++i) {
        User user;
        string line;
        if (getline(inFile, line)) {
            istringstream iss(line);
            if (!(iss >> user.username >> user.password >> user.privilege)) {
                cerr << "Error parsing line: " << line << '\n';
                continue;
            }
            arrUsers[i] = user;
        } else {
            std::cerr << "Unexpected end of file.\n";
            break;
        }
    }

    inFile.close();
}

bool valid_router(const string &ipAddress)
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
}

bool in_range(const string &ipAddress, const string &routerAddress)
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

bool valid_password(const string &password)
{
    /* the password must have the following:
     * 1 uppercase character
     * 1 lowercase character
     * 1 digit
     * 1 special character as defined below
     * must be at least 8 characters long    */

    //specify the special character and initialaze the condition booleans
    const string specialChars = "!@#$%^&*()-_=+[]{}|;:.<>?";
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

void add_user(User*& arrUsers, int& numUsers) {
    //init variables the user will enter

}

void remove_user(User*& arrUsers, int& numUsers)
{

}

int first_startup()
{
    cout << "Initial Setup Screen" << endl;
    return 0;
}

int user_login()
{
    return 0;
}

void staticAddress_menu()
{

}

void dns_menu()
{

}

void dhcp_menu()
{

}

void user_management(User arrUsers[], int& numUsers)
{
    int menuChoice = 0;
    User* pUsers = arrUsers;

    do
    {
        //table headings
        cout << left << setw(5) << "No." << setw(25) << "Username" << setw(15) << "Privilege" << endl;

        //for loop loops through user array and displays users
        for (int i = 0; i < numUsers; i++)
        {
            cout << left << setw(5) << i+1 << setw(25) << arrUsers[i].username << setw(15) << arrUsers[i].privilege << endl;
        }

        //display options to user
        cout << "1. Add user" << endl
             << "2. Remover user" << endl
             << "0. Return to main menu" << endl;
        cout << endl << "Enter option: ";
        cin >> menuChoice;

        if (menuChoice == 1)
        {
            //init user variables
            string username, password, cPassword;
            int privilege;

            //input username
            cout << "Username: ";
            cin >> username;

            //input password
            cout << "Password: ";
            cin >> password;

            //validate password
            while (!valid_password(password)) {
                cout << "Password does not meet minimum requirements. Enter again: ";
                cin >> password;
            }

            //confirm password
            cout << "Confirm password: ";
            cin >> cPassword;
            while (cPassword != password) {
                cout << "Passwords do not match. Enter again: ";
                cin >> cPassword;
            }

            //input permission level
            do {
                cout << "Permission level for user " << username << " (0, 1): ";
                cin >> privilege;

                if (privilege != 0 && privilege != 1) {
                    cout << "Error: Invalid value for permission level." << endl;
                }
            } while (privilege != 0 && privilege != 1);

            //add the new user
            arrUsers[numUsers].username = username;
            arrUsers[numUsers].password = password;
            arrUsers[numUsers].privilege = privilege;

            //increment the user count
            numUsers++;
        }
        else if (menuChoice == 2)
        {
            //remove a user
            break;
        }
        else if (menuChoice == 0)
        {
            break;
        }
        else
        {
            cout << "Error: Invalid option." << endl;
        }

        //clear the screen
        system("cls");

    } while (menuChoice != 0);

    //clear the screen
    system("cls");
}

//this function allows the user to reset the router
//done by overwriting both txt files and setting the conf file contents to default values
bool reset_system()
{
    int option;
    cout << "Are you sure you want to reset the system?" << endl
            << "1. Reset system" << endl
            << "0. Return to main menu" << endl;
    cin >> option;

    //clears the screen
    system("cls");

    do
    {
        //switch to handle user option
        switch (option)
        {
            //if the user chooses to reset the system they will have to confirm
            //their choice by repeating a randomly generated 7 digit integer
            case 1:
            {
                int randNum, compareNum;
                cout << "Confirm by entering the 7 digit pin shown below:" << endl;
                randNum = 1000000 + (rand()% 9000000);
                cout << randNum << " : ";
                cin >> compareNum;

                if (compareNum != randNum)
                {
                    cout << "The pin you provided does not match. Returning to the main menu." << endl;
                    return false;
                }
                else
                {
                    //change the value of the startup.conf file and return string true
                    string confFile {"startup.conf"};
                    ofstream outFile {confFile};
                    outFile << "true";
                    return true;
                }


            }

                //if the user changes their mind they can choose to exit this menu by typing 0
            case 0:
                return false;
            default:
                cout << "Invalid selection, please try again: ";

        }
    } while (option != 0);
    //clear the screen
    system("cls");
    return false;
}

void save_files(const User arrUsers[], const int& numUsers,string arrAddresses[], const int& numAddresses)
{
    //open txt files for saving
    ofstream outUsers {"users.txt"};
    ofstream outAddresses {"addresses.txt"};

    //write users to users.txt
    for (int i = 0; i < numUsers; i++)
    {
        outUsers << arrUsers[i].username << "," << arrUsers[i].password << "," << arrUsers[i].privilege << endl;
    }

    //write ip addresses to addresses.txt
    for (int i = 0; i < numAddresses; i++)
    {
        outAddresses << arrAddresses[i] << endl;
    }

    //close the files that where written to
    outUsers.close();
    outAddresses.close();
}

int main()
{
    //set seed for random generation
    srand(time(0));

    //declare arrays to store users and ip addresses
    User arrUsers[100];
    string arrAddresses[254];
    int privilege = 0, numUsers = 0, numAddresses = 0;

    //call the read_conf function to get the first startup variable
    bool isFirstStartup = read_files(arrUsers, numUsers, arrAddresses, numAddresses);

    //if the conf file does not exist of contains true the first startup function will be called
    if (!isFirstStartup)
    {
        privilege = user_login();
    }
    else
    {
        privilege = first_startup();
    }

    //main menu
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
                user_management(arrUsers, numUsers);
                break;
            case 5:
                //exit the menu and program if the function returns true
                if (privilege == 0)
                {
                    reset_system();
                    option = 0;
                }
                else
                {
                    cout << "Error: Access denied." << endl;
                }
                break;
            default:
                printf("!! Please select a valid option !!\n");
                break;
        }
    }while (option != 0);

    //save user and ip address files
    save_files(arrUsers, numUsers, arrAddresses, numAddresses);

    return 0;
}
