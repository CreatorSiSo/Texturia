#pragma once

#include "txpch.hpp"

#include <cstdint>
#include <iterator>
#include <variant>

namespace Texturia {

struct VariantToString {
  std::string operator()(bool value) { return value ? "true" : "false"; }
  std::string operator()(char value) { return std::string(1, value); }
  std::string operator()(int value) { return std::to_string(value); }
  std::string operator()(float value) { return std::to_string(value); }
  std::string operator()(double value) { return std::to_string(value); }
  std::string operator()(const std::string& value) { return value; }
};

using NodeSocketType = std::variant<bool, int, float, char, std::string>;

struct NodeSocket {
  NodeSocketType Value;

  NodeSocket(const NodeSocketType& defaultValue) : Value(defaultValue) {}
  ~NodeSocket() = default;
};

class Node {
public:
  Node(const std::string& label = "Default Node") : m_Label(label)
  {
    m_NodeSockets.push_back(NodeSocket(true));
    m_NodeSockets.push_back(NodeSocket(1));
    m_NodeSockets.push_back(NodeSocket(1.0f));
    m_NodeSockets.push_back(NodeSocket('c'));
    m_NodeSockets.push_back(NodeSocket("string"));
  }
  ~Node() = default;

  inline std::string ToString() const
  {
    std::ostringstream os;
    os << m_Label << ": { ";
    if (!m_NodeSockets.empty()) {
      for (NodeSocket nodeSocket : m_NodeSockets) { os << std::visit(VariantToString(), nodeSocket.Value) << ", "; }
      os.seekp(-2, os.cur);
    } else {
      os << "!EMPTY!";
    }
    os << " }";
    return os.str();
  }

private:
  std::string m_Label;
  std::vector<Texturia::NodeSocket> m_NodeSockets;
};

inline std::ostream& operator<<(std::ostream& os, const Node& node)
{
  return os << node.ToString();
}

class NodesTree {
public:
  NodesTree(std::string name = "Default Node Tree") : m_Name(name) {}
  ~NodesTree() = default;

  u_int64_t AddNode(const Node& node);
  Node GetNode(const u_int64_t& ID);
  void DeleteNode(const u_int64_t& ID);
  void Clear();

  inline std::string ToString() const
  {
    std::ostringstream os;
    os << m_Name << ":";
    if (!m_Nodes.empty()) {
      for (auto node : m_Nodes) os << "\n" + std::to_string(node.first) + ": " + node.second.ToString();
    } else {
      os << " !EMPTY!";
    }
    return os.str();
  }

private:
  std::string m_Name;
  std::unordered_map<u_int64_t, Node> m_Nodes;
  u_int64_t m_LastID = 0;
};

inline std::ostream& operator<<(std::ostream& os, const NodesTree& nodesTree)
{
  return os << nodesTree.ToString();
}

} // namespace Texturia
