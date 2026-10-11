#include "tree.h"

#include <iostream>
#include <stdexcept>
#include <string>

bool IncidenceListTree::AddEdge(Edge edge) {
    if (incidence_list_[edge.from].contains(edge)) {
        std::cout << "AddEdge: edge already exists" << std::endl;
        return true;
    }

    bool cycle_created = vertices_.contains(edge.from) && vertices_.contains(edge.to);
    if (cycle_created) {
        std::cerr << "AddEdge: cycle created; from, to: " << edge.from.id << ' ' << edge.to.id << std::endl;
        return false;
    }

    bool component_created = !vertices_.contains(edge.from) && !vertices_.contains(edge.to) && !vertices_.empty();
    if (component_created) {
        std::cerr << "AddEdge: component created" << std::endl;
        return false;
    }

    vertices_.emplace(edge.from);
    vertices_.emplace(edge.to);
    incidence_list_[edge.from].emplace(edge);
    incidence_list_[edge.to].emplace(Edge{edge.to, edge.from});

    return true;
}

bool IncidenceListTree::AddVertex(Vertex vertex) {
    if (!vertices_.empty()) {
        return false;
    }

    vertices_.emplace(vertex);

    return true;
}

std::expected<std::vector<Vertex>, ITree::GetLayerDiagnostic> IncidenceListTree::GetLayer(Vertex root,
                                                                                          Depth depth) const {
    if (!vertices_.contains(root)) {
        return std::unexpected(GetLayerDiagnostic::RootAbsent);
    }

    std::vector<Vertex> result = GetLayerImpl(root, root, depth, 0);

    if (result.empty()) {
        return std::unexpected(GetLayerDiagnostic::LayerEmpty);
    }

    return result;
}

std::vector<Vertex> IncidenceListTree::GetLayerImpl(Vertex v, Vertex parent, Depth depth, Depth current_depth) const {
    if (current_depth == depth) {
        return std::vector{v};
    }

    if (!incidence_list_.contains(v)) {
        return {};
    }

    std::vector<Vertex> result;

    for (auto edge : incidence_list_.at(v)) {
        if (edge.to == parent) {
            continue;
        }
        std::vector<Vertex> to_result = GetLayerImpl(edge.to, edge.from, depth, current_depth + 1);
        for (auto i : to_result) {
            result.emplace_back(i);
        }
    }

    return result;
}
