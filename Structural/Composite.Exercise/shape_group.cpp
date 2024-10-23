#include "shape_group.hpp"
#include "shape_factories.hpp"
#include <algorithm>

using namespace std;
using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance().register_creator(
        ShapeGroup::id, &std::make_unique<ShapeGroup>);
}

ShapeGroup::ShapeGroup(const ShapeGroup& source)
{
    std::transform(source.shapes_.begin(), source.shapes_.end(),
        std::back_inserter(shapes_),
        [](const auto& shp) { return shp->clone(); });
}

ShapeGroup& ShapeGroup::operator=(const ShapeGroup& source)
{
    ShapeGroup temp(source);
    swap(temp);

    return *this;
}

void ShapeGroup::add(std::unique_ptr<Shape> shp)
{
    shapes_.push_back(std::move(shp));
}

void ShapeGroup::move(int x, int y)
{
    for (const auto& shp : shapes_)
        shp->move(x, y);
}

void ShapeGroup::draw() const
{
    for (const auto& shp : shapes_)
        shp->draw();
}

void ShapeGroup::swap(ShapeGroup& other)
{
    shapes_.swap(other.shapes_);
}