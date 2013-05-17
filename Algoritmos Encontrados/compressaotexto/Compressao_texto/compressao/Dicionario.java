package compressao;

import java.util.HashMap;

/**
 * Classe que se encontra encarregue da cria��o do dicion�rio para o algoritmo de LZW
 * 
 * @author Paulo Pinto
 *
 */
public class Dicionario {

	/**
	 * C�digo da proxima palavra a ser adicionada ao dicionario
	 */
	private int codigo = 1;

	/**
	 * HashMap com chaves os codigos de cada String (dicion�rio para descomprimir)
	 */
	private HashMap <Integer,String> chaves;
	
	/**
	 * HashMap com chaves as String relacionando-as assim com os seus c�digos (dicion�rio para comprimir)
	 */
	private HashMap <String,Integer> raizes;
	
	
	/**
	 * Constructor
	 * 
	 * @param comprimir 	parametro necess�rio para ser criado o dicion�rio para comprimir ou descomprmir
	 * @see #add_palavra(String, boolean)							
	 */
	public Dicionario(boolean comprimir){

		if(comprimir) //decis�o do diconario a criar, consoante a fun��o seja comprimir ou descomprimir
			this.raizes = new HashMap<String,Integer>();
		else this.chaves = new HashMap<Integer,String>();//cria��o dos HashMap's
		
		
		for(int i = 0 ; i!= 256; i++) //cria��o do dicion�rio por defeito com os 256 codigos poss�veis (2^8=256)
		{							  
			this.add_palavra(((char)i)+"", comprimir);
		}
	}
	
	/**
	 * Metodo que adiciona uma "String" ao dicion�rio
	 * 
	 * @param pal		palavra codigo a ser inserida no dicion�rio
	 * @param comprimir	booleano que � passado a fun��o para adicionar ao dicionario de compress�o ou de descompress�o 
	 * 
	 */
	public void add_palavra(String pal,boolean comprimir) {
		if(codigo == 65536) //palavras codigo de 16bits
			return;
		
		if(comprimir)//decis�o consoante a fun��o do dicion�rio seja comprimir ou descomprimir
			this.raizes.put(pal, codigo);
		else this.chaves.put(codigo, pal);
		
		++codigo;//incrementa o c�digo a medida que vai introduzindo uma palavra
	}

	////////////////////FUN��ES NECESS�RIAS PARA COMPRESS�O////////////////////
	
	/**
	 * Procura uma "palavra" no dicion�rio
	 * 
	 * @param raiz		a string a procurar no dicion�rio
	 * @return			retorna verdadeiro se a string existir no dicion�rio
	 * 
	 */
	public boolean procurar_raiz(String raiz) { 
		return raizes.containsKey(raiz);    

	}

	/**
	 * Metodo para devolver o c�digo de uma palavra
	 * 
	 * @param raiz		a string a que se deseja saber o c�digo
	 * @return			retorna um inteiro que � o c�digo da string
	 * 
	 */
	public int devolver_codigo(String raiz) { 
		return raizes.get(raiz);
	}

	////////////////////FUN��ES NECESS�RIAS PARA DESCOMPRESS�O//////////////////
	
	
	/**
	 * Metodo que devolve a palavra de c�digo a partir do c�digo fornecido
	 * 
	 * @param codigo		inteiro que corresponde ao c�digo que se pretende saber a que "palavra" esta associado
	 * @return				devolve a string correspondente ao c�digo fornecido
	 * 
	 */
	public String devolve_raiz(int codigo) { 
		return chaves.get(codigo);
	}
	
	/**
	 * Procura um c�digo no dicion�rio
	 * 
	 * @param codigo		inteiro que corresponde ao c�digo
	 * @return				devolve verdadeiro se o c�digo existir e falso se n�o se verificar a condi��o anterior
	 * 
	 */
	public boolean procurar_codigo(int codigo) { 
		return chaves.containsKey(codigo);
	}

}
