# C PHONE BOOK MANAGEMENT SYSTEM

## 1. Project Title

**C Phone Book Management System**

## 2. Project Description

The C Phone Book Management System is a console-based application developed using the **C programming language**. The project is designed to manage contact information efficiently through a simple menu-driven interface.

The system allows the user to create, view, search, edit, and delete contacts. Each contact can contain multiple phone numbers along with an email address and physical address.

The project also implements **file handling** to store contact information permanently. When the application is closed, the contact information can be saved into a binary file. When the application is started again, the previously saved contacts can be loaded automatically.

The project demonstrates important C programming concepts such as structures, pointers, linked lists, dynamic memory allocation, string handling, functions, and file handling.

---

## 3. Objective

The main objective of this project is to develop a reliable and user-friendly phone book application using core C programming concepts.

The project is intended to provide practical implementation of:

* Structures
* Pointers
* Dynamic memory allocation
* Linked lists
* Functions
* String manipulation
* File handling
* Menu-driven programming
* Memory management
* Input handling
* Searching and editing operations

---

## 4. Technologies and Tools Used

### Programming Language

**C Programming Language**

The complete application logic is implemented in C.

### Compiler

**GCC (GNU Compiler Collection)**

GCC is used to compile the C source code and generate the executable program.

### Debugger

**GDB (GNU Debugger)**

GDB can be used to debug the program, inspect variables, trace execution, and identify runtime problems.

### Development Environment

**VS Code is not considered part of the project technology requirements.**

The project is a standard C application and can be compiled using GCC in a suitable terminal or C development environment.

### Data Storage

The application uses a **binary file** named:

```text
phonebook.dat
```

The file stores contact information so that data can be retained between program executions.

---

## 5. Main Features

The application provides the following major features:

### 5.1 Create Contact

The user can create a new contact by entering:

* Name
* One or more phone numbers
* Email address
* Address

The application checks whether the contact name is already present before creating a new contact.

A contact must have a valid non-empty name and at least one phone number.

---

### 5.2 View Contacts

The system can display all contacts stored in the phone book.

For every contact, the application displays:

* Contact name
* All phone numbers
* Email address
* Physical address

If an email address or address is not available, the application displays:

```text
Not available
```

---

### 5.3 Find Contact

The Find operation allows the user to search for a contact using the contact name.

The program searches through the linked list and compares the entered name with stored contact names.

If the contact exists, its complete information is displayed.

If the contact does not exist, an appropriate message is displayed.

---

### 5.4 Delete Contact

The Delete operation removes a contact from the phone book.

The program searches for the specified contact and removes the corresponding node from the linked list.

The memory associated with the contact is also released.

The operation supports deletion of:

* The first contact
* A middle contact
* The last contact
* The only contact in the list

---

### 5.5 Edit Contact

The Edit operation allows existing contact information to be modified.

The user can edit:

* Name
* Phone numbers
* Email address
* Physical address

The phone number section provides additional operations such as:

* Add phone number
* Change phone number
* Delete phone number
* Display phone numbers

---

### 5.6 Multiple Phone Numbers

The project supports storing multiple phone numbers for a single contact.

For example:

```text
Name: Rahul

Phone 1: 9876543210
Phone 2: 9123456780
Phone 3: 9000000000
```

The phone numbers are stored dynamically using dynamically allocated memory.

This avoids fixing the number of phone numbers that a contact can have.

---

### 5.7 Save Contacts

The Save operation stores the current phone book information into:

```text
phonebook.dat
```

The application writes the contact information to the binary file.

The saved information includes:

* Number of contacts
* Contact names
* Number of phone numbers
* Phone numbers
* Email addresses
* Physical addresses

---

### 5.8 Load Contacts

When the application starts, it attempts to load previously saved contact information from:

```text
phonebook.dat
```

This provides data persistence.

For example:

```text
Program Run 1
     ↓
Create contacts
     ↓
Save
     ↓
phonebook.dat
     ↓
Program closes
     ↓
Program Run 2
     ↓
Load contacts
     ↓
Previous contacts available
```

---

## 6. Data Structure Used

The project uses a structure named:

```c
struct Contact
```

The structure contains:

```c
char name[NAME_SIZE];
char **phone;
int phone_count;
char email[EMAIL_SIZE];
char address[ADDRESS_SIZE];
struct Contact *next;
```

### Name

```c
char name[NAME_SIZE];
```

Stores the contact name.

### Phone

```c
char **phone;
```

A dynamically allocated array of character pointers is used to store multiple phone numbers.

### Phone Count

```c
int phone_count;
```

Stores the number of phone numbers belonging to the contact.

### Email

```c
char email[EMAIL_SIZE];
```

Stores the email address.

### Address

```c
char address[ADDRESS_SIZE];
```

Stores the physical address.

### Next Pointer

```c
struct Contact *next;
```

Stores the address of the next contact in the linked list.

---

## 7. Linked List Implementation

The project uses a **singly linked list** to maintain the contacts.

The global pointer:

```c
struct Contact *head = NULL;
```

points to the first contact.

The basic structure is:

```text
head
 ↓
[Contact 1] → [Contact 2] → [Contact 3] → NULL
```

Each contact contains a `next` pointer that points to the next contact.

This allows contacts to be dynamically added and removed during program execution.

---

## 8. Dynamic Memory Allocation

Dynamic memory allocation is an important part of the project.

Memory is dynamically allocated when:

* A new contact is created
* A new phone number is added
* Contacts are loaded from the file

The project uses functions such as:

```c
malloc()
```

and

```c
realloc()
```

to manage memory dynamically.

Memory is released using:

```c
free()
```

when contacts or phone numbers are deleted.

---

## 9. Memory Management

The project includes dedicated memory-management functions.

The contact memory is released when a contact is deleted.

The phone numbers belonging to that contact are also released.

When the program exits, all remaining contacts are freed.

The general process is:

```text
Contact
   ↓
Phone Pointer Array
   ↓
Individual Phone Strings
```

All dynamically allocated memory must be released in the reverse logical hierarchy.

This prevents unnecessary memory usage and helps avoid memory leaks.

---

## 10. File Handling

The project uses binary file handling for persistent storage.

The file name is:

```text
phonebook.dat
```

The file is opened in binary write mode when saving:

```c
fopen(FILE_NAME, "wb");
```

The file is opened in binary read mode when loading:

```c
fopen(FILE_NAME, "rb");
```

The project uses functions such as:

```c
fopen()
fwrite()
fread()
fclose()
```

for file operations.

---

## 11. Program Flow

The overall program execution is:

```text
Start Program
      ↓
Load Existing Contacts
      ↓
Display Main Menu
      ↓
User Selects Operation
      ↓
Create / Print / Find / Edit / Delete / Save
      ↓
Return to Main Menu
      ↓
User Selects Quit
      ↓
Save Contacts
      ↓
Free Allocated Memory
      ↓
Exit Program
```

---

## 12. Main Menu

The application provides the following main menu operations:

```text
C/c : Create contact
P/p : Print contacts
D/d : Delete contact
F/f : Find contact
E/e : Edit contact
S/s : Save contacts
Q/q : Quit
```

The user can select an operation using either uppercase or lowercase characters.

---

## 13. Create Contact Flow

The contact creation process follows these steps:

```text
Select Create
      ↓
Enter Name
      ↓
Check Empty Name
      ↓
Check Duplicate Name
      ↓
Enter First Phone Number
      ↓
Ask for Additional Phone Numbers
      ↓
Enter Email
      ↓
Enter Address
      ↓
Create Linked List Node
      ↓
Add Contact to Phone Book
```

---

## 14. Edit Contact Flow

When the user selects Edit:

```text
Select Edit
      ↓
Enter Contact Name
      ↓
Search Contact
      ↓
Display Edit Menu
      ↓
Edit Name
Edit Phone Numbers
Edit Email
Edit Address
      ↓
Return to Main Menu
```

The phone number editing section provides additional options for managing multiple phone numbers.

---

## 15. Delete Contact Flow

The delete operation works as follows:

```text
Enter Contact Name
      ↓
Search Linked List
      ↓
Contact Found?
    /       \
  Yes        No
   ↓          ↓
Remove Node  Display Error
   ↓
Free Memory
   ↓
Return to Menu
```

The linked-list pointers are updated after removing the contact.

---

## 16. Search Mechanism

The project uses string comparison to find contacts.

The contact name entered by the user is compared with stored names.

The search is based on an exact name match.

The search function traverses the linked list until:

* The required contact is found, or
* The end of the list is reached.

---

## 17. Input Handling

The application includes input-handling functions to safely read user input.

The input buffer is cleared where necessary to prevent leftover characters from affecting subsequent input operations.

String input is handled using a dedicated function:

```c
read_string()
```

This allows the program to read complete strings containing spaces, such as:

```text
Birakayala Mahanth
```

or:

```text
Hyderabad, Telangana
```

---

## 18. Error Handling

The project performs several basic validation checks.

Examples include:

* Empty contact name
* Duplicate contact name
* Empty first phone number
* Contact not found
* Invalid contact data while loading
* Memory allocation failure
* File opening failure
* Invalid menu choice

These checks help prevent the application from continuing with invalid data.

---

## 19. Data Persistence

Data persistence is one of the important features of this project.

Without file storage, all contacts would disappear when the program terminates.

This project stores the contacts in:

```text
phonebook.dat
```

Therefore:

```text
Create Contact
       ↓
Save Contact
       ↓
phonebook.dat
       ↓
Close Program
       ↓
Open Program Again
       ↓
Load Contact
       ↓
Contact Available Again
```

---

## 20. Compilation

The program can be compiled using GCC.

Use:

```bash
gcc -g phonebook.c -o phonebook.exe
```

The `-g` option includes debugging information, which can be useful when debugging the program with GDB.

---

## 21. Program Execution

After successful compilation, run the executable using:

```bash
phonebook.exe
```

or on PowerShell:

```powershell
.\phonebook.exe
```

---

## 22. Testing Performed

The following functional areas should be tested:

### Test 1 – Create Contact

Verify that a new contact can be created with:

* Name
* Phone number
* Email
* Address

### Test 2 – Multiple Phone Numbers

Verify that multiple phone numbers can be added to one contact.

### Test 3 – Print Contacts

Verify that all stored contact information is displayed correctly.

### Test 4 – Find Contact

Verify that an existing contact can be searched using its name.

### Test 5 – Find Non-existing Contact

Verify that an appropriate message is displayed when the contact does not exist.

### Test 6 – Edit Name

Verify that the contact name can be changed.

### Test 7 – Edit Phone Number

Verify that existing phone numbers can be changed.

### Test 8 – Add Phone Number

Verify that a new phone number can be added.

### Test 9 – Delete Phone Number

Verify that a selected phone number can be removed.

### Test 10 – Edit Email

Verify that the email address can be changed or removed.

### Test 11 – Edit Address

Verify that the address can be changed or removed.

### Test 12 – Delete Contact

Verify that a complete contact can be removed.

### Test 13 – Save

Verify that contacts are written to `phonebook.dat`.

### Test 14 – Reload

Close and restart the application and verify that previously saved contacts are loaded.

### Test 15 – Quit

Verify that the application saves the phone book and releases allocated memory before termination.

---

## 23. Concepts Demonstrated

This project provides practical implementation of the following C programming concepts:

1. Variables and data types
2. Constants
3. Functions
4. Function parameters
5. Structures
6. Structure pointers
7. Character arrays
8. Strings
9. Pointers
10. Pointer-to-pointer concepts
11. Dynamic memory allocation
12. `malloc()`
13. `realloc()`
14. `free()`
15. Singly linked lists
16. Linked-list traversal
17. Node insertion
18. Node deletion
19. String comparison
20. File handling
21. Binary files
22. `fopen()`
23. `fread()`
24. `fwrite()`
25. `fclose()`
26. Input-buffer handling
27. Menu-driven programming
28. Error handling
29. Memory cleanup

---

## 24. Advantages

* Simple console-based interface
* Supports multiple phone numbers
* Uses dynamic memory allocation
* Uses a linked-list data structure
* Supports complete contact management
* Provides persistent storage
* Demonstrates practical C programming concepts
* Includes memory cleanup
* Supports editing of individual contact fields

---

## 25. Current Limitations

The current implementation has some limitations:

* Search uses exact contact-name matching.
* Phone-number format validation is limited.
* Email-format validation is limited.
* The storage format is a custom binary format.
* The application is console based.
* The binary data file is intended for use with the same program structure and environment.

---

## 26. Possible Future Improvements

The project can be extended with:

* Case-insensitive search
* Partial-name search
* Phone-number validation
* Email validation
* Sorting contacts alphabetically
* Search by phone number
* Export to CSV
* Import from CSV
* Password protection
* Contact categories
* Favorite contacts
* Improved user interface
* Cross-platform improvements
* More robust file-format validation

---

## 27. Learning Outcomes

After completing this project, the following practical skills are demonstrated:

* Designing a menu-driven C application
* Working with structures
* Creating and managing linked lists
* Using pointers effectively
* Allocating and freeing dynamic memory
* Managing multiple dynamically allocated strings
* Implementing CRUD operations
* Working with binary files
* Maintaining data persistence
* Handling user input
* Implementing validation
* Debugging C programs
* Organizing a medium-sized C source file

---

## 28. Conclusion

The **C Phone Book Management System** demonstrates how fundamental C programming concepts can be combined to develop a practical application.

The project implements contact creation, viewing, searching, editing, deletion, and persistent storage. The use of structures, linked lists, pointers, dynamic memory allocation, and file handling provides practical experience with important programming concepts used in systems and embedded software development.

The project also demonstrates the importance of proper memory management and structured program design when developing applications in C.

---

## 29. Project Files

The project can contain the following files:

```text
C-PhoneBook-Management-System/
│
├── phonebook.c
├── README.md
└── .gitignore
```

During program execution, the application may generate:

```text
phonebook.dat
```

The `phonebook.dat` file contains the application's saved contact data.

---

## 30. Project Author

**Name:** Birakayala Mahanth

**Qualification:** B.Tech – Electronics and Communication Engineering

**Project:** C Phone Book Management System

**Programming Language:** C

**Compiler:** GCC

---

## 31. Final Project Summary

The **C Phone Book Management System** is a practical C programming project that demonstrates:

```text
Structures
    +
Pointers
    +
Dynamic Memory
    +
Linked Lists
    +
File Handling
    +
String Handling
    +
CRUD Operations
    +
Input Validation
    +
Memory Management
    =
Complete Phone Book Management System
```

The project is suitable for demonstrating fundamental C programming, data structures, memory management, and file-handling skills in an academic or technical project submission.
