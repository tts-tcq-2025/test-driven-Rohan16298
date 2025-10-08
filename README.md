# TDD Driven StringCalculator

**Requirement:** StringCalculator Add Method

**Purpose:**
Implement a StringCalculator class with an Add method that processes a string input containing numbers separated by delimiters and returns their sum.

**Functional Requirements:**
The Add method accepts a string input representing numbers separated by delimiters.
If the input string is empty, the method returns 0.
The method supports an unknown number of numbers in the input.
Numbers can be separated by commas (,) or new lines (\n).

Example valid input: "1\n2,3" returns 6.

Example invalid input: "1,\n" is not supported.
The method supports custom delimiters specified in the format:
"//[delimiter]\n[numbers...]"

Example: "//;\n1;2" returns 3.

The custom delimiter can be of any length, e.g., "//[***]\n1***2***3" returns 6.
Negative numbers in the input cause the method to throw an exception with the message "negatives not allowed" followed by the list of negative numbers found.
Numbers greater than 1000 are ignored in the sum.
All existing scenarios (default delimiters, new lines, custom delimiters) must be supported simultaneously.

**Quality Parameters:**
Maximum Cyclomatic Complexity Number (CCN) per function: 3.
100% line and branch coverage through unit tests.
Test-Driven Development (TDD) approach: write the smallest failing test first, implement minimal code to pass, then refactor.



**Suggested TDD Steps**
Write a test for empty string input returning 0.
Implement minimal code to pass the test.
Write tests for single number input.
Implement code to handle single number.
Write tests for two numbers separated by comma.
Implement code to sum two numbers.
Write tests for unknown amount of numbers.
Implement code to handle multiple numbers.
Write tests for new line delimiter support.
Implement code to handle new lines.
Write tests for custom delimiter support.
Implement code to parse and use custom delimiters.
Write tests for negative number exception.
Implement exception throwing with all negatives listed.
Write tests for ignoring numbers > 1000.
Implement logic to ignore large numbers.
Refactor code ensuring CCN ≤ 3 and 100% coverage.
