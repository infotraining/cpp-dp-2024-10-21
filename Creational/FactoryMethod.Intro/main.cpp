#include "factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

namespace StronglyCoupled
{
    class MusicApp
    {
    public:
        MusicApp() = default;

        void play(const std::string& track_title)
        {
            // creation of product
            SpotifyService music_service("spotify_user", "rjdaslf276%2", 45);

            std::optional<Track> track = music_service.get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto& note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

using namespace ModernFactoryMethod;

class MusicApp
{
    MusicServiceCreator music_service_creator_;

public:
    MusicApp(MusicServiceCreator music_service_creator)
        : music_service_creator_(music_service_creator)
    {
    }

    void play(const std::string& track_title)
    {
        // creation of the object
        std::unique_ptr<MusicService> music_service = music_service_creator_();

        // usage of the object
        std::optional<Track> track = music_service->get_track(track_title);

        if (track)
        {
            std::cout << "Playing track: ";
            for (const auto& note : *track)
                std::cout << note << ".";
            std::cout << "|\n";
        }
        else
        {
            std::cout << "Track not found!\n";
        }
    }
};

void foo(int arg)
{
    std::cout << "foo(" << arg << ")\n";
}

struct Foo
{
    int counter = 0;

    void operator()(int arg)
    {
        ++counter;
        std::cout << "Foo::operator()(" << arg << ")\n";
    }
};

void std_function_demo()
{    
    void (*ptr_fun)(int) = foo;
    ptr_fun(42);

    Foo foonctor;
    foonctor(42);
    foonctor(42);
    assert(foonctor.counter == 2);

    //////////////////////////////////

    std::function<void(int)> f;
    f = foo;
    f(42);

    f = Foo{};
    f(665);

    f = [](int arg) { std::cout << "Lambda: " << arg << "\n"; };
    f(123);
}

// parametrized factory
using MusicServiceFactory = std::unordered_map<std::string, MusicServiceCreator>;

int main()
{
    MusicServiceFactory music_service_factory;
    music_service_factory.emplace("Tidal", TidalServiceCreator("tidal_user", "KJH8324d&df"));
    music_service_factory.emplace("Spotify", SpotifyServiceCreator("spotify_user", "rjdaslf276%2", 45));
    music_service_factory.emplace("Filesystem", []() { return std::make_unique<FilesystemMusicService>("/"); });

    std::string id_from_config = "Spotify";
    MusicApp app(music_service_factory.at(id_from_config));
    app.play("Would?");
}