#include "Nodes.hpp"

#include <frameio/ImGui/Nodes.hpp>
#include <frameio/frameio.hpp>

namespace Texturia {

Node::Node(const std::string& label, Frameio::UUID uuid) : Label(label), UUID(uuid)
{
  m_NodeSockets.push_back(NodeSocket("Bool", true));
  m_NodeSockets.push_back(NodeSocket("Int", 1));
  m_NodeSockets.push_back(NodeSocket("Float", 1.0f));
  m_NodeSockets.push_back(NodeSocket("Char", 'c'));
  m_NodeSockets.push_back(NodeSocket("String", "string"));
}

void Node::OnImGuiRender()
{
  ImNodes::BeginNode(UUID);
  ImNodes::BeginNodeTitleBar();
  ImGui::TextUnformatted(Label.c_str());
  ImNodes::EndNodeTitleBar();

  ImNodes::BeginOutputAttribute(UUID + 1, ImNodesPinShape_TriangleFilled);
  ImGui::Text("Output Socket");
  ImNodes::EndOutputAttribute();

  ImNodes::BeginOutputAttribute(UUID + 2, ImNodesPinShape_QuadFilled);
  ImGui::Text("Output Socket");
  ImNodes::EndOutputAttribute();

  for (auto nodeSocket : m_NodeSockets) {
    ImNodes::BeginInputAttribute(nodeSocket.UUID, ImNodesPinShape_CircleFilled);
    ImGui::Text("Input Socket");
    ImNodes::EndInputAttribute();
  }

  ImNodes::EndNode();
}

void NodesTree::AddNode(const Node& node)
{
  auto result = m_Nodes.insert({ node.UUID, node });
  FR_ASSERT(result.second, "Node { " + node.Label + ", " + std::to_string(node.UUID) + " } already exists!");
}

// Frameio::Ref<Node> NodesTree::GetNodeRef(const Frameio::UUID& uuid)
// {
//   return Frameio::Ref<Node>(m_Nodes);
// }

void NodesTree::DeleteNode(const Frameio::UUID& uuid)
{
  m_Nodes.erase(uuid);
}

void NodesTree::Clear()
{
  m_Nodes.clear();
}

void NodesTree::OnImGuiRender()
{
  for (auto node : m_Nodes) { node.second.OnImGuiRender(); }
}

} // namespace Texturia
