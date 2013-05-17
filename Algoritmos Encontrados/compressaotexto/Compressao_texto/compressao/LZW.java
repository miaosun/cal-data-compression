package compressao;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Classe com a implementacao do algoritmo LZW de compress�o e descompress�o
 * 
 * @author Paulo Pinto
 *
 */
public class LZW {


	
	/**
	 * Metodo que usa o algoritmo de LZW para comprimir
	 * 
	 * @param ficheiro_entrada	caminho do ficheiro a comprimir
	 * @param ficheiro_saida	caminho do ficheiro a comprimido
	 * @throws IOException
	 * 
	 */
	public static void comprimir(String ficheiro_entrada, String ficheiro_saida)
			throws IOException {

		// criar dicionario por defeito
		Dicionario dic = new Dicionario(true);
		
		// necess�rio para ler do ficheiro
		DataInputStream is = null;
		is = new DataInputStream(new FileInputStream(ficheiro_entrada));

		// necess�rio para escrever do ficheiro
		DataOutputStream out = null;
		out = new DataOutputStream(new FileOutputStream(ficheiro_saida));

		//vari�veis
		String P = "";//string que representa um prefixo
		char C = 0;
		String auxiliar = "";

		//numero de bytes que ser�o lidos
		int numero_bytes = is.available();

		/////////////////////////////Algoritmo LZW para compressao////////////////////////////
		
		while (numero_bytes != 0) {
			
			C = Read_Write.ler_byte(is);//caracter da sequencias de entrada
			
			auxiliar = P+C;
			
			if (dic.procurar_raiz(auxiliar)) { //Se P+C existir no dicion�rio
				P = auxiliar;
			} 
			else {
				Read_Write.escrever_bytes(dic.devolver_codigo(P),out);//escrever no ficheiro codificado
																		//a palavra c�digo de P
				dic.add_palavra(auxiliar,true); //adiciona-se a string P+C ao dicion�rio (true = condificacao)
				P = C+"";
			}
			
			--numero_bytes; //decrementar o numero de bytes lidos
		}

		//n�o existindo mais caracteres na sequencia de entrada colocar a palavra codigo de P no ficheiro
		Read_Write.escrever_bytes(dic.devolver_codigo(P),out);

		out.close();
		is.close();
		return;

	}
	
	/**
	 * Metodo que descodifica um ficheiro codificado pelo algoritmo de LZW
	 * 
	 * @param ficheiro_entrada	caminho do ficheiro comprimido que se deseja descomprimir
	 * @param ficheiro_saida	caminho do ficheiro descomprimido
	 * @throws IOException
	 *
	 */
	public static void descomprimir(String ficheiro_entrada, String ficheiro_saida)throws IOException {
		
		// criar dicionario por defeito
		Dicionario dic = new Dicionario(false);
		
		// necess�rio para ler do ficheiro
		DataInputStream is = null;
		is = new DataInputStream(new FileInputStream(ficheiro_entrada));

		// necess�rio para escrever do ficheiro
		DataOutputStream out = null;
		out = new DataOutputStream(new FileOutputStream(ficheiro_saida));
		
		String SS; // sequ�ncia de saida
		String P;//string que representa um prefixo
		char C;//caracter
		int pW;//palavra c�digo que representa um prefixo
		int cW = Read_Write.ler_codigo(is); // primeira palavra c�digo na sequ�ncia
								// codificada (� sempre uma raiz)

		
		SS = dic.devolve_raiz(cW);// Coloca a string(cW) na sequ�ncia de sa�da
		
		//numero de bytes que ser�o lidos
		int numero_bytes = is.available();

		////////////////////////////Algoritmo LZW para descompressao///////////////////////////
		
		while (numero_bytes != 0) {

				pW = cW;

				cW = Read_Write.ler_codigo(is);//pr�xima palavra c�digo da sequ�ncia codificada;

				if (dic.procurar_codigo(cW)) { // se a raiz existe no dicion�rio
					String raiz = dic.devolve_raiz(cW);
					SS += raiz;// coloca a string(cW) na sequ�ncia de sa�da
					P = dic.devolve_raiz(pW);
					C = raiz.charAt(0); // C = primeiro caracter da string(cW)
					dic.add_palavra(P + C,false); // adicione a string P+C ao dicion�rio
				} else {
					P = dic.devolve_raiz(pW);
					C = P.charAt(0); // C <= primeiro caracter da string(pW)
					SS = P + C; // coloca a string P+C na sequ�ncia de
								// sa�da e adicione-a ao dicion�rio
					dic.add_palavra(SS,false);//adiciona-se a string SS ao dicion�rio (false = descodificacao)

				}
				//escrever SS no ficheiro descomprimido
				Read_Write.escrever_texto(SS,out);
				//limpa a string SS
				SS = "";
				//decrementa o numero de bytes em 2;
				numero_bytes-= 2;
			}
			
		
		out.close();
		is.close();
		return;
	}
	
		
	
}
