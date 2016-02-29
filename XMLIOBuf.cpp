#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <assert.h>

#include "dbg.h"
#include "minmax.h"
#include "strs.h"
#include "XMLIOBuf.h"

CXMLIOBuf::CXMLIOBuf()
{
  InitParams();
}

CXMLIOBuf::~CXMLIOBuf()
{
  DestroyObjs();
}

void CXMLIOBuf::InitParams()
{
  m_buf = 0;
  m_bufleng = 0;
  m_pos = 0;
  m_startpos = 0;
  m_isend = 0;
}

void CXMLIOBuf::DestroyObjs()
{
  if(m_buf){
    free(m_buf);
    m_buf = 0;
  }
  m_bufleng = 0;
  m_pos = 0;
  m_startpos = 0;
  m_isend = 0;
}

int CXMLIOBuf::AllocBuf(int srcbufleng)
{
  if(m_buf){
    free(m_buf);
    m_buf = 0;
  }

  if((srcbufleng < 0) || (srcbufleng > XMLIOLINELEN)){
    abort();
    return 1;
  }
  m_bufleng = srcbufleng;

  m_buf = (char*)malloc(sizeof(char) * (m_bufleng + 1));
  if(!m_buf){
    fprintf(stderr, "XMLIOBuf : SetBuf : buf alloc error !!!\n");
    abort();
    return 1;
  }
  memset(m_buf, 0, sizeof(char) * (m_bufleng + 1));

  m_pos = 0;
  m_startpos = 0;
  m_isend = 0;


  return 0;
}

int CXMLIOBuf::SetBuf(char* srcbuf, unsigned int srcbufleng)
{
  if(m_buf){
    free(m_buf);
    m_buf = 0;
  }

  if(!srcbuf){
    fprintf(stderr, "XMLIOBuf : SetBuf : srcbuf NULL error !!!\n");
    abort();
    return 1;
  }

  int srcleng = strlen(srcbuf);
  int cplen = uimin(srcleng, srcbufleng);
  
  m_bufleng = cplen;
  m_pos = 0;
  m_startpos = 0;
  m_isend = 0;

  if((m_bufleng > 0) && (cplen < XMLIOLINELEN)){
    m_buf = (char*)malloc(sizeof(char) * (m_bufleng + 1));
    if(!m_buf){
      fprintf(stderr, "XMLIOBuf : SetBuf : buf alloc error !!!\n");
      abort();
      return 1;
    }
    memset(m_buf, 0, sizeof(char) * (m_bufleng + 1));

    strncpy_s(m_buf, m_bufleng + 1, srcbuf, cplen);
  }else{
    fprintf(stderr, "XMLIOBuf : SetBuf : cplen overflow error !!!\n");
    abort();
    return 1;
  }

  return 0;
}

int CXMLIOBuf::ConvStr(char* dststr, unsigned int dstleng, unsigned int srcstart, const char* befpat, const char* aftpat)
{
  if(!dststr || !befpat || !aftpat){
    abort();
    return 1;
  }
  if((srcstart < 0) || (srcstart >= m_bufleng)){
    abort();
    return 1;
  }

  int res;
  char* befbuf = m_buf + srcstart;
  char* nextbuf = strstr(befbuf, befpat);//変換前パターン

  if (!nextbuf){
    //befbufからtdbufの最後まで書き出し
    res = strcat_s(dststr, dstleng, befbuf);
    assert(!res);
  }else{
    while (nextbuf){
      int cpleng = (int)(nextbuf - befbuf);
      if(cpleng < 0){
	abort();
      }
      //変換前パターンの前まで
      res = strncat_s(dststr, dstleng, befbuf, cpleng);
      assert(!res);
      //変換後のパターン
      res = strcat_s(dststr, dstleng, aftpat);
      assert(!res);
      
      befbuf = nextbuf + strlen(befpat);//変換前パターン分進める
      nextbuf = strstr(befbuf, befpat);//つぎの変換前パターン
      if (!nextbuf){
	//tdbufの最後まで書き出し
	res = strcat_s(dststr, dstleng, befbuf);
	assert(!res);
	nextbuf = 0;
      }
    }
  }

  return 0;
}
