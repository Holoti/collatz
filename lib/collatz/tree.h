#pragma once

#include <compare>
#include <cstdint>
#include <expected>
#include <set>
#include <unordered_map>
#include <vector>

using Depth = uint64_t;

using VertexId = uint64_t;

struct Vertex {
    VertexId id;

    std::strong_ordering operator<=>(const Vertex& other) const = default;
};

template <>
struct std::hash<Vertex> {
    size_t operator()(const Vertex& k) const { return std::hash<uint64_t>{}(k.id); }
};

struct Edge {
    Vertex from;
    Vertex to;

    std::strong_ordering operator<=>(const Edge& other) const = default;
};

class ITree {
   public:
    virtual bool AddEdge(Edge edge) = 0;

    virtual bool AddVertex(Vertex vertex) = 0;

    virtual const std::set<Vertex>& GetVertices() const = 0;

    enum class GetLayerDiagnostic { RootAbsent, LayerEmpty };
    virtual std::expected<std::vector<Vertex>, GetLayerDiagnostic> GetLayer(Vertex root, Depth depth) const = 0;

    ~ITree() = default;
};

// class MatrixTree : public ITree {
//    public:
//     MatrixTree(const std::vector<std::vector<BigInt>>& matrix);
// };

class IncidenceListTree : public ITree {
   public:
    IncidenceListTree() = default;

    IncidenceListTree(const IncidenceListTree& other) = default;

    IncidenceListTree(const std::unordered_map<Vertex, std::set<Edge>>& incidence_list);

    virtual bool AddEdge(Edge edge) override;

    virtual bool AddVertex(Vertex vertex) override;

    virtual const std::set<Vertex>& GetVertices() const override { return vertices_; }

    virtual std::expected<std::vector<Vertex>, GetLayerDiagnostic> GetLayer(Vertex root, Depth depth) const override;

   private:
    std::set<Vertex> vertices_;
    std::unordered_map<Vertex, std::set<Edge>> incidence_list_;

    std::vector<Vertex> GetLayerImpl(Vertex v, Vertex parent, Depth depth, Depth current_depth) const;
};

// class EdgesListTree : public ITree {
//    public:
//     EdgesListTree(const std::vector<Edge>& edge_list);
// };
