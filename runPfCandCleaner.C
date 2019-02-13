#include "PfCandCleaner.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]){
  if(argc!=3){
    std::cout << "./runPfCandCleaner <inputfile> <outputfile>" << std::endl;
    exit(-1);
  }
  std::string input_str = std::string(argv[1]);
  std::string output_str = std::string(argv[2]);

  PfCandCleaner pfcleaner(input_str, output_str);
  pfcleaner.Init();
  pfcleaner.PfCandTreeUpdate();
  pfcleaner.TrackTreeUpdate();
  pfcleaner.Execute();
  pfcleaner.End();
  return 0;
}
