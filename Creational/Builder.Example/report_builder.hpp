#ifndef RAPORT_BUILDER_HPP
#define RAPORT_BUILDER_HPP

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using DataRow = std::vector<std::string>;
using HtmlDocument = std::string;
using CsvDocument = std::vector<std::string>;

class ReportBuilder
{
public:    
    void parse(const std::string& file_name)
    {
        add_header(std::string("Raport from file: ") + file_name);

        begin_data();

        std::ifstream fin(file_name.c_str());

        while (!fin.eof())
        {
            std::string row;
            std::getline(fin, row);

            std::istringstream iss(row);
            DataRow data(std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>());

            add_row(data);
        }

        end_data();

        add_footer("Copyright RaportBuilder 2013");
    }

    virtual ~ReportBuilder() = default;
public:
    virtual ReportBuilder& add_header(const std::string& header_text) = 0;
    virtual ReportBuilder& begin_data() = 0;
    virtual ReportBuilder& add_row(const DataRow& data_row) = 0;
    virtual ReportBuilder& end_data() = 0;
    virtual ReportBuilder& add_footer(const std::string& footer) = 0;
};

class HtmlReportBuilder : public ReportBuilder
{
public:
    ReportBuilder& add_header(const std::string& header_text) override;
    ReportBuilder& begin_data() override;
    ReportBuilder& add_row(const DataRow& data_row) override;
    ReportBuilder& end_data() override;
    ReportBuilder& add_footer(const std::string& footer) override;
public:
    HtmlDocument get_report();

private:
    HtmlDocument doc_;
};

class CsvReportBuilder : public ReportBuilder
{
public:
    ReportBuilder& add_header(const std::string& header_text) override;
    ReportBuilder& begin_data() override;
    ReportBuilder& add_row(const DataRow& data_row) override;
    ReportBuilder& end_data() override;
    ReportBuilder& add_footer(const std::string& footer) override;
public:
    CsvDocument get_report();

private:
    CsvDocument doc_;
};

#endif // RAPORT_BUILDER_HPP
