#include <imgui-SFML.h>
#include <imgui.h>
#include <time.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "physics/geometry_vector.h"
#include "physics/integrator.h"
#include "physics/physics_engine.h"
#include "physics/physics_state.h"
#include "physics/time_types.h"

int main() {
    using namespace Physics;

    std::shared_ptr<IIntegrator<EuclideanVector2D>> integrator = std::make_shared<Integrator<EuclideanVector2D>>();
    PhysicsEngine<EuclideanVector2D> engine(integrator, Time::Clock::now());

    // engine.AddPoint({{500, 360.0}, {0.0, -5.0}});
    // engine.AddPoint({{-200, 0.0}, {0.0, 0.0}});
    // engine.AddPoint({{200, 360.0}, {0.0, 0.0}});

    std::setprecision(12);
    std::cout << std::fixed;

    // while (true) {
    //     auto state = engine.Step(Time::Clock::now());

    //     std::cout << state.GetStorage().x_.at(0) << ' ' << state.GetStorage().y_.at(0) << std::endl;
    //     std::cout << state.GetStorage().x_.at(1) << ' ' << state.GetStorage().y_.at(1) << std::endl;
    //     std::cout << std::endl;

    //     std::this_thread::sleep_for(50ms);
    // }

    constexpr int width = 1280;
    constexpr int height = 720;

    sf::RenderWindow window(sf::VideoMode({width, height}), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // sf::CircleShape circle1(5.0);
    // sf::CircleShape circle2(5.0);
    // sf::CircleShape circle3(5.0);

    std::vector<sf::CircleShape> circles(300, sf::CircleShape(5.0));
    for (size_t i = 0; i < circles.size(); ++i) {
        engine.AddPoint({{i * 10, i * 5}, {static_cast<double>(i) / 10, 2}});
    }

    sf::CircleShape center(1.0);
    center.setFillColor(sf::Color::Red);
    center.setPosition({width / 2, height / 2});

    sf::Clock deltaClock;
    while (window.isOpen()) {
        // sf::Event event;
        // while (window.pollEvent(event)) {
        //     ImGui::SFML::ProcessEvent(event);

        //     if (event.type == sf::Event::Closed) {
        //         window.close();
        //     }
        // }

        while (const std::optional event = window.pollEvent()) {
            if (event.has_value()) {
                ImGui::SFML::ProcessEvent(window, event.value());
            }
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // circle1.setPosition({storage.x_.at(0) + width / 2, storage.y_.at(0) + height / 2});
        // circle2.setPosition({storage.x_.at(1) + width / 2, storage.y_.at(1) + height / 2});
        // circle3.setPosition({storage.x_.at(2) + width / 2, storage.y_.at(2) + height / 2});

        // std::cout << state.GetStorage().x_.at(0) << ' ' << state.GetStorage().y_.at(0) << std::endl;
        // std::cout << state.GetStorage().x_.at(1) << ' ' << state.GetStorage().y_.at(1) << std::endl;
        // std::cout << state.GetStorage().x_.at(2) << ' ' << state.GetStorage().y_.at(2) << std::endl;
        // std::cout << std::endl;

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        window.clear();
        window.draw(center);

        auto state = engine.Step(Time::Clock::now());
        auto storage = state.GetStorage();
        for (size_t i = 0; i < circles.size(); ++i) {
            circles[i].setPosition({storage.x_.at(i) + width / 2, storage.y_.at(i) + height / 2});
            // std::cout << storage.x_.at(i) << ' ' << storage.y_.at(i) << std::endl;
            window.draw(circles[i]);
        }
        std::cout << std::endl;

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}