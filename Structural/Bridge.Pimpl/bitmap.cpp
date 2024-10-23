#include "bitmap.hpp"
#include <algorithm>
#include <array>

using namespace std;

struct Bitmap::Impl
{
    std::vector<char> image_;

    Impl(size_t size) : image_(size)
    {}
};

Bitmap::Bitmap(size_t size, char fill_char) : pimpl_{std::make_unique<Impl>(size)}
{
    fill_n(pimpl_->image_.begin(), pimpl_->image_.size(), fill_char);
}

Bitmap::~Bitmap()
{    
}

void Bitmap::draw()
{
    cout << "Image: ";
    for (size_t i = 0; i < pimpl_->image_.size(); ++i)
        cout << pimpl_->image_[i];
    cout << endl;
}
