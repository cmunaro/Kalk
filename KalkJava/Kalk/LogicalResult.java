package Kalk;

import java.util.*;

public class LogicalResult extends Result {
	private ArrayList<ArrayList<Boolean>> matrix = new ArrayList<ArrayList<Boolean>>();
	private ArrayList<Character> columns = new ArrayList<Character>();

	public LogicalResult(ArrayList<ArrayList<Boolean>> matrix, ArrayList<Character> c) {
		super();
		this.matrix = new ArrayList<ArrayList<Boolean>>(matrix);
		this.columns = new ArrayList<Character>(c);
	}
	
	public LogicalResult(LogicalResult l) {
		super();
		this.columns = new ArrayList<Character>(l.columns);
		for(int i = 0; i < l.matrix.size(); i++) {
			matrix.add(new ArrayList<Boolean>());
			for(int j = 0; j < l.matrix.get(i).size(); ++j) {
				matrix.get(i).add(l.matrix.get(i).get(j));
			}
		}
	}
	
	public final ArrayList<Character> getColumnNames() {
		return columns;
	}

	public final ArrayList<ArrayList<Boolean>> getMatrix() {
		return matrix;
	}

	@Override
	public final void stampa() {
		for(int i = 0; i < columns.size(); i++) {
			System.out.print(columns.get(i));
			System.out.print("\t");
		}
		System.out.print("Ris: ");
		System.out.print("\n");
		for(ArrayList<Boolean> i : matrix) {
			for(Boolean j : i) {
				System.out.print(j);
				System.out.print("\t");
			}
			System.out.print("\n");
		}
	}

	public final LogicalResult copyFrom(LogicalResult l) {
		if(this != l) {
			for(Character i : l.columns) {
				columns.add(i);
			}
			for(int i = 0; i < l.matrix.size(); i++) {
				matrix.add(new ArrayList<Boolean>());
				for(int j = 0; j < l.matrix.get(i).size(); ++j) {
					matrix.get(i).add(l.matrix.get(i).get(j));
				}
			}
		}
		return this;
	}

	public double toDouble() {
		double s = 0;
		for(ArrayList<Boolean> l : matrix)
			if(l.get(l.size() - 1))
				++s;
		s = s / matrix.size() * 100;
		return s;
	}
}