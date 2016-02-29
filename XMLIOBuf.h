#ifndef XMLIOBUFH
#define XMLIOBUFH

#define XMLIOLINELEN 65536

class CXMLIOBuf
{
 public:
  CXMLIOBuf();
  ~CXMLIOBuf();

  int SetBuf(char* srcbuf, unsigned int srcbufleng);
  int AllocBuf(int srcbufleng);
  int ConvStr(char* dststr, unsigned int dstleng, unsigned int srcstart, const char* befpat, const char* aftpat);


  char* GetBuf(){
    return m_buf;
  };
  int GetBufLeng(){
    return m_bufleng;
  };
  int GetPos(){
    return m_pos;
  };
  int GetStartPos(){
    return m_startpos;
  };
  int GetIsEnd(){
    return m_isend;
  };

  void SetPos(int srcpos){
    m_pos = srcpos;
  };
  void SetStartPos(int srcstart){
    m_startpos = srcstart;
  };
  void SetIsEnd(int srcisend){
    m_isend = srcisend;
  };

 private:
  void InitParams();
  void DestroyObjs();


 private:
  char* m_buf;
  unsigned int m_bufleng;
  int m_pos;
  int m_startpos;
  int m_isend;
};

#endif
