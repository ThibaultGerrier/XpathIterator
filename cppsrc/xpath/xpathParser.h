//#include <napi.h>
#include <vector>
#include <memory>
#include "../pugixml/src/pugixml.hpp"

class XpathParser {
 public:
  XpathParser(std::string xml, std::string iterator);
  int getNumElems();
  std::vector<std::string> getData(int index, std::string selector);
 private:
  pugi::xpath_node_set nodes;
  pugi::xml_document doc;
};
