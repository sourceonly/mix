#ifndef __DATA_H
#define __DATA_H

#define MIX_WORD_BITS 6
#define MIX_MEM_COUNT 4000
/* define magic number for REG */

#define MIX_REG_COUNT 9
#define MIX_REG_rA  0
#define MIX_REG_rX  1
#define MIX_REG_rI1 2
#define MIX_REG_rI2 3
#define MIX_REG_rI3 4
#define MIX_REG_rI4 5
#define MIX_REG_rI5 6
#define MIX_REG_rI6 7
#define MIX_REG_rJ  8
/* define magic number for DEV */
#define MIX_DEV_COUNT 10



struct list_header {
  struct list_header *prev;
  struct list_header *next; 
};

typedef struct mix_cell {
  struct list_header list_head;
  short value; 
} MIX_CELL;

typedef struct mix_word {
  MIX_CELL* cell[MIX_WORD_BITS];
  struct list_header list_head;
} MIX_WORD;

typedef struct mix_mem {
  MIX_WORD* word[MIX_MEM_COUNT];
} MIX_MEM;



static void init_list_head (struct list_header * list) {
  list->prev=list;
  list->next=list;
}

static void init_cell (MIX_CELL* cell) {
  cell->value=0;
  init_list_head(&(cell->list_head));
}



typedef struct mix_reg {
  MIX_WORD* REG[MIX_REG_COUNT];
} MIX_REG;

typedef struct mix_dev {
  MIX_WORD* REG[MIX_DEV_COUNT];
} MIX_DEV;



typedef struct mix_sim {
  MIX_MEM* mem;
  int overflow;
  int compare_indicator;
  MIX_DEV* dev;
  MIX_REG* reg;
} MIX_SIM;

void init_word (MIX_WORD* ) ;
void init_mem (MIX_MEM*);
void init_reg (MIX_REG*);
void init_dev (MIX_DEV*);
void init_sim (MIX_SIM*);


void print_cell(MIX_CELL*,int);
void print_word(MIX_WORD*,int);
void print_mem(MIX_MEM*, int);










static void list_add ( struct list_header * new, struct list_header * head) {
  new->prev=head;
  new->next=head->next;
  (new->next)->prev=new;
  head->next=new;
}



#define list_entry(ptr, typeof, member ) \
  ((typeof *) ((char *)( ptr ) - (char *) (&( ( (typeof *) 0 )->member))))


















#endif 
