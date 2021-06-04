// See https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Top-Level.html
#include <iostream>
#include "driver.hh"
#include "TreeNode.h"
#include "vector"
#include "iostream"

using namespace std;


int main (int argc, char *argv[])
{
  driver drv;
  drv.root = new TreeNode(ID,"test");

  drv.file = "inputFiles/correct1.go";
  cout << "Using File: " << drv.file << endl;

  drv.trace_parsing = true;
  drv.trace_scanning = true;

  drv.parse(drv.file);
  vector<string> out = drv.root->printTree();
  for (int i = 0; i < out.size(); ++i)
      cout << out[i] << endl;
}

