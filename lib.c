#include "lib.h"
#include "font.h"

static int pos = -NUM_COLS;
static int le = 0;
//static char str[] = "JLAB is the most progressive unit in Jungo.{|~}";
static const char str[] = "*****  There is no need to run faster than light. No one will ever see and no one will be impressed.  *****";
//char ring[NUM_COLS];
//char ring_idx, str_pos, char_pos;
 

static inline int text(int x, int y)
{
    const unsigned char *c;

    if (x > le || x < 0)
	  return 0;

    /* Font size 8x7 */
    c = font[str[x >> 3] - ' '];
    return c[y] & (1<<(x & 0x7));
}

int point(int x, int y)
{  
    return text(x + pos, y);

}

#if 1
static inline int str_len(const char *s)
{
	int l = 0;
	
	while (*s)
	{
		l += 8/* - font[*str - ' '][7]*2*/;
		s++;
	}
		 
	return l-1;
}
#endif
#if 0
inline static void init_ring(void)
{
	int i;
	
	for (i=0; i < NUM_COLS; i++)
		ring[i][1] = i+1;
		
	ring[NUM_COLS-1][1] = 0;
	
}
#endif

void update(void)
{
    if (!le)
    {
	  /* First time length calculation */
	  le = str_len(str);
//	  init_ring();
    }
    if (pos++ > le)
	  pos = -NUM_COLS;
}
