#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

// enum StatisticsType
// {
//     avg,
//     min_max,
//     sum
// };

class Algorithm
{
public:
    virtual Results calculate(Data& data) = 0;
    virtual ~Algorithm() = default;
};

class AvgAlgorithm : public Algorithm
{
    Results calculate(Data& data) override
    {    
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double avg = sum / data.size();
     
        return Results{StatResult{"Avg", avg}}; // r-value
    }
};

class MinMaxAlgorithm : public Algorithm
{
    Results calculate(Data& data) override
    {
        Results results;
        double min = *(std::min_element(data.begin(), data.end()));
        double max = *(std::max_element(data.begin(), data.end()));

        results.push_back(StatResult("Min", min));
        results.push_back(StatResult("Max", max));
        return results;
    }
};

class SumAlgorithm : public Algorithm
{
    Results calculate(Data& data) override
    {
        Results results;
        double sum = std::accumulate(data.begin(), data.end(), 0.0);

        results.push_back(StatResult("Sum", sum));
        return results;
    }
};

class CompositeAlgorithm : public Algorithm
{
    std::vector<std::shared_ptr<Algorithm>> stats_;
public:
    void add_statistics(std::shared_ptr<Algorithm> stat)
    {
        stats_.push_back(stat);
    }

    Results calculate(Data& data) override
    {
        Results results{};

        for(const auto& stat : stats_)
        {
            Results tmp_result = stat->calculate(data);
            results.insert(results.end(), tmp_result.begin(), tmp_result.end());
        }

        return results;
    }
};

class DataAnalyzer
{    
    std::shared_ptr<Algorithm> algorithm_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(std::shared_ptr<Algorithm> stat)
        : algorithm_{stat}
    {        
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(std::shared_ptr<Algorithm> stat)
    {
        algorithm_ = stat;
    }

    void calculate()
    {
        Results result = algorithm_->calculate(data_);
        results_.insert(results_.end(), result.begin(), result.end());
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    auto avg = std::make_shared<AvgAlgorithm>();
    auto min_max = std::make_shared<MinMaxAlgorithm>();
    auto sum = std::make_shared<SumAlgorithm>();

    auto std_stats = std::make_shared<CompositeAlgorithm>();
    std_stats->add_statistics(avg);
    std_stats->add_statistics(min_max);
    std_stats->add_statistics(sum);

    DataAnalyzer da{std_stats};
    da.load_data("stats_data.dat");
    da.calculate();    
    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_stats_data.dat");
    da.calculate();

    show_results(da.results());
}
