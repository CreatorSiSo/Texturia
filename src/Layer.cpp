#include "txpch.hpp"

#include "Layer.hpp"

namespace Texturia {

Layer::Layer(const std::string &debugName) : m_DebugName(debugName) {}
Layer::~Layer() {}

void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate() {}
void Layer::OnEvent(Event &e) {}

} // namespace Texturia
