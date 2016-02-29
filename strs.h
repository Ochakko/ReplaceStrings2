#ifdef STRSH
//straddはsrcとdstに同じものを指定してはいけない。
int stradd_s(char* srcstr, char* addstr, char* dststr, int dstmaxlen);
int strnadd_s(char* srcstr, char* addstr, int addlen, char* dststr, int dstmaxlen);
int strcat_s(char* srcstr, int srcmaxlen, const char* addstr);
int strncat_s(char* srcstr, int srcmaxlen, const char* addstr, int addlen);
int strcpy_s(char* dststr, int dstmaxlen, char* srcstr);
int strncpy_s(char* dststr, int dstmaxlen, char* srcstr, int cplen); 
#else
extern int stradd_s(char* srcstr, char* addstr, char* dststr, int dstmaxlen);
extern int strnadd_s(char* srcstr, char* addstr, int addlen, char* dststr, int dstmaxlen);
extern int strcat_s(char* srcstr, int srcmaxlen, const char* addstr);
extern int strncat_s(char* srcstr, int srcmaxlen, const char* addstr, int addlen);
extern int strcpy_s(char* dststr, int dstmaxlen, char* srcstr);
extern int strncpy_s(char* dststr, int dstmaxlen, char* srcstr, int cplen); 
#endif
