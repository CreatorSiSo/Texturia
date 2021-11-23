#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

// Really dumb data structure provided for the example.
// Note that we storing links are INDICES (not ID) to make example code
// shorter, obviously a bad idea for any general purpose code.
static void ShowExampleAppCustomNodeGraph(bool *opened) {
  struct Node {
    int ID;
    char Name[32];
    ImVec2 Pos, Size;
    float Value;
    int InputsCount, OutputsCount;

    Node(int id, const char *name, const ImVec2 &pos, float value,
         int inputs_count, int outputs_count) {
      ID = id;
      strncpy(Name, name, 31);
      Name[31] = 0;
      Pos = pos;
      Value = value;
      InputsCount = inputs_count;
      OutputsCount = outputs_count;
    }

    ImVec2 GetInputSlotPos(int slot_no) const {
      return ImVec2(Pos.x, Pos.y + Size.y * ((float)slot_no + 1) /
                                       ((float)InputsCount + 1));
    }
    ImVec2 GetOutputSlotPos(int slot_no) const {
      return ImVec2(Pos.x + Size.x, Pos.y + Size.y * ((float)slot_no + 1) /
                                                ((float)OutputsCount + 1));
    }
  };
  struct NodeLink {
    int InputIdx, InputSlot, OutputIdx, OutputSlot;

    NodeLink(int input_idx, int input_slot, int output_idx, int output_slot) {
      InputIdx = input_idx;
      InputSlot = input_slot;
      OutputIdx = output_idx;
      OutputSlot = output_slot;
    }
  };

  static ImVector<Node> nodes;
  static ImVector<NodeLink> links;
  static bool inited = false;
  static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
  static int node_selected = -1;
  if (!inited) {
    nodes.push_back(Node(0, "MainTex", ImVec2(40, 50), 0.5f, 1, 1));
    nodes.push_back(Node(1, "BumpMap", ImVec2(40, 150), 0.42f, 1, 1));
    nodes.push_back(Node(2, "Combine", ImVec2(270, 80), 1.0f, 2, 2));
    links.push_back(NodeLink(0, 0, 2, 0));
    links.push_back(NodeLink(1, 0, 2, 1));
    inited = true;
  }

  int node_hovered_in_scene = -1;

  ImGui::BeginGroup();

  const float NODE_SLOT_RADIUS = 4.0f;
  const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);

  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
  ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true,
                    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
  ImGui::PushItemWidth(120.0f);

  ImDrawList *draw_list = ImGui::GetWindowDrawList();
  draw_list->ChannelsSplit(2);
  ImVec2 offset = ImGui::GetCursorScreenPos() - scrolling;

  draw_list->ChannelsSetCurrent(0); // Background

  // Render node links

  // Render nodes
  for (int node_idx = 0; node_idx < nodes.Size; node_idx++) {
    Node *node = &nodes[node_idx];
    ImGui::PushID(node->ID);

    ImVec2 node_rect_min = offset + node->Pos;

    // Display node contents first
    draw_list->ChannelsSetCurrent(1); // Foreground

    bool old_any_active = ImGui::IsAnyItemActive();
    ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
    ImGui::BeginGroup(); // Lock horizontal position
    ImGui::Text("%s", node->Name);
    ImGui::EndGroup();

    node->Size =
        ImGui::GetItemRectSize() + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
    ImVec2 node_rect_max = node_rect_min + node->Size;

    bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());

    // Render node background/box

    // Render node sockets

    ImGui::PopID();
  }
  draw_list->ChannelsMerge();

  // Scrolling
  if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() &&
      ImGui::IsMouseDragging(2, 0.0f)) {
    scrolling.x -= ImGui::GetIO().MouseDelta.x;
    scrolling.y -= ImGui::GetIO().MouseDelta.y;
  }

  ImGui::PopItemWidth();
  ImGui::EndChild();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar();
  ImGui::EndGroup();
}