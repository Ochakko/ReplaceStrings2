#ifdef MINMAXH
int imin(int val1, int val2);
int imax(int val1, int val2);
unsigned int uimin(unsigned int val1, unsigned int val2);
unsigned int uimax(unsigned int val1, unsigned int val2);
#else
extern int imin(int val1, int val2);
extern int imax(int val1, int val2);
extern unsigned int uimin(unsigned int val1, unsigned int val2);
extern unsigned int uimax(unsigned int val1, unsigned int val2);
#endif
