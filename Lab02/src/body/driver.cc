// See https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Parsing-Driver.html
#include "../header/driver.hh"
#include "../../FlexBisonOutput/parser.hh"

driver::driver ()
  : trace_parsing (false), trace_scanning (false)
{
  variables["one"] = 1;
  variables["two"] = 2;
}

int
driver::parse (const std::string &f)
{
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parse (*this);
  parse.set_debug_level (trace_parsing);
  int res = parse ();
  scan_end ();
  return res;
}
