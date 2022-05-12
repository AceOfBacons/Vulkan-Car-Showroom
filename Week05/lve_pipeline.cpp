#include "lve_pipeline.hpp"
#include <fstream>
#include <iostream>

namespace lve {
	LvePipeline::LvePipeline(LveDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipeLineConfigInfo& configInfo)
		: lveDevice{device}
	{
		createGraphicsPipeLine(vertFilePath, fragFilePath, configInfo);
	}
	PipeLineConfigInfo LvePipeline::defaultPipeLineConfigInfo(uint32_t width, uint32_t height)
	{
		PipeLineConfigInfo configInfo{};
		return configInfo;
	}
	std::vector<char> LvePipeline::readFile(const std::string& filepath)
	{
		std::ifstream file{ filepath, std::ios::ate | std::ios::binary };

		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file: " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}
	void LvePipeline::createGraphicsPipeLine(const std::string& vertFilePath, const std::string& fragFilePath, const PipeLineConfigInfo& configInfo)
	{
		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		std::cout << "Vertex shader code size: " << vertCode.size() << "\n";
		std::cout << "Frag shader code size: " << fragCode.size() << "\n";
	}
	void LvePipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create shader module");
		}
	}
}