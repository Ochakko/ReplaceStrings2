#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STRSH
#include "strs.h"
#include "minmax.h"

int stradd_s(char* srcstr, char* addstr, char* dststr, int dstmaxlen)
{
  if(!srcstr || !addstr || !dststr){
    return 1;
  }
  if(dstmaxlen <= 0){
    return 1;
  }

  memset(dststr, 0, dstmaxlen);
  
  int srclen = strlen(srcstr);
  int addlen = strlen(addstr);
  int newlen = srclen + addlen;

  if(newlen < dstmaxlen){
    if(srclen > 0){
      strcpy(dststr, srcstr);
      if(addlen > 0){
	strcat(dststr, addstr);
      }
    }
  }else{
    return 1;
  }
  return 0;
}

int strnadd_s(char* srcstr, char* addstr, int addlen, char* dststr, int dstmaxlen)
{
  if(!srcstr || !addstr || !dststr){
    return 1;
  }
  if(dstmaxlen <= 0){
    return 1;
  }

  memset(dststr, 0, dstmaxlen);
  
  int srclen = strlen(srcstr);
  int addlen2 = uimin(strlen(addstr), addlen);//!!!!
  int newlen = srclen + addlen2;

  if(newlen < dstmaxlen){
    if(srclen > 0){
      strcpy(dststr, srcstr);
      if(addlen2 > 0){
	strncat(dststr, addstr, addlen2);
      }
    }
  }else{
    return 1;
  }
  return 0;
}

//////////
int strcat_s(char* srcstr, int srcmaxlen, const char* addstr)
{
  if(!srcstr || !addstr){
    return 1;
  }
  if(srcmaxlen <= 0){
    return 1;
  }

  
  int srclen = strlen(srcstr);
  int addlen = strlen(addstr);
  int newlen = srclen + addlen;

  if(addlen > 0){
    if(newlen < srcmaxlen){
      strcat(srcstr, addstr);
    }else{
      return 1;
    }
  }
  return 0;
}

int strncat_s(char* srcstr, int srcmaxlen, const char* addstr, int addlen)
{
  if(!srcstr || !addstr){
    return 1;
  }
  if(srcmaxlen <= 0){
    return 1;
  }

  
  int srclen = strlen(srcstr);
  int addlen2 = uimin(strlen(addstr), addlen);//!!!!!!!!!!!!
  int newlen = srclen + addlen2;

  if(addlen2 > 0){
    if(newlen < srcmaxlen){
      strncat(srcstr, addstr, addlen2);
      *(srcstr + srclen + addlen2) = 0;
    }else{
      return 1;
    }
  }
  return 0;
}

/////////////////
int strcpy_s(char* dststr, int dstmaxlen, char* srcstr)
{
  if(!srcstr || !dststr){
    return 1;
  }
  if(dstmaxlen <= 0){
    return 1;
  }

  memset(dststr, 0, dstmaxlen);

  int srclen = strlen(srcstr);
  if((srclen > 0) && (srclen < dstmaxlen)){
    strcpy(dststr, srcstr);
  }else{
    return 1;
  }
  return 0;
}

int strncpy_s(char* dststr, int dstmaxlen, char* srcstr, int cplen)
{
  if(!srcstr || !dststr){
    return 1;
  }
  if(dstmaxlen <= 0){
    return 1;
  }

  memset(dststr, 0, dstmaxlen);

  int cplen2 = uimin(strlen(srcstr), cplen);
  if((cplen2 > 0) && (cplen2 < dstmaxlen)){
    strncpy(dststr, srcstr, cplen2);
    *(dststr + cplen2) = 0;
  }else{
    return 1;
  }
  return 0;
}
