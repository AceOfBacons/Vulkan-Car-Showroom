#pragma once
#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"

namespace lve {
	class FirstApp {
	private:
		LveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan" };
		LveDevice lveDevice{ lveWindow };
		LvePipeline lvePipeLine{lveDevice, "vert.spv", "frag.spv", LvePipeline::defaultPipeLineConfigInfo(WIDTH, HEIGHT)};

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		void run();
		
	};
}