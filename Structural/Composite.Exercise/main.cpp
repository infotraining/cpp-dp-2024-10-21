#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "shape.hpp"
#include "shape_factories.hpp"
#include "shape_group.hpp"
#include "shape_readers_writers/shape_group_reader_writer.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

class GraphicsDoc
{
    ShapeGroup shapes_;
    ShapeFactory& shape_factory_;
    ShapeRWFactory& shape_rw_factory_;

public:
    GraphicsDoc(ShapeFactory& shape_factory, ShapeRWFactory& shape_rw_factory)
        : shape_factory_{shape_factory}, shape_rw_factory_{shape_rw_factory}
    {
    }

    void add(unique_ptr<Shape> shp)
    {
        shapes_.add(std::move(shp));
    }

    void render()
    {
        shapes_.draw();
    }

    void load(const string& filename)
    {
        ifstream file_in{filename};

        if (!file_in)
        {
            cout << "File not found!" << endl;
            exit(1);
        }

        string shape_id;
        file_in >> shape_id;

        assert(file_in);            
        assert(shape_id == "ShapeGroup");

        cout << "Loading " << shape_id << "..." << endl;

        ShapeGroupReaderWriter shape_group_rw(shape_factory_, shape_rw_factory_);
        shape_group_rw.read(shapes_, file_in);        
    }

    void save(const string& filename)
    {
        ofstream file_out{filename};
        
        ShapeGroupReaderWriter shape_group_rw(shape_factory_, shape_rw_factory_);
        shape_group_rw.write(shapes_, file_out);
    }
};

int main()
{
    cout << "Start..." << endl;

    GraphicsDoc doc(SingletonShapeFactory::instance(), SingletonShapeRWFactory::instance());

    doc.load("drawing_composite.txt");

    cout << "\n";

    doc.render();

    doc.save("new_drawing_composite.txt");
}
