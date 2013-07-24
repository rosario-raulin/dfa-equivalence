package de.raulin.rosario.dfa;

import java.util.List;
import java.util.Map;

public final class Main {

	public static void main(String[] args) {

		DFA d = new DFA(6, 0, "ab");
		
		d.addFinalState(0);
	    d.addFinalState(2);
	    
	    d.addTransition(0, 'a', 1);
	    d.addTransition(0, 'b', 3);
	    d.addTransition(1, 'a', 4);
	    d.addTransition(1, 'b', 2);
	    d.addTransition(2, 'a', 1);
	    d.addTransition(2, 'b', 5);
	    d.addTransition(3, 'a', 0);
	    d.addTransition(3, 'b', 4);
	    d.addTransition(4, 'a', 4);
	    d.addTransition(4, 'b', 4);
	    d.addTransition(5, 'a', 2);
	    d.addTransition(5, 'b', 4);
	    
	    Map<Integer, List<Integer>> classes = d.getEquivClasses();
	    
	    StringBuilder builder = new StringBuilder();
	    for (Integer key : classes.keySet()) {
	    	builder.append('[');
	    	for (Integer eq : classes.get(key)) {
	    		builder.append(eq).append(", ");
	    	}
	    	builder.delete(builder.length()-2, builder.length());
	    	builder.append(']').append('\n');
	    }
	    System.out.println(builder.toString());
	}

}
