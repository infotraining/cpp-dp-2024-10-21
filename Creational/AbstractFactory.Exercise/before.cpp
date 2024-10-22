#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#define MOTIF

enum class IconType
{
    none,
    ok,
    cancel,
    warning,
    error
};

class Widget
{
public:
    virtual void draw() = 0;
    virtual ~Widget() = default;
};

class Button : public Widget
{
    std::string caption_;
    IconType icon_type_;

public:
    Button(const std::string& caption, IconType icon_type)
        : caption_{caption}
        , icon_type_{icon_type}
    {
    }

    std::string caption() const
    {
        return caption_;
    }

    IconType icon() const
    {
        return icon_type_;
    }
};

class Menu : public Widget
{
    std::string text_;

public:
    Menu(const std::string& text)
        : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }
};

class MotifButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "MotifButton [ " << caption() << " ]\n";
    }
};

class MotifMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "MotifMenu { " << text() << " }\n";
    }
};

class WindowsButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "WindowsButton [ " << caption() << " ]\n";
    }
};

class WindowsMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "WindowsMenu { " << text() << " }\n";
    }
};

class WidgetFactory
{
public:
    virtual ~WidgetFactory() = default;
    virtual std::unique_ptr<Button> create_button(const std::string& caption, IconType icon_type) = 0;
    virtual std::unique_ptr<Menu> create_menu(const std::string& text) = 0;
};

class MotifFactory : public WidgetFactory
{
public:
    virtual ~MotifFactory() = default;

    std::unique_ptr<Button> create_button(const std::string& caption, IconType icon_type) override
    {
        return std::make_unique<MotifButton>(caption, icon_type);
    }

    std::unique_ptr<Menu> create_menu(const std::string& text) override
    {
        return std::make_unique<MotifMenu>(text);
    }
};

class WindowsFactory : public WidgetFactory
{
public:
    virtual ~WindowsFactory() = default;

    std::unique_ptr<Button> create_button(const std::string& caption, IconType icon_type) override
    {
        return std::make_unique<WindowsButton>(caption, icon_type);
    }

    std::unique_ptr<Menu> create_menu(const std::string& text) override
    {
        return std::make_unique<WindowsMenu>(text);
    }
};

class Window
{
    std::vector<std::unique_ptr<Widget>> widgets;

public:
    void display() const
    {
        std::cout << "######################\n";
        for (const auto& w : widgets)
            w->draw();
        std::cout << "######################\n\n";
    }

    void add_widget(std::unique_ptr<Widget> widget)
    {
        widgets.push_back(std::move(widget));
    }
};

std::unique_ptr<WidgetFactory> create_widget_factory()
{
    #ifdef MOTIF
        return std::make_unique<MotifFactory>();
    #else // WINDOWS
        return std::make_unique<WindowsFactory>();
    #endif
}

class WindowOne : public Window
{
public:
    WindowOne(WidgetFactory& factory)
    {
        add_widget(factory.create_button("OK", IconType::ok));
        add_widget(factory.create_menu("File"));
    }
};

class WindowTwo : public Window
{
public:    
    WindowTwo(WidgetFactory& factory)
    {
        add_widget(factory.create_menu("Edit"));
        add_widget(factory.create_button("OK", IconType::ok));
        add_widget(factory.create_button("Cancel", IconType::cancel));
    }
};

int main(void)
{
    auto widget_factory = create_widget_factory();

    WindowOne w1(*widget_factory);
    w1.display();

    WindowTwo w2(*widget_factory);
    w2.display();
}
