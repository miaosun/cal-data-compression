package Interface;


import java.awt.GridLayout;
import java.io.IOException;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;


/**
 * classe referente a interface gráfica que cria o JTabbedPane e inicializa com os parâmetros correspondentes.
 * 
 * @author Paulo Pinto
 *
 */
public class Tabs extends JPanel {

	
	private static final long serialVersionUID = 1L;
	
	/**
	 * Painel com os componentes para compressão
	 */
	private JPanel painel_comprimir = null;
	/**
	 * Painel com os componentes de descompressão
	 */
	private JPanel painel_descomprimir = null;
	


	/**
	 * Constructor
	 */
	public Tabs() throws IOException {
		
		JTabbedPane jtb = new JTabbedPane();
		//cria o painel comprimir
		painel_comprimir = new Painel("comprimir");
		jtb.addTab("Comprimir",painel_comprimir);
		jtb.setSelectedIndex(0);
		//cria o painel comprimir
		painel_descomprimir = new Painel("descomprimir");
		jtb.addTab("Descomprimir", painel_descomprimir);
	
		setLayout(new GridLayout(1, 1));
		add(jtb);
	}
}
	
	