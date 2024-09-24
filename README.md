# Program Scope
This project aims to recreate the interface of a router cli and is coded in C++. 
I chose to write my code using the JetBrains Clion IDE for the following reasons:
-- easy connection to git repository
-- more modern interface compared to alternatives like Codeblocks
-- easy setup of compiler

## The following functions will be replicated
- basic user management
  + create / delete
- permission levels
  + admin / user / guest
  + represented by integers
- ip address management
  + router / dns server / static
  + validation of ip addresses

## First startup
- a .conf file will be created if it does not already exist which will
    + set the **first startup bool** variable to **true**
- the first time the program will run will open to an initial setup screen where:
    + the user will set the admin password
    + the user will set the router ip address
- **after completion** of the setup process the **first startup bool** will be set to **false**

## Typical Program Flow
### User will be faced with a login message and be prompted for a username and password.
    + both the username and password inputs will be received before logical operation for security reasons.
    + validation will not be enforced for security reasons.
### User inputs username and password.
    Both are checked against an array that stores existing usernames and passwords (hashed to enforce security).
    + pass -> user is given an integer value as a permission level
           -> user is taken to the main menu
    + fail -> user is shown an error message
           -> program operation ends
### Main Menu
    5 Options handled by a switch:
      1. DNS server
      2. DHCP server
      3. Static IP addresses
      4. User Management
      5. Reset (admin only)
      default:
        An invalid input message will be displayed and user will be prompted to re-enter a correct option
#### 1. DNS server
    The currently configured IP addresses of the DNS servers will be displayed followed by
    3 options handled by a do-while loop:
      1. Change main server
      2. Change secondary server
      0. Return to main menu
    *a switch-case might be a better implementation
#### 2. DHCP server
    The currently configured IP address of the DHCP server will be displayed followed by
    2 options handled by a do-while loop:
      1. Change server
      0. Return to main menu
<sub>the dhcp and dns server menus will use the same function to edit the addresses with the function call requiring the server address to change</sub>

#### 3. Static IP addresses
    All static ip addresses will be displayed (if any are present) in a table followed by
    3 options handled by a switch-case
      1. Add address
      2. Remove address
      0. Return to main menu
    *a switch-case might be a better implementation
#### 4. User Management (admin only)
    + Users management will only be available for admin level users.
    + sers with insufficient privilege will be returned to the main menu with an error message
    A table of all users will be displayed in a table with ID, Username, Privilege Level properties followed by
    4 options handled by a switch-case
      1. Add a user
        username -> password -> privilege level
      2. Remove a user
        + admin user cannot be deleted
      3. Change admin password
        old password -> new password -> confirm new password
      0. Return to main menu
#### 5. Reset Router (admin only)
    User is prompted to reset the routher
    User is prompted to enter a randomly generated string that is shown on screen to confirm
    first startup bool is set to false and saved to config file
    program operation ends
    
