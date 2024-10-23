#ifndef SHAPEGROUPREADERWRITER_HPP
#define SHAPEGROUPREADERWRITER_HPP

#include "../shape_factories.hpp"
#include "../shape_group.hpp"
#include "shape_reader_writer.hpp"

namespace Drawing
{
    namespace IO
    {
        class ShapeGroupReaderWriter : public ShapeReaderWriter
        {
            ShapeFactory& shape_factory_;
            ShapeRWFactory& shape_rw_factory_;

        public:
            ShapeGroupReaderWriter(ShapeFactory& shape_factory, ShapeRWFactory& shape_rw_factory)
                : shape_factory_{shape_factory}, shape_rw_factory_{shape_rw_factory}
            {
            }

        public:
            void read(Shape& shp, std::istream& in) override;

            void write(const Shape& shp, std::ostream& out) override;
        };
    }
}

#endif // SHAPEGROUPREADERWRITER_HPP
