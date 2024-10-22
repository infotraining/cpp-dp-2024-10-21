#include "circle.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;

namespace {
    bool is_registered = SingletonShapeFactory::instance().register_creator(Circle::id, 
    [] { return std::make_unique<Circle>(); });
}