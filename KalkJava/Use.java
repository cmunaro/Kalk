
import Kalk.*;

public class Use {

	public static void main(String[] args) {
		Result r;
		
	    Espressione e = new Logica("1|(!(B|(A))&!C)");
	    try {
	        e.calculate();
		    r = e.getResult();
		    r.stampa();
	    } catch (Eccezione ecc) {
	        System.out.println(ecc.getError());
	    }

	    System.out.println("\n\n\n");

	    e = new Aritmetica("2+3-1");
	    try {
	        e.calculate();
		    r = e.getResult();
		    r.stampa();
	    } catch (Eccezione ecc) {
	        System.out.println(ecc.getError());
	    }

	    System.out.println("\n\n\n");

	    e = new Funzione("x*2");
	    try {
	        e.calculate();
		    r = e.getResult();
		    r.stampa();	
	    } catch (Eccezione ecc) {
	        System.out.println(ecc.getError());
	    }
	    
	    e = new Logica("A|B");
	    e = ((Logica)e).add('&');
	    e = ((Logica)e).add('C');
	    try {
	    	e.calculate();
	    } catch (Eccezione ecc) {
	        System.out.println(ecc.getError());
	        System.exit(1);
	    }
	    Aritmetica a = new Aritmetica("4+5*2");
	    try {
		    a = a.add((int)e.toDouble());	//Aritmetica += Logica
		    a.calculate();
	    } catch (Eccezione ecc) {
	        System.out.println(ecc.getError());
	        System.exit(1);
	    }
	    e = new Funzione("x*x*x/1");
	    try {
		    ((Funzione)e).decrement();		//Remove 1
		    e = ((Funzione)e).add(50).add('0');
		    Funzione f = new Funzione("-x");
		    e = ((Funzione)e).add(f);
		    System.out.println("\n\n\nTesto funzione: " + e.getText() + "\n\n\n");
		    e.calculate();
		    e.getResult().stampa();
	    } catch (Eccezione ecc) {
	        System.out.println(ecc.getError());
	        System.exit(1);
	    }    
	    
	}
}
