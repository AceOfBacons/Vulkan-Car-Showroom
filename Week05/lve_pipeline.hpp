#pragma once
#include <string>
#include <vector>
#include "lve_device.hpp"

namespace lve {
	struct PipeLineConfigInfo{};
	class LvePipeline {
	public:
		LvePipeline(LveDevice &device,const std::string& vertFilePath, const std::string& fragFilePath, const PipeLineConfigInfo & configInfo);
		~LvePipeline() {};

		LvePipeline(const LvePipeline&) = delete;
		void operator=(const LvePipeline&) = delete;

		static PipeLineConfigInfo defaultPipeLineConfigInfo(uint32_t width, uint32_t height);

	private:
		static std::vector<char> readFile(const std::string& filepath);
		void createGraphicsPipeLine(const std::string& vertFilePath, const std::string& fragFilePath, const PipeLineConfigInfo& configInfo);
		void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		LveDevice& lveDevice;
		VkPipeline graphicsPipeLine;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
}