

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "class.h"


static void *dec8le(uint8_t *x, const void *buffer)
{
   uint8_t *ptr = (uint8_t *)buffer;
   
   *x = ptr[0];
   ptr += sizeof(uint8_t);
   return (void *)ptr;
}

static void *dec16le(uint16_t *x, const void *buffer)
{
   uint8_t *ptr = (uint8_t *)buffer;

   *x = (uint16_t)((uint16_t)ptr[0] | (uint16_t)(ptr[1] << 8) );
   ptr += sizeof(uint16_t);     
   return (void *)ptr;
}

static void *dec32le(uint32_t *x, const void *buffer)
{
   uint8_t *ptr = (uint8_t *)buffer;
   
   *x = (uint32_t)((uint32_t)(ptr[0])       | 
                   (uint32_t)(ptr[1] <<  8) | 
                   (uint32_t)(ptr[2] << 16) |
                   (uint32_t)(ptr[3] << 24)); 
   ptr += sizeof(uint32_t);   
   return (void *)ptr;
}

static void *dec32be(uint32_t *x, const void *buffer)
{
   uint8_t *ptr = (uint8_t *)buffer;
  
   *x = (uint32_t)((uint32_t)(ptr[0] << 24) |
                   (uint32_t)(ptr[1] << 16) |
                   (uint32_t)(ptr[2] <<  8) |
                   (uint32_t)ptr[3]);
   ptr += sizeof(uint32_t);
   return (void *)ptr;
}

static int read_magic(const char *path)
{
   uint8_t buffer[4];
   u4 magic;
   FILE *fp;
   int nr;

   fp = fopen(path, "rb");
   if (fp == NULL)
       return errno == ENOENT ? CLASS_ERROR_ENOENT : CLASS_ERROR_DEBUG;  

   nr = fread(buffer, 1, 4, fp);
   if (nr != 4) {
       /* Let's keep it simple, for now. */
       return CLASS_ERROR_IOFAIL;   
   }

   fclose(fp);
   dec32be(&magic, buffer);

   printf("Magic: 0x%08X \n", magic); 

   return magic == CLASS_MAGIC ? CLASS_ERROR_SUCCESS : CLASS_ERROR_BADMAGIC;
}


void jclass_free(ClassFile *class)
{
   if (class != NULL) {
       free(class);
   }
}


int jclass_read(const char *path, ClassFile **class)
{
   ClassFile *cf = NULL;
   FILE *fp;   
   uint8_t buffer[256]; /* Not sure about the final size. */
   struct _stat statbuf;
   int result;
   int nr;
   
   /* Okay, all the things we need here. */

   result = _stat(path, &statbuf);
   if (result != 0) {
       return CLASS_ERROR_ENOENT;               
   }

   result = read_magic(path);
  
   cf = *class = malloc(sizeof(ClassFile));
   if (cf == NULL)
       return CLASS_ERROR_NOMEM;

   fp = fopen(path, "rb");
   if (fp == NULL)
       return CLASS_ERROR_IOFAIL;

   nr = fread(buffer, 1, sizeof(buffer), fp);
   if (nr != sizeof(buffer)) 
       return CLASS_ERROR_IOFAIL;
   
   uint8_t *ptr = buffer;

   ptr = dec32be(&cf->magic, ptr);
   ptr = dec16le(&cf->minor_version, ptr);
   ptr = dec16le(&cf->major_version, ptr);
   ptr = dec16le(&cf->constant_pool_count, ptr);


   


   return CLASS_ERROR_SUCCESS;
}

