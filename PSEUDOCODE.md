## Pseudocode
The router simulator program can be broken down into phases that always follow this order:
- Configuration
- Setup
- Login
- Data Malipulation
- Save & Logout

### Configuration
When the program start it firstly defines a class User that will act as a template for user creation. Then it declares a boolean isFirstStart, 2 strings dnsAddress and dhcpAddress, an array arrUsers that is defined by the User class, and another array arrStaticAddresses to store static IP addresses.

After that the program checks if a file called startup.conf exists and if it does not if will create it and write "true" to the first line of the file.

Then the value of the first line is assigned to a string confString. If the string is "true" the variable *isFirstStartup* will be assigned the boolean value *true*, if it is "false" it will be assigned the value *false*.

The program will also check if files called users.txt and addresses.txt exist and create them if they don't. If they do exist, the program will loop through them until the end of the files are reached and assign the values in users.txt to the arrUsers array, and the values in the addresses.txt in the arrStaticAddresses array.


### Setup
If the value of *isFirstStartup* is true, then the program will call the first_startup function. It asks the user to create a password for the admin user and stores it to the first index of the arrUsers array. Then it asks the user to create an IP address for the router and stores it in the string variable routerAddress. The function then returns int 0 which the program will assign to a variable int privilege.

### Login
If the value of *isFirstStartup* is false, the the program will call the login_user function. It asks the user to enter a username and assigns it to a variable string username, and a password and assigns it to a string password. Then the variables are compared with each entry in arrUsers.username and  arrUsers.password to find a match. If a match is not found the program will end operation and close. If a match is found the value of the corresponding arrUsers.privilege entry will be returned which the program will assign to the int privilege variable.

### Data Manipulation


