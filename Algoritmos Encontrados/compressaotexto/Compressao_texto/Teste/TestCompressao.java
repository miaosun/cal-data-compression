package Teste;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import compressao.Dicionario;
import compressao.Huffman;
import compressao.LZW;


import junit.framework.TestCase;


public class TestCompressao extends TestCase {
	
	private void comprimir(int tipo, String ficheiro_entrada, String ficheiro_saida, long expectedMaxTime) throws IOException{

		long start = System.currentTimeMillis();

		if(tipo == 0)
			
		LZW.comprimir(ficheiro_entrada, ficheiro_saida);
		else
		Huffman.comprimir(ficheiro_entrada, ficheiro_saida);

		long finish = System.currentTimeMillis();

		System.out.println("     Compressao: "+ficheiro_entrada);
		System.out.println("                Tempo= " + (finish - start) + "ms TempoMaximo= " + expectedMaxTime + "ms");
		if (finish - start > expectedMaxTime)
			assertEquals("maximum execution time", expectedMaxTime, finish-start);
	}
	
	private void descomprimir(int tipo, String ficheiro_entrada, String ficheiro_saida,long expectedMaxTime) throws IOException{

		long start = System.currentTimeMillis();

		if(tipo == 0)
			
			LZW.descomprimir(ficheiro_entrada, ficheiro_saida);
			else
			Huffman.descomprimir(ficheiro_entrada, ficheiro_saida);

		long finish = System.currentTimeMillis();
		
		File entrada = new File(ficheiro_entrada);
		entrada.delete();

		System.out.println("     Descompressao: "+ficheiro_entrada);
		System.out.println("                   Tempo= " + (finish - start) + "ms TempoMaximo= " + expectedMaxTime + "ms");
		if (finish - start > expectedMaxTime)
			assertEquals("maximum execution time", expectedMaxTime, finish-start);
		
		
		
	}
	
	private void comparar_ficheiros(String ficheiro_original, String ficheiro_descomprimido) throws IOException {

		
		// necessário para ler do ficheiro
		DataInputStream original = null;
		original = new DataInputStream(new FileInputStream(ficheiro_original));
		
		DataInputStream descomprimido = null;
		descomprimido = new DataInputStream(new FileInputStream(ficheiro_descomprimido));
		
		boolean iguais = true;
		
		int numero_bytes1 = original.available();
		int numero_bytes2 = descomprimido.available();
		
		
		if (numero_bytes1 != numero_bytes2)
			iguais = false;
		else {
			while (numero_bytes1 != 0) {
				if (original.read() != descomprimido.read()) {
					iguais = false;
					break;
				}
				--numero_bytes1;
			}
		}
		
		original.close();
		descomprimido.close();
		
		File file = new File(ficheiro_descomprimido);
		file.delete();
		
		
		assertEquals(iguais, true);
		
	}
	
	private void taxa_compressao(String ficheiro_original, String ficheiro_comprimido) throws IOException {
		
		DataInputStream original = null;
		original = new DataInputStream(new FileInputStream(ficheiro_original));
		
		DataInputStream descomprimido = null;
		descomprimido = new DataInputStream(new FileInputStream(ficheiro_comprimido));
		
		float numero_bytes1 = original.available();
		float numero_bytes2 = descomprimido.available();
		
		float taxa =100 - ((numero_bytes2/numero_bytes1) * 100);
		
		System.out.println("                Taxa de compressao= "+taxa + "%");
		System.out.println();
		
		
		
	}
	
	
	public void testDicionarioDefault_perfomance() throws IOException {
		
		long expectedMaxTime = 20;
		
		long start = System.currentTimeMillis();
		
		@SuppressWarnings("unused")
		Dicionario dic = new Dicionario(true);
		
		long finish = System.currentTimeMillis();
		
		System.out.println("Criacao do dicionario ->");
		System.out.println("Time= " + (finish - start) + "ms ExpectedMaxTime= " + expectedMaxTime + "ms");
		if (finish - start > expectedMaxTime)
			assertEquals("maximum execution time", expectedMaxTime, finish-start);
		System.out.println();
	}
	
	public void test_LZW50KB() throws IOException{
		
		System.out.println("LZW ficheiro 50kb-----------------------------------------------");
		System.out.println();

		comprimir(0,"./ficheiros_teste/arquivo50kb.txt", "./ficheiros_teste/ficheiro_pequeno_comprimido.lzw",1000);
		
		taxa_compressao("./ficheiros_teste/arquivo50kb.txt", "./ficheiros_teste/ficheiro_pequeno_comprimido.lzw");

		descomprimir(0,"./ficheiros_teste/ficheiro_pequeno_comprimido.lzw","./ficheiros_teste/ficheiro_pequeno_descomprimido.txt",1000);

		comparar_ficheiros("./ficheiros_teste/arquivo50kb.txt","./ficheiros_teste/ficheiro_pequeno_descomprimido.txt");
		
		System.out.println();
		
	}
	
	public void test_LZW100KB() throws IOException{
		
		System.out.println("LZW ficheiro 100kb-----------------------------------------------");
		System.out.println();

		comprimir(0,"./ficheiros_teste/arquivo100kb.txt", "./ficheiros_teste/ficheiro_medio_comprimido.lzw",2000);
		
		taxa_compressao("./ficheiros_teste/arquivo100kb.txt", "./ficheiros_teste/ficheiro_medio_comprimido.lzw");

		descomprimir(0,"./ficheiros_teste/ficheiro_medio_comprimido.lzw","./ficheiros_teste/ficheiro_medio_descomprimido.txt",2000);

		comparar_ficheiros("./ficheiros_teste/arquivo100kb.txt","./ficheiros_teste/ficheiro_medio_descomprimido.txt");
		
		System.out.println();
		
	}
	public void test_LZW1MB() throws IOException{
		
		System.out.println("LZW ficheiro 1mb-----------------------------------------------");
		System.out.println();

		comprimir(0,"./ficheiros_teste/arquivo1mb.txt", "./ficheiros_teste/ficheiro_grande_comprimido.lzw",20000);
		
		taxa_compressao("./ficheiros_teste/arquivo1mb.txt", "./ficheiros_teste/ficheiro_grande_comprimido.lzw");

		descomprimir(0,"./ficheiros_teste/ficheiro_grande_comprimido.lzw","./ficheiros_teste/ficheiro_grande_descomprimido.txt",20000);

		comparar_ficheiros("./ficheiros_teste/arquivo1mb.txt","./ficheiros_teste/ficheiro_grande_descomprimido.txt");
		
		System.out.println();
		
	}
	public void test_LZWImagem() throws IOException{

		System.out.println("LZW ficheiro imagem-----------------------------------------------");
		System.out.println();
		
		comprimir(0,"./ficheiros_teste/imagem.bmp", "./ficheiros_teste/imagem.lzw",14000);
		
		taxa_compressao("./ficheiros_teste/imagem.bmp", "./ficheiros_teste/imagem.lzw");

		descomprimir(0,"./ficheiros_teste/imagem.lzw","./ficheiros_teste/imagem_descomprimida.bmp",14000);

		comparar_ficheiros("./ficheiros_teste/imagem.bmp","./ficheiros_teste/imagem_descomprimida.bmp");
		
		System.out.println();
		
	}
	
	
	public void test_HUF50KB() throws IOException{
		
		System.out.println("HUF ficheiro 50kb-----------------------------------------------");
		System.out.println();

		comprimir(1,"./ficheiros_teste/arquivo50kb.txt", "./ficheiros_teste/ficheiro_pequeno_comprimido.huf",1000);
		
		taxa_compressao("./ficheiros_teste/arquivo50kb.txt", "./ficheiros_teste/ficheiro_pequeno_comprimido.huf");

		descomprimir(1,"./ficheiros_teste/ficheiro_pequeno_comprimido.huf","./ficheiros_teste/ficheiro_pequeno_descomprimido.txt",1000);

		comparar_ficheiros("./ficheiros_teste/arquivo50kb.txt","./ficheiros_teste/ficheiro_pequeno_descomprimido.txt");
		
		System.out.println();
		
	}
	
	public void test_HUF100KB() throws IOException{
		
		System.out.println("HUF ficheiro 100kb-----------------------------------------------");
		System.out.println();

		comprimir(1,"./ficheiros_teste/arquivo100kb.txt", "./ficheiros_teste/ficheiro_medio_comprimido.huf",2000);
		
		taxa_compressao("./ficheiros_teste/arquivo100kb.txt", "./ficheiros_teste/ficheiro_medio_comprimido.huf");

		descomprimir(1,"./ficheiros_teste/ficheiro_medio_comprimido.huf","./ficheiros_teste/ficheiro_medio_descomprimido.txt",2000);

		comparar_ficheiros("./ficheiros_teste/arquivo100kb.txt","./ficheiros_teste/ficheiro_medio_descomprimido.txt");
		
		System.out.println();
		
	}
	public void test_HUF1MB() throws IOException{
		
		System.out.println("HUF ficheiro 1MB-----------------------------------------------");
		System.out.println();

		comprimir(1,"./ficheiros_teste/arquivo1mb.txt", "./ficheiros_teste/ficheiro_grande_comprimido.huf",20000);
		
		taxa_compressao("./ficheiros_teste/arquivo1mb.txt", "./ficheiros_teste/ficheiro_grande_comprimido.huf");

		descomprimir(1,"./ficheiros_teste/ficheiro_grande_comprimido.huf","./ficheiros_teste/ficheiro_grande_descomprimido.txt",20000);

		comparar_ficheiros("./ficheiros_teste/arquivo1mb.txt","./ficheiros_teste/ficheiro_grande_descomprimido.txt");
		
		System.out.println();
		
	}
	public void test_HUFImagem() throws IOException{
		
		System.out.println("HUF ficheiro Imagem-----------------------------------------------");
		System.out.println();

		comprimir(1,"./ficheiros_teste/imagem.bmp", "./ficheiros_teste/imagem.huf",14000);
		
		taxa_compressao("./ficheiros_teste/imagem.bmp", "./ficheiros_teste/imagem.huf");

		descomprimir(1,"./ficheiros_teste/imagem.huf","./ficheiros_teste/imagem_descomprimida.bmp",14000);

		comparar_ficheiros("./ficheiros_teste/imagem.bmp","./ficheiros_teste/imagem_descomprimida.bmp");
		
		System.out.println();
		
	}
	
	
	
	
}