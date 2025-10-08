#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator
{
public:
    int Add(const std::string &input);

private:
    bool HasCustomDelimiter(const std::string &input) const;
    void ParseCustomDelimiter(const std::string &input, std::vector<std::string> &delimiters, std::string &numbersPart) const;
    std::vector<int> SplitAndConvert(const std::string &numbersPart, const std::vector<std::string> &delimiters) const;
    void CheckNegatives(const std::vector<int> &numbers) const;
    int SumNumbers(const std::vector<int> &numbers) const;
};

#endif // STRINGCALCULATOR_H
