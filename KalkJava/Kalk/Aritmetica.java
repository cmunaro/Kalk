package Kalk;

public class Aritmetica extends Espressione {
	private int i;

	private boolean isSymbol(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
	}
	private double number() {
		double result = (double)(text.charAt(i++) - '0');
		while(i < text.length() && text.charAt(i) >= '0' && text.charAt(i) <= '9') {
			result = 10 * result + text.charAt(i++) - '0';
		}
		return result;
	}
	private double factor() {
		if(text.charAt(i) >= '0' && text.charAt(i) <= '9') {
			return number();
		} else if(text.charAt(i) == '(') {
			i++; // '('
			double result = sum();
			i++; // ')'
			return result;
		} else if(text.charAt(i) == '-') {
			i++;
			return -factor();
		}
		throw new Eccezione("Espressione non valida");
	}
	private double priority() {
		double result = factor();
		while(i < text.length() && (text.charAt(i) == '*' || text.charAt(i) == '/')) {
			if(text.charAt(i++) == '*') {
				result *= factor();
			} else {
				result /= factor();
			}
		}
		return result;
	}
	private double sum() {
		double result = priority();
		while(i < text.length() && (text.charAt(i) == '+' || text.charAt(i) == '-')) {
			if(text.charAt(i++) == '+') {
				result += priority();
			} else {
				result -= priority();
			}
		}
		return result;
	}

	protected final double evaluate() {
		for(int i = 0; i < text.length(); ++i) {
			if(!isSymbol(text.charAt(i)) && !isNumber(text.charAt(i))) {
				throw new Eccezione("Espressione non valida");
			}
		}

		i = 0;
		return sum();
	}

	protected final boolean isNumber(char c) {
		return c >= '0' && c <= '9';
	}

	public Aritmetica(String s) {
		super(s);
	}
	public Aritmetica(Aritmetica a) {
		super(a.text);
		if(a.result != null) {
			result = new AritmeticResult((AritmeticResult)((a.result instanceof AritmeticResult) ? a.result : null));
		} else {
			result = null;
		}
	}
	public Aritmetica() {
		this("");
	}

	@Override
	public Result calculate() {
		if(!checkParentesi()) {
			throw new Eccezione("Espressione non valida");
		}
		for(int i = 0; i < text.length() - 1; ++i) {
			if(text.charAt(i) == ')' && isNumber(text.charAt(i + 1))) {
				throw new Eccezione("Espressione non valida");
			}
		}
		double evaluated = evaluate();
		result = new AritmeticResult(evaluated);
		return result;
	}

	public final Aritmetica copyFrom(Aritmetica a) {
	  if(this != a) {
		if (a.result != null)
			result = new AritmeticResult((AritmeticResult)((a.result instanceof AritmeticResult) ? a.result : null));
		else
			result  = null;
		text = a.text;
	  }
	  return this;
	}

	public Aritmetica add(Aritmetica a) {
		Aritmetica neo = new Aritmetica(text + '+' + a.text);
		return neo;
	}

	public Aritmetica subtract(Aritmetica a) {
		Aritmetica neo = new Aritmetica("(" + text + ")-(" + a.text + ')');
		return neo;
	}

	public Aritmetica multiply(Aritmetica a) {
		Aritmetica neo = new Aritmetica("(" + text + ")*(" + a.text + ')');
		return neo;
	}

	public Aritmetica divide(Aritmetica a) {
		Aritmetica neo = new Aritmetica("(" + text + ")/(" + a.text + ')');
		return neo;
	}

	public Aritmetica add(char c) {
		Aritmetica neo = new Aritmetica(text + (char)c);
		return neo;
	}

	public Aritmetica add(int i) {
		String s = "";
		if(text.length() > 0 && text.charAt(text.length() - 1) != '+' && text.charAt(text.length() - 1) != '-' && text.charAt(text.length() - 1) != '*' && text.charAt(text.length() - 1) != '/') {
			s = "+";
		}
		Aritmetica neo = new Aritmetica(text + s + String.valueOf(i));
		return neo;
	}
	
	public Aritmetica decrement() {
		if(text.length() > 0) {
			text = text.substring(0, text.length() - 1);
			if(result != null) {
				result = null;
			}
		}
		return this;
	}

	public double toDouble() {
		if(result != null) {
			return ((AritmeticResult)result).toDouble();
		}
		return 0;
	}
}


