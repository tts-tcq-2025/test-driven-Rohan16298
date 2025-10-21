#ifndef STRINGCALCULATOR_H_
#define STRINGCALCULATOR_H_

#include <string>
#include <vector>

class StringCalculator {
 public:
    int Add(const std::string &input);

 private:
    bool HasCustomDelimiter(const std::string &input) const;
    std::vector<std::string> ExtractDelimiters(const std::string &delimiterPart) const;
    void ParseCustomDelimiter(const std::string &input,
                              std::vector<std::string> &delimiters,
                              std::string &numbersPart) const;
    std::string ReplaceDelimitersWithComma(std::string temp,
                                           const std::vector<std::string> &delimiters) const;
    std::vector<int> SplitAndConvert(const std::string &numbersPart,
                                    const std::vector<std::string> &delimiters) const;
    int ConvertTokenToInt(const std::string &token) const;
    std::vector<int> GetNegatives(const std::vector<int> &numbers) const;
    void CheckNegatives(const std::vector<int> &numbers) const;
    std::string BuildNegativeNumbersMessage(const std::vector<int> &negatives) const;
    int SumNumbers(const std::vector<int> &numbers) const;
};

#endif  // STRINGCALCULATOR_H_
