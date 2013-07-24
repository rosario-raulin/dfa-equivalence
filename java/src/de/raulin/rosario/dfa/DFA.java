package de.raulin.rosario.dfa;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public final class DFA {
	private int states;
	private int initial;
	private char[] alphabet;
	private Set<Integer> finalStates;
	private Map<Pair<Integer, Character>, Integer> transitions;

	public DFA(int states, int initial, String alphabet) {
		this.states = states;
		this.initial = initial;
		this.finalStates = new HashSet<Integer>();
		this.transitions = new HashMap<Pair<Integer, Character>, Integer>();
		this.alphabet = alphabet.toCharArray();
	}

	public void addTransition(Integer from, Character input, Integer to) {
		transitions.put(new Pair<Integer, Character>(from, input), to);
	}

	public void addFinalState(Integer state) {
		finalStates.add(state);
	}

	public boolean accepts(String input) {
		Integer state = initial;

		for (int i = 0; i < input.length(); ++i) {
			Pair<Integer, Character> key = new Pair<Integer, Character>(state,
					input.charAt(i));
			if (transitions.containsKey(key)) {
				state = transitions.get(key);
			} else {
				return false;
			}
		}

		return finalStates.contains(state);
	}

	public Map<Integer, List<Integer>> getEquivClasses() {
		boolean[][] table = new boolean[states][states];

		for (Integer state : finalStates) {
			for (int i = 0; i < states; ++i) {
				if (!finalStates.contains(i)) {
					table[state][i] = true;
					table[i][state] = true;
				}
			}
		}

		boolean change;
		do {
			change = false;

			for (int i = 0; i < states; ++i) {
				for (int j = 1; j < i; ++j) {
					if (i !=j && table[i][j] == false) {
						for (int k = 0; k < alphabet.length; ++k) {
							Integer t1 = transitions
									.get(new Pair<Integer, Character>(i,
											alphabet[k]));
							Integer t2 = transitions
									.get(new Pair<Integer, Character>(j,
											alphabet[k]));

							if (table[t1][t2] == true) {
								change = true;
								table[i][j] = true;
								table[j][i] = true;
							}
						}
					}
				}
			}
		} while (change == true);

		Map<Integer, List<Integer>> classes = new HashMap<Integer, List<Integer>>();
		for (int i = 0; i < states; ++i) {
			boolean newClass = true;
			for (int j = 0; j < i; ++j) {
				if (table[i][j] == false) {
					if (classes.get(j) == null) {
						List<Integer> li = new ArrayList<Integer>();
						li.add(i);
						classes.put(j, li);
					} else {
						classes.get(j).add(i);
					}
					newClass = false;
				}
			}
			if (newClass == true) {
				List<Integer> li = new ArrayList<Integer>();
				li.add(i);
				classes.put(i, li);
			}
		}

		return classes;
	}
}
