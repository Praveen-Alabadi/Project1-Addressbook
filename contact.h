#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact; //data type for structure  contact

typedef struct {
    Contact contacts[100];   //structure array - data type contact & array name is contacts 
    int contactCount;
} AddressBook;  //data type for structure  AddressBook

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
//int validatename(char *name);
int duplicateContact(AddressBook *addressBook, char *name, char *phone, char *email);

#endif
