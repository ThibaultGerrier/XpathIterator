#include "xpathParser.h"
#include <vector>
#include <iostream>

XpathParser::XpathParser(std::string xml, std::string iterator){
    this->doc.load_string(xml.c_str());
    pugi::xpath_query query_remote_tools(iterator.c_str());
    this->nodes = query_remote_tools.evaluate_node_set(doc);
}

int XpathParser::getNumElems(){
  return this->nodes.size();
}

std::vector<std::string> XpathParser::getData(int index, std::string selector){
  try {
    pugi::xpath_query query_remote_tools(selector.c_str());

    pugi::xpath_node_set result_nodes = query_remote_tools.evaluate_node_set(this->nodes[index]);

    std::vector<std::string> result;

    for (pugi::xpath_node_set::const_iterator it = result_nodes.begin(); it != result_nodes.end(); ++it) {
        pugi::xpath_node node = *it;
        if(node.attribute()){
          result.push_back(node.attribute().value());
        }if(node.node()){
          result.push_back(node.node().text().get());
        }
    }
    return result;
  } catch (const std::exception& e) {
    return {};
  }
}