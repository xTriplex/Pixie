#include "ppch.h"
#include "Core/Engine.h"
#include "Events/ApplicationEvent.h"

namespace Pixie
{
	Engine::Engine(const EngineSpecification& spec)
		: m_Spec(spec)
	{
		Init();
	}

	Engine::~Engine()
	{
		Shutdown();
	}

	void Engine::Init()
	{
		Log::Init();
		PX_CORE_INFO("Initializing PixieEngine v{}", PIXIE_VERSION);

		// Create platform independent window
		m_Window = std::unique_ptr<Window>
			(
				Window::Create(m_Spec.Title, m_Spec.Width, m_Spec.Height, m_Spec.VSync)
			);
		PX_CORE_ASSERT(m_Window, "Window creation failed!");

		// Hook-up events
		m_Window->SetEventCallback([this](Event& event) 
			{
				OnEvent(event); 
			});

		// TODO: Initialize ECS, Renderer, Auido, Scripting etc.
	}

	void Engine::Run()
	{
		m_LastFrameTime = m_Window->GetTime();

		while (m_Running)
		{
			float time = m_Window->GetTime();
			float delta = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// TODO: m_ECS->OnUpdate(delta);

			// Poll OS events and swap buffers
			m_Window->OnUpdate();

			// TODO: Rendering calls
			// e.g. Renderer2D::BeginScene(); m_ECS->GetSystem<RenderSystem>().Render(); Renderer2D::EndScene();
		}
	}

	void Engine::OnEvent(Event& event)
	{
		// Close the app if window close event
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent&)
			{
				PX_CORE_INFO("Received Window Close event, stopping engine.");
				m_Running = false;
				return true;
			});

		// TODO: Dispatch other events (resize, input etc) to layers or systems
	}

	void Engine::Shutdown()
	{
		PX_CORE_INFO("Shutting down PixieEngine");
		// TODO: m_ECS.reset();
		m_Window.reset();
	}

	Engine* CreateEngine(const EngineSpecification& spec)
	{
		return new Engine(spec);
	}
}

