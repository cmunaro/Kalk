package Kalk;

public class Eccezione extends RuntimeException{
	private static final long serialVersionUID = 1L;
	private String motivo;
	
	public Eccezione(String s) {
		this.motivo = s;
	}

	public final String getError() {
		return motivo;
	}
}