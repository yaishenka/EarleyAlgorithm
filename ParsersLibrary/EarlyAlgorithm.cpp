#include "EarlyAlgorithm.hpp"

using namespace parsers;

bool EarlyAlgorithm::IsBelongToGrammar(const parsers::Grammar& grammar,
                                       const std::string& word) {
  BuildSets(grammar, word);

  Rule first_rule = grammar.GetRules()[0];
  Situation final_situation(first_rule, 1, 0);

  return situations_sets_[word.size()].find(final_situation) !=
         situations_sets_[word.size()].end();
}

void EarlyAlgorithm::BuildSets(const parsers::Grammar& grammar,
                               const std::string& word) {
  situations_sets_.clear();
  situations_sets_.resize(word.size() + 1);

  Rule first_rule = grammar.GetRules()[0];

  situations_sets_[0].emplace(first_rule, 0, 0);

  ssize_t current_size = -1;

  while (current_size != situations_sets_[0].size()) {
    current_size = situations_sets_[0].size();

    Predict(0, grammar);
    Complete(0);
  }

  for (size_t i = 1; i < word.size() + 1; ++i) {
    Scan(i - 1, word[i - 1]);

    current_size = -1;

    while (current_size != situations_sets_[i].size()) {
      current_size = situations_sets_[i].size();

      Predict(i, grammar);
      Complete(i);
    }
  }
}

void EarlyAlgorithm::Predict(size_t situation_set_number,
                             const Grammar& grammar) {
  for (const auto& situation : situations_sets_[situation_set_number]) {
    char needed_start = situation.GetCurrentSymbol();
    for (const auto& rule : grammar.GetRulesWithMatchingStart(needed_start)) {
      situations_sets_[situation_set_number].emplace(rule, 0,
                                                     situation_set_number);
    }
  }
}

void EarlyAlgorithm::Scan(size_t situation_set_number, char symbol) {
  for (const auto& situation : situations_sets_[situation_set_number]) {
    if (situation.GetCurrentSymbol() == symbol) {
      situations_sets_[situation_set_number + 1].emplace(
          situation.rule, situation.point_position + 1,
          situation.begin_position);
    }
  }
}

void EarlyAlgorithm::Complete(size_t situation_set_number) {
  for (const auto& situation : situations_sets_[situation_set_number]) {
    if (situation.IsCompleted()) {
      for (const auto& possible_situation :
           situations_sets_[situation.begin_position]) {
        if (possible_situation.GetCurrentSymbol() ==
            situation.rule.GetStartState()) {
          situations_sets_[situation_set_number].emplace(
              possible_situation.rule, possible_situation.point_position + 1,
              possible_situation.begin_position);
        }
      }
    }
  }
}