## Pseudocode
The router simulator program can be broken down into phases that always follow this order:
- Configuration
- Setup
- Login
- Data Malipulation
- Save & Logout

### Configuration
When the program starts it firstly defines a class User that will act as a template for user creation. Then it declares a boolean isFirstStart, 2 strings dnsAddress and dhcpAddress, an array arrUsers that is defined by the User class, and another array arrStaticAddresses to store static IP addresses.

After that the program checks if a file called startup.conf exists and if it does not if will create it and write "true" to the first line of the file.

Then the value of the first line is assigned to a string confString. If the string is "true" the variable *isFirstStartup* will be assigned the boolean value *true*, if it is "false" it will be assigned the value *false*.

The program will also check if files called users.txt and addresses.txt exist and create them if they don't. If they do exist, the program will loop through them until the end of the files are reached and assign the values in users.txt to the arrUsers array, and the values in the addresses.txt in the arrStaticAddresses array.

At the end the program will clear the screen to make space for the next phase of the program.


### Setup
If the value of *isFirstStartup* is true, then the program will call the first_startup function. It asks the user to create a password for the admin user and stores it to the first index of the arrUsers array. Then it asks the user to create an IP address for the router and stores it in the string variable routerAddress. The function then returns int 0 which the program will assign to a variable int privilege. At the end the program will clear the screen to make space for the next phase of the program.

### Login
If the value of *isFirstStartup* is false, the the program will call the login_user function. It asks the user to enter a username and assigns it to a variable string username, and a password and assigns it to a string password. Then the variables are compared with each entry in arrUsers.username and  arrUsers.password to find a match. If a match is not found the program will end operation and close. If a match is found the value of the corresponding arrUsers.privilege entry will be returned which the program will assign to the int privilege variable. At the end the program will clear the screen to make space for the next phase of the program.

### Data Manipulation
A menu will appear prompting the user to select from the following options: static addresses, dns server, dhcp server, user management and reset system. When the user enters 0 as their option the program will exit, save arrUsers, arrStaticAddresses, dnsServer and dhcpServer, and end operation.
A while loop that that ends when the user enters 0 will handle the above part of the program as well as contain a switch-case that will handle the menu options.

#### Static Addresses
If the user enters 1, the program will loop through the entries in arrStaticAddresses and output a numbered list of all static IP addresses followed by menu options: add an address, remove an address and return to main menu. A switch-case will handle the user selections.

**If the user selects option 1** they will be prompted to enter an IP address to add. A separate function will validate the user input and prompt for re-entry if it is incorrect. If it is correct the ip address will be appended to arrStaticAddresses and the Static Address menu will reappear with an updated list of static addresses.
**If the user selects option 2** they will be prompted to enter the number of the IP address they want to remove. The program will then remove the IP address with the corresponding index from arrStaticAddresses. The previous menu will then reappear with an updated list of static addresses.
**If the user selects option 0** they will exit the switch-case and return to the main menu.
**If an invalid option is selected** it will be handled by a **default case** and the user will be asked to select a valid option.

#### DNS Server



