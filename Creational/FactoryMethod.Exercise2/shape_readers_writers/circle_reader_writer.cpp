#include "circle_reader_writer.hpp"
#include "../circle.hpp"
#include "../shape_factories.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

namespace {
    bool is_registered = SingletonShapeRWFactory::instance()
        .register_creator(
            make_type_index<Circle>(), 
            [] { return make_unique<CircleReaderWriter>(); });
}
