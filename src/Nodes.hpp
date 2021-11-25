#pragma once

#include "txpch.hpp"


namespace Texturia {

class Node {
public:
  Node(const std::string &label = "Node Label") : m_Label(label) {}
  ~Node() = default;

  inline std::string ToString() const
  {
    // clang-format off
return m_Label + R"(
  test2: ifdhfuh,
  test5: 38466
)";
    // clang-format on
  }

private:
  std::string m_Label;
};

class NodesTree {
public:
  NodesTree(std::string debugLabel = "Default");
  ~NodesTree() = default;

  u_int64_t AddNode(const Node& node);
  Node GetNode(const u_int64_t& ID);
  void DeleteNode(const u_int64_t& ID);
  void DeleteNode(u_int64_t ID[3]);
  void Clear();

  inline std::string ToString() const
  {
    std::string returnString;
    for (auto node : m_Nodes) returnString.append("\n" + std::to_string(node.first) + ": " + node.second.ToString());
    return returnString;
  }

private:
  std::string m_DebugLabel;
  std::unordered_map<u_int64_t, Node> m_Nodes;
  u_int64_t m_LastID = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Node& node)
{
  return os << node.ToString();
}

inline std::ostream& operator<<(std::ostream& os, const NodesTree& nodesTree)
{
  return os << nodesTree.ToString();
}

} // namespace Texturia
