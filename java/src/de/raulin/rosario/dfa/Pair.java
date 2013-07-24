package de.raulin.rosario.dfa;

public final class Pair<T1, T2> {
	private T1 first;
	private T2 second;
	
	public Pair(T1 first, T2 second) {
		this.first = first;
		this.second = second;
	}
	
	public T1 first() {
		return first;
	}
	
	public T2 second() {
		return second;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null) return false;
		if (other == this) return true;
		if (other instanceof Pair) {
			@SuppressWarnings("unchecked")
			Pair<T1,T2> otherPair = (Pair<T1,T2>) other;
			return first.equals(otherPair.first) && second.equals(otherPair.second);
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		return first.hashCode() * 23 + second.hashCode();
	}
}
