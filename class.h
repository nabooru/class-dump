


#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdint.h>


typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;    


typedef struct {
   u1 tag;
   u1 *info;
} cp_info;


typedef struct {
   u2 test;
} attribute_info;

typedef struct {
   u2   access_flags;
   u2   name_index;
   u2   descriptor_index;
   u2   attributes_count;   
} field_info;


typedef struct {
   uint8_t test;
} method_info;


#define CLASS_MAGIC      0xCAFEBABE

typedef struct {
   u4              magic;
   u2              minor_version;
   u2              major_version;
   u2              constant_pool_count;
   cp_info        *constant_pool;
   u2              access_flags;
   u2              this_class;
   u2              super_class;
   u2              interfaces_count;
   u2             *interfaces;
   u2              fields_count;
   field_info     *fields; 
   u2              methods_count;
   method_info    *methods;               
   u2              attributes_count;
   attribute_info *attributes;
} ClassFile; 


/* Internal errors. */

#define CLASS_OK             0x000  
#define CLASS_ERROR_SUCCESS  0x000
#define CLASS_ERROR_BADMAGIC 0x201
#define CLASS_ERROR_ENOENT   0x202
#define CLASS_ERROR_IOFAIL   0x203

#define CLASS_ERROR_NOMEM    0x204
#define CLASS_ERROR_DEBUG    0x210


extern void jclass_free(ClassFile *class);
extern int  jclass_read(const char *path, ClassFile **class);


#endif /* _CLASS_H_ */
