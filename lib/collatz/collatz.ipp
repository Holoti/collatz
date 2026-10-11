#include "collatz.h"
#include "tree.h"

#include <iostream>

template <typename TreeType>
Collatz<TreeType> Collatz<TreeType>::ByLayers(VertexId depth) {
    Collatz collatz;
    
    collatz.tree_->AddEdge(Edge{1, 2});
    collatz.tree_->AddEdge(Edge{2, 4});
    collatz.tree_->AddEdge(Edge{4, 8});

    for (Depth current_depth = 3; current_depth <= depth; ++current_depth) {
        auto layer = collatz.tree_->GetLayer(Vertex{1}, current_depth);

        std::cout << "ByLayers: " << current_depth << ' ' << layer.has_value() << std::endl;

        if (!layer.has_value()) {
            break;
        }

        for (const auto& vertice : *layer) {
            std::cout << vertice.id << ' ';

            VertexId number = vertice.id;

            VertexId a = number * 2;
            Edge edge_a{number, a};
            if (!collatz.tree_->AddEdge(edge_a)) {
                throw std::runtime_error("Collatz::ByLayersImpl: failed to add edge_a");
            }

            VertexId b = (number - 1) / 3;
            if (b % 2 == 1 && b * 3 + 1 == number) {
                Edge edge_b{number, b};
                if (!collatz.tree_->AddEdge(edge_b)) {
                    throw std::runtime_error("Collatz::ByLayersImpl: failed to add edge_b");
                }
            }

            std::cout << std::endl;
        }
    }

    return collatz;
}
