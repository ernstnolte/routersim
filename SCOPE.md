# Router Simulator Scope
This project aims to recreate the interface of a router cli using methods and best practice both learned during participation in CMPG121 and while researching approaches required by the project brief.

### The following functions of a typical network router will be replicated
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

### Meeting Requirements
- **Arrays** will be used to store users and IP addresses added during the runtime of the program. When a user/ip address is added/removed it will be done using arrays.
- A **Class** will be used to define a template for users and possibly functions associated with creating and removing users.
- **Functions** for each main option inside the main menu will be defined, namely:
  - Handling users
  - Resetting the system
  - Handling IP addresses (static and server addresses)
  - Validation of IP addresses
  - Reading from and writing to files etc.
- **File Handling** can be implemented to save configuration of the router, for example the DNS and DHCP server IP addresses, database of users and passwords.
- **Smart Pointers** will likely be used when variables are required by certain functions, like the add/remove users functions, to directly change the values inside arrays without duplication of variables in memory.
