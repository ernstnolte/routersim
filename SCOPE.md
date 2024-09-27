# Router Simulator Scope
This project aims to recreate the interface of a router cli and will be written in C++.

**The following functions will be replicated**
- Basic user management
  - the program will allow you to log in as a user, of which there will be 2 types (admin / user). Each type will have different permission levels. Admin will be allowed to change any settings, but normal user can not add or remove users, or reset the router simulator.
  - A database of existing users will be stored in an array and saved to a text file upon program end.
- IP Address Management
  - The user will be able to add and remove static IP addresses that will be validated using a program-defined function.
  - There will also be options to change the DNS and DHCP servers of the network within the router settings.
- Login / Setup Functions
  - If the user starts the program for the first time, they will be prompted to create a password for the admin user and set the IP addresses for the DNS and DHCP servers.
  - After that they will be sent to the main menu logged in as admin.
  - If the user runs the program again, they will have to log in using a username and password
- System Reset Function
  - The user will be allowed to reset the system as a menu option, which will set everything to default.
  - When the program is opened again the user will be prompted with the setup screen once again.
