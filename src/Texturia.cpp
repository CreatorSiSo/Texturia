#include "frameio/frameio.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <imgui.h>

class GuiLayer : public Frameio::Layer {
public:
  GuiLayer()
      : Layer("Texturia: Gui"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
        m_CameraMoveDirection(0.0f) {

    // TRIANGLE
    m_TriangleVertexArray.reset(Frameio::VertexArray::Create());

    float triangleVertices[3 * 7] = {
        // clang-format off
       0.0f,  0.5f, 0.0f, 0.1f, 0.6f, 1.0f, 1.0f,
       0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.9f, 1.0f,
      -0.5f, -0.5f, 0.0f, 0.4f, 0.1f, 1.0f, 1.0f
        // clang-format on
    };

    std::shared_ptr<Frameio::VertexBuffer> triangleVertexBuffer;
    triangleVertexBuffer.reset(Frameio::VertexBuffer::Create(
        sizeof(triangleVertices), triangleVertices));

    Frameio::BufferLayout layout = {
        {Frameio::ShaderDataType::Float3, "a_Position"},
        {Frameio::ShaderDataType::Float4, "a_Color"}};

    triangleVertexBuffer->SetLayout(layout);
    m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

    uint32_t triangleIndices[3] = {0, 1, 2};

    std::shared_ptr<Frameio::IndexBuffer> triangleIndexBuffer;
    triangleIndexBuffer.reset(Frameio::IndexBuffer::Create(
        sizeof(triangleIndices) / sizeof(uint32_t), triangleIndices));

    m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);
    // END TRIANGLE

    // SQUARE
    m_SquareVertexArray.reset(Frameio::VertexArray::Create());

    float squareVertices[4 * 7] = {
        // clang-format off
      -1.6f,  0.9f, 0.0f, 0.7f, 0.3f, 0.2f, 1.0f,
       1.6f,  0.9f, 0.0f, 0.9f, 0.3f, 0.3f, 1.0f,
       1.6f, -0.9f, 0.0f, 0.7f, 0.4f, 0.2f, 1.0f,
      -1.6f, -0.9f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f
        // clang-format on
    };

    std::shared_ptr<Frameio::VertexBuffer> squareVertexBuffer;
    squareVertexBuffer.reset(
        Frameio::VertexBuffer::Create(sizeof(squareVertices), squareVertices));

    squareVertexBuffer->SetLayout(layout);
    m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

    uint32_t squareIndices[6] = {0, 1, 2, 0, 3, 2};

    std::shared_ptr<Frameio::IndexBuffer> squareIndexBuffer;
    squareIndexBuffer.reset(Frameio::IndexBuffer::Create(
        sizeof(squareIndices) / sizeof(uint32_t), squareIndices));

    m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
    // END SQUARE

    std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjectionMatrix;

            out vec3 s_Position;
            out vec4 s_Color;

            void main() {
              s_Position = a_Position;
              s_Color = a_Color;
              gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
            }
          )";

    std::string fragmentSource = R"(
            #version 330 core

            layout(location = 0) out vec4 o_Color;

            in vec3 s_Position;
            in vec4 s_Color;

            void main() {
              // o_Color = vec4(s_Position, 1.0);
              o_Color = s_Color;
            }
          )";

    std::string fragmentSourcePos = R"(
            #version 330 core

            layout(location = 0) out vec4 o_Color;

            in vec3 s_Position;
            in vec4 s_Color;

            void main() {
              o_Color = mix(s_Color, vec4(s_Position, 1.0), 0.3);
            }
          )";

    m_Shader.reset(new Frameio::Shader(vertexSource, fragmentSource));
    m_ShaderPos.reset(new Frameio::Shader(vertexSource, fragmentSourcePos));
  }

  void OnUpdate() override {
    animationTime++;

    // clang-format off
    m_CameraMoveDirection = glm::rotateZ(
      glm::vec3(0.0f, m_CameraMoveSpeed, 0.0f),
      glm::pi<float>() - glm::orientedAngle(
        glm::normalize(glm::vec2(0.0f, 1.0f)),
        glm::normalize(glm::vec2(
          // TODO Access window from layer
          Frameio::Input::GetMouseX() /  1280 * 2 - 1,
          Frameio::Input::GetMouseY() / 720 /* m_Window->GetHeight( )*/ * 2 - 1)
        )
      )
    );

    if (Frameio::Input::IsKeyDown(FR_KEY_W))
      m_Camera.SetPosition(m_Camera.GetPosition() + m_CameraMoveDirection);

    if (Frameio::Input::IsKeyDown(FR_KEY_A))
      m_Camera
          .SetPosition(m_Camera.GetPosition() + glm::vec3(-m_CameraMoveSpeed, 0.0f, 0.0f) /* glm::rotateZ(m_CameraMoveDirection, glm::half_pi<float>()) */);

    if (Frameio::Input::IsKeyDown(FR_KEY_S))
      m_Camera.SetPosition(m_Camera.GetPosition() + glm::rotateZ(m_CameraMoveDirection, glm::pi<float>()));

    if (Frameio::Input::IsKeyDown(FR_KEY_D))
      m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(m_CameraMoveSpeed, 0.0f, 0.0f) /* glm::rotateZ(m_CameraMoveDirection, -glm::half_pi<float>()) */);
    // clang-format on

    // m_Camera.SetRotation(glm::degrees(glm::orientedAngle(
    //     glm::vec2(0.0f, -1.0f),
    //     glm::normalize(glm::vec2(Input::GetMouseX() / 1280 * 2 - 1,
    //                              Input::GetMouseY() / 720 * 2 - 1)))));

    m_Camera.SetRotation(glm::sin(animationTime / 16));

    Frameio::RenderCommand::SetClearColor({0.09f, 0.09f, 0.09f, 1.0f});
    Frameio::RenderCommand::Clear();

    Frameio::Renderer::BeginScene(m_Camera);

    Frameio::Renderer::Submit(m_SquareVertexArray, m_Shader);
    Frameio::Renderer::Submit(m_TriangleVertexArray, m_ShaderPos);

    Frameio::Renderer::EndScene();
  }

  void OnImGuiRender() override {
    ImGui::DockSpaceOverViewport();

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Edit")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("View")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Help")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Platform")) {
#ifdef TX_PLATFORM_WINDOWS
        ImGui::MenuItem("Windows");
#endif
#ifdef TX_PLATFORM_LINUX
        ImGui::MenuItem("Linux");
#endif
#ifdef TX_PLATFORM_MACOS
        ImGui::MenuItem("MacOS");
#endif
        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }
  }

  void OnEvent(Frameio::Event &event) override {
    if (event.GetEventType() == Frameio::EventType::KeyTyped) {
      Frameio::KeyTypedEvent &e = (Frameio::KeyTypedEvent &)event;
      FR_TRACE((char)e.GetKeyCode());
    }
  }

private:
  std::shared_ptr<Frameio::Shader> m_Shader;
  std::shared_ptr<Frameio::Shader> m_ShaderPos;
  std::shared_ptr<Frameio::VertexArray> m_TriangleVertexArray;
  std::shared_ptr<Frameio::VertexArray> m_SquareVertexArray;

  int animationTime = 0;

  Frameio::OrthographicCamera m_Camera;
  float m_CameraMoveSpeed = 0.04f;
  glm::vec3 m_CameraMoveDirection;
};

class TexturiaApp : public Frameio::App {
public:
  TexturiaApp() { PushOverlay(new GuiLayer()); }
  ~TexturiaApp() = default;
};

Frameio::App *Frameio::CreateApp() { return new TexturiaApp(); }
