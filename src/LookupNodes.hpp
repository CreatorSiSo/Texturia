// Really dumb data structure provided for the example.
// Note that we storing links are INDICES (not ID) to make example code shorter, obviously a bad idea for any general
// purpose code.
static void ShowExampleAppCustomNodeGraph()
{
  struct Node {
    int ID;
    char Name[32];
    ImVec2 Pos, Size;
    float Value;
    int InputsCount, OutputsCount;

    Node(int id, const char* name, const ImVec2& pos, float value, int inputs_count, int outputs_count)
    {
      ID = id;
      strncpy(Name, name, 31);
      Name[31] = 0;
      Pos = pos;
      Value = value;
      InputsCount = inputs_count;
      OutputsCount = outputs_count;
    }

    ImVec2 GetInputSlotPos(int slot_no) const
    {
      return ImVec2(Pos.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)InputsCount + 1));
    }
    ImVec2 GetOutputSlotPos(int slot_no) const
    {
      return ImVec2(Pos.x + Size.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)OutputsCount + 1));
    }
  };
  struct NodeLink {
    int InputIdx, InputSlot, OutputIdx, OutputSlot;

    NodeLink(int input_idx, int input_slot, int output_idx, int output_slot)
    {
      InputIdx = input_idx;
      InputSlot = input_slot;
      OutputIdx = output_idx;
      OutputSlot = output_slot;
    }
  };

  static ImVector<Node> nodes;
  static ImVector<NodeLink> links;
  static bool inited = false;
  static ImVec2 canvasPos = ImVec2(0.0f, 0.0f);
  static int selectedNodeID = -1;
  if (!inited) {
    nodes.push_back(Node(0, "MainTex", ImVec2(40, 50), 0.5f, 1, 1));
    nodes.push_back(Node(1, "BumpMap", ImVec2(40, 150), 0.42f, 1, 1));
    nodes.push_back(Node(2, "Combine", ImVec2(270, 80), 1.0f, 2, 2));
    links.push_back(NodeLink(0, 0, 2, 0));
    links.push_back(NodeLink(1, 0, 2, 1));
    inited = true;
  }

  int node_hovered_in_scene = -1;

  ImGui::SameLine();
  ImGui::BeginGroup();

  const float NODE_SLOT_RADIUS = 4.0f;
  const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);

  ImGui::Text("Canvas Position: (%.2f,%.2f)", canvasPos.x, canvasPos.y);
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::BeginChild("NodesCanvas", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
  ImGui::PushItemWidth(120.0f);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  draw_list->ChannelsSplit(2);
  ImVec2 offset = ImGui::GetCursorScreenPos() - canvasPos;

  // Display links
  draw_list->ChannelsSetCurrent(0); // Background
  for (int link_idx = 0; link_idx < links.Size; link_idx++) {
    NodeLink* link = &links[link_idx];
    Node* node_inp = &nodes[link->InputIdx];
    Node* node_out = &nodes[link->OutputIdx];

#if 1
    // Hermite spline
    // TODO: move to Path API
    ImVec2 p1 = offset + node_inp->GetOutputSlotPos(link->InputSlot);
    ImVec2 t1 = ImVec2(+80.0f, 0.0f);
    ImVec2 p2 = offset + node_out->GetInputSlotPos(link->OutputSlot);
    ImVec2 t2 = ImVec2(+80.0f, 0.0f);
    const int STEPS = 12;
    for (int step = 0; step <= STEPS; step++) {
      float t = (float)step / (float)STEPS;
      float h1 = +2 * t * t * t - 3 * t * t + 1.0f;
      float h2 = -2 * t * t * t + 3 * t * t;
      float h3 = t * t * t - 2 * t * t + t;
      float h4 = t * t * t - t * t;
      draw_list->PathLineTo(
          ImVec2(h1 * p1.x + h2 * p2.x + h3 * t1.x + h4 * t2.x, h1 * p1.y + h2 * p2.y + h3 * t1.y + h4 * t2.y));
    }
    draw_list->PathStroke(ImColor(200, 200, 100), false, 3.0f);
#else
    draw_list->AddLine(offset + node_inp->GetOutputSlotPos(link->InputSlot),
                       offset + node_out->GetInputSlotPos(link->OutputSlot),
                       ImColor(200, 200, 100),
                       3.0f);
#endif
  }

  // Display nodes
  for (int node_idx = 0; node_idx < nodes.Size; node_idx++) {
    Node* node = &nodes[node_idx];
    ImGui::PushID(node->ID);

    ImVec2 node_rect_min = offset + node->Pos;

    // Display node contents first
    draw_list->ChannelsSetCurrent(1); // Foreground

    bool old_any_active = ImGui::IsAnyItemActive();
    ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
    ImGui::BeginGroup(); // Lock horizontal position
    ImGui::Text("%s", node->Name);
    ImGui::SliderFloat("##value", &node->Value, 0.0f, 1.0f, "Alpha %.2f");
    float dummy_color[3] = { node->Pos.x / ImGui::GetWindowWidth(),
                             node->Pos.y / ImGui::GetWindowHeight(),
                             fmodf((float)node->ID * 0.5f, 1.0f) };
    ImGui::ColorEdit3("##color", &dummy_color[0]);
    ImGui::EndGroup();

    node->Size = ImGui::GetItemRectSize() + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
    ImVec2 node_rect_max = node_rect_min + node->Size;

    bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());

    // Display node box
    draw_list->ChannelsSetCurrent(0); // Background
    ImGui::SetCursorScreenPos(node_rect_min);
    ImGui::InvisibleButton("node", node->Size);
    if (ImGui::IsItemHovered()) { node_hovered_in_scene = node->ID; }
    bool node_moving_active = ImGui::IsItemActive();
    if (node_widgets_active || node_moving_active) selectedNodeID = node->ID;
    if (node_moving_active && ImGui::IsMouseDragging(0)) {
      node->Pos.x += ImGui::GetIO().MouseDelta.x;
      node->Pos.y += ImGui::GetIO().MouseDelta.y;
    }

    draw_list->AddRectFilled(node_rect_min,
                             node_rect_max,
                             (node_hovered_in_scene == node->ID || (selectedNodeID == node->ID)) ? ImColor(75, 75, 75)
                                                                                                 : ImColor(60, 60, 60),
                             4.0f);
    draw_list->AddRect(node_rect_min, node_rect_max, ImColor(100, 100, 100), 4.0f);
    for (int slot_idx = 0; slot_idx < node->InputsCount; slot_idx++) {
      ImVec2 pos = node->GetInputSlotPos(slot_idx);
      draw_list->AddCircleFilled(offset + pos, NODE_SLOT_RADIUS, ImColor(150, 150, 150, 150));
    }
    for (int slot_idx = 0; slot_idx < node->OutputsCount; slot_idx++) {
      ImVec2 pos = node->GetOutputSlotPos(slot_idx);
      draw_list->AddCircleFilled(offset + pos, NODE_SLOT_RADIUS, ImColor(150, 150, 150, 150));
    }

    ImGui::PopID();
  }
  draw_list->ChannelsMerge();

  // canvasPos
  if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(2, 0.0f)) {
    canvasPos.x -= ImGui::GetIO().MouseDelta.x;
    canvasPos.y -= ImGui::GetIO().MouseDelta.y;
  }

  ImGui::PopItemWidth();
  ImGui::EndChild();
  ImGui::PopStyleVar(2);
  ImGui::EndGroup();
}