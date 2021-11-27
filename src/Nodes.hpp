#pragma once

#include "txpch.hpp"

#include <frameio/frameio.hpp>

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
  std::string Label;
  NodeSocketType Value;

  NodeSocket(std::string label, const NodeSocketType& initialValue) : Label(label), Value(initialValue) {}
  ~NodeSocket() = default;

  inline std::string ToString() const
  {
    std::ostringstream os;
    os << Label << ": " << std::visit(VariantToString(), Value);
    return os.str();
  }
};

struct Node {
  std::string Label;
  Frameio::UUID UUID;

  Node(const std::string& label = "Default Node", Frameio::UUID uuid = Frameio::UUID()) : Label(label), UUID(uuid)
  {
    m_NodeSockets.push_back(NodeSocket("Bool", true));
    m_NodeSockets.push_back(NodeSocket("Int", 1));
    m_NodeSockets.push_back(NodeSocket("Float", 1.0f));
    m_NodeSockets.push_back(NodeSocket("Char", 'c'));
    m_NodeSockets.push_back(NodeSocket("String", "string"));
  }

  ~Node() = default;

  inline std::string ToString() const
  {
    std::ostringstream os;
    os << "{\n  Label: " << Label << ","
       << "\n  UUID: " << UUID << ","
       << "\n  Sockets: {";
    if (!m_NodeSockets.empty()) {
      for (NodeSocket nodeSocket : m_NodeSockets) { os << "\n    " << nodeSocket.ToString() << ", "; }
      os.seekp(-2, os.cur);
    } else {
      os << "!EMPTY!";
    }
    os << "\n  }\n}";
    return os.str();
  }

private:
  std::vector<Texturia::NodeSocket> m_NodeSockets;
};

inline std::ostream& operator<<(std::ostream& os, const Node& node)
{
  return os << node.ToString();
}

class NodesTree {
public:
  NodesTree(std::string label = "Default Node Tree") : m_Label(label) {}
  ~NodesTree() = default;

  Frameio::UUID AddNode();
  // Frameio::UUID AddNode(const Node& node);
  // Frameio::Ref<Node> GetNodeRef(const Frameio::UUID& uuid);
  void DeleteNode(const Frameio::UUID& uuid);
  void Clear();

  inline std::string ToString() const
  {
    std::ostringstream os;
    os << m_Label << ":";
    if (!m_Nodes.empty()) {
      for (auto node : m_Nodes) os << "\n" + node.second.ToString();
    } else {
      os << " !EMPTY!";
    }
    return os.str();
  }

private:
  std::string m_Label;
  std::unordered_map<Frameio::UUID, Node> m_Nodes;
};

inline std::ostream& operator<<(std::ostream& os, const NodesTree& nodesTree)
{
  return os << nodesTree.ToString();
}

} // namespace Texturia
