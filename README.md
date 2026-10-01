# C Phone Book Management System

## Project Overview

The **C Phone Book Management System** is a console-based application developed in C programming language for managing contact information.

The application allows users to create, view, search, edit, delete, save, and reload contacts. Each contact can contain multiple phone numbers, an email address, and a physical address.

The project demonstrates important C programming concepts including **structures, pointers, dynamic memory allocation, linked lists, string handling, functions, file handling, and memory management**.

---

## Features

* Create a new contact
* Store multiple phone numbers for a contact
* Store email address
* Store physical address
* Display all contacts
* Search for a contact by name
* Delete a contact
* Edit an existing contact
* Add, change, and delete individual phone numbers
* Change or remove email address
* Change or remove address
* Save contacts to a file
* Automatically load saved contacts when the application starts
* Automatically save contacts before exiting
* Dynamic memory allocation
* Duplicate contact-name checking
* Memory cleanup before program termination

---

## Technologies Used

* **Programming Language:** C
* **Compiler:** GCC
* **Debugger:** GDB
* **Development Environment:** Visual Studio Code
* **Data Storage:** Binary file
* **Operating System:** Windows

---

## C Concepts Demonstrated

This project demonstrates several important C programming concepts:

### Structures

A `Contact` structure is used to store contact information such as name, phone numbers, email, address, and the pointer to the next contact.

### Linked List

Contacts are maintained using a singly linked list.

```c
struct Contact *next;
```

The global `head` pointer stores the beginning of the contact list.

### Dynamic Memory Allocation

The project uses:

* `malloc()`
* `realloc()`
* `free()`

Dynamic allocation is used for contacts and multiple phone numbers.

### Pointers

Pointers are used extensively for:

* Linked-list traversal
* Dynamic memory
* Phone-number arrays
* Passing contacts to functions

### File Handling

Contacts are stored in a binary file:

```text
phonebook.dat
```

The application uses:

* `fopen()`
* `fwrite()`
* `fread()`
* `fclose()`

### String Handling

The project uses functions such as:

* `strlen()`
* `strcmp()`
* `strcpy()`
* `strcspn()`
* `fgets()`

---

## Contact Information

Each contact can contain:

* Name
* One or more phone numbers
* Email address
* Physical address

The phone-number implementation uses a dynamically allocated array, allowing each contact to have multiple phone numbers.

---

## Main Menu

When the application starts, the following operations are available:

```text
c/C : Create a new contact
p/P : Print all contacts
d/D : Delete contact
f/F : Find contact
e/E : Edit a contact
s/S : Save contacts
q/Q : Quit
```

---

## Contact Editing

The edit functionality provides options to:

```text
1. Edit name
2. Edit phone numbers
3. Edit email
4. Edit address
5. Show contact
6. Finish editing
```

Phone-number editing provides:

```text
1. Add phone number
2. Change phone number
3. Delete phone number
4. Show phone numbers
5. Back
```

---

## Data Persistence

The application stores contact information in:

```text
phonebook.dat
```

Contacts can be saved manually using:

```text
s/S : Save contacts
```

The application also automatically saves the contacts when the user selects:

```text
q/Q : Quit
```

Previously saved contacts are loaded automatically when the program starts.

---

## How to Compile

Make sure GCC is installed and available in the terminal.

Open the project directory:

```powershell
cd "C:\Users\B.MAHANTH\Desktop\C-PhoneBook-Management-System"
```

Compile the program:

```powershell
gcc -g phonebook.c -o phonebook.exe
```

The `-g` option adds debugging information for GDB and VS Code debugging.

---

## How to Run

After successful compilation:

```powershell
.\phonebook.exe
```

The Phone Book application will start in the terminal.

---

## Example Workflow

### Create a Contact

Select:

```text
c
```

Enter the contact name and phone number.

You can optionally add:

* Additional phone numbers
* Email
* Address

### Search

Select:

```text
f
```

Enter the contact name to search for the contact.

### Edit

Select:

```text
e
```

Enter the contact name and select the information that needs to be modified.

### Delete

Select:

```text
d
```

Enter the contact name to remove the contact.

### Save

Select:

```text
s
```

The contacts are stored in the binary data file.

### Exit

Select:

```text
q
```

The application saves the contacts and releases allocated memory before closing.

---

## Project Structure

```text
C-PhoneBook-Management-System/
│
├── phonebook.c
├── README.md
└── phonebook.dat
```

`phonebook.dat` is generated by the application when contacts are saved.

---

## Memory Management

The project carefully manages dynamically allocated memory.

When a contact is deleted, its dynamically allocated phone numbers and contact memory are released.

Before the application terminates, all contacts are released from memory.

---

## Future Improvements

Possible future enhancements include:

* Contact sorting
* Search by phone number
* Search by email
* Phone-number validation
* Email validation
* Import/export functionality
* Improved user interface
* Contact groups
* Password protection
* CSV export
* Backup and restore functionality

---

## Project Objective

The main objective of this project is to develop a practical C application while applying fundamental and intermediate C programming concepts to a real-world contact-management problem.

---

## Author

**Birakayala Mahanth**

B.Tech – Electronics and Communication Engineering

---

## License

This project is intended for educational and learning purposes.
