package Kalk;

import java.util.*;

public class Logica extends Espressione {
	private ArrayList<Pair<Character, Boolean>> vars = new ArrayList<Pair<Character, Boolean>>(); //Vettore variabile-stato_tentativo

	private boolean isSymbol(char c) {
		return c == '|' || c == '&' || c == '!' || c == '(' || c == ')';
	}
	private boolean evaluate(String s) {
		int i = 0;
		int indexParentesi = 0;
		boolean op1 = false;
		boolean op2 = false;

		while(s.length() != 1) {
			if(i >= s.length()) {
			   i = 0;
			}
			switch(s.charAt(i)) {
				case '(':
					indexParentesi = i;
					if(!isSymbol(s.charAt(i + 1)) && s.charAt(i + 2) == ')') {
						if(Character.isDigit(s.charAt(i + 1))) {
							if(s.charAt(i + 1) == '0') {
								s = (s.substring(0, i) + "0" + s.substring(i + 3));
							} else if(s.charAt(i + 1) == '1') {
								s = (s.substring(0, i) + "1" + s.substring(i + 3));
							} else {
								throw new Eccezione("Espressione non valida");
							}
						} else {
							for(int j = 0; j < vars.size(); ++j) {
								if(vars.get(j).first == s.charAt(i + 1)) {
									op1 = vars.get(j).second;
								}
							}
							if(op1 == false) {
								s = (s.substring(0, i) + "0" + s.substring(i + 3));
							} else if(op1 == true) {
								s = (s.substring(0, i) + "1" + s.substring(i + 3));
							} else {
								throw new Eccezione("Espressione non valida");
							}
						}
					}
					++i;
					break;

				case ')':
					if(indexParentesi > i) {
						throw new Eccezione("Espressione non valida");
					} else if(!isSymbol(s.charAt(i - 1)) && s.charAt(i - 2) == '(') {
							if(Character.isDigit(s.charAt(i - 1))) {
								if(s.charAt(i - 1) == '0') {
									s = (s.substring(0, i - 2) + "0" + s.substring(i - 2 + 3));
								} else if(s.charAt(i - 1) == '1') {
									s = (s.substring(0, i - 2) + "1" + s.substring(i - 2 + 3));
								} else {
									throw new Eccezione("Espressione non valida");
								}
							} else {
								for(int j = 0; j < vars.size(); ++j) {
									if(vars.get(j).first == s.charAt(i - 1)) {
										op1 = vars.get(j).second;
									}
								}
								if(op1 == false) {
									s = (s.substring(0, i - 2) + "0" + s.substring(i - 2 + 3));
								} else if(op1 == true) {
									s = (s.substring(0, i - 2) + "1" + s.substring(i - 2 + 3));
								} else {
									throw new Eccezione("Espressione non valida");
								}
							}
					} else {
						i++;
					}
				break;
				case '|': {
					if(i == 0 || (isSymbol(s.charAt(i - 1)) && !(s.charAt(i - 1) == ')' && indexParentesi < i))) { //Controllo carattere precedente
						throw new Eccezione("Espressione non valida");
					}
					if(isSymbol(s.charAt(i + 1))) {
						if(s.charAt(i + 1) == '!') {
							int j = 1;
							while(s.charAt(i + j) == '!') {
								j++; //Conta quanti ! ci sono + 1
							}
							if(s.charAt(i + j) == '(') {
								indexParentesi = i + j;
								i = indexParentesi + 1;
								break;
							} else if(isSymbol(s.charAt(i + j))) {
								throw new Eccezione("Espressione non valida");
							} else
							{ //Calcola "!.. A"
								boolean b = evaluate(s.substring(i + 1, i + 1 + j));
								s = (s.substring(0, i + 1) + b != null ? "1" : "0" + s.substring(i + 1 + j));
								break;
							}
						} else if(s.charAt(i + 1) == '(') {
								indexParentesi = i + 1;
								i = indexParentesi + 1;
								break;
						} else {
							throw new Eccezione("Espressione non valida");
						}
					} else if(s.charAt(i - 1) == ')') {
						if(s.charAt(indexParentesi) != '(') {
							indexParentesi = 0;
							i = 0;
						} else {
							i = indexParentesi;
						}
					}
					//Non è un simbolo
					if(Character.isDigit(s.charAt(i - 1))) {
						if(s.charAt(i - 1) == '1') {
							op1 = true;
						} else if(s.charAt(i - 1) == '0') {
							op1 = false;
						} else {
							throw new Eccezione("Espressione non valida");
						}
					} else {
						for(int j = 0; j < vars.size(); ++j) {
							if(vars.get(j).first == s.charAt(i - 1)) {
								op1 = vars.get(j).second;
							}
						}
					}
					if(Character.isDigit(s.charAt(i + 1))) {
						if(s.charAt(i + 1) == '1') {
							op2 = true;
						} else if(s.charAt(i + 1) == '0') {
							op2 = false;
						} else {
							throw new Eccezione("Espressione non valida");
						}
					} else {
						for(int j = 0; j < vars.size(); ++j) {
							if(vars.get(j).first == s.charAt(i + 1)) {
								op2 = vars.get(j).second;
							}
						}
					}
					s = (s.substring(0, i - 1) + (op1 | op2 ? "1" : "0" + s.substring(i - 1 + 3)));
					break;
				}
				case '&': {
					if(i == 0 || (isSymbol(s.charAt(i - 1)) && !(s.charAt(i - 1) == ')' && indexParentesi < i))) { //Controllo carattere precedente
						throw new Eccezione("Espressione non valida");
					}
					if(isSymbol(s.charAt(i + 1))) {
						if(s.charAt(i + 1) == '!') {
							int j = 1;
							while(s.charAt(i + j) == '!') {
								j++; //Conta quanti ! ci sono + 1
							}
							if(s.charAt(i + j) == '(') {
								indexParentesi = i + j;
								i = indexParentesi + 1;
								break;
							} else if(isSymbol(s.charAt(i + j))) {
								throw new Eccezione("Espressione non valida");
							} else
							{ //Calcola "!.. A"
								boolean b = evaluate(s.substring(i + 1, i + 1 + j));
								s = (s.substring(0, i + 1) + b != null ? "1" : "0" + s.substring(i + 1 + j));
								break;
							}
						} else if(s.charAt(i + 1) == '(') {
								indexParentesi = i + 1;
								i = indexParentesi + 1;
								break;
						} else {
							throw new Eccezione("Espressione non valida");
						}
					} else if(s.charAt(i - 1) == ')') {
						if(s.charAt(indexParentesi) != '(') {
							indexParentesi = 0;
							i = 0;
						} else {
							i = indexParentesi;
						}
						break;
					}
					//Non è un simbolo
					if(Character.isDigit(s.charAt(i - 1))) {
						if(s.charAt(i - 1) == '1') {
							op1 = true;
						} else if(s.charAt(i - 1) == '0') {
							op1 = false;
						} else {
							throw new Eccezione("Espressione non valida");
						}
					}
					else { //è una variabile
						for(int j = 0; j < vars.size(); ++j) {
							if(vars.get(j).first == s.charAt(i - 1)) {
								op1 = vars.get(j).second;
							}
						}
					}
					if(Character.isDigit(s.charAt(i + 1))) {
						if(s.charAt(i + 1) == '1') {
							op2 = true;
						} else if(s.charAt(i + 1) == '0') {
							op2 = false;
						} else {
							throw new Eccezione("Espressione non valida");
						}
					} else {
						for(int j = 0; j < vars.size(); ++j) {
							if(vars.get(j).first == s.charAt(i + 1)) {
								op2 = vars.get(j).second;
							}
						}
					}
					s = (s.substring(0, i - 1) + (op1 & op2 ? "1" : "0" + s.substring(i - 1 + 3)));
					break;
				}
				case '!': {
					if(i > 0 && (s.charAt(i - 1) == ')' || !isSymbol(s.charAt(i - 1)))) {
						throw new Eccezione("Espressione non valida");
					}
					int j = 0;
					while(s.charAt(i + j) == '!') {
						j++; //Conta quanti ! ci sono + 1
					}
					if(s.charAt(i + j) == '(') {
						indexParentesi = i + j;
						i = indexParentesi + 1;
						break;
					} else if(i + j < s.length() && isSymbol(s.charAt(i + j))) {
						throw new Eccezione("Espressione non valida");
					}
					//Calcola "!.. A"
					boolean b = false;
					if(i + j >= s.length()) {
						throw new Eccezione("Espressione non valida");
					}
					if(!Character.isDigit(s.charAt(i + j))) {
						for(int x = 0; x < vars.size(); ++x) {
							if(vars.get(x).first == s.charAt(i + j)) {
								b = vars.get(x).second;
							}
						}
					} else if(s.charAt(i + j) == '1') {
						b = true;
					} else if(s.charAt(i + j) == '0') {
						b = false;
					} else {
						throw new Eccezione("Espressione non valida");
					}
					if(j % 2 == 1) {
						b = !b;
					}
					s = (s.substring(0, i) + b != null ? "1" : "0" + s.substring(i + j + 1));
					break;
				}
				default:
					++i;
			}
		}
		if(Character.isDigit(s.charAt(0))) {
			if(s.charAt(0) == '1') {
				return true;
			}
			if(s.charAt(0) == '0') {
				return false;
			}
			throw new Eccezione("Espressione non valida");
		} else {
			if(vars.size() > 0) {
			for(int j = 0; j < vars.size(); ++j) {
				if(vars.get(j).first == s.charAt(i)) {
					return vars.get(i).second;
				}
			}
			} else {
			   throw new Eccezione("Espressione non valida");
			}
		}
		return false;
	}

	public Logica(String s) {
		super(s);
	}
	public Logica(Logica l) {
		super(l.text);
		if(l.result != null) {
			result = new LogicalResult((LogicalResult)((l.result instanceof LogicalResult) ? l.result : null));
		} else {
			result = null;
		}
	}
	public Logica() {
		this("");
	}

	@Override
	public final Result calculate() {
		if(text.equals("")) {
			return null;
		}
		//Controlla se ci sono stringhe di variabili es. AA
		for(int i = 1; i < text.length(); ++i) {
			if(!isSymbol(text.charAt(i - 1)) && !isSymbol(text.charAt(i))) {
				throw new Eccezione("Espressione non valida");
			}
		}
		if(!checkParentesi()) {
			throw new Eccezione("Espressione non valida");
		}

		//Carica le variabili-0
		for(int i = 0; i < text.length(); ++i) {
			if(!isSymbol(text.charAt(i))) {
				boolean found = false;
				for(int j = 0; !found && j < vars.size(); ++j) {
					if(vars.get(j).first == text.charAt(i)) {
						found = true;
					}
				}
				if(!found && !Character.isDigit(text.charAt(i))) {
					vars.add(new Pair<Character, Boolean>(text.charAt(i), false));
				}
			}
		}
		vars.sort(null);
		ArrayList<ArrayList<Boolean>> ris = new ArrayList<ArrayList<Boolean>>();
		for(int i = 0; i < Math.pow(2, vars.size()); ++i) {
			ris.add(new ArrayList<Boolean>());
		}
		//Calcolo tabella verità
		int n = 0;
		do {
			for(int i = 0; i < vars.size(); ++i) { //Carica input tabella verità
				ris.get(n).add(vars.get(i).second);
			}
			ris.get(n).add(evaluate(text)); //Calcola output riga tabella

			for(int j = 0; j < vars.size(); ++j) { //Cambia input
				if(vars.get(j).second == false) {
					vars.get(j).second = true;
					break;
				} else {
					vars.get(j).second = false;
				}
			}
		} while(++n < Math.pow(2, vars.size()));

		ArrayList<Character> columnsName = new ArrayList<Character>();
		for(int i = 0; i < vars.size(); ++i) {
			columnsName.add(vars.get(i).first);
		}

		result = new LogicalResult(ris, columnsName);
		return result;
	}

	public final Logica copyFrom(Logica l) {
		if(this != l) {
			text = l.text;
			if(l.result != null) {
				result = new LogicalResult((LogicalResult)((l.result instanceof LogicalResult) ? l.result : null));
			}
		}
		return this;
	}

	public Logica add(Logica a) {
		Logica neo = new Logica(text + '+' + a.text);
		return neo;
	}

	public Logica subtract(Logica a) {
		Logica neo = new Logica("(" + text + ")&(" + a.text + ')');
		return neo;
	}

	public Logica add(char c) {
		Logica neo = new Logica(text + (char)c);
		return neo;
	}

	public Logica add(int i) {
		int r = i == 0 ? 0 : 1;
		String s = "";
		if(text.length() > 0 && text.charAt(text.length() - 1) != '|' && text.charAt(text.length() - 1) != '&' && text.charAt(text.length() - 1) != '!') {
			s = "|";
		}
		Logica neo = new Logica(text + s + String.valueOf(r));
		return neo;
	}
	
	@Override
	public double toDouble() {
		if(result != null) {
			return ((LogicalResult)((result instanceof LogicalResult) ? result : null)).toDouble();
		}
		return 0;
	}
	public Logica decrement() {
		if(text.length() > 0) {
			text = text.substring(0, text.length() - 1);
			if(result != null) {
				result = null;
			}
		}
		return this;
	}
}