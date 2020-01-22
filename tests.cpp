/** @author yaishenka
    @date 2020-01-22 */
#include <gtest/gtest.h>
#include "ParsersLibrary/EarlyAlgorithm.cpp"

TEST(CORRECT_BRACKET_SEQUENCE, CORRECT) {
  std::vector<char> alphabet = {'(', ')'};
  std::vector<Rule> rules = {Rule("U->S"), Rule("S->(S)S"), Rule("S->S(S)"),
                             Rule("S->")};

  Grammar grammar(rules, alphabet);

  EarlyAlgorithm parser;

  std::string word = "(()(()))()";

  EXPECT_EQ(parser.IsBelongToGrammar(grammar, word), true);
}

TEST(CORRECT_BRACKET_SEQUENCE, INCORRECT) {
  std::vector<char> alphabet = {'(', ')'};
  std::vector<Rule> rules = {Rule("U->S"), Rule("S->(S)S"), Rule("S->S(S)"),
                             Rule("S->")};

  Grammar grammar(rules, alphabet);

  EarlyAlgorithm parser;

  std::string word = "((())";

  EXPECT_EQ(parser.IsBelongToGrammar(grammar, word), false);
}

TEST(PALINDROM, STRONGEST_MOUSE) {
  std::vector<char> alphabet;

  for (char letter = 'a'; letter <= 'z'; ++letter) {
    alphabet.emplace_back(letter);
  }

  alphabet.emplace_back(' ');

  std::vector<Rule> rules;

  rules.emplace_back("U->S");

  std::string start_state = "S->";

  rules.emplace_back(start_state);

  for (const auto& letter : alphabet) {
    std::string finish_state = std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
    finish_state += "S" + std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
  }

  Grammar grammar(rules, alphabet);

  std::string word = "sum summus mus";

  EarlyAlgorithm parser;

  EXPECT_EQ(parser.IsBelongToGrammar(grammar, word), true);
}

TEST(PALINDROM, MUSASUM) {
  std::vector<char> alphabet;

  for (char letter = 'a'; letter <= 'z'; ++letter) {
    alphabet.emplace_back(letter);
  }

  alphabet.emplace_back(' ');

  std::vector<Rule> rules;

  rules.emplace_back("U->S");

  std::string start_state = "S->";

  rules.emplace_back(start_state);

  for (const auto& letter : alphabet) {
    std::string finish_state = std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
    finish_state += "S" + std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
  }

  Grammar grammar(rules, alphabet);

  std::string word = "musasum";

  EarlyAlgorithm parser;

  EXPECT_EQ(parser.IsBelongToGrammar(grammar, word), true);
}

TEST(PALINDROM, SKOPA) {
  std::vector<char> alphabet;

  for (char letter = 'a'; letter <= 'z'; ++letter) {
    alphabet.emplace_back(letter);
  }

  alphabet.emplace_back(' ');

  std::vector<Rule> rules;

  rules.emplace_back("U->S");

  std::string start_state = "S->";

  rules.emplace_back(start_state);

  for (const auto& letter : alphabet) {
    std::string finish_state = std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
    finish_state += "S" + std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
  }

  Grammar grammar(rules, alphabet);

  std::string word = "sponenkov";

  EarlyAlgorithm parser;

  EXPECT_EQ(parser.IsBelongToGrammar(grammar, word), false);
}

TEST(PALINDROM, SPACES) {
  std::vector<char> alphabet;

  for (char letter = 'a'; letter <= 'z'; ++letter) {
    alphabet.emplace_back(letter);
  }

  alphabet.emplace_back(' ');

  std::vector<Rule> rules;

  rules.emplace_back("U->S");

  std::string start_state = "S->";

  rules.emplace_back(start_state);

  for (const auto& letter : alphabet) {
    std::string finish_state = std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
    finish_state += "S" + std::string(1, letter);
    rules.emplace_back(start_state + finish_state);
  }

  Grammar grammar(rules, alphabet);

  std::string word = "   ";

  EarlyAlgorithm parser;

  EXPECT_EQ(parser.IsBelongToGrammar(grammar, word), true);
}

TEST(EXCEPTIONS, EMPTY_START_STATE) {
  std::vector<char> alphabet = {'(', ')'};
  ASSERT_ANY_THROW(Rule("->(S)S"));
}

TEST(EXCEPTIONS, TOO_LONG_START_STATE) {
  std::vector<char> alphabet = {'(', ')'};
  ASSERT_ANY_THROW(Rule("S(->(S)S"));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
