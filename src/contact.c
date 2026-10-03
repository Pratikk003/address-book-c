#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

/* Returns 1 if the email contains an '@' with text before and after it, and no spaces */
static int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (at == NULL)            return 0;   // no '@' at all
    if (at == email)           return 0;   // nothing before '@'
    if (*(at + 1) == '\0')     return 0;   // nothing after '@'
    if (strchr(at + 1, '@'))   return 0;   // more than one '@'
    if (strchr(email, ' '))    return 0;   // no spaces allowed
    return 1;
}

/* Keeps asking until a valid email is entered */
static void readValidEmail(char *dest, const char *prompt)
{
    do
    {
        printf("%s", prompt);
        scanf(" %49[^\n]", dest);
        if (!isValidEmail(dest))
            printf("Invalid Email! It must contain '@' (e.g. name@example.com).\n");
    } while (!isValidEmail(dest));
}

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    
    printf("1. Sort by name\n2. Sort by phone number\n3. Sort by email\n4. Exit\n");
    int sortChoice;
    printf("Enter your choice : ");
    scanf("%d",&sortChoice);
    switch (sortChoice)
    {
    case 1:
        for(int i=0;i< addressBook -> contactCount-1; i++)
        {
            for(int j=0;j< addressBook -> contactCount-i-1 ;j++)
            {
                
                if(strcmp(addressBook->contacts[j].name , addressBook->contacts[j+1].name ) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]= addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
        break;
    case 2:
        for(int i=0;i< addressBook -> contactCount-1; i++)
        {
            for(int j=0;j< addressBook -> contactCount-i-1 ;j++)
            {
              
                if(strcmp(addressBook->contacts[j].phone , addressBook->contacts[j+1].phone) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]= addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
        break;    
        
    case 3:
        for(int i=0;i< addressBook -> contactCount-1; i++)
        {
            for(int j=0;j< addressBook -> contactCount-i-1 ;j++)
            {
                
                if(strcmp(addressBook->contacts[j].email , addressBook->contacts[j+1].email) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]= addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
        break;
    case 4:
        return; //to exit the choice of sorting 
    }
    printf("=========================");             
    printf("\n::: Contacts List :::\n");
    printf("========================="); 
    
    printf("\n-------------------------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------------------\n");
    
    for(int i=0;i< addressBook->contactCount;++i)
    {
        printf("%-5d %-20s %-15s %-30s\n",
            i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);

    }
    printf("-------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("Enter the name : ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    do
    {
        printf("Enter the phone number : ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        
        if(strlen(addressBook -> contacts[addressBook -> contactCount].phone) !=10)
        {
            printf("Invalid Phone Number! It must contain exactly 10 digits.\n");
        }
    }
    while(strlen(addressBook->contacts[addressBook->contactCount].phone) != 10);
    
    readValidEmail(addressBook->contacts[addressBook->contactCount].email, "Enter the email id : ");
    
    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
     printf("1. Search by name\n2. Search by phone number\n3. Search by email\n4. Exit\n");
    int searchChoice;
    printf("Enter your choice : ");
    scanf("%d",&searchChoice);
    char name[50], phone[15], email[50];
    switch (searchChoice)
    {
    case 1:
        printf("Enter the name : ");
        scanf(" %[^\n]",name);
        
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasecmp(addressBook->contacts[i].name,name)==0)
                {
                    printf("Name: %s, Phone: %s, Email: %s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                    return i;//data found
                }
        }
        return -2;//the contact is not present or contact is not found
        break;
    case 2:
        printf("Enter the phone number : ");
        scanf(" %[^\n]",phone);
        
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasecmp(addressBook->contacts[i].phone,phone)==0)
                {
                    printf("Name: %s, Phone: %s, Email: %s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                    return i;//data found
                }
        }
        return -2;//the contact is not present or contact is not found
        break;
    
    case 3:
    printf("Enter the email Id :");
    scanf(" %[^\n]",email);
        
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasecmp(addressBook->contacts[i].email,email)==0)
                {
                    printf("Name: %s, Phone: %s, Email: %s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                    return i;//data found
                }
        }
        return -2;//the contact is not present or contact is not found
        break;
    case 4:
        return -1; // Exit
    default:
        printf("Invalid choice.\n");
        return -1;
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
    printf("1. Edit name\n2. Edit phone number\n3. Edit email\n4. Exit\n");
    int editChoice;
    printf("Enter your choice : ");
    scanf("%d",&editChoice);
    
    int index = searchContact(addressBook);

    if(index == -1)
    {
        printf("Exit from search contact\n");
    }
    else if (index == -2)
    {
        printf("Contact not found\n");
    }
    else
    {
        switch (editChoice)
        {
            case 1:
            { 
                printf("Enter the edit Name : ");
                scanf(" %[^\n]", addressBook ->contacts[index].name);
            }        
            break;

            case 2:
            { 
                printf("Enter the edit Phone Number : ");
                scanf(" %[^\n]", addressBook ->contacts[index].phone);
            }        
            break;

            case 3:
            { 
                readValidEmail(addressBook ->contacts[index].email, "Enter the edit Email Id : ");
            }        
            break;

            case 4:
                return;
        
        }
    }
}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
      
    int index = searchContact(addressBook);
    char choice;
    if(index == -1)
    {
        printf("Exit from search contact\n");
    }
    else if (index == -2)
    {
        printf("Contact not found\n");
    }
    else
    {
        printf("Are you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &choice);
        if(choice == 'Y' || choice == 'y')
        {
            for(int i= index; i< addressBook -> contactCount - 1; i++)
            {
                addressBook ->contacts[i] = addressBook ->contacts[i+1];
            }
            addressBook->contactCount--;//to remove dummy/empty contact after deleting i.e. Name: , Phone: , Email:
            printf("Contact deleted successfully.\n");
        }
        else
        {
            printf("Deletion cancelled.\n");
        }
    }
}
