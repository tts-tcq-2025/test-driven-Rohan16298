#include "include/stringcalculator.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <regex>

int StringCalculator::Add(const std::string &input) {
    if (input.empty()) {
        return 0;
    }

    std::string numbersPart = input;
    std::vector<std::string> delimiters{",", "\n"};

    if (HasCustomDelimiter(input)) {
        ParseCustomDelimiter(input, delimiters, numbersPart);
    }

    std::vector<int> numbers = SplitAndConvert(numbersPart, delimiters);
    CheckNegatives(numbers);
    return SumNumbers(numbers);
}

bool StringCalculator::HasCustomDelimiter(const std::string &input) const {
    return input.size() > 2 && input[0] == '/' && input[1] == '/';
}

std::vector<std::string> StringCalculator::ExtractDelimiters(
    const std::string &delimiterPart) const {
    std::vector<std::string> delimiters;
    std::regex re(R"(\[(.*?)\])");
    auto begin = std::sregex_iterator(delimiterPart.begin(), delimiterPart.end(), re);
    auto end = std::sregex_iterator();

    for (auto i = begin; i != end; ++i) {
        delimiters.push_back(i->str(1));
    }
    return delimiters;
}

void StringCalculator::ParseCustomDelimiter(const std::string &input,
                                            std::vector<std::string> &delimiters,
                                            std::string &numbersPart) const {
    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos) {
        numbersPart = input;
        return;
    }

    std::string delimiterPart = input.substr(2, newlinePos - 2);
    numbersPart = input.substr(newlinePos + 1);

    delimiters.clear();

    AddDelimitersFromPart(delimiterPart, delimiters);
}

void StringCalculator::AddDelimitersFromPart(const std::string &delimiterPart,
                                             std::vector<std::string> &delimiters) const {
    if (!delimiterPart.empty() && delimiterPart[0] == '[') {
        delimiters = ExtractDelimiters(delimiterPart);
    } else {
        delimiters.push_back(delimiterPart);
    }
}

std::string StringCalculator::ReplaceDelimitersWithComma(
    std::string temp, const std::vector<std::string> &delimiters) const {
    for (const auto &delim : delimiters) {
        size_t pos = 0;
        while ((pos = temp.find(delim, pos)) != std::string::npos) {
            temp.replace(pos, delim.length(), ",");
            pos += 1;
        }
    }
    return temp;
}

std::vector<int> StringCalculator::SplitAndConvert(
    const std::string &numbersPart, const std::vector<std::string> &delimiters) const {
    std::vector<int> numbers;
    std::string temp = ReplaceDelimitersWithComma(numbersPart, delimiters);

    std::stringstream ss(temp);
    std::string token;
    while (std::getline(ss, token, ',')) {
        if (token.empty()) {
            throw std::invalid_argument("Invalid input: empty number detected");
        }
        numbers.push_back(ConvertTokenToInt(token));
    }
    return numbers;
}

int StringCalculator::ConvertTokenToInt(const std::string &token) const {
    try {
        return std::stoi(token);
    } catch (const std::exception &) {
        throw std::invalid_argument("Invalid number format");
    }
}

std::vector<int> StringCalculator::GetNegatives(const std::vector<int> &numbers) const {
    std::vector<int> negatives;
    for (int num : numbers) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
    return negatives;
}

void StringCalculator::CheckNegatives(const std::vector<int> &numbers) const {
    auto negatives = GetNegatives(numbers);
    if (!negatives.empty()) {
        throw std::invalid_argument(BuildNegativeNumbersMessage(negatives));
    }
}

std::string StringCalculator::BuildNegativeNumbersMessage(
    const std::vector<int> &negatives) const {
    std::string msg = "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        msg += std::to_string(negatives[i]);
        if (i != negatives.size() - 1) {
            msg += ", ";
        }
    }
    return msg;
}

int StringCalculator::SumNumbers(const std::vector<int> &numbers) const {
    int sum = 0;
    for (int num : numbers) {
        if (num <= 1000) {
            sum += num;
        }
    }
    return sum;
}
