#include "application.hpp"
#include "command.hpp"

#include <iostream>

using namespace std;

int main()
{
    Document doc;
    Terminal terminal;
    SharedClipboard shared_clipboard;
    CommandHistory cmd_history;

    Application app(terminal);
    app.add_command("Print"s, std::make_shared<PrintCmd>(doc, terminal));
    app.add_command("ToUpper"s, std::make_shared<ToUpperCmd>(doc, cmd_history));
    app.add_command("Clear"s, std::make_shared<ClearCmd>(doc, cmd_history));
    app.add_command("AddText"s, std::make_shared<AddTextCmd>(doc, terminal, cmd_history));
    app.add_command("Paste"s, std::make_shared<PasteCmd>(doc, shared_clipboard, cmd_history));
    app.add_command("Undo"s, std::make_shared<UndoCmd>(terminal, cmd_history));

    // TODO - register two commands: CopyCmd & ToLowerCmd

    app.run();
}
