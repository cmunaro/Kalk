package Kalk;

import java.util.*;

public class Funzione extends Aritmetica {
	public Funzione(String s) {
		super(s);
	}
	public Funzione(Funzione f) {
		super(f.text);
		if(result != null) {
			result = new FunctionResult((FunctionResult)((f.result instanceof FunctionResult) ? f.result : null));
		} else {
			result = null;
		}
	}
	public Funzione() {
		this("");
	}

	public final Result calculate() {
		if(text.length() < 1) {
			throw new Eccezione("Espressione non valida");
		}
		if(!checkParentesi()) {
			throw new Eccezione("Espressione non valida");
		}

		for(int i = 0; i < text.length() - 1; ++i) {
			if((text.charAt(i) == ')' && isNumber(text.charAt(i + 1))) || (isNumber(text.charAt(i)) && text.charAt(i + 1) == 'x') || (isNumber(text.charAt(i + 1)) && text.charAt(i) == 'x')) {
				throw new Eccezione("Espressione non valida");
			}
		}

		String original = text;
		ArrayList<Pair<Double, Double>> points = new ArrayList<Pair<Double, Double>>();

		for(int i = -500; i < 501; i++) {
			Pair<Double, Double> point = new Pair<Double, Double>();
			point.first = (double)i;
			while(text.indexOf('x') > -1 && text.charAt(text.indexOf('x')) == 'x') {
				text = (text.substring(0, text.indexOf('x')) + String.valueOf(i) + text.substring(text.indexOf('x') + 1));
			}
			try {
				point.second = super.evaluate();
			} catch(Eccezione e) {
				text = original; //Restore input text
				throw e; //And continue the exception
			}
			points.add(point);
			text = original;
		}

		result = new FunctionResult(new ArrayList<Pair<Double, Double>>(points));
		return result;
	}

	public final Funzione copyFrom(Funzione f) {
		if(this != f) {
			if(f.result != null) {
				result = new FunctionResult((FunctionResult)((f.result instanceof FunctionResult) ? f.result : null));
			}
		}
		return this;
	}

	public Funzione add(Funzione a) {
		Funzione neo = new Funzione(text + '+' + a.text);
		return neo;
	}

	public Funzione subtract(Funzione a) {
		Funzione neo = new Funzione("(" + text + ")-(" + a.text + ')');
		return neo;
	}

	public Funzione multiply(Funzione a) {
		Funzione neo = new Funzione("(" + text + ")*(" + a.text + ')');
		return neo;
	}

	public Funzione divide(Funzione a) {
		Funzione neo = new Funzione("(" + text + ")/(" + a.text + ')');
		return neo;
	}

	public Funzione add(char c) {
		Funzione neo = new Funzione(text + (char)c);
		return neo;
	}

	public Funzione add(int i) {
		String s = "";
		if(text.length() > 0 && text.charAt(text.length() - 1) != '+' && text.charAt(text.length() - 1) != '-' && text.charAt(text.length() - 1) != '*' && text.charAt(text.length() - 1) != '/') {
			s = "+";
		}
		Funzione neo = new Funzione(text + s + String.valueOf(i));
		return neo;
	}

	@Override
	public double toDouble() {
		if(result != null) {
			return ((FunctionResult)result).toDouble();
		}
		return 0;
	}
	
	public Funzione decrement() {
		if(text.length() > 0) {
			text = text.substring(0, text.length() - 1);
			if(result != null) {
				result = null;
			}
		}
		return this;
	}
}