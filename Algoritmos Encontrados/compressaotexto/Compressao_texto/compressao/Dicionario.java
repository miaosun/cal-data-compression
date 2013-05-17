package compressao;

import java.util.HashMap;

/**
 * Classe que se encontra encarregue da criação do dicionário para o algoritmo de LZW
 * 
 * @author Paulo Pinto
 *
 */
public class Dicionario {

	/**
	 * Código da proxima palavra a ser adicionada ao dicionario
	 */
	private int codigo = 1;

	/**
	 * HashMap com chaves os codigos de cada String (dicionário para descomprimir)
	 */
	private HashMap <Integer,String> chaves;
	
	/**
	 * HashMap com chaves as String relacionando-as assim com os seus códigos (dicionário para comprimir)
	 */
	private HashMap <String,Integer> raizes;
	
	
	/**
	 * Constructor
	 * 
	 * @param comprimir 	parametro necessário para ser criado o dicionário para comprimir ou descomprmir
	 * @see #add_palavra(String, boolean)							
	 */
	public Dicionario(boolean comprimir){

		if(comprimir) //decisão do diconario a criar, consoante a função seja comprimir ou descomprimir
			this.raizes = new HashMap<String,Integer>();
		else this.chaves = new HashMap<Integer,String>();//criação dos HashMap's
		
		
		for(int i = 0 ; i!= 256; i++) //criação do dicionário por defeito com os 256 codigos possíveis (2^8=256)
		{							  
			this.add_palavra(((char)i)+"", comprimir);
		}
	}
	
	/**
	 * Metodo que adiciona uma "String" ao dicionário
	 * 
	 * @param pal		palavra codigo a ser inserida no dicionário
	 * @param comprimir	booleano que é passado a função para adicionar ao dicionario de compressão ou de descompressão 
	 * 
	 */
	public void add_palavra(String pal,boolean comprimir) {
		if(codigo == 65536) //palavras codigo de 16bits
			return;
		
		if(comprimir)//decisão consoante a função do dicionário seja comprimir ou descomprimir
			this.raizes.put(pal, codigo);
		else this.chaves.put(codigo, pal);
		
		++codigo;//incrementa o código a medida que vai introduzindo uma palavra
	}

	////////////////////FUNÇÕES NECESSÁRIAS PARA COMPRESSÃO////////////////////
	
	/**
	 * Procura uma "palavra" no dicionário
	 * 
	 * @param raiz		a string a procurar no dicionário
	 * @return			retorna verdadeiro se a string existir no dicionário
	 * 
	 */
	public boolean procurar_raiz(String raiz) { 
		return raizes.containsKey(raiz);    

	}

	/**
	 * Metodo para devolver o código de uma palavra
	 * 
	 * @param raiz		a string a que se deseja saber o código
	 * @return			retorna um inteiro que é o código da string
	 * 
	 */
	public int devolver_codigo(String raiz) { 
		return raizes.get(raiz);
	}

	////////////////////FUNÇÕES NECESSÁRIAS PARA DESCOMPRESSÃO//////////////////
	
	
	/**
	 * Metodo que devolve a palavra de código a partir do código fornecido
	 * 
	 * @param codigo		inteiro que corresponde ao código que se pretende saber a que "palavra" esta associado
	 * @return				devolve a string correspondente ao código fornecido
	 * 
	 */
	public String devolve_raiz(int codigo) { 
		return chaves.get(codigo);
	}
	
	/**
	 * Procura um código no dicionário
	 * 
	 * @param codigo		inteiro que corresponde ao código
	 * @return				devolve verdadeiro se o código existir e falso se não se verificar a condição anterior
	 * 
	 */
	public boolean procurar_codigo(int codigo) { 
		return chaves.containsKey(codigo);
	}

}
