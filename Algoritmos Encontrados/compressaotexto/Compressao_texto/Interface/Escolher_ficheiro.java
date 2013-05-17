package Interface;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 * classe que apresenta um construtor com vários parâmetros para apresentação de um janela de dialogo de abrir/guardar um ficheiro, ou seja um JFileChooser.
 * 
 * @author Paulo Pinto
 *
 */
public class Escolher_ficheiro extends JFileChooser {

	private static final long serialVersionUID = 1L;
	
	/**
	 * caminho do ficheiro selecionado
	 */
	public String path = "";
	
	
	
	/**
	 * Constructor
	 * @param	tipo	comprimir ou descomprimir
	 * @param	gravar	se a caixa de dialogo (JFileChooser) é para gravar um ficheiro ou para procurar
	 * @param	metodo	corresponde a 0 para LZW ou a 1 para Huffman
	 * @see	#initialize(String, boolean, int)
	 */
	public Escolher_ficheiro(String tipo,boolean gravar,int metodo) {
		super();
		initialize(tipo, gravar,metodo);
	}


	/**
	 * Metodo que inicialia o JFileChooser
	 * 
	 * @param	tipo	comprimir ou descomprimir
	 * @param	gravar	se a caixa de dialogo (JFileChooser) é para gravar um ficheiro ou para procurar
	 * @param	metodo	corresponde a 0 para LZW ou a 1 para Huffman
	 * @see	#gravar_ficheiro_comprimido(int)
	 * @see	#gravar_ficheiro_texto()
	 * @see	#procurar_ficheiro_comprimido()
	 * @see #procurar_ficheiro_txt()
	 */
	private void initialize(String tipo, boolean gravar, int metodo) {
		
		if (gravar)
			if (tipo.equals("comprimir"))
				path = gravar_ficheiro_comprimido(metodo);
			else
				path = gravar_ficheiro_texto();
		else 
			if (tipo.equals("descomprimir"))
				path = procurar_ficheiro_comprimido();
			else
				path = procurar_ficheiro_txt();
		
	}
	
	//metodo que devolve o caminho do ficheiro de texto que se pretende comprimir
	
	/**
	 * Metodo que abre uma janela de dialogo com objectivo de selecionar um ficheiro
	 * 
	 * @return	devolve o caminho do ficheiro
	 */
	private String procurar_ficheiro_txt()
	{
		this.setDialogTitle("Seleção de ficheiro texto para compactar");
		this.setFileFilter(new FileNameExtensionFilter("txt","TXT"));
		this.showOpenDialog(this);
		return this.getSelectedFile().getPath() ;
	}
	

	/**
	 * Metodo necessario para gravar um ficheiro comprimido
	 * 
	 * @param	tipo	1 corresponde a compressao de huffman e 0 a compressao de lzw
	 * @return	devolve o caminho do ficheiro para ser gravado
	 */
	private String gravar_ficheiro_comprimido(int tipo)
	{
		this.setDialogTitle("Guardar");
		
		if(tipo==1)
			this.setFileFilter(new FileNameExtensionFilter("huf","HUF"));
		else if(tipo==0)
			this.setFileFilter(new FileNameExtensionFilter("lzw","LZW"));
		
		this.showSaveDialog(this);
		return this.getSelectedFile().getPath() ;
	}
	
	
	/**
	 * Metodo que abre uma janela de dialogo para procurar um ficheiro a descomprimir
	 * 
	 * @return devolve o caminho do ficheiro
	 */
	private String procurar_ficheiro_comprimido()
	{
		this.setDialogTitle("Seleção de ficheiro texto para descompactar");
		this.setFileFilter(new FileNameExtensionFilter("lzw, huf","LZW","HUF"));
		this.showOpenDialog(this);
		return this.getSelectedFile().getPath() ;
	}
	
	/**
	 * Metodo para escolher a localização do ficheiro de texto a gravar apos descompressão
	 * @return devolve o caminho do ficheiro
	 */
	private String gravar_ficheiro_texto()
	{
		this.setDialogTitle("Guardar");
		this.setFileFilter(new FileNameExtensionFilter("txt","TXT"));
		this.showSaveDialog(this);
		return this.getSelectedFile().getPath()+".txt" ;
	}
	
	
}
