#ifndef __DATA_H
#define __DATA_H

#define MIX_WORD_BITS 6
#define MIX_MEM_COUNT 4000



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
void init_word (MIX_WORD* ) ;
void init_mem (MIX_MEM*);



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
