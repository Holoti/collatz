#pragma once

#include <cstdint>
#include <memory>

#include "tree.h"

template <typename TreeType>
class Collatz {
   public:
    Collatz() : tree_(std::make_shared<TreeType>()) { tree_->AddVertex(Vertex{1}); }

    static Collatz ByLayers(Depth depth);
    static Collatz FromNumber(VertexId number);

    std::shared_ptr<const ITree> GetTreeCopy() const { return tree_; }

   private:
    std::shared_ptr<ITree> tree_;

    void FromNumberImpl(VertexId number);
};

#include "collatz.ipp"