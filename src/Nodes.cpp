#include "Nodes.hpp"

Frameio::UUID Texturia::NodesTree::AddNode()
{
  Frameio::UUID uuid;
  m_Nodes[uuid] = Node("label", uuid);
  return uuid;
}

// Frameio::Ref<Texturia::Node> Texturia::NodesTree::GetNodeRef(const Frameio::UUID& uuid)
// {
//   return Frameio::Ref<Texturia::Node>(m_Nodes);
// }

void Texturia::NodesTree::DeleteNode(const Frameio::UUID& uuid)
{
  m_Nodes.erase(uuid);
}

void Texturia::NodesTree::Clear()
{
  m_Nodes.clear();
}
