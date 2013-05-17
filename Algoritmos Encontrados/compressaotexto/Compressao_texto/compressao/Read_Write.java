package compressao;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Classe responsável pela escrita e leitura de ficheiros necessário para o algoritmo de LZW
 * 
 * @author Paulo Pinto
 *
 */
public class Read_Write {

	/**
	 * Escreve texto fornecido num DataOutputStream
	 * 
	 * @param ss	string que comtem a sequencia de bits que se deseja escrever no ficheiro
	 * @param out	DataOutputStream
	 * @throws IOException
	 */
	static void escrever_texto(String ss, DataOutputStream out) throws IOException {
		// TODO Auto-generated method stub
		out.writeBytes(ss);
		out.flush();
		
	}

	
	/**
	 * Lê um código codificado num ficheiro comprimido pelo algoritmo de LZW
	 * 
	 * @param is	DataInputStream
	 * @return	devolve o inteiro correspondente ao código lido
	 * @throws IOException
	 */
	static int ler_codigo(DataInputStream is) throws IOException {
		// TODO Auto-generated method stub
		return  (int) (is.read()<<8) + is.read(); //le codigo que se encontra no ficheiro
	}

	/**
	 * Escreve o código codificado pelo algoritmo LZW num ficheiro
	 * 
	 * @param palavra_codigo	codigo de 16bits
	 * @param out				DataOutputStream
	 * @throws IOException
	 */
	static void escrever_bytes(int palavra_codigo, DataOutputStream out) throws IOException {
		// TODO Auto-generated method stub
		out.write((palavra_codigo & 0xFF00) >> 8);//mascara para escrever os 8bits mais significativos
		out.write(palavra_codigo & 0xFF);// e depois o 8 bits menos significativos

		out.flush();
	}
	
	
	/**
	 * Lê os bytes correspendentes a um caracter
	 * 
	 * @param is	DataInputStream
	 * @return	devolve o caracter
	 * @throws IOException
	 */
	static char ler_byte(DataInputStream is) throws IOException {
		// TODO Auto-generated method stub
		return (char)is.read(); //escreve para um char visto que "byte" corresponderá a -127 a 128
								//devido ao bit de sinal 1bit_sinal + 2^7

		
		
	}
}
