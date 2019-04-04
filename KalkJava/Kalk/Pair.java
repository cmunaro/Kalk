package Kalk;

class Pair<T extends Comparable<T>, U> implements Comparable<Pair<T, U>>{    
	T first;
    U second;
    
    public Pair(T fisrt, U second) {
    	this.first = fisrt;
    	this.second = second;
	}
    public Pair() {
    	this.first = null;
    	this.second = null;
	}
    
	@Override
	public int compareTo(Pair<T, U> to) {
		return first.compareTo(to.first);
	}
}