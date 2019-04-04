package Kalk;

public class AritmeticResult extends Result {
	private double ris;
	public AritmeticResult(double ris) {
		super();
		this.ris = ris;
	}
	public AritmeticResult(AritmeticResult e) {
		this.ris = e.ris;
	}

	@Override
	public final void stampa() {
		System.out.print("Ris: ");
		System.out.print(ris);
		System.out.print("\n");
	}

	public final double getValue() {
		return ris;
	}

	public final AritmeticResult copyFrom(AritmeticResult e) {
		if(this != e) {
			ris = e.ris;
		}
		return this;
	}

	public double toDouble() {
		return ris;
	}
}