#include "first_app.hpp"
#include "lve_camera.hpp"
#include "keyboard_movement_controller.hpp"
#include "point_light_system.hpp"
#include "simple_render_system.hpp"
#include "lve_buffer.hpp"
#include <glm/gtc/constants.hpp>
#include <stdlib.h>
#include <stdexcept>
#include <chrono>
#include <array>

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

//USER MANUAL
//1,2,3,4,5,6 Keys control rotation on each vehicle
// R key is used to change the lightning
// WASD controllers for moving the camera around
// Arrows keys to move the view of the camera
// 
namespace lve {
	
	FirstApp::FirstApp()
	{
		globalPool =
			LveDescriptorPool::Builder(lveDevice)
			.setMaxSets(LveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, LveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();
		loadGameObjects();
		
	}
	FirstApp::~FirstApp()
	{
	}

	void FirstApp::run()
	{
		
		std::vector<std::unique_ptr<LveBuffer>> uboBuffers(LveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < uboBuffers.size(); i++) {
			uboBuffers[i] = std::make_unique<LveBuffer>(
				lveDevice,
				sizeof(GlobalUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
			uboBuffers[i]->map();
		}

		auto globalSetLayout =
			LveDescriptorSetLayout::Builder(lveDevice)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
			.build();

		std::vector<VkDescriptorSet> globalDescriptorSets(LveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalDescriptorSets.size(); i++) {
			auto bufferInfo = uboBuffers[i]->descriptorInfo();
			LveDescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &bufferInfo)
				.build(globalDescriptorSets[i]);
		}

		SimpleRenderSystem simpleRenderSystem{
			lveDevice,
			lveRenderer.getSwapChainRenderPass(),
			globalSetLayout->getDescriptorSetLayout() };

		PointLightSystem pointLightSystem{
			lveDevice,
			lveRenderer.getSwapChainRenderPass(),
			globalSetLayout->getDescriptorSetLayout() };

		LveCamera camera{};
		
		auto viewerObject = LveGameObject::createGameObject();
		viewerObject.transform.translation.z = -8.f;
		KeyboardMovementController cameraController{};

		LveGameObject* car1 = nullptr;
		auto findCar = gameObjects.find(0);
		if (findCar != gameObjects.end()) {
			car1 = &(findCar->second);
		}

		LveGameObject* car2 = nullptr;
		findCar = gameObjects.find(2);
		if (findCar != gameObjects.end()) {
			car2 = &(findCar->second);
		}

		LveGameObject* car3 = nullptr;
		findCar = gameObjects.find(4);
		if (findCar != gameObjects.end()) {
			car3 = &(findCar->second);
		}

		LveGameObject* car4 = nullptr;
		findCar = gameObjects.find(6);
		if (findCar != gameObjects.end()) {
			car4 = &(findCar->second);
		}

		LveGameObject* car5 = nullptr;
		findCar = gameObjects.find(8);
		if (findCar != gameObjects.end()) {
			car5 = &(findCar->second);
		}

		LveGameObject* car6 = nullptr;
		findCar = gameObjects.find(10);
		if (findCar != gameObjects.end()) {
			car6 = &(findCar->second);
		}

		LveGameObject* light = nullptr;
		findCar = gameObjects.find(14);
		if (findCar != gameObjects.end()) {
			light = &(findCar->second);
		}

		LveGameObject* light2 = nullptr;
		findCar = gameObjects.find(15);
		if (findCar != gameObjects.end()) {
			light2 = &(findCar->second);
		}

		LveGameObject* light3 = nullptr;
		findCar = gameObjects.find(16);
		if (findCar != gameObjects.end()) {
			light3 = &(findCar->second);
		}

		LveGameObject* light4 = nullptr;
		findCar = gameObjects.find(17);
		if (findCar != gameObjects.end()) {
			light4 = &(findCar->second);
		}

		LveGameObject* light5 = nullptr;
		findCar = gameObjects.find(18);
		if (findCar != gameObjects.end()) {
			light5 = &(findCar->second);
		}

		LveGameObject* light6 = nullptr;
		findCar = gameObjects.find(19);
		if (findCar != gameObjects.end()) {
			light6 = &(findCar->second);
		}

		LveGameObject* light7 = nullptr;
		findCar = gameObjects.find(20);
		if (findCar != gameObjects.end()) {
			light7 = &(findCar->second);
		}

		LveGameObject* light8 = nullptr;
		findCar = gameObjects.find(21);
		if (findCar != gameObjects.end()) {
			light8 = &(findCar->second);
		}

		auto currentTime = std::chrono::high_resolution_clock::now();

		srand((unsigned)time(0));

		float rRed = rand() % 10 + 1;
		float rBlue = rand() % 10 + 1;
		float rGreen = rand() % 10 + 1;

		while (!lveWindow.shouldClose()) {

			glfwPollEvents(); //while our windows does not want to close hold window events, like clicks

			bool isCar1Moving = true;
			bool isCar2Moving = true;
			bool isCar3Moving = true;
			bool isCar4Moving = true;
			bool isCar5Moving = true;
			bool isCar6Moving = true;

			bool isLightNormal = true;

			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime =
				std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			currentTime = newTime;

			//frameTime = glm::min(frameTime, MAX_FRAME_TIME);

			cameraController.moveInPlaneXZ(lveWindow.getGLFWwindow(), frameTime, viewerObject);
			camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

			bool isKey1Pressed = false;
			bool isKey2Pressed = false;
			bool isKey3Pressed = false;
			bool isKey4Pressed = false;
			bool isKey5Pressed = false;
			bool isKey6Pressed = false;

			bool isKeyLightRPressed = false;

			if (car1 != nullptr) {
				
				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_1) == GLFW_PRESS && !isKey1Pressed) {
					isCar1Moving = !isCar1Moving;
					isKey1Pressed = true;
				}
				else if (isKey1Pressed)
				{
					isKey1Pressed = false;
				}
				if (isCar1Moving == true) {
					car1->transform.rotation.y = glm::mod(car1->transform.rotation.y + (0.2f * frameTime), glm::two_pi<float>());
					//GLFW_KEY_UP
				}
			}

			if (car2 != nullptr) {

				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_2) == GLFW_PRESS && !isKey2Pressed) {
					isCar2Moving = !isCar2Moving;
					isKey2Pressed = true;
				}
				else if (isKey2Pressed)
				{
					isKey2Pressed = false;
				}
				if (isCar2Moving == true) {
					car2->transform.rotation.y = glm::mod(car2->transform.rotation.y + (0.2f * frameTime), glm::two_pi<float>());
					//GLFW_KEY_UP
				}
			}

			if (car3 != nullptr) {

				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_3) == GLFW_PRESS && !isKey3Pressed) {
					isCar3Moving = !isCar3Moving;
					isKey3Pressed = true;
				}
				else if (isKey3Pressed)
				{
					isKey3Pressed = false;
				}
				if (isCar3Moving == true) {
					car3->transform.rotation.y = glm::mod(car3->transform.rotation.y + (0.2f * frameTime), glm::two_pi<float>());
					//GLFW_KEY_UP
				}
			}

			if (car4 != nullptr) {

				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_4) == GLFW_PRESS && !isKey4Pressed) {
					isCar4Moving = !isCar4Moving;
					isKey4Pressed = true;
				}
				else if (isKey4Pressed)
				{
					isKey4Pressed = false;
				}
				if (isCar4Moving == true) {
					car4->transform.rotation.y = glm::mod(car4->transform.rotation.y + (0.2f * frameTime), glm::two_pi<float>());
					//GLFW_KEY_UP
				}
			}

			if (car5 != nullptr) {

				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_5) == GLFW_PRESS && !isKey5Pressed) {
					isCar5Moving = !isCar5Moving;
					isKey5Pressed = true;
				}
				else if (isKey5Pressed)
				{
					isKey5Pressed = false;
				}
				if (isCar5Moving == true) {
					car5->transform.rotation.y = glm::mod(car5->transform.rotation.y + (0.2f * frameTime), glm::two_pi<float>());
					//GLFW_KEY_UP
				}
			}

			if (car6 != nullptr) {

				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_6) == GLFW_PRESS && !isKey6Pressed) {
					isCar6Moving = !isCar6Moving;
					isKey6Pressed = true;
				}
				else if (isKey6Pressed)
				{
					isKey6Pressed = false;
				}
				if (isCar6Moving == true) {
					car6->transform.rotation.y = glm::mod(car6->transform.rotation.y + (0.2f * frameTime), glm::two_pi<float>());
				}
			}

			if (light != nullptr) {
				

				if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_R) == GLFW_PRESS && !isKeyLightRPressed) {
					isLightNormal = !isLightNormal;
					isKeyLightRPressed = true;
				}
				else if (isKeyLightRPressed)
				{
					isKeyLightRPressed = false;
				}
				if (isLightNormal == false) {
					light->color = { rRed, rBlue, rGreen };
					light2->color = { rRed, rBlue, rGreen };
					light3->color = { rRed, rBlue, rGreen };
					light4->color = { rRed, rBlue, rGreen };
					light5->color = { rRed, rBlue, rGreen };
					light6->color = { rRed, rBlue, rGreen };
					light7->color = { rRed, rBlue, rGreen };
					light8->color = { rRed, rBlue, rGreen };
				}
				if (isLightNormal == true) {
					light->color = { 1.f, 1.f, 1.f };
					light2->color = { 1.f, 1.f, 1.f };
					light3->color = { 1.f, 1.f, 1.f };
					light4->color = { 1.f, 1.f, 1.f };
					light5->color = { 1.f, 1.f, 1.f };
					light6->color = { 1.f, 1.f, 1.f };
					light7->color = { 1.f, 1.f, 1.f };
					light8->color = { 1.f, 1.f, 1.f };
				}
				
			}

			float aspect = lveRenderer.getAspectRatio();
			// camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);
			camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

			if (auto commandBuffer = lveRenderer.beginFrame()) {
				int frameIndex = lveRenderer.getFrameIndex();
				FrameInfo frameInfo{
				frameIndex,
				frameTime,
				commandBuffer,
				camera,
				globalDescriptorSets[frameIndex],
				gameObjects };

				// update
				GlobalUbo ubo{};
				ubo.projection = camera.getProjection();
				ubo.view = camera.getView();
				ubo.inverseView = camera.getInverseView();
				pointLightSystem.update(frameInfo, ubo);
				uboBuffers[frameIndex]->writeToBuffer(&ubo);
				uboBuffers[frameIndex]->flush();

				// render
				lveRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(frameInfo);
				pointLightSystem.render(frameInfo);
				lveRenderer.endSwapChainRenderPass(commandBuffer);
				lveRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(lveDevice.device());
	}
	
	void FirstApp::loadGameObjects()
	{
		std::shared_ptr<LveModel> lveModel = LveModel::createModelFromFile(lveDevice, "models\\911.obj");

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\911.obj");
		auto porsche = LveGameObject::createGameObject();
		porsche.model = lveModel;
		porsche.transform.translation = { -6.f, 1.f, 13.f };
		porsche.transform.rotation = { 0.f, 2.5f, 3.15f};
		
		gameObjects.emplace(porsche.getId(), std::move(porsche));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\platform.obj");
		auto platform = LveGameObject::createGameObject();
		platform.model = lveModel;
		platform.transform.translation = { -5.7f, 2.3f, 13.f };
		platform.transform.rotation = { 0.f, 2.5f, 3.15f };
		platform.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(platform.getId(), std::move(platform));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\datsun.obj");
		auto datsun = LveGameObject::createGameObject();
		datsun.model = lveModel;
		datsun.transform.translation = { -5.5f, 0.f, 0.f };
		datsun.transform.rotation = { 0.f, 2.5f, 3.15f };
		datsun.transform.scale = { .25f, .25f, .25f };
		gameObjects.emplace(datsun.getId(), std::move(datsun));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\platform.obj");
		auto platform2 = LveGameObject::createGameObject();
		platform2.model = lveModel;
		platform2.transform.translation = { -5.5f, 2.3f, 0.f };
		platform2.transform.rotation = { 0.f, 2.5f, 3.15f };
		platform2.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(platform2.getId(), std::move(platform2));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\fairlady.obj");
		auto fairlady = LveGameObject::createGameObject();
		fairlady.model = lveModel;
		fairlady.transform.translation = { -5.f, 1.7f, -12.f };
		fairlady.transform.rotation = { 0.f, 2.5f, 3.15f };
		fairlady.transform.scale = { 1.7f, 1.7f, 1.7f };
		gameObjects.emplace(fairlady.getId(), std::move(fairlady));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\platform.obj");
		auto platform3 = LveGameObject::createGameObject();
		platform3.model = lveModel;
		platform3.transform.translation = { -5.f, 2.3f, -12.f };
		platform3.transform.rotation = { 0.f, 2.5f, 3.15f };
		platform3.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(platform3.getId(), std::move(platform3));

		//Cars right
		lveModel = LveModel::createModelFromFile(lveDevice, "models\\benz300.obj");
		auto benz = LveGameObject::createGameObject();
		benz.model = lveModel;
		benz.transform.translation = { 6.8f, 1.5f, 12.7f };
		benz.transform.rotation = { 0.f, 4.f, 3.15f };
		benz.transform.scale = { 2.f, 2.f, 2.f};
		gameObjects.emplace(benz.getId(), std::move(benz));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\platform.obj");
		auto platform4 = LveGameObject::createGameObject();
		platform4.model = lveModel;
		platform4.transform.translation = { 6.6f, 2.f, 12.5f };
		platform4.transform.rotation = { 0.f, 2.5f, 3.15f };
		platform4.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(platform4.getId(), std::move(platform4));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\rx7.obj");
		auto rx7 = LveGameObject::createGameObject();
		rx7.model = lveModel;
		rx7.transform.translation = { 7.1f, 2.25f, -0.1f };
		rx7.transform.rotation = { 0.f, 4.f, 3.15f };
		rx7.transform.scale = { 1.25f, 1.25f, 1.25f };
		gameObjects.emplace(rx7.getId(), std::move(rx7));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\platform.obj");
		auto platform5 = LveGameObject::createGameObject();
		platform5.model = lveModel;
		platform5.transform.translation = { 7.2f, 2.2f, 0.f };
		platform5.transform.rotation = { 0.f, 2.5f, 3.15f };
		platform5.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(platform5.getId(), std::move(platform5));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\m3.obj");
		auto m3 = LveGameObject::createGameObject();
		m3.model = lveModel;
		m3.transform.translation = { 7.5f, 0.1f, -11.5f };
		m3.transform.rotation = { 0.f, 4.f, 3.15f };
		m3.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(m3.getId(), std::move(m3));

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\platform.obj");
		auto platform6 = LveGameObject::createGameObject();
		platform6.model = lveModel;
		platform6.transform.translation = { 7.6f, 2.2f, -11.4f };
		platform6.transform.rotation = { 0.f, 2.5f, 3.15f };
		platform6.transform.scale = { .7f, .7f, .7f };
		gameObjects.emplace(platform6.getId(), std::move(platform6));

		//middle

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\testa.obj");
		auto testa = LveGameObject::createGameObject();
		testa.model = lveModel;
		testa.transform.translation = { 1.f,  1.9f,  2.f };
		testa.transform.rotation = { 0.f, 9.4f, 3.15f };
		testa.transform.scale = { 2.0f, 2.0f, 2.0f };
		gameObjects.emplace(testa.getId(), std::move(testa));

		//showroom

		lveModel = LveModel::createModelFromFile(lveDevice, "models\\Showroom.obj");
		auto showroom = LveGameObject::createGameObject();
		showroom.model = lveModel;
		showroom.transform.translation = { 1.f, 1.f, 1.f };
		showroom.transform.rotation = { 0.f, 3.1f, 3.15f };
		showroom.transform.scale = { 1.5f, 1.5f, 1.5f };
		showroom.color = { 50.f, 1.f, 1.f };
		gameObjects.emplace(showroom.getId(), std::move(showroom));


		//Lights now include specular and diffuse lightning, so 
		auto pointLight = LveGameObject::makePointLight(1.5f);
		pointLight.transform.translation = { -5.8f, -4.5f, 13.f };
		//pointLight.color = { 50.f, 1.f, 1.f };
		gameObjects.emplace(pointLight.getId(), std::move(pointLight));

		auto pointLight2 = LveGameObject::makePointLight(1.5f);
		pointLight2.transform.translation = { -5.7f, -4.5f, 5.f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight2.getId(), std::move(pointLight2));

		auto pointLight7 = LveGameObject::makePointLight(1.5f);
		pointLight7.transform.translation = { -5.2f, -4.5f, -3.5f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight7.getId(), std::move(pointLight7));

		auto pointLight3 = LveGameObject::makePointLight(1.5f);
		pointLight3.transform.translation = { -4.8f, -4.5f, -12.f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight3.getId(), std::move(pointLight3));

		//Lights right

		auto pointLight4 = LveGameObject::makePointLight(1.5f);
		pointLight4.transform.translation = { 6.5f, -4.5f, 13.6f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight4.getId(), std::move(pointLight4));

		auto pointLight5 = LveGameObject::makePointLight(1.5f);
		pointLight5.transform.translation = { 6.8f, -4.5f, 5.3f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight5.getId(), std::move(pointLight5));

		auto pointLight8 = LveGameObject::makePointLight(1.5f);
		pointLight8.transform.translation = { 7.2f, -4.5f, -2.9f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight8.getId(), std::move(pointLight8));

		auto pointLight6 = LveGameObject::makePointLight(1.5f);
		pointLight6.transform.translation = { 7.7f, -4.5f, -11.4f };
		//pointLight2.color = { 50.f, 50.f, 1.f };
		gameObjects.emplace(pointLight6.getId(), std::move(pointLight6));

	}
		
}