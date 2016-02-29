#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dbg.h"
#include "XMLIO.h"
#include "strs.h"

#include <mcheck.h>


int main(int argc, char** argv)
{
  mtrace();

  OpenDbgFile();
	
  if (argc < 2){
    printf("%d : usage : replacespace.exe inputfilename", argc);
    abort();
    CloseDbgFile();
    return 1;
  }
	
  char inputfilename[1024] = { 0 };
  char outputfilename[1024] = { 0 };
  char addname[256];

  strcpy_s(inputfilename, 1024, *(argv + 1));
  strcpy(addname, ".conv0");
  stradd_s(inputfilename, addname, outputfilename, 1024);


  int ret;
  CXMLIO* infile;
  infile = new CXMLIO();
  if(!infile){
    abort();
    exit(1);
  }
  ret = infile->OpenXMLFile(inputfilename, 0);
  if (ret){
    abort();
    fprintf(stderr, "inputfile open error %s !!!", inputfilename);
    CloseDbgFile();
    return 1;
  }


  CXMLIO* outfile;
  outfile = new CXMLIO();
  if(!outfile){
    abort();
    exit(1);
  }
  ret = outfile->OpenXMLFile(outputfilename, 1);
  if (ret){
    fprintf(stderr, "outputfile open error %s!!!", outputfilename);
    abort();
    CloseDbgFile();
    return 1;
  }

  char strblock[XMLIOLINELEN] = { 0 };
  

  int endflag = 0;
  while (endflag == 0){
    memset(strblock, 0, sizeof(char) * XMLIOLINELEN);
    int blksize;
    blksize = infile->ReplaceSpace(strblock, XMLIOLINELEN);
    if (blksize < 0){
      //fprintf(stderr, "pat not found : strblock!!!!!!!!!!!!!!!!!!!!\n%s\n\n\n", strblock);
      outfile->Write2File((char*)strblock);
      fprintf(stderr, "ReplaceSpace end !!!!");
      endflag = 1;
    }
    else{
      //fprintf(stderr, "strblock!!!!!!!!!!!!!!!!!!!!\n%s\n\n\n", strblock);
      outfile->Write2File((char*)strblock);
    }    
  }

  
  if(infile){
    delete infile;
    infile = 0;
  }
  if(outfile){
    delete outfile;
    outfile = 0;
  }

  CloseDbgFile();
  
  muntrace();

  return 0;

}
