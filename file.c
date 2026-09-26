#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv", "w");

    if (fptr == NULL)
    {
        printf("File is not opened\n");
        return;
    }
    fprintf(fptr,"Contact count = %d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fptr);

    printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "r");

    if(fptr == NULL)
    {
        printf("File is not opened\n");
        return;
    }

    char line[100];

    // Skip the first line
    fgets(line, sizeof(line), fptr);

    while(fscanf(fptr, "%49[^,],%19[^,],%49[^\n]\n", addressBook->contacts[addressBook->contactCount].name, addressBook->contacts[addressBook->contactCount].phone,
                    addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fptr);
}
