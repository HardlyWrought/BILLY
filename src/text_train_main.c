#include "text_train.h"

int main(int argc, char **argv)
{
  Open_Database("db/training_dict.db");
  	
  for (int i = 1; i < argc; i++)
  { 
    Train_Tagger(argv[i]);
  }
  Close_Database();
  return 55;
}
