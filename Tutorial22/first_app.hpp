#pragma once
#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_renderer.hpp"
#include "lve_model.hpp"
#include "lve_game_object.hpp"
#include "simple_render_system.hpp"
#include "lve_frame_info.hpp"
#include "lve_descriptors.hpp"

#include <memory>
#include <vector>

namespace lve {
	class FirstApp {
	public:
		FirstApp();
		~FirstApp();

		FirstApp(const LveWindow&) = delete;
		FirstApp& operator=(const LveWindow&) = delete;
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		void run();
	private:
		void sierpinski(std::vector<LveModel::Vertex>& vertices,
			int depth,
			glm::vec2 left,
			glm::vec2 right,
			glm::vec2 top);

		void loadGameObjects();

		LveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan" };
		LveDevice lveDevice{ lveWindow };
		LveRenderer lveRenderer{ lveWindow,lveDevice };

		// note: order of declarations matters
		std::unique_ptr<LveDescriptorPool> globalPool{};
		LveGameObject::Map gameObjects;

	
		
	};
}