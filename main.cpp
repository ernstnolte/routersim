//43769780 EH Nolte
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

//declare router address constant
const string ROUTER_ADDRESS = "192.168.0.1";

//this struct will define the format of a given user
class User {
public:
    string username;
    string password;
    int privilege;
};

//class contains functions related to the reading and writing of config files
class Config
{
public:
    bool read_files(User arrUsers[], int &numUsers, string arrAddresses[], int &numAddresses, string& dnsServer, string& dhcpServer)
    {
        //init first startup bool and declare as true
        bool isFirstStartup;

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
            getline(inFile, confString);        //this denotes the first startup bool
            getline(inFile, dnsServer);         //this denotes the dns server entry
            getline(inFile, dhcpServer);        //this denotes the dhcp server entry

            //will set isFirstStartup to false if the condition is false
            isFirstStartup = (confString == "true");
        }

        //create files
        ofstream outUsers {"users.txt", ios::app};
        ofstream outAddresses {"addresses.txt", ios::app};
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

    void save_files(const User arrUsers[], const int& numUsers,string arrAddresses[], const int& numAddresses, const bool& isFirstStartup, const string& dnsServer, const string& dhcpServer)
    {
        //open txt files for saving
        ofstream outConf {"startup.conf"};
        ofstream outUsers {"users.txt"};
        ofstream outAddresses {"addresses.txt"};

        //write server addresses to conf file
        outConf << "false" << endl
                << dnsServer << endl
                << dhcpServer;

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


};

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
                cout << "Error: Could not parse line " << line << endl;
                continue;
            }
            arrUsers[i] = user;
        } else {
            cout << "Error: Unexpected end of file.\n";
            break;
        }
    }

    inFile.close();
}

//checks if a given ip address is within the range of the ipv4 subnet
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

//checks if a given password meets complexity requirements
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
    for (const char ch : password)
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
        //checks if the char is a special character defined by a string specialChars
        if (specialChars.find(ch) != string::npos)
        {
            hasSpecial = true;
        }
    }

    // if all bools are true the function will return true and the password is valid
    // length check is done at the end of the function to avoid a while loop with counter variable
    return hasUpper && hasLower && hasDigit && hasSpecial && (password.length() >= 8);
}

//gets router and user settings from user
int user_setup(User arrUsers[], int& numUsers, string& dnsServer, string& dhcpServer)
{
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "|           Initial Setup         |       Router Address: " << ROUTER_ADDRESS << "    |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    //add admin user to users array
    arrUsers[0].username = "admin";
    arrUsers[0].privilege = 0;

    //get new admin password from user
    string password, cPassword;
    bool notValid;
    do
    {
        do
        {
            cout << "Set admin password: ";
            cin >> password;

            //check is password is valid
            if(!valid_password(password))
            {
                cout << "Error: Invalid password." << endl;
                notValid = true;
            }
            else
            {
                notValid = false;
            }
        } while(notValid);

        //confirm password
        cout << "Confirm password: ";
        cin >> cPassword;

        //check if password is valid
        if (cPassword != password)
        {
            cout << "Error: Passwords do not match." << endl;
        }
    }while(cPassword != password);

    //save password to users array
    arrUsers[0].password = password;
    numUsers++;

    //get dns server from user
    bool validIP = false;
    do
    {
        cout << endl << "Enter DNS Server address: ";
        cin >> dnsServer;

        if(!in_range(dnsServer, ROUTER_ADDRESS))
        {
            cout << "Error: Invalid IP address" << endl;
            validIP = false;
        }
        else
        {
            validIP = true;
        }
    } while(!validIP);
    //reset ip validation bool
    validIP = false;
    //get dhcp server from user
    do
    {
        cout << endl << "Enter DHCP Server address: ";
        cin >> dhcpServer;

        if(!in_range(dhcpServer, ROUTER_ADDRESS))
        {
            cout << "Error: Invalid IP address" << endl;
            validIP = false;
        }
        else
        {
            validIP = true;
        }
    } while(!validIP);


    //returns 0 as privilege level
    return 0;
}

int user_login(User arrUsers[], int& numUsers)
{
    //init login variables
    int index;
    string username, password;
    bool match;

    //get username
    cout << "Username: ";
    cin >> username;

    //get password
    cout << "Password: ";
    cin >> password;

    //find username in array and compare passwords
    for (int i = 0; i < numUsers; i++)
    {
        if (username == arrUsers[i].username)
        {
            if (password == arrUsers[i].password)
            {
                match = true;
                index = i;
            }
            else
            {
                match = false;
            }
        }
    }
    if (!match)
    {
        //user not found
        cout << "Could not verify login credential.";
        return -1;
    }

    //clear screen and return user privilege
    system("cls");
    return arrUsers[index].privilege;
}

void staticAddress_menu(string arrAddresses[], int& numAddresses)
{
    //init menu option variable
    int option;
    do
    {
        //display current static addresses and menu options
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "                          Static IP Addresses                             " << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        cout << left << setw(5) << "NO." << setw(10) << "Static Address" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        //loop through ip address array and print to table
        for (int i = 0; i < numAddresses; i++)
        {
            cout << left << setw(5) << i+1 << setw(10) << arrAddresses[i] << endl;
        }
        cout << "--------------------------------------------------------------------------" << endl;
        cout << endl << "1. Add static address" << endl
                     << "2. Remove static address" << endl
                     << "0. Return to main menu" << endl;

        //get option from user
        cout << "Select menu option: ";
        cin >> option;

        //add address to static assignment array
        if (option == 1)
        {
            //init user entry string
            string address;
            cout << "Enter static address: ";
            cin >> address;

            //validate user entry
            bool match = false;
            //looks for existing ip address in array
            for (int i = 0; i < numAddresses; i++)
            {
                if(address == arrAddresses[i])
                {
                    match = true;
                    break;
                }
            }

            //if matching entry is found, throw error
            if (match)
            {
                cout << "Error: Static address assignment exists." << endl;
            }
            //if address is invalid/not in range, throw error
            else if(!in_range(address, ROUTER_ADDRESS))
            {
                cout << "Error: Invalid IP address." << endl;
            }
            //if all requirements are met add address to array and increase number of addresses
            else
            {
                arrAddresses[numAddresses] = address;
                numAddresses++;
                cout << address << " has been added." << endl;
            }
        }
        //remove address from static assignment array
        else if (option == 2)
        {
            //init utility variables
            int removeNum;
            cout << "Enter ID: ";
            cin >> removeNum;

            //check if id valid
            if (removeNum < 1 || removeNum > numAddresses)
            {
                cout << "Error: Address is not statically assigned." << endl;
            }
            else
            {
                //move elements into gap in array
                int index = removeNum - 1;
                for (int i = index; i < numAddresses-1; ++i)
                {
                    arrAddresses[i] = arrAddresses[i+1];
                }
                //decrease number of addresses
                numAddresses--;

                cout << "Success: Address removed from static assignment.";
            }
        }
        //return to main menu
        else if (option == 0)
        {
            //do nothing
            break;
        }
        //invalid option
        else
        {
            cout <<"Error: Invalid menu selection." << endl;
        }

        //clear the screen
        system("cls");
    } while (option != 0);

    //clear the screen
    system("cls");
}

void serverAddress_menu(const string& concatString, string& address)
{
    //init variables
    string newAddress;
    int option;

    do
    {
        //display the current specified server address
        cout << left << concatString << setw(5) << " Server: " << address << endl;
        cout << endl << "1. Change server address" << endl
                     << "0. Return to main menu" << endl;

        cout << "Enter menu option: ";
        cin >> option;

        if (option == 1)
        {
            //get address from user
            cout << "Enter new " << concatString << " address: ";
            cin >> newAddress;

            //validate user entered ip address
            if (!in_range(newAddress, ROUTER_ADDRESS))
            {
                cout << endl << "Error: Invalid IP address" << endl;
            }
            else
            {
                //set user input addess as new server address
                address = newAddress;
                cout << endl << concatString << " server address changed successfully." << endl;

                //clear the screen
                system("cls");
            }
        }
        else if (option == 0)
        {
            break;
        }
        else
        {
            cout << "Error: Invalid menu option." << endl;
            //clear the screen
            system("cls");
        }
    }while (option != 0);

    //clear the screen
    system("cls");
}

void userManagement_menu(User arrUsers[], int& numUsers)
{
    int menuChoice = 0;
    User* pUsers = arrUsers;

    do
    {
        //table headings
        cout << "------------------------------------------------" << endl;
        cout << left << setw(5) << "No." << setw(25) << "Username" << setw(10) << "Privilege" << endl;
        cout << "------------------------------------------------" << endl;

        //for loop loops through user array and displays users
        for (int i = 0; i < numUsers; i++)
        {
            cout << left << setw(5) << i+1 << setw(25) << arrUsers[i].username << setw(15) << arrUsers[i].privilege << endl;
        }

        cout << "------------------------------------------------" << endl;

        //display options to user
        cout << "1. Add user" << endl
             << "2. Remover user" << endl
             << "0. Return to main menu" << endl;
        cout << endl << "Enter option: ";
        cin >> menuChoice;

        //add user
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
        //remove user
        else if (menuChoice == 2)
        {
            //ask user for id of user entry to delete from array
            int removeNum;
            cout << "Enter ID: ";
            cin >> removeNum;

            //check if id valid
            if(arrUsers[removeNum-1].username == "admin")
            {
                cout << "Error: Cannot delete default admin user" << endl;
            }
            else if (removeNum < 1 || removeNum > numUsers)
            {
                cout << "Error: User not found." << endl;
            }
            else
            {
                //move elements into gap in array
                int index = removeNum - 1;
                for (int i = index; i < numUsers-1; ++i)
                {
                    arrUsers[i] = arrUsers[i+1];
                }
                //decrease number of users
                numUsers--;
            }
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
//done by overwriting all txt files and setting the conf file contents to default values
bool systemReset_menu()
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
                    randNum = 1000000 + (rand() % 9000000);
                    cout << randNum << " : ";
                    cin >> compareNum;

                    if (compareNum != randNum)
                    {
                        cout << "The pin you provided does not match. Returning to the main menu." << endl;
                        return false;
                    }
                    //change the value of the startup.conf file and return string true
                    ofstream outFile {"startup.conf"};
                    if(!outFile.is_open())
                    {
                        cout << "Error: Could not process config file. Reset aborted." << endl;
                        return false;
                    }
                    //set init value of
                    outFile << "true";

                    //delete array storage files
                    if(remove("users.txt") != 0 || remove("addresses.txt") != 0)
                    {
                        cout << "Could not delete one or more files.";
                        return false;
                    }
                    return true;
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

int main()
{
    //set seed for random generation
    srand(time(0));

    //declare arrays to store users and ip addresses, and config object containing configuration functions
    User arrUsers[100];
    Config file_manager;
    string arrAddresses[254], dnsServer, dhcpServer, router_address = "192.168.0.1";
    //declare utility varialbles
    int privilege = 0, numUsers = 0, numAddresses = 0;
    bool isReset = false;

    //call the read_conf function to get the first startup variable
    bool isFirstStartup = file_manager.read_files(arrUsers, numUsers, arrAddresses, numAddresses, dnsServer, dhcpServer);

    //if the conf file does not exist or contains true the first startup function will be called
    if (!isFirstStartup)
    {
        privilege = user_login(arrUsers, numUsers);
    }
    else
    {
        privilege = user_setup(arrUsers, numUsers, dnsServer, dhcpServer);
    }

    if (privilege == -1)
    {
        //end the program
        return -1;
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
                serverAddress_menu("DNS", dnsServer);
                break;
            case 2:
                serverAddress_menu("DHCP", dhcpServer);
                break;
            case 3:
                staticAddress_menu(arrAddresses, numAddresses);
                break;
            case 4:
                //checks if user has required privileges
                if (privilege == 0)
                {
                    userManagement_menu(arrUsers, numUsers);
                }
                else
                {
                    cout << "Error: Access denied." << endl;
                }
                break;
            case 5:
                //checks if user has required privileges
                if (privilege == 0)
                {
                    if(systemReset_menu())
                    {
                        isReset = true;
                        option = 0;
                    }
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
    if (isReset == false)
    {
        file_manager.save_files(arrUsers, numUsers, arrAddresses, numAddresses, isFirstStartup, dnsServer, dhcpServer);
        cout << "Saving files" << endl;
    }

    return 0;
}
