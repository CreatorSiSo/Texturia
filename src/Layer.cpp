#include "txpch.hpp"

#include "Layer.h"

namespace Texturia {

Layer::Layer(const std::string &debugName) : m_DebugName(debugName) {}
Layer::~Layer() {}

void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate() {}
void Layer::OnEvent() {}

} // namespace Texturia
