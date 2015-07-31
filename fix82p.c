/*
   fix82p, a program to fix the "size" and "checksum" fields of a TI-82 binary
   BASIC program.  Mostly useful for generating TI-82 BASIC programs that have
   invalid variables, such as L7, Pic7, etc.
 */

#include <inttypes.h>
#include <stdio.h>

/* exceed the storage capacity of a TI-82 */
unsigned char data[30000];

/* read from stdin, write to stdout, for easiest use in a piped toolchain */
int main()
{
   int c;
   uint16_t checksum = 0;
   uint16_t i;
   uint16_t size = 0;

   /* read in the program */
   while ((c = getchar()) != EOF)
   {
      data[size] = c;
      size++;
   }

   /* fix the "size" fields */
   data[53] = (size - 57) % 256;
   data[54] = (size - 57) / 256;
   data[57] = (size - 72) % 256;
   data[58] = (size - 72) / 256;
   data[68] = (size - 72) % 256;
   data[69] = (size - 72) / 256;
   data[70] = (size - 74) % 256;
   data[71] = (size - 74) / 256;

   /* calculate the checksum and write it out */
   for (i = 55; i < size - 2; i++)
   {
      checksum += data[i];
   }
   data[size - 2] = checksum % 256;
   data[size - 1] = checksum / 256;

   /* write out the program */
   for (i = 0; i < size; i++)
   {
      putchar(data[i]);
   }

   return 0;
}
