#include <mix_op.h>


void set_overflow(MIX_SIM* sim, int flag) {
  sim->overflow=!(!(flag));
}

void set_compare_indicator (MIX_SIM* sim, int flag) {
  if (flag > 0) {
    sim->compare_indicator=1;
  } else if (flag==0) {
    sim->compare_indicator=0;
  } else {
    sim->compare_indicator=-1;
  }
}

void set_cell_value (MIX_CELL* cell,int value) {
  cell->value=value;
}


void load_cell(MIX_CELL* dest, MIX_CELL* orig) {
  dest->value=orig->value;
}

void load_word(MIX_WORD* dest, MIX_WORD* orig, int field) {
  int i,j;
  int L,R;
  L=field/8;
  R=field%8;
  if (L==0) {
    load_cell(dest->cell[0],orig->cell[0]);
    L++;
  }
  MIX_CELL* current;
  for (i=R,j=MIX_WORD_BITS-1;i>=L;i--,j--) {
    current=dest->cell[j];
    load_cell(current,orig->cell[i]);
  }
}

void store_cell (MIX_CELL* dest, MIX_CELL* target ) {
  load_cell(target,dest);
}
void store_word (MIX_WORD* dest , MIX_WORD* target, int field) {
  int i,j;
  int L,R;
  L=field/8;
  R=field%8;
  if (L==0) {
    store_cell(dest->cell[0],target->cell[0]);
    L++;
  }
  MIX_CELL* current;
  for (i=R,j=MIX_WORD_BITS-1;i>=L;i--,j--) {
    current=dest->cell[j];
    store_cell(current,target->cell[i]);
  }
}



#ifdef MIX_OP_DEBUG
void createA (MIX_WORD* word) {
  set_cell_value(word->cell[0],10);
  set_cell_value(word->cell[1],12);
  set_cell_value(word->cell[2],13);
  set_cell_value(word->cell[3],14);
  set_cell_value(word->cell[4],15);
  set_cell_value(word->cell[5],16);
}
void createB (MIX_WORD* word) {
  set_cell_value(word->cell[0],40);
  set_cell_value(word->cell[1],39);
  set_cell_value(word->cell[2],38);
  set_cell_value(word->cell[3],37);
  set_cell_value(word->cell[4],36);
  set_cell_value(word->cell[5],35);
}
int main () {


  MIX_WORD A,B;
  init_word(&A);
  init_word(&B);
  createA(&A);
  createB(&B);

  print_word(&A,5);
  print_word(&B,5);


  /* hline("after load cell"); */
  /* load_cell(A.cell[4],B.cell[3]); */
  
  /* print_word(&A,5); */
  /* print_word(&B,5); */
  
  
  hline("load word");
  int i=0,j=0;
  MIX_WORD C;
  
  createA(&A);
  load_word(&A,&B,11);
  print_word(&A,5);
  print_word(&B,5);
  
  createA(&A);
  createB(&B);


  hline ("store cell");

  MIX_CELL X;
  MIX_CELL Y;
  init_cell(&X);
  init_cell(&Y);
  X.value=10;
  Y.value=20;
  store_cell(&X,&Y);

  print_cell(&X,2);
  print_cell(&Y,2);
  
    

  
  hline("store word");

    
  createA(&A);
  createB(&B);

  store_word(&A,&B,5);
  print_word(&A,5);
  print_word(&B,5);

  hline("1");

    
  createA(&A);
  createB(&B);
  store_word(&A,&B,13);
  print_word(&A,5);
  print_word(&B,5);

  hline("2");
  
  createA(&A);
  createB(&B);

  store_word(&A,&B,21);
  print_word(&A,5);
  print_word(&B,5);

  
  hline("3");
  createA(&A);
  createB(&B);

  store_word(&A,&B,20);
  print_word(&A,5);
  print_word(&B,5);


  
}
#endif

