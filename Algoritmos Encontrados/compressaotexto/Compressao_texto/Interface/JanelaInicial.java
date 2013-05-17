package Interface;

import java.awt.BorderLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

import javax.swing.JPanel;
import javax.swing.JFrame;


/**
 * classe que tem como funcionalidade inicializar a janela principal do programa
 * 
 * @author Paulo Pinto
 *
 */
public class JanelaInicial extends JFrame {

	private static final long serialVersionUID = 1L;

	private JPanel jContentPane = null;

	
	/**
	 * Constructor do JFrame inicial
	 * 
	 * @throws IOException
	 */
	public JanelaInicial() throws IOException {
		super();
		initialize();
		this.getContentPane().add(new Tabs(),BorderLayout.CENTER);
		
		this.addWindowListener(new WindowAdapter() {

			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});

	}


	/**
	 * Inicializa o JFrame com as definicões pré-stablecidas
	 */
	private void initialize() {
		this.setSize(540, 360);
		this.setLocation(300,300);
		this.setResizable(false); //nao permite aumentar o tamanho da Janela
		Image im = Toolkit.getDefaultToolkit().getImage("./imagens/icon.gif"); //icon da janela
		this.setIconImage(im);

		this.setContentPane(getJContentPane());
		this.setTitle("Java Compactador");
	}

	
	/**
	 * Metodo que devolve o JPanel
	 * @return devolve o JPanel
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			jContentPane = new JPanel();
			jContentPane.setLayout(new BorderLayout());
		}
		return jContentPane;
	}
	


}
