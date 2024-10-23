#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;
using namespace boost;

using Bitmap = vector<char>;

class Sprite
{
    Bitmap bitmap_;
    const string filename_;

public:
    Sprite(const string& filename) : filename_{ filename }
    {
        cout << "Creating a sprite: " << filename_ << endl;
        load_from_file();
    }

    void render(int x, int y) const
    {
        cout << "rendering ";

        copy(bitmap_.begin(), bitmap_.end(), ostream_iterator<char>{ cout });

        cout << " mem_address(" << this << ") at " << x << ", " << y << endl;
    }

    const string& filename() const
    {
        return filename_;
    }

private:
    void load_from_file()
    {
        copy(filename_.begin(), filename_.end(), back_inserter(bitmap_));
    }
};

struct SpriteKeyExtractor
{
    const string& operator()(const Sprite& s) const
    {
        return s.filename();
    }
};

using SpriteFlyweight = flyweight<flyweights::key_value<string, Sprite, SpriteKeyExtractor> >;

constexpr const char* filenames[] = { "%", "#", "@" };

class GameBoard
{
    vector<SpriteFlyweight> sprites_;
    const int sprites_count_;

public:
    GameBoard(int sprites_count) : sprites_count_{ sprites_count }
    {
    }

    void init_sprites(uint64_t seed)
    {
        cout << "Initializing sprites on board:\n";

        mt19937_64 rnd_engine{seed};
        uniform_int_distribution<> rnd_gen{ 0, 2 };

        for (int i = 0; i < sprites_count_; ++i)
        {
            int index = rnd_gen(rnd_engine);
            sprites_.emplace_back(filenames[index]);
        }
    }

    void render(uint64_t seed)
    {
        mt19937_64 rnd_engine{seed};
        uniform_int_distribution<> rnd_gen{ 0, 100 };

        for (const Sprite& sprite : sprites_)
        {
            int x = rnd_gen(rnd_engine);
            int y = rnd_gen(rnd_engine);
            sprite.render(x, y);
        }
    }
};

int main()
{
    GameBoard game_board(20);

    game_board.init_sprites(42);

    cout << "\n\n";

    game_board.render(665);

    cout << "\n\n";

    game_board.render(665);
}
