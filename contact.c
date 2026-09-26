#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "file.h"
//#include "populate.h"

// function declatration.
int validatename(char *name);
int validatephone(char *phone);
int validateemail(char *email);
int duplicateContact(AddressBook *addressBook, char *name, char *phone, char *email);


void listContacts(AddressBook *addressBook, int sortCriteria)
{
    printf("\nSort contacts by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &sortCriteria);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        for(int j = i + 1; j < addressBook->contactCount; j++)
        {
            int result;

            if(sortCriteria == 1)
            {
                result = strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
            }
            else if(sortCriteria == 2)
            {
                result = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
            }
            else if(sortCriteria == 3)
            {
                result = strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email);
            }
            else
            {
                printf("Invalid choice\n");
                return;
            }

            if(result > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Name : %s\tPhone : %s\tEmail : %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50];
    do{
    printf("enter the name :");
    scanf("%49s", name);

    }while(validatename(name) == 0);


    char phone[20];

    do{
        printf("Enter the Phone: ");
        scanf("%19s",phone);
    }while(validatephone(phone) == 0);


    char email[50];

    do{
        printf("Enter the email: ");
        scanf("%49s",email);
    }while(validateemail(email) == 0);


    int ret = duplicateContact(addressBook, name, phone, email);

    if(ret == 1)
    {
        printf("Contact already exists\n");
        return;
    }

    if(ret == 0)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);
        addressBook->contactCount++;
    }

    printf("Contact created successfully");
 
}
int validatename(char *name)
{
    int i=0;
    for(i=0; name[i] !=0; i++)
    {
        if((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] >= '0' && name[i] <= '9')
        {
            continue;
        }
        else
        {
            printf("Invalid name.. re-enter the name :");
            return 0;
        }
    }
    return 1;
}

int validatephone(char *phone)
{
    int i=0,count=0;
    while(phone[i]!=0)
    {
        count++;
        i++;
    }

    if(count == 10)
    {
        if(phone[0] <= '5')
        {
            printf("Invalid number.. re-enter the number :");
            return 0;
        }

        for(i=0; phone[i]!=0; i++)
        {
            if(phone[i] <'0' || phone[i] >'9')
            {
                printf("Invalid number.. re-enter the number :");
                return 0;
            }
        }
        return 1;
    }
    else{
        printf("Invalid number.. re-enter the number :");
        return 0;
    }
}

int validateemail(char *email)
{
    int i = 0, flag = 0;

    // 1. Check uppercase, spaces and @
    while(email[i] != '\0')
    {
        // Uppercase not allowed
        if('A' <= email[i] && email[i] <= 'Z')
        {
            printf("Invalid email.. re-enter the email: ");
            return 0;
        }

        // Space not allowed
        if(email[i] == ' ')
        {
            printf("Invalid email.. re-enter the email: ");
            return 0;
        }

        // Check @
        if(email[i] == '@')
        {
            flag = 1;
        }

        i++;
    }

    // 2. @ must be present
    if(flag == 0)
    {
        printf("Invalid email.. re-enter the email: ");
        return 0;
    }

    // 3. Find length and @ position
    int length = 0;
    int Position = 0;

    for(i = 0; email[i] != '\0'; i++)
    {
        length++;

        if(email[i] == '@')
        {
            Position = i;
        }
    }

    if(email[length - 1] != 'm' || email[length - 2] != 'o' || email[length - 3] != 'c' || email[length - 4] != '.')
    {
        printf("Invalid email.. re-enter the email: ");
        return 0;
    }

    // 5. At least one character between @ and .com
    if((length - 4) - Position <= 1)
    {
        printf("Invalid email.. re-enter the email: ");
        return 0;
    }

    // 6. All validations passed
    return 1;
}

int duplicateContact(AddressBook *addressBook, char *name, char *phone, char *email)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(name, addressBook->contacts[i].name) == 0)
        {
            printf("Name is already there, re-enter the name");
            return 1;
        }
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printf("Number is already there, re-enter the number");
            return 1;
        }
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printf("email is already there, re-enter the email");
            return 1;
        }
    }
    return 0;
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    char search[50];
    int found = 0;

    printf("\nSearch contact by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter search value: ");
    scanf("%49s", search);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        char *field;

        if(choice == 1)
        {
            field = addressBook->contacts[i].name;
        }
        else if(choice == 2)
        {
            field = addressBook->contacts[i].phone;
        }
        else if(choice == 3)
        {
            field = addressBook->contacts[i].email;
        }
        else
        {
            printf("Invalid choice\n");
            return;
        }

        if(strcasestr(field, search) != NULL)
        {
            printf("\nContact matched...\n");
            printf("Name : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("Contact not found\n");
    }
}

int findcontact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char searchname[50];
    printf("Enter the name to search: ");
    scanf("%s", searchname);
    int flag;
    int found = 0;

    for(int i = 0; i < addressBook->contactCount; i++)    //Go to AddressBook structure pointed to by variable of addressBook,and get  contactCount member.
    {
        flag = 1;
        int j = 0;

        while(searchname[j] != '\0' && addressBook->contacts[i].name[j] != '\0')
        {
            if(searchname[j] != addressBook->contacts[i].name[j])
            {
                flag = 0;    // FOUND → return index
                break;
            }
            j++;
        }

        if(searchname[j] == '\0' && addressBook->contacts[i].name[j] == '\0')
        {
            return i;
        }
    }
    return -1;     // NOT FOUND

}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int ret=findcontact(addressBook); // function calling searching name,and its return.

    if(ret == -1)
    {
        printf("Contact not found\n");
        return;   //return is not returning a value. It is used to stop the editContact() function
    }

        int choice;
        printf("What do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
                    
        switch (choice) 
        {
            case 1:
                {
                    char newname[50];

                    printf("Enter new name: ");
                    scanf("%s", newname);

                    strcpy(addressBook->contacts[ret].name,newname); // now update the old name
                    break;
                }
            case 2:
                {
                    char newphone[50];

                    printf("Enter new phone number: ");
                    scanf("%s",newphone);

                    strcpy(addressBook->contacts[ret].phone,newphone);  // now update the old phone
                    break;

                }
            case 3:
            {
                char newemail[50];

                printf("Enter new email: ");
                scanf("%s",newemail);

                strcpy(addressBook->contacts[ret].email,newemail);  // now update the old email
                break;

            }
            default:
                printf("Invalid choice. Please try again.\n");
       }

}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int ret = findcontact(addressBook);
    if(ret == -1)
    {
        printf("Contact not found\n");
        return;
    }

    for(int i = ret; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully\n");
}
