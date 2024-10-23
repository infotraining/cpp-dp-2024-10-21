#ifndef SHAPEGROUP_HPP
#define SHAPEGROUP_HPP

#include <memory>
#include <vector>

#include "shape.hpp"

namespace Drawing
{
    class ShapeGroup : public CloneableShape<ShapeGroup>
    {
        std::vector<std::unique_ptr<Shape>> shapes_;

        void swap(ShapeGroup& other);

    public:
        static constexpr const char* id = "ShapeGroup";

        using iterator = std::vector<std::unique_ptr<Shape>>::iterator;
        using const_iterator = std::vector<std::unique_ptr<Shape>>::const_iterator;

        ShapeGroup() = default;

        ShapeGroup(const ShapeGroup& source);

        ShapeGroup& operator=(const ShapeGroup& source);

        ShapeGroup(ShapeGroup&&) noexcept = default;

        ShapeGroup& operator=(ShapeGroup&&) noexcept = default;

        void add(std::unique_ptr<Shape> shp);

        void move(int x, int y) override;

        void draw() const override;

        iterator begin()
        {
            return shapes_.begin();
        }

        const_iterator begin() const
        {
            return shapes_.begin();
        }

        iterator end()
        {
            return shapes_.end();
        }

        const_iterator end() const
        {
            return shapes_.end();
        }

        size_t size() const
        {
            return shapes_.size();
        }
    };
}

#endif // SHAPEGROUP_HPP
