#ifndef __MIX_OP_H
#define __MIX_OP_H

#include <mix_data.h>
void set_overflow(MIX_SIM* ,int);
void set_compare_indicator(MIX_SIM*, int);

void set_cell_value(MIX_CELL*,int);



void load_cell (MIX_CELL* , MIX_CELL* );
void load_word (MIX_WORD* , MIX_WORD* , int);



void store_cell (MIX_CELL* , MIX_CELL* ) ;
void store_word (MIX_WORD* , MIX_WORD*, int) ;







#endif
