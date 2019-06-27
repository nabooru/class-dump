
/*******************************************************************************
 * Java Class File Dump
 * Reference: The class File Format at docs.oracle.com
 *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "class.h"


static void jclass_dump(ClassFile *class)
{
   printf("Dump!\n");

}

int main(int argc, char *argv[])
{
   ClassFile *class = NULL;
   int result;
   
   if (argc != 2) {
       printf("Error: invalid number of arguments.\n");
       printf("Usage: %s filename\n", argv[0]); 
       return EXIT_FAILURE;
   }

  
   result = jclass_read(argv[1], &class);
   if (result != CLASS_OK) {
       printf("An error has occurred.\n");
   }   

   /* Dump */  

   jclass_dump(class);   
   jclass_free(class);


   return EXIT_SUCCESS;
}