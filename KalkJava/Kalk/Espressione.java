package Kalk;

public abstract class Espressione {
	protected String text;
	protected Result result;

	protected final boolean checkParentesi() {
		//Controlla il bilanciamento delle parentesi
		int check = 0;
		for(int i = 0; i < text.length(); ++i) {
			if(text.charAt(i) == '(') {
				++check;
			} else if(text.charAt(i) == ')' && --check < 0) {
				return false;
			}
		}
		if(check != 0) {
			return false;
		}
		for(int i = 0; i < text.length() - 1; ++i) {
			if(text.charAt(i) == '(' && text.charAt(i + 1) == ')') {
				return false;
			}
		}
		return true;
	}
	protected Espressione(String s) {
		this.text = s;
		this.result = null;
	}
	
	public abstract double toDouble();

	public final Result getResult() {
		return result;
	}

	public final String getText() {
		return (String)text;
	}

	public abstract Result calculate();
}