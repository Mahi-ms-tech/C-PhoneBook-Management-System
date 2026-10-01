#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   CONSTANTS
   ========================================================= */

#define NAME_SIZE       50
#define PHONE_SIZE      20
#define EMAIL_SIZE      100
#define ADDRESS_SIZE    150

#define FILE_NAME       "phonebook.dat"


/* =========================================================
   CONTACT STRUCTURE
   ========================================================= */

struct Contact
{
    char name[NAME_SIZE];

    /*
       Dynamic array of phone numbers.

       phone
       |
       +----> phone[0] ---> "9390453115"
       |
       +----> phone[1] ---> "8888888888"
       |
       +----> phone[2] ---> "7777777777"
    */

    char **phone;

    int phone_count;

    char email[EMAIL_SIZE];

    char address[ADDRESS_SIZE];

    /*
       Pointer to next contact.
    */

    struct Contact *next;
};


/* =========================================================
   GLOBAL HEAD POINTER
   ========================================================= */

struct Contact *head = NULL;


/* =========================================================
   FUNCTION DECLARATIONS
   ========================================================= */

/* Input functions */
void clear_input_buffer(void);
void read_string(char *str, int size);

/* Contact search */
struct Contact *find_contact_by_name(const char *name);
int contact_exists(const char *name);

/* Phone functions */
int add_phone(struct Contact *contact, const char *number);
int change_phone(struct Contact *contact);
int delete_phone(struct Contact *contact);
void edit_phone_numbers(struct Contact *contact);

/* Contact operations */
void create_contact(void);
void print_one_contact(struct Contact *contact);
void print_contacts(void);
void find_contact(void);
void delete_contact(void);
void edit_contact(void);

/* Edit functions */
void edit_name(struct Contact *contact);
void edit_email(struct Contact *contact);
void edit_address(struct Contact *contact);

/* File operations */
void save_contacts(void);
void load_contacts(void);

/* Memory */
void free_contact(struct Contact *contact);
void free_all_contacts(void);


/* =========================================================
   CLEAR INPUT BUFFER
   ========================================================= */

void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Remove remaining characters */
    }
}


/* =========================================================
   READ STRING
   ========================================================= */

void read_string(char *str, int size)
{
    if (fgets(str, size, stdin) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
    }
    else
    {
        str[0] = '\0';
    }
}


/* =========================================================
   FIND CONTACT BY NAME
   ========================================================= */

struct Contact *find_contact_by_name(const char *name)
{
    struct Contact *temp;

    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}


/* =========================================================
   CHECK WHETHER CONTACT EXISTS
   ========================================================= */

int contact_exists(const char *name)
{
    if (find_contact_by_name(name) != NULL)
    {
        return 1;
    }

    return 0;
}


/* =========================================================
   ADD PHONE NUMBER
   ========================================================= */

int add_phone(struct Contact *contact, const char *number)
{
    char **temp;

    /*
       Increase pointer-array size by one.
    */

    temp = realloc(
        contact->phone,
        (contact->phone_count + 1) * sizeof(char *)
    );

    if (temp == NULL)
    {
        return 0;
    }

    contact->phone = temp;

    /*
       Allocate memory for the new phone string.
    */

    contact->phone[contact->phone_count] =
        malloc(strlen(number) + 1);

    if (contact->phone[contact->phone_count] == NULL)
    {
        return 0;
    }

    /*
       Copy phone number.
    */

    strcpy(
        contact->phone[contact->phone_count],
        number
    );

    contact->phone_count++;

    return 1;
}


/* =========================================================
   CREATE CONTACT
   ========================================================= */

void create_contact(void)
{
    struct Contact *new_contact;
    struct Contact *temp;

    char number[PHONE_SIZE];
    char choice;

    /*
       Allocate memory for contact.
    */

    new_contact = malloc(sizeof(struct Contact));

    if (new_contact == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    /*
       Initialize contact.
    */

    new_contact->phone = NULL;
    new_contact->phone_count = 0;
    new_contact->email[0] = '\0';
    new_contact->address[0] = '\0';
    new_contact->next = NULL;

    /*
       Get name.
    */

    printf("\nEnter contact name: ");
    read_string(new_contact->name, NAME_SIZE);

    if (strlen(new_contact->name) == 0)
    {
        printf("Name cannot be empty.\n");

        free(new_contact);

        return;
    }

    /*
       Check duplicate.
    */

    if (contact_exists(new_contact->name))
    {
        printf("Contact already exists.\n");

        free(new_contact);

        return;
    }

    /*
       First phone number.
    */

    while (1)
    {
        printf("Enter first phone number: ");

        read_string(number, PHONE_SIZE);

        if (strlen(number) == 0)
        {
            printf("Phone number cannot be empty.\n");
            continue;
        }

        break;
    }

    /*
       Add first phone number.
    */

    if (add_phone(new_contact, number) == 0)
    {
        printf("Unable to allocate memory for phone number.\n");

        free(new_contact);

        return;
    }

    /*
       Add additional phone numbers.
    */

    while (1)
    {
        printf("Do you want to add another phone number? (y/n): ");

        scanf(" %c", &choice);

        clear_input_buffer();

        if (choice == 'y' || choice == 'Y')
        {
            printf("Enter phone number: ");

            read_string(number, PHONE_SIZE);

            if (strlen(number) == 0)
            {
                printf("Phone number cannot be empty.\n");
                continue;
            }

            if (add_phone(new_contact, number) == 0)
            {
                printf("Unable to add phone number.\n");
                break;
            }
        }
        else if (choice == 'n' || choice == 'N')
        {
            break;
        }
        else
        {
            printf("Please enter y or n.\n");
        }
    }

    /*
       Email.
    */

    printf("Do you want to add email? (y/n): ");

    scanf(" %c", &choice);

    clear_input_buffer();

    if (choice == 'y' || choice == 'Y')
    {
        printf("Enter email: ");

        read_string(new_contact->email, EMAIL_SIZE);
    }

    /*
       Address.
    */

    printf("Do you want to add address? (y/n): ");

    scanf(" %c", &choice);

    clear_input_buffer();

    if (choice == 'y' || choice == 'Y')
    {
        printf("Enter address: ");

        read_string(new_contact->address, ADDRESS_SIZE);
    }

    /*
       Insert into linked list.
    */

    if (head == NULL)
    {
        head = new_contact;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_contact;
    }

    printf("\nContact created successfully.\n");
}


/* =========================================================
   PRINT ONE CONTACT
   ========================================================= */

void print_one_contact(struct Contact *contact)
{
    int i;

    printf("\n========================================\n");

    printf("Name    : %s\n", contact->name);

    printf("Phone Numbers:\n");

    if (contact->phone_count == 0)
    {
        printf("  No phone numbers\n");
    }
    else
    {
        for (i = 0; i < contact->phone_count; i++)
        {
            printf("  %d. %s\n",
                   i + 1,
                   contact->phone[i]);
        }
    }

    if (strlen(contact->email) > 0)
    {
        printf("Email   : %s\n",
               contact->email);
    }
    else
    {
        printf("Email   : Not available\n");
    }

    if (strlen(contact->address) > 0)
    {
        printf("Address : %s\n",
               contact->address);
    }
    else
    {
        printf("Address : Not available\n");
    }

    printf("========================================\n");
}


/* =========================================================
   PRINT ALL CONTACTS
   ========================================================= */

void print_contacts(void)
{
    struct Contact *temp;

    if (head == NULL)
    {
        printf("\nPhone Book is empty.\n");
        return;
    }

    temp = head;

    while (temp != NULL)
    {
        print_one_contact(temp);

        temp = temp->next;
    }
}


/* =========================================================
   FIND CONTACT
   ========================================================= */

void find_contact(void)
{
    char name[NAME_SIZE];

    struct Contact *contact;

    printf("\nEnter contact name to find: ");

    read_string(name, NAME_SIZE);

    contact = find_contact_by_name(name);

    if (contact == NULL)
    {
        printf("\nContact not found.\n");
        return;
    }

    printf("\nContact found:\n");

    print_one_contact(contact);
}


/* =========================================================
   DELETE CONTACT
   ========================================================= */

void delete_contact(void)
{
    struct Contact *temp;
    struct Contact *previous;

    char name[NAME_SIZE];

    printf("\nEnter contact name to delete: ");

    read_string(name, NAME_SIZE);

    temp = head;
    previous = NULL;

    /*
       Search contact.
    */

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            break;
        }

        previous = temp;
        temp = temp->next;
    }

    /*
       Contact not found.
    */

    if (temp == NULL)
    {
        printf("Contact not found.\n");
        return;
    }

    /*
       If deleting first node.
    */

    if (previous == NULL)
    {
        head = temp->next;
    }
    else
    {
        /*
           Bypass current node.
        */

        previous->next = temp->next;
    }

    /*
       Free contact memory.
    */

    free_contact(temp);

    printf("Contact deleted successfully.\n");
}


/* =========================================================
   FREE ONE CONTACT
   ========================================================= */

void free_contact(struct Contact *contact)
{
    int i;

    if (contact == NULL)
    {
        return;
    }

    /*
       Free every phone number.
    */

    for (i = 0; i < contact->phone_count; i++)
    {
        free(contact->phone[i]);
    }

    /*
       Free phone pointer array.
    */

    free(contact->phone);

    /*
       Free contact node.
    */

    free(contact);
}


/* =========================================================
   EDIT CONTACT NAME
   ========================================================= */

void edit_name(struct Contact *contact)
{
    char new_name[NAME_SIZE];

    struct Contact *existing;

    printf("\nCurrent name: %s\n",
           contact->name);

    printf("Enter new name: ");

    read_string(new_name, NAME_SIZE);

    if (strlen(new_name) == 0)
    {
        printf("Name cannot be empty.\n");
        return;
    }

    /*
       If same name was entered,
       nothing needs to change.
    */

    if (strcmp(contact->name, new_name) == 0)
    {
        printf("Name remains unchanged.\n");
        return;
    }

    /*
       Check duplicate name.
    */

    existing = find_contact_by_name(new_name);

    if (existing != NULL)
    {
        printf("Another contact already has this name.\n");
        return;
    }

    strcpy(contact->name, new_name);

    printf("Contact name updated successfully.\n");
}


/* =========================================================
   CHANGE ONE PHONE NUMBER
   ========================================================= */

int change_phone(struct Contact *contact)
{
    int number;

    char new_number[PHONE_SIZE];

    char *new_phone;

    int index;

    if (contact->phone_count == 0)
    {
        printf("No phone numbers available.\n");
        return 0;
    }

    /*
       Display phone numbers.
    */

    printf("\nCurrent phone numbers:\n");

    for (index = 0;
         index < contact->phone_count;
         index++)
    {
        printf("%d. %s\n",
               index + 1,
               contact->phone[index]);
    }

    printf("Enter phone number index to change: ");

    if (scanf("%d", &number) != 1)
    {
        clear_input_buffer();

        printf("Invalid input.\n");

        return 0;
    }

    clear_input_buffer();

    /*
       Validate index.
    */

    if (number < 1 ||
        number > contact->phone_count)
    {
        printf("Invalid phone number index.\n");

        return 0;
    }

    printf("Enter new phone number: ");

    read_string(new_number, PHONE_SIZE);

    if (strlen(new_number) == 0)
    {
        printf("Phone number cannot be empty.\n");

        return 0;
    }

    /*
       Allocate new string first.

       This is safer than freeing the old
       string before allocation succeeds.
    */

    new_phone = malloc(strlen(new_number) + 1);

    if (new_phone == NULL)
    {
        printf("Memory allocation failed.\n");

        return 0;
    }

    strcpy(new_phone, new_number);

    /*
       Free old phone number.
    */

    index = number - 1;

    free(contact->phone[index]);

    /*
       Replace pointer.
    */

    contact->phone[index] = new_phone;

    printf("Phone number changed successfully.\n");

    return 1;
}


/* =========================================================
   DELETE ONE PHONE NUMBER
   ========================================================= */

int delete_phone(struct Contact *contact)
{
    int number;

    int index;

    int i;

    char **temp;

    if (contact->phone_count == 0)
    {
        printf("No phone numbers available.\n");

        return 0;
    }

    /*
       Display phone numbers.
    */

    printf("\nCurrent phone numbers:\n");

    for (i = 0;
         i < contact->phone_count;
         i++)
    {
        printf("%d. %s\n",
               i + 1,
               contact->phone[i]);
    }

    /*
       Ask which phone to delete.
    */

    printf("Enter phone number index to delete: ");

    if (scanf("%d", &number) != 1)
    {
        clear_input_buffer();

        printf("Invalid input.\n");

        return 0;
    }

    clear_input_buffer();

    /*
       Validate index.
    */

    if (number < 1 ||
        number > contact->phone_count)
    {
        printf("Invalid phone number index.\n");

        return 0;
    }

    index = number - 1;

    /*
       Free selected phone number.
    */

    free(contact->phone[index]);

    /*
       Shift remaining pointers left.
    */

    for (i = index;
         i < contact->phone_count - 1;
         i++)
    {
        contact->phone[i] =
            contact->phone[i + 1];
    }

    contact->phone_count--;

    /*
       If there are no phone numbers left,
       free the pointer array.
    */

    if (contact->phone_count == 0)
    {
        free(contact->phone);

        contact->phone = NULL;
    }
    else
    {
        /*
           Reduce pointer-array size.

           If realloc fails, keeping the original
           larger allocation is still safe.
        */

        temp = realloc(
            contact->phone,
            contact->phone_count * sizeof(char *)
        );

        if (temp != NULL)
        {
            contact->phone = temp;
        }
    }

    printf("Phone number deleted successfully.\n");

    return 1;
}


/* =========================================================
   EDIT PHONE NUMBERS
   ========================================================= */

void edit_phone_numbers(struct Contact *contact)
{
    int choice;

    char number[PHONE_SIZE];

    while (1)
    {
        printf("\n========================================\n");
        printf("         PHONE NUMBER EDIT\n");
        printf("========================================\n");

        printf("1. Add phone number\n");
        printf("2. Change phone number\n");
        printf("3. Delete phone number\n");
        printf("4. Show phone numbers\n");
        printf("5. Back\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            clear_input_buffer();

            printf("Invalid choice.\n");

            continue;
        }

        clear_input_buffer();

        /*
           ADD
        */

        if (choice == 1)
        {
            printf("Enter phone number: ");

            read_string(number, PHONE_SIZE);

            if (strlen(number) == 0)
            {
                printf("Phone number cannot be empty.\n");
                continue;
            }

            if (add_phone(contact, number))
            {
                printf("Phone number added successfully.\n");
            }
            else
            {
                printf("Unable to add phone number.\n");
            }
        }

        /*
           CHANGE
        */

        else if (choice == 2)
        {
            change_phone(contact);
        }

        /*
           DELETE
        */

        else if (choice == 3)
        {
            delete_phone(contact);
        }

        /*
           SHOW
        */

        else if (choice == 4)
        {
            int i;

            if (contact->phone_count == 0)
            {
                printf("No phone numbers available.\n");
            }
            else
            {
                printf("\nPhone numbers:\n");

                for (i = 0;
                     i < contact->phone_count;
                     i++)
                {
                    printf("%d. %s\n",
                           i + 1,
                           contact->phone[i]);
                }
            }
        }

        /*
           BACK
        */

        else if (choice == 5)
        {
            return;
        }

        else
        {
            printf("Invalid choice.\n");
        }
    }
}


/* =========================================================
   EDIT EMAIL
   ========================================================= */

void edit_email(struct Contact *contact)
{
    char choice;

    char new_email[EMAIL_SIZE];

    printf("\nCurrent email: ");

    if (strlen(contact->email) == 0)
    {
        printf("Not available\n");
    }
    else
    {
        printf("%s\n",
               contact->email);
    }

    printf("\n1. Change email\n");
    printf("2. Remove email\n");
    printf("3. Keep current email\n");

    printf("Enter choice: ");

    scanf(" %c", &choice);

    clear_input_buffer();

    /*
       CHANGE EMAIL
    */

    if (choice == '1')
    {
        printf("Enter new email: ");

        read_string(new_email, EMAIL_SIZE);

        if (strlen(new_email) == 0)
        {
            printf("Email cannot be empty.\n");
            return;
        }

        strcpy(contact->email, new_email);

        printf("Email updated successfully.\n");
    }

    /*
       REMOVE EMAIL
    */

    else if (choice == '2')
    {
        contact->email[0] = '\0';

        printf("Email removed successfully.\n");
    }

    /*
       KEEP
    */

    else if (choice == '3')
    {
        printf("Email unchanged.\n");
    }

    else
    {
        printf("Invalid choice.\n");
    }
}


/* =========================================================
   EDIT ADDRESS
   ========================================================= */

void edit_address(struct Contact *contact)
{
    int choice;

    char new_address[ADDRESS_SIZE];

    printf("\nCurrent address: ");

    if (strlen(contact->address) == 0)
    {
        printf("Not available\n");
    }
    else
    {
        printf("%s\n",
               contact->address);
    }

    printf("\n1. Change address\n");
    printf("2. Remove address\n");
    printf("3. Keep current address\n");

    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
    {
        clear_input_buffer();

        printf("Invalid choice.\n");

        return;
    }

    clear_input_buffer();

    /*
       CHANGE
    */

    if (choice == 1)
    {
        printf("Enter new address: ");

        read_string(new_address, ADDRESS_SIZE);

        if (strlen(new_address) == 0)
        {
            printf("Address cannot be empty.\n");
            return;
        }

        strcpy(contact->address, new_address);

        printf("Address updated successfully.\n");
    }

    /*
       REMOVE
    */

    else if (choice == 2)
    {
        contact->address[0] = '\0';

        printf("Address removed successfully.\n");
    }

    /*
       KEEP
    */

    else if (choice == 3)
    {
        printf("Address unchanged.\n");
    }

    else
    {
        printf("Invalid choice.\n");
    }
}


/* =========================================================
   EDIT CONTACT
   ========================================================= */

void edit_contact(void)
{
    char name[NAME_SIZE];

    struct Contact *contact;

    int choice;

    printf("\nEnter contact name to edit: ");

    read_string(name, NAME_SIZE);

    contact = find_contact_by_name(name);

    if (contact == NULL)
    {
        printf("Contact not found.\n");

        return;
    }

    while (1)
    {
        printf("\n========================================\n");
        printf("             EDIT CONTACT\n");
        printf("========================================\n");

        printf("Contact: %s\n",
               contact->name);

        printf("\n1. Edit name\n");
        printf("2. Edit phone numbers\n");
        printf("3. Edit email\n");
        printf("4. Edit address\n");
        printf("5. Show contact\n");
        printf("6. Finish editing\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            clear_input_buffer();

            printf("Invalid choice.\n");

            continue;
        }

        clear_input_buffer();

        switch (choice)
        {
            case 1:

                edit_name(contact);

                break;

            case 2:

                edit_phone_numbers(contact);

                break;

            case 3:

                edit_email(contact);

                break;

            case 4:

                edit_address(contact);

                break;

            case 5:

                print_one_contact(contact);

                break;

            case 6:

                printf("Finished editing contact.\n");

                return;

            default:

                printf("Invalid choice.\n");
        }
    }
}


/* =========================================================
   SAVE CONTACTS
   ========================================================= */

void save_contacts(void)
{
    FILE *fp;

    struct Contact *temp;

    int i;

    int contact_count = 0;

    /*
       Open file in binary write mode.

       "wb" means:
       w = write
       b = binary
    */

    fp = fopen(FILE_NAME, "wb");

    if (fp == NULL)
    {
        printf("Unable to open file for saving.\n");

        return;
    }

    /*
       Count contacts.
    */

    temp = head;

    while (temp != NULL)
    {
        contact_count++;

        temp = temp->next;
    }

    /*
       Store number of contacts first.
    */

    fwrite(
        &contact_count,
        sizeof(int),
        1,
        fp
    );

    /*
       Save every contact.
    */

    temp = head;

    while (temp != NULL)
    {
        /*
           Save name.
        */

        fwrite(
            temp->name,
            sizeof(char),
            NAME_SIZE,
            fp
        );

        /*
           Save number of phone numbers.
        */

        fwrite(
            &temp->phone_count,
            sizeof(int),
            1,
            fp
        );

        /*
           Save each phone number.
        */

        for (i = 0;
             i < temp->phone_count;
             i++)
        {
            fwrite(
                temp->phone[i],
                sizeof(char),
                PHONE_SIZE,
                fp
            );
        }

        /*
           Save email.
        */

        fwrite(
            temp->email,
            sizeof(char),
            EMAIL_SIZE,
            fp
        );

        /*
           Save address.
        */

        fwrite(
            temp->address,
            sizeof(char),
            ADDRESS_SIZE,
            fp
        );

        temp = temp->next;
    }

    fclose(fp);

    printf("\nContacts saved successfully.\n");
}


/* =========================================================
   LOAD CONTACTS
   ========================================================= */

void load_contacts(void)
{
    FILE *fp;

    struct Contact *new_contact;

    struct Contact *temp;

    int contact_count;

    int i;

    /*
       Open saved file.
    */

    fp = fopen(FILE_NAME, "rb");

    /*
       If file does not exist,
       start with an empty phone book.
    */

    if (fp == NULL)
    {
        return;
    }

    /*
       Read contact count.
    */

    if (fread(
            &contact_count,
            sizeof(int),
            1,
            fp) != 1)
    {
        fclose(fp);

        return;
    }

    /*
       Basic validation.
    */

    if (contact_count < 0)
    {
        fclose(fp);

        return;
    }

    /*
       Load each contact.
    */

    for (i = 0;
         i < contact_count;
         i++)
    {
        int j;

        /*
           Allocate contact.
        */

        new_contact =
            malloc(sizeof(struct Contact));

        if (new_contact == NULL)
        {
            printf("Memory allocation failed while loading.\n");

            fclose(fp);

            return;
        }

        /*
           Initialize.
        */

        new_contact->phone = NULL;
        new_contact->phone_count = 0;
        new_contact->email[0] = '\0';
        new_contact->address[0] = '\0';
        new_contact->next = NULL;

        /*
           Read name.
        */

        if (fread(
                new_contact->name,
                sizeof(char),
                NAME_SIZE,
                fp) != NAME_SIZE)
        {
            free(new_contact);

            break;
        }

        /*
           Read phone count.
        */

        if (fread(
                &new_contact->phone_count,
                sizeof(int),
                1,
                fp) != 1)
        {
            free(new_contact);

            break;
        }

        /*
           Validate phone count.
        */

        if (new_contact->phone_count < 0 ||
            new_contact->phone_count > 1000)
        {
            printf("Invalid phone data in file.\n");

            free(new_contact);

            break;
        }

        /*
           Allocate phone pointer array.
        */

        if (new_contact->phone_count > 0)
        {
            new_contact->phone =
                malloc(
                    new_contact->phone_count *
                    sizeof(char *)
                );

            if (new_contact->phone == NULL)
            {
                free(new_contact);

                fclose(fp);

                return;
            }

            /*
               Initialize pointers.
            */

            for (j = 0;
                 j < new_contact->phone_count;
                 j++)
            {
                new_contact->phone[j] = NULL;
            }

            /*
               Read each phone number.
            */

            for (j = 0;
                 j < new_contact->phone_count;
                 j++)
            {
                char phone_buffer[PHONE_SIZE];

                /*
                   Read fixed-size phone field.
                */

                if (fread(
                        phone_buffer,
                        sizeof(char),
                        PHONE_SIZE,
                        fp) != PHONE_SIZE)
                {
                    int k;

                    for (k = 0;
                         k < j;
                         k++)
                    {
                        free(
                            new_contact->phone[k]
                        );
                    }

                    free(new_contact->phone);
                    free(new_contact);

                    fclose(fp);

                    return;
                }

                /*
                   Make sure string is terminated.
                */

                phone_buffer[PHONE_SIZE - 1] = '\0';

                /*
                   Allocate memory.
                */

                new_contact->phone[j] =
                    malloc(
                        strlen(phone_buffer) + 1
                    );

                if (new_contact->phone[j] == NULL)
                {
                    int k;

                    for (k = 0;
                         k < j;
                         k++)
                    {
                        free(
                            new_contact->phone[k]
                        );
                    }

                    free(new_contact->phone);
                    free(new_contact);

                    fclose(fp);

                    return;
                }

                /*
                   Copy phone number.
                */

                strcpy(
                    new_contact->phone[j],
                    phone_buffer
                );
            }
        }

        /*
           Read email.
        */

        if (fread(
                new_contact->email,
                sizeof(char),
                EMAIL_SIZE,
                fp) != EMAIL_SIZE)
        {
            free_contact(new_contact);

            break;
        }

        /*
           Read address.
        */

        if (fread(
                new_contact->address,
                sizeof(char),
                ADDRESS_SIZE,
                fp) != ADDRESS_SIZE)
        {
            free_contact(new_contact);

            break;
        }

        /*
           Add loaded contact to linked list.
        */

        if (head == NULL)
        {
            head = new_contact;
        }
        else
        {
            temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = new_contact;
        }
    }

    fclose(fp);
}


/* =========================================================
   FREE ALL CONTACTS
   ========================================================= */

void free_all_contacts(void)
{
    struct Contact *temp;

    struct Contact *next;

    temp = head;

    while (temp != NULL)
    {
        next = temp->next;

        free_contact(temp);

        temp = next;
    }

    head = NULL;
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */

int main(void)
{
    char choice;

    /*
       Load previously saved contacts.
    */

    load_contacts();

    printf("\n========================================\n");
    printf("            PHONE BOOK APP\n");
    printf("========================================\n");

    while (1)
    {
        printf("\n========================================\n");
        printf("               MAIN MENU\n");
        printf("========================================\n");

        printf("c/C : Create a new contact\n");
        printf("p/P : Print all contacts\n");
        printf("d/D : Delete contact\n");
        printf("f/F : Find contact\n");
        printf("e/E : Edit a contact\n");
        printf("s/S : Save contacts\n");
        printf("q/Q : Quit\n");

        printf("\nEnter your choice: ");

        scanf(" %c", &choice);

        clear_input_buffer();

        switch (choice)
        {
            /*
               CREATE
            */

            case 'c':
            case 'C':

                create_contact();

                break;


            /*
               PRINT
            */

            case 'p':
            case 'P':

                print_contacts();

                break;


            /*
               DELETE
            */

            case 'd':
            case 'D':

                delete_contact();

                break;


            /*
               FIND
            */

            case 'f':
            case 'F':

                find_contact();

                break;


            /*
               EDIT
            */

            case 'e':
            case 'E':

                edit_contact();

                break;


            /*
               SAVE
            */

            case 's':
            case 'S':

                save_contacts();

                break;


            /*
               QUIT
            */

            case 'q':
            case 'Q':

                /*
                   Automatically save before quitting.
                */

                save_contacts();

                /*
                   Release all allocated memory.
                */

                free_all_contacts();

                printf("\nPhone Book closed successfully.\n");

                return 0;


            /*
               INVALID OPTION
            */

            default:

                printf("\nInvalid choice. Please try again.\n");

                break;
        }
    }

    return 0;
}   