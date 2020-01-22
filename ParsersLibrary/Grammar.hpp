/*!
 * @author yaishenka
 * @date 2020-01-22
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace parsers {
const std::string rule_delimiter = "->";
const std::vector<char> default_alphabet = {'a', 'b', 'c'};

class IncorrectRuleFormat : public std::exception {
  const char* what() const noexcept override { return "Incorrect rule format"; }
};

class StartStateError : public std::exception {
  const char* what() const noexcept override {
    return "Start state too long or too short (supports only N->finish format)";
  }
};


/*!
 * \brief Class for contain grammar rule
 *
 * This class define grammar rules. Rules format: N->(alphabet + N)* N (alphabet + N)*
 * Empty word <=> empty finish: S->
 */
class Rule {
 public:
  /*!
   * Construct empty rule
   */
  Rule();

  /*!
   * Construct rule from string
   * @param rule string in format N->(alphabet + N)* N (alphabet + N)*
   */
  explicit Rule(const std::string& rule);
  Rule(const Rule&) = default;
  Rule(Rule&&) = default;
  Rule& operator=(const Rule&) = default;
  Rule& operator=(Rule&&) = default;

  char GetStartState() const { return start_; }
  std::string GetFinishState() const { return finish_; }

  bool operator<(const Rule& other) const;

  bool operator==(const Rule& other) const;

  friend std::istream& operator>>(std::istream& in, Rule& rule);
  friend std::ostream& operator<<(std::ostream& out, const Rule& rule);

 private:
  char start_;
  std::string finish_;
};

std::istream& operator>>(std::istream& in, Rule& rule);
std::ostream& operator<<(std::ostream& out, const Rule& rule);


/*!
 * \brief This class define grammar
 *
 * Contains alphabet and rules
 */
class Grammar {
 public:
  explicit Grammar(std::vector<char>&& alphabet);
  explicit Grammar(const std::vector<char>& alphabet = default_alphabet);
  Grammar(std::vector<Rule>&& rules, std::vector<char>&& alphabet);
  explicit Grammar(const std::vector<Rule>& rules,
                   const std::vector<char>& alphabet = default_alphabet);
  Grammar(const std::vector<Rule>& rules, std::vector<char>&& alphabet);
  explicit Grammar(std::vector<Rule>&& rules,
                   const std::vector<char>& alphabet = default_alphabet);

  Grammar(const Grammar&) = default;
  Grammar(Grammar&&) = default;
  Grammar& operator=(const Grammar&) = default;
  Grammar& operator=(Grammar&&) = default;

  size_t GetRulesCount() const { return rules_.size(); }
  std::vector<Rule> GetRules() const { return rules_; }

  std::vector<char> GetAlphabet() const { return alphabet_; }

  void AddRule(Rule rule);

  /*!
   * Method to get rules where rule.start == start
   * @param start  char \in N
   * @return vector of matching rules
   */
  std::vector<Rule> GetRulesWithMatchingStart(char start) const;

  friend std::istream& operator>>(std::istream& in, Grammar& grammar);
  friend std::ostream& operator<<(std::ostream& out, const Grammar& grammar);

 private:
  std::vector<Rule> rules_;
  std::vector<char> alphabet_;
};

}  // namespace parsers
