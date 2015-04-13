#include <mix_data.h>
#include <malloc.h>

void init_word (MIX_WORD* word) {
  init_list_head(&(word->list_head));
  int i ;
  for (i=0;i<MIX_WORD_BITS;i++) {
    word->cell[i]=malloc(sizeof(MIX_WORD));
    init_cell(word->cell[i]);
    if (i> 0) {
      list_add(&(word->cell[i]->list_head),(&(word->cell[0]->list_head))->prev);
    }
  }
}

void init_mem (MIX_MEM * mem) {
  int i;
  for (i=0;i<MIX_MEM_COUNT;i++) {
    mem->word[i]=malloc(sizeof(MIX_WORD));
    init_word(mem->word[i]);
    if (i>0) {
      list_add(&(mem->word[i]->list_head),(&(mem->word[0]->list_head))->prev);
    }
  }
}
void init_reg (MIX_REG* reg) {
  int i;
  for (i=0;i<MIX_REG_COUNT;i++) {
    reg->reg[i]=malloc(sizeof(MIX_REG));
    init_word(reg->reg[i]);
  }
}

void init_dev (MIX_DEV* dev) {
}
void init_sim (MIX_SIM* sim) {
  sim->dev=malloc(sizeof(MIX_DEV));
  init_dev(sim->dev);
  sim->reg=malloc(sizeof(MIX_REG));
  init_reg(sim->reg);
  sim->mem=malloc(sizeof(MIX_MEM));
  init_mem(sim->mem);
  sim->overflow=0;
  sim->compare_indicator=0;
}



void print_cell(MIX_CELL* cell,int sign) {
  /* int 0 print sign only */
  /* otherwise print value */
  if (sign > 0) {
    printf(" %4d ", cell->value);
  } else {
    if (cell->value >= 32) {
      printf(" %4s ", "+");
    } else {
      printf (" %4s ", "-");
    }
  }
}
void print_word(MIX_WORD* word ,int field) {
  /* field -> 8L + R */
  int L=field/8;
  int R=field%8;
  int i ;
  printf(" FIELD:%d-%d ", L, R);
  for (i=L;i<=R;i++) {
    print_cell(word->cell[i],i);
  }
  printf("\n");
  
}
void print_mem(MIX_MEM* mem, int field) {
  /*  field -> 8000*L + R */
  int L=field/8000;
  int R=field%8000;
  int i ;
  for (i=L;i<=R;i++) {
    printf("ADDR %4d:\t",i);
    print_word(mem->word[i],5);
  }
  printf("\n");
}
void print_reg(MIX_REG* reg, int field) {
  const char* name[]={"rA",
		"rX",
		"rI1",
		"rI2",
		"rI3",
		"rI4",
		"rI5",
		"rI6",
		"rJ"};
  int i;
  for(i=0;i<MIX_REG_COUNT;i++) {
    printf("%-4s:\t",name[i]);
    print_word(reg->reg[i],field);
  }
}






void hline(const char* string) {
  printf("\n========%s==========\n",string);
}

#ifdef DATA_DEBUG
void dump_cell(MIX_CELL* cell) {
  printf("\t==========cell info========\n");
  printf("\t ADDR: %d \n ", cell);
  printf("\t PREV: %d \t NEXT: %d \n ", (cell->list_head).prev, (cell->list_head).next);
  printf("\t VALUE: %d \n", cell->value);
}

void dump_word (MIX_WORD* word) {
  int i ;
  for(i=0;i<MIX_WORD_BITS;i++) {
    printf(">>>>CELL %d\n",i);
    dump_cell(word->cell[i]);
  }
}




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  MIX_CELL A;
  MIX_CELL *B;
  B=list_entry(&(A.list_head),MIX_CELL,list_head);
  printf("A:%d\tB:%d\n",&A,B);
  hline("list_add");
  MIX_CELL C,D,E;

  init_cell(&C);
  init_cell(&D);
  init_cell(&E);
  
  dump_cell(&C);
  dump_cell(&D);
  dump_cell(&E);

  list_add(&(D.list_head),&(C.list_head));
  list_add(&(E.list_head),&(C.list_head));


  dump_cell(&C);
  dump_cell(&D);
  dump_cell(&E);



  MIX_WORD word;
  init_word(&word);
  dump_word(&word);

  MIX_MEM mem;
  init_mem(&mem);


  (&mem)->word[1234]->cell[4]->value=100;
  
  MIX_WORD* ptr1418=list_entry((&((&mem)->word[1420]->list_head))->prev->prev,MIX_WORD,list_head);
  ptr1418->cell[4]->value=1000;
  
  print_mem(&mem,3999*8000+3999);
  MIX_SIM sim;
  init_sim(&sim);
  
  print_reg((&sim)->reg, 5);
  exit(0);
}
#endif
