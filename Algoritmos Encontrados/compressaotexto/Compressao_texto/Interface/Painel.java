package Interface;

import java.awt.Font;
import java.io.IOException;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.SwingWorker;
import javax.swing.border.TitledBorder;
import compressao.Huffman;
import compressao.LZW;


/**
 * 
 * classe que esta encarregue de construir o painel (JPanel) referente a compressão e a descompressão do ficheiro com todos os seus componentes.
 *
 * @author Paulo Pinto
 *
 */
public class Painel extends JPanel {

	private static final long serialVersionUID = 1L;

	/**
	 * variavel para associar ao tipo de compressão
	 */
	private int comp = 0;
	/**
	 * caminho do ficheiro de entrada
	 */
	private String ficheiro_entrada = "";
	
	/**
	 * caminho do ficheiro de saida
	 */
	private String ficheiro_saida = "";


	/**
	 * Constructor
	 * 
	 * @param	tipo comprimir ou descomprimir
	 */
	public Painel(String tipo) throws IOException {
		super();
		initialize(tipo);
	}


	/**
	 * metodo responsavel pela inicialização do Painel (JPanel)
	 * 
	 * @param tipo	comprimir ou descomprimir
	 */
	private void initialize(String tipo) throws IOException {
		this.setLayout(null);
		if (tipo.equals("comprimir"))
			create_painel_comprimir();
		else if (tipo.equals("descomprimir"))
			create_painel_descomprimir();
	}

	/**
	 * Painel responsavel pela descompressão
	 *
	 */
	protected void create_painel_descomprimir() {

		//JLabel = "Ficheiro entrada: "
		JLabel jlbDisplay = new JLabel("Ficheiro entrada: ");
		jlbDisplay.setSize(100, 20);
		jlbDisplay.setLocation(10, 18);

		//Caixa de texto onde aparece o caminho do ficheiro
		final JTextField path_entrada = new JTextField();
		path_entrada.setSize(500, 20);
		path_entrada.setLocation(10, 40);

		//Botao procurar que abre o JFileChooser (classe Escolher_ficheiro)
		JButton open = new JButton();
		open.setSize(70, 20);
		open.setLocation(439, 18);
		open.setText("Procurar");

		open.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mouseClicked(java.awt.event.MouseEvent e) {
				comp = -1;
				ficheiro_entrada = "";
				while (comp == -1) { //enquanto nao tiver sido escolhido um ficheiro
										//com extensao valida

					Escolher_ficheiro janela_escolha = new Escolher_ficheiro(
							"descomprimir", false, 0);

					//cainho do ficheiro de entrada
					ficheiro_entrada = janela_escolha.path;
					//a string extensao corresponde a extensao do ficheiro escolhido pela
					//pela janela de dialogo
					String extensao = ficheiro_entrada.substring(
							(ficheiro_entrada.length() - 3), ficheiro_entrada
									.length());

					//modifica o valor da variavel comp consoante o tipo de compressao
					if (extensao.equals("lzw") || extensao.equals("LZW"))
						comp = 0;
					else if (extensao.equals("huf") || extensao.equals("HUF"))
						comp = 1;

				}

				path_entrada.setText(ficheiro_entrada);//coloca o caminho do ficheiro na
						//caixa de texto

			}
		});

		//Botao descomprimir que chama o metodo correspondente para descomprimir o ficheiro
		JButton descomprimir = new JButton();
		descomprimir.setSize(200, 30);
		descomprimir.setLocation(150, 250);
		descomprimir.setText("Descomprimir");

		descomprimir.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mouseClicked(java.awt.event.MouseEvent e) {

				Escolher_ficheiro janela_escolha = new Escolher_ficheiro(
						"descomprimir", true, 0);

				ficheiro_saida = janela_escolha.path;

				final JanelaDialogo dialogo = new JanelaDialogo();

				//Classe responsavel pelo gerenciamento de Thread's para permite a actualizacao
				//da janela de dialogo ao mesmo tempo que a funcao decorre
				SwingWorker worker = new SwingWorker() {

					protected Object doInBackground() throws Exception {
						if (comp == 0)
							try {
								LZW.descomprimir(ficheiro_entrada,
										ficheiro_saida);
							} catch (IOException e1) {
								e1.printStackTrace();
							}
						else
							try {
								Huffman.descomprimir(ficheiro_entrada,
										ficheiro_saida);
							} catch (IOException e1) {
								e1.printStackTrace();
							}
						return null;
					}

					public void done() {
						dialogo.imobilizar();
						path_entrada.setText("");
					}

				};
				worker.execute(); //Start the background thread

			}
		});

		//Imagem
		ImageIcon icon = new ImageIcon("./imagens/imagem_des.png");
		JLabel label = new JLabel(icon);
		label.setSize(150, 150);
		label.setLocation(300, 80);

		//adiciona os varios componentes criados ao JPanel
		this.add(jlbDisplay);
		this.add(path_entrada);
		this.add(open);
		this.add(descomprimir);
		this.add(label);

		return;
	}

	/**
	 * Metodo responsavel pela criação do painel de compressão
	 * 
	 * @throws IOException
	 */
	protected void create_painel_comprimir() throws IOException {

		//JLabel com o texto "Ficheiro entrada: "
		JLabel jlbDisplay = new JLabel("Ficheiro entrada: ");
		jlbDisplay.setSize(100, 20);
		jlbDisplay.setLocation(10, 18);

		//Caixa de Texto que contem o caminho do ficheiro escolhido
		final JTextField path_entrada = new JTextField();
		path_entrada.setSize(500, 20);
		path_entrada.setLocation(10, 40);

		//JButton Procurar
		JButton open = new JButton();
		open.setSize(70, 20);
		open.setLocation(439, 18);
		open.setText("Procurar");

		open.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mouseClicked(java.awt.event.MouseEvent e) {

				Escolher_ficheiro janela_escolha = new Escolher_ficheiro(
						"comprimir", false, 0);

				ficheiro_entrada = janela_escolha.path;
				path_entrada.setText(ficheiro_entrada);

			}
		});

		//Botoes de escolha da compressao
		Font f = new Font("Arial", Font.ITALIC, 12);

		//Painel para agrupar os JRadionButton
		JPanel agrupar_compressao = new JPanel();
		agrupar_compressao.setSize(200, 100);
		agrupar_compressao.setLayout(null);
		agrupar_compressao.setLocation(310, 100);

		TitledBorder title;
		title = BorderFactory.createTitledBorder("Algoritmos de compressao");
		agrupar_compressao.setBorder(title);

		final JRadioButton lzw = new JRadioButton();
		lzw.setSelected(true);
		lzw.setLocation(80, 30);
		lzw.setSize(20, 20);
		JRadioButton Huff = new JRadioButton();
		Huff.setLocation(80, 60);
		Huff.setSize(20, 20);

		//Grupo de botoes que contem os JRadionButton LZW E HUF
		ButtonGroup compressao = new ButtonGroup();
		compressao.add(lzw);
		compressao.add(Huff);

		JLabel jlbLZW = new JLabel("LZW");
		jlbLZW.setFont(f);
		jlbLZW.setSize(50, 20);
		jlbLZW.setLocation(100, 30);

		JLabel jlbHUF = new JLabel("Huffman");
		jlbHUF.setFont(f);
		jlbHUF.setSize(50, 20);
		jlbHUF.setLocation(100, 60);

		agrupar_compressao.add(jlbHUF);
		agrupar_compressao.add(jlbLZW);
		agrupar_compressao.add(lzw);
		agrupar_compressao.add(Huff);

		//JButton Comprimir que quando é clicado tem como funcao 
		JButton comprimir = new JButton();
		comprimir.setSize(200, 30);
		comprimir.setLocation(150, 250);
		comprimir.setText("Comprimir");

		comprimir.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mouseClicked(java.awt.event.MouseEvent e) {

				if (!lzw.isSelected()) //se o JRaddionButton LZW nao estiver selecionado
					comp = 1;			// a variavel comp=1, para ser usado o metodo de Huffman

				Escolher_ficheiro janela_escolha = new Escolher_ficheiro(
						"comprimir", true, comp);

				ficheiro_saida = janela_escolha.path;

				final JanelaDialogo dialogo = new JanelaDialogo();

//				Classe responsavel pelo gerenciamento de Thread's para permite a actualizacao
				//da janela de dialogo ao mesmo tempo que a funcao decorre
				SwingWorker worker = new SwingWorker() {

					protected Object doInBackground() throws Exception {
						if (comp == 0)
							try {
								LZW.comprimir(ficheiro_entrada, ficheiro_saida
										+ ".lzw");
							} catch (IOException e1) {
								e1.printStackTrace();
							}
						else
							try {
								Huffman.comprimir(ficheiro_entrada,
										ficheiro_saida + ".huf");
							} catch (IOException e1) {
								e1.printStackTrace();
							} 
						return null;
					}

					public void done() {
						dialogo.imobilizar();
						path_entrada.setText("");
					}

				};
				worker.execute(); //Start the background thread

			}
		});

		//Imagem
		ImageIcon icon = new ImageIcon("./imagens/imagem_comp.png");
		JLabel label = new JLabel(icon);
		label.setSize(150, 150);
		label.setLocation(50, 80);

		//adiciona os varios componentes criados ao JPanel
		this.add(jlbDisplay);
		this.add(path_entrada);
		this.add(open);
		this.add(agrupar_compressao);
		this.add(comprimir);
		this.add(label);

		return;

	}

}
