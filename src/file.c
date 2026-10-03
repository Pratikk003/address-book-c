#include <stdio.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  //create the file pointer in write mode
  FILE *fp = fopen("contacts.csv" , "w");

  if (fp == NULL)
  {
    printf("Unable to open file.\n");
    return;
  }

  fprintf(fp , "No. of contacts: %d\n" , addressBook->contactCount);  //to measure the count of entries in database
  //print the data  in csv file (contacts.csv)
  for(int i=0;i< addressBook->contactCount;++i)
    {
        fprintf(fp,"%s,%s,%s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);

    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
    //create the file pointer in read mode
  FILE *fp = fopen("contacts.csv" , "r");
  
  if (fp == NULL)
  {
    printf("Unable to open file.\n");
    return;
  }
  
    fscanf(fp, "No. of contacts: %d\n", &addressBook->contactCount);  //reading the no. of contacts in database
    if(addressBook->contactCount < 0 || addressBook->contactCount > MAX_CONTACTS)
        addressBook->contactCount = 0;
   
  //read the data  in csv file (contacts.csv)
  for(int i=0;i< addressBook->contactCount;++i)
    {
        fscanf(fp," %[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);

    }
    fclose(fp);

    // Remove any stray '\r' / trailing spaces so search & delete match correctly
    for(int i=0;i< addressBook->contactCount;++i)
    {
        char *fields[3] = { addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email };
        for(int k=0;k<3;++k)
        {
            size_t n = strlen(fields[k]);
            while(n > 0 && (fields[k][n-1]=='\r' || fields[k][n-1]=='\n' || fields[k][n-1]==' '))
                fields[k][--n] = '\0';
        }
    }
}
