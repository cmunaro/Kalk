package Kalk;

import java.util.*;

public class FunctionResult extends Result {
	private ArrayList<Pair<Double, Double>> points = new ArrayList<Pair<Double, Double>>();

	public FunctionResult(ArrayList<Pair<Double, Double>> v) {
		super();
		this.points = new ArrayList<Pair<Double, Double>>(v);
	}
	public FunctionResult(FunctionResult f) {
		super();
		this.points = new ArrayList<Pair<Double, Double>>(f.points);
	}

	public final ArrayList<Pair<Double, Double>> getPoints() {
		return points;
	}

	@Override
	public final void stampa() {
		System.out.print("X\tY");
		System.out.print("\n");

		for(int i = 0; i < points.size(); i++) {
			System.out.print(points.get(i).first);
			System.out.print("\t");
			System.out.print(points.get(i).second);
			System.out.print("\t");
			System.out.print("\n");
		}
	}

	public final FunctionResult copyFrom(FunctionResult f) {
		if(this != f) {
			points = new ArrayList<Pair<Double, Double>>();
			for(Pair<Double, Double> i : f.points) {
				points.add(new Pair<Double, Double>(i.first,i.second));
			}
		}
		return this;
	}

	public double toDouble() {
		double s = 0;
		for(Pair<Double, Double> i : points) {
			s += i.second;
		}
		s /= points.size();
		return s;
	}
}