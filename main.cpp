#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool read_conf();           //complete
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

    if (isFirstStartup)
    {
        first_startup();
    }

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

void staticAddress_menu() {

}

void dns_menu() {

}

void dhcp_menu() {

}

void user_management() {

}

void reset_system() {

}

