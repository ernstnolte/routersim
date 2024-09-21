## Program Scope
This project aims to recreate the interface of a router cli and is coded in C++. 
I chose to write my code using the JetBrains Clion IDE for the following reasons:
-- easy connection to git repository
-- more modern interface compared to alternatives like Codeblocks
-- easy setup of compiler

### The following functions will be replicated
- basic user management
  + create / delete
- permission levels
  + admin / user / guest
  + represented by integers
- ip address management
  + router / dns server / static
  + validation of ip addresses

### First startup
- a .conf file will be created if it does not already exist which will
    + set the **first startup bool** variable to **true**
- the first time the program will run will open to an initial setup screen where:
    + the user will set the admin password
    + the user will set the router ip address
- **after completion** of the setup process the **first startup bool** will be set to **false**


