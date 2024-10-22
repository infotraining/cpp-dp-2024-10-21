#include "report_builder.hpp"
#include "data_parser.hpp"
#include <fstream>
#include <iostream>

using namespace std;

constexpr auto file_name = "data_builder.txt";

HtmlDocument build_html_document()
{
    HtmlReportBuilder html_builder;

    html_builder.parse(file_name);

    return html_builder.get_report();
}

CsvDocument build_csv_document()
{
    CsvReportBuilder csv_builder;

    csv_builder.parse(file_name);

    return csv_builder.get_report();
}

int main()
{
    HtmlDocument doc_html = build_html_document();

    cout << doc_html << endl;

    ///////////////////////////////////////////////////////////
    cout << "///////////////////////////////////////////////////////////\n";

    CsvDocument csv_doc = build_csv_document();

    for (const auto& line : csv_doc)
        cout << line << endl;

    cout << "///////////////////////////////////////////////////////////\n";

    HtmlReportBuilder html_builder;

    html_builder
        .add_header("TITLE")
            .begin_data()
                .add_row({"1", "2", "3"})
                .add_row({"four", "five", "six"})
            .end_data()
        .add_footer("THE END");

    std::cout << html_builder.get_report() << "\n";

}
