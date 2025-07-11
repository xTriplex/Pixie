#pragma once

#include "Core/Core.h"
#include "Core/Log.h"
#include "Platforms/Window.h"
#include "Events/Event.h"

namespace Pixie
{
	struct EngineSpecification
	{
		const char* Title = "PixieEngine";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool VSync = true;
	};

	class Engine
	{
	public:
		explicit Engine(const EngineSpecification& spec = EngineSpecification());
		~Engine();

		void Run();
		void OnEvent(Event& event);
		void Stop() { m_Running = false; }

	private:
		void Init();
		void Shutdown();

	private:
		EngineSpecification m_Spec;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		float m_LastFrameTime = 0.0f;

		// TODO: std::unique_ptr<ECS::ECSManager> m_ECS;
	};

	Engine* CreateEngine(const EngineSpecification& spec = EngineSpecification());
}
