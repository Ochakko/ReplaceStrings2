#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int imin(int val1, int val2)
{
  if(val1 <= val2){
    return val1;
  }else{
    return val2;
  }
}
int imax(int val1, int val2)
{
  if(val1 >= val2){
    return val1;
  }else{
    return val2;
  }
}
unsigned int uimin(unsigned int val1, unsigned int val2)
{
  if(val1 <= val2){
    return val1;
  }else{
    return val2;
  }
}
unsigned int uimax(unsigned int val1, unsigned int val2)
{
  if(val1 >= val2){
    return val1;
  }else{
    return val2;
  }
}
