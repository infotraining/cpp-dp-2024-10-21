#ifndef TEXT_HPP
#define TEXT_HPP

#include "paragraph.hpp"
#include "shape.hpp"
#include <string>

namespace Drawing
{
    class Text : public ShapeBase, private LegacyCode::Paragraph
    {
    public:
        static constexpr const char* id = "Text";

        Text(int x = 0, int y = 0, const std::string& text = "")
            : ShapeBase{x, y}, LegacyCode::Paragraph(text.c_str())
        {}

        void set_text(const std::string& text)
        {
            set_paragraph(text.c_str());
        }

        const std::string& text() const
        {
            return get_paragraph();
        }

        void draw() const override
        {
            render_at(coord().x, coord().y);
        }
    };
}

#endif
