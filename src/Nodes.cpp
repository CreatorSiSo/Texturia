#include "Nodes.hpp"

Texturia::NodesTree::NodesTree(std::string debugLabel) : m_DebugLabel(debugLabel) {}

uint64_t Texturia::NodesTree::AddNode(const Node& node)
{
  m_LastID++;
  m_Nodes[m_LastID] = node;
  return m_LastID;
}

Texturia::Node Texturia::NodesTree::GetNode(const u_int64_t& ID)
{
  return m_Nodes[ID];
}

void Texturia::NodesTree::DeleteNode(const u_int64_t& ID)
{
  m_Nodes.erase(ID);
}

void Texturia::NodesTree::Clear()
{
  m_Nodes.clear();
}
