#include "Grammar.hpp"

using namespace parsers;

Rule::Rule() : start_{' '} {};

Rule::Rule(const std::string& rule) {
  size_t delimiter_position = rule.find(rule_delimiter);

  if (delimiter_position == std::string::npos) {
    throw IncorrectRuleFormat();
  }

  std::string start = rule.substr(0, delimiter_position);

  if (start.size() > 1 || start.empty()) {
    throw StartStateError();
  }

  start_ = start[0];

  finish_ = rule.substr(delimiter_position + rule_delimiter.size());
}

bool Rule::operator<(const Rule& other) const {
  if (start_ == other.start_) {
    return finish_ < other.finish_;
  }

  return start_ < other.start_;
}

bool Rule::operator==(const Rule& other) const {
  return (!(*this < other) && !(other < *this));
}

std::istream& parsers::operator>>(std::istream& in, Rule& rule) {
  std::string string_rule;

  in >> string_rule;

  rule = Rule(string_rule);

  return in;
}

std::ostream& parsers::operator<<(std::ostream& out, const Rule& rule) {
  out << rule.start_ << rule_delimiter << rule.finish_;

  return out;
}

Grammar::Grammar(std::vector<char>&& alphabet)
    : alphabet_(std::move(alphabet)) {}

Grammar::Grammar(const std::vector<char>& alphabet)
    : Grammar(std::vector<char>(alphabet)) {}

Grammar::Grammar(std::vector<parsers::Rule>&& rules,
                 std::vector<char>&& alphabet)
    : rules_(std::move(rules)), alphabet_(std::move(alphabet)) {}

Grammar::Grammar(const std::vector<parsers::Rule>& rules,
                 const std::vector<char>& alphabet)
    : rules_(std::vector<Rule>(rules)),
      alphabet_(std::vector<char>(alphabet)) {}

Grammar::Grammar(const std::vector<parsers::Rule>& rules,
                 std::vector<char>&& alphabet)
    : rules_(std::vector<Rule>(rules)),
      alphabet_(std::forward<std::vector<char>>(alphabet)) {}

Grammar::Grammar(std::vector<parsers::Rule>&& rules,
                 const std::vector<char>& alphabet)
    : rules_(std::forward<std::vector<Rule>>(rules)),
      alphabet_(std::vector<char>(alphabet)) {}

void Grammar::AddRule(parsers::Rule rule) {
  rules_.emplace_back(std::move(rule));
}

std::vector<Rule> Grammar::GetRulesWithMatchingStart(char start) const {
  std::vector<Rule> matching_rules;

  for (const auto& rule : rules_) {
    if (rule.GetStartState() == start) {
      matching_rules.emplace_back(rule);
    }
  }

  return matching_rules;
}

std::istream& parsers::operator>>(std::istream& in, Grammar& grammar) {
  size_t rules_count;

  in >> rules_count;

  Rule rule;

  for (size_t i = 0; i < rules_count; ++i) {
    in >> rule;

    grammar.AddRule(rule);
  }

  return in;
}

std::ostream& parsers::operator<<(std::ostream& out, const Grammar& grammar) {
  out << "Alphabet: ";

  for (const auto& symbol : grammar.alphabet_) {
    out << symbol << " ";
  }

  out << std::endl << "Rules: " << std::endl;

  for (const auto& rule : grammar.rules_) {
    out << rule << std::endl;
  }

  return out;
}