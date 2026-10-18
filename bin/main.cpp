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

    engine.AddPoint({{500, 360.0}, {0.0, 0.0}});
    engine.AddPoint({{505, 360.0}, {0.0, 0.0}});
    engine.AddPoint({{700, 360.0}, {0.0, 0.0}});

    std::setprecision(12);
    std::cout << std::fixed;

    // while (true) {
    //     auto state = engine.Step(Time::Clock::now());

    //     std::cout << state.GetStorage().x_.at(0) << ' ' << state.GetStorage().y_.at(0) << std::endl;
    //     std::cout << state.GetStorage().x_.at(1) << ' ' << state.GetStorage().y_.at(1) << std::endl;
    //     std::cout << std::endl;

    //     std::this_thread::sleep_for(50ms);
    // }

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape circle1(10.0);
    sf::CircleShape circle2(10.0);
    sf::CircleShape circle3(10.0);

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

        auto state = engine.Step(Time::Clock::now());

        auto storage = state.GetStorage();

        circle1.setPosition({storage.x_.at(0), storage.y_.at(0)});
        circle2.setPosition({storage.x_.at(1), storage.y_.at(1)});
        circle3.setPosition({storage.x_.at(2), storage.y_.at(2)});

        std::cout << state.GetStorage().x_.at(0) << ' ' << state.GetStorage().y_.at(0) << std::endl;
        std::cout << state.GetStorage().x_.at(1) << ' ' << state.GetStorage().y_.at(1) << std::endl;
        std::cout << state.GetStorage().x_.at(2) << ' ' << state.GetStorage().y_.at(2) << std::endl;
        std::cout << std::endl;

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        window.clear();
        window.draw(circle1);
        window.draw(circle2);
        window.draw(circle3);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}