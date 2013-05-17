package Interface;

import javax.swing.JPanel;
import javax.swing.JDialog;
import javax.swing.JProgressBar;
import java.awt.Rectangle;
import javax.swing.JButton;

/**
 * classe responsável pela janela de diálogo quando se realiza uma compressão ou descompressão de um ficheiro, contem a animação da barra de progresso.
 * 
 * @author Paulo Pinto
 *
 */
public class JanelaDialogo extends JDialog {

	private static final long serialVersionUID = 1L;
	private JPanel jContentPane = null;
	private JProgressBar progressBar_animado = null;
	private JButton OK = null;
	
	
	/**
	 * Constructor
	 * 
	 * @see	#initialize()
	 */
	public JanelaDialogo() {
		initialize();
	}

	/**
	 * Metodo que inicializa a classe
	 *
	 */
	private void initialize() {
		this.setSize(303, 140);
		this.setVisible(true);
		this.setLocation(350, 550);
		this.setDefaultCloseOperation(0);
		this.setContentPane(getJContentPane());
		this.setTitle("a processar...");
	}

	/**
	 * Metodo que inicializa o JContentPane
	 * @return JPanel criado necessário para a janela de diálogo
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			jContentPane = new JPanel();
			jContentPane.setLayout(null);
			jContentPane.add(getProgressBar_animado(), null);
			jContentPane.add(getOK(), null);
		}
		return jContentPane;
	}


	/**
	 * Metodo que inicializa o progressBar_animado
	 * 
	 * @return JProgressBar com as definições estabelecidas
	 */
	private JProgressBar getProgressBar_animado() {
		if (progressBar_animado == null) {

			progressBar_animado = new JProgressBar();
			progressBar_animado.setIndeterminate(true);
			progressBar_animado.setBounds(new Rectangle(51, 35, 200, 26));
			progressBar_animado.setString("espere um momento...");
			progressBar_animado.setStringPainted(true);

		}
		return progressBar_animado;

	}

	/**
	 * Metodo que fecha a janela de dialogo
	 *
	 */
	public void fechar() {
		this.dispose();
	}

	/**
	 * Metodo que inicializa o JButton "OK"
	 * @return o botão incializado
	 */
	private JButton getOK() {
		if (OK == null) {
			OK = new JButton();
			OK.setEnabled(false);
			OK.setText("OK");
			OK.setBounds(new Rectangle(120, 71, 55, 24));
			OK.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					fechar();
				}

			});
		}
		return OK;
	}

	
	/**
	 * Metodo que imobiliza a animacao da janela e activa o botao Ok
	 */
	public void imobilizar() {
		OK.setEnabled(true);
		progressBar_animado.setIndeterminate(false);
		progressBar_animado.setString("Terminado!!!");

	}

}
