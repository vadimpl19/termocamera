#include "types.h"
#include "base.h"
UINT max,ptr;
void inihist(UINT start_adr,UINT maxadr){

ptr=start_adr;
max=maxadr;
}
void addh(int h){
if (ptr<max){hrem[ptr++]=h;};
}
