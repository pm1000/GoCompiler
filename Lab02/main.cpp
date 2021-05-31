// See https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Top-Level.html
#include <iostream>
#include "driver.hh"
#include "TreeNode.h"


int
main (int argc, char *argv[])
{
  int res = 0;
  driver drv;

  drv.file = "inputFiles/correct1.go";
  cout << "Using File: " << drv.file << endl;

  drv.trace_parsing = true;
  drv.trace_scanning = true;

  drv.parse(drv.file);
  drv.root->printTree();
}

