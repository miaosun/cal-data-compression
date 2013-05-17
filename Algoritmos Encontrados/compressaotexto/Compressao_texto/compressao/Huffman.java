package compressao;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.ListIterator;

import bitIO.BitInputStream;
import bitIO.BitOutputStream;


/**
 * Classe que comprime ficheiros com o algoritmo de huffman
 * 
 * @author Rui Campos
 * 
 */
public class Huffman {
	
	/**
	 * Comprime o ficheiro de entrada com o algoritmo de huffman
	 * 
	 * @param ficheiro_entrada	string com o nome do ficheiro que vai ser comprimido
	 * @param ficheiro_saida     string com o nome do ficheiro que é a versao comprimida do ficheiro de entrada
	 */
	@SuppressWarnings("unchecked")
	public static void comprimir(String ficheiro_entrada, String ficheiro_saida) throws IOException
	{
		File f = new File(ficheiro_entrada);
		Reader reader = new FileReader(f);
		BufferedReader bReader = new BufferedReader(reader);
		Hashtable < String, Node> vals = new Hashtable<String, Node>();
		Node tmp;
		Node tmp2;
		
		
		Character ch= ' ';
		while(bReader.ready())
		{		
			//leitura de char
			ch = (char)bReader.read();
			//existe no array o nó correspondente ao char?
			tmp =  vals.get(ch.toString());
			if(tmp != null)
				//incrementar ao nó
				tmp.incCounter();
			else{
			//nao
				
				//acrescentar ao array de nós um nó com o char
				tmp = new Node(ch.toString());
				vals.put(ch.toString(), tmp);
			}
		}
		//ordenacao por frequencia
		LinkedList<Node> sorted_nodes = new LinkedList<Node>();
		Enumeration keys = vals.keys();		
		String next;		
		while(keys.hasMoreElements())
		{
			next = (String)keys.nextElement();
			sorted_nodes.addFirst(vals.get(next));

		}
		
		java.util.Collections.sort(sorted_nodes);
		sorted_nodes.addFirst(new Node("sb", 1));
		
		//criação da arvore
		boolean added = false;
		while(sorted_nodes.size() > 1)
		{
			added = false;
			//criar nó com os primeiros dois nós
			tmp = new Node(sorted_nodes.get(0), sorted_nodes.get(1));
			//remover da lista de nós
			sorted_nodes.removeFirst();
			sorted_nodes.removeFirst();
			//inserir o nó na lista ordenada
			for(ListIterator<Node> iter = sorted_nodes.listIterator(); iter.hasNext();)
			{
				tmp2 = iter.next();
				if(0 < tmp2.compareTo(tmp))
				{
						iter.add(tmp);
						added = true;
						break;
				}				
				
				
			}
			if(!added)
				sorted_nodes.addLast(tmp);
		}
		//criação da hash table apartir da arvore
		Hashtable<String, String> codificacao = new Hashtable<String,String>();	
		File s = new File(ficheiro_saida + ".hufc");
		BufferedWriter bWriterDicionario = new BufferedWriter(new FileWriter(s));
		encodingHashtable(sorted_nodes.getFirst(), codificacao, new String());
		keys = codificacao.keys();
		//remoção do codigo de stopbits
		String stopbits_code = codificacao.get("sb");
		bWriterDicionario.write(stopbits_code);
		codificacao.remove("sb");
		bWriterDicionario.write('\n');
		//guardar a codificação
		while(keys.hasMoreElements())
		{
			String nova_key = (String)keys.nextElement();
			bWriterDicionario.write(nova_key);
			bWriterDicionario.write((String)codificacao.get(nova_key));
			bWriterDicionario.write('\n');
		}
		bWriterDicionario.write(((Integer)(determineBiggestSizeofCode(codificacao) + 1)).toString());
		bWriterDicionario.close();
		
		//codificar
		FileOutputStream file = new FileOutputStream(ficheiro_saida);
		BitOutputStream bbWriter = new BitOutputStream( file);
		bReader = new BufferedReader(new FileReader(ficheiro_entrada));
		while(bReader.ready())
		{
			ch = (char)bReader.read();
			String str = codificacao.get(ch.toString());
			for(int i = 0; str.length() > i; ++i)
			bbWriter.writeBit((str.charAt(i) == '1') ? 1 : 0);
				
		}
		for(int i = 0; i < stopbits_code.length(); ++i)
		{
				if((stopbits_code.charAt(i)) == '1'){
					bbWriter.writeBit(1);
				}
				else{
				bbWriter.writeBit(0);
				}
		}
		bbWriter.close();
		bReader.close();
		
		
		}
	
	/**
	 * Descomprime o ficheiro de entrada com o algoritmo de huffman
	 * 
	 * @param ficheiro_entrada	string com o nome do ficheiro que vai ser descomprimido
	 * @param ficheiro_saida     string com o nome do ficheiro que vai ficar com a versão descomprimida do ficheiro de entrada
	 */
		
	public static void descomprimir(String ficheiro_entrada, String ficheiro_saida) throws IOException
	{
		File f = new File(ficheiro_entrada + ".hufc");
		Reader reader = new FileReader(f);
		BufferedReader bReader = new BufferedReader(reader);
		//obter hashtable de codificacao
		Hashtable<String, String> codificacao = new Hashtable<String,String>();	
		//primeira linha é o codigo dos stopbits
		Character ch;
		String tmp = bReader.readLine();
		int size = 0;
		codificacao.put("sb", tmp);
		while(bReader.ready())
		{
			ch = (char)bReader.read();
			tmp = bReader.readLine();
			if(!bReader.ready()){
				if(tmp == null)
				size = Integer.parseInt(ch.toString());
				else
				size = Integer.parseInt(ch + tmp);
				break;
			}

			
				
			codificacao.put(ch.toString(), tmp);	

		}	
		//criar arvore apartir da hashtable
			//criar arvore generica apartir do tamanho dos stopbits
				Node arvore = generateGenericTree(size);				
				//substituir as folhas da arvore pelos elementos da hashtable
				Enumeration chaves = codificacao.keys();
				String val;
				String code;
				while(chaves.hasMoreElements())
				{
				val = (String)chaves.nextElement();
				code = codificacao.get(val);
				arvore.setValatCode(val, code);
				}
				FileInputStream file = new FileInputStream(ficheiro_entrada);
				BitInputStream bbReader = new BitInputStream( file);	
		BufferedWriter bWriter = new BufferedWriter(new FileWriter(new File(ficheiro_saida)));
		//ler e escrever
			//ler
				Node node = arvore;
				while(bbReader.ready())
				{
				//caminhar sobre a arvore
					
					if(bbReader.readBit() == 1)
					node = node.getRightNode();
					else{
						node = node.getLeftNode();
					}
					if(node.getVal() != null)
					{
						//escrever no ficheiro
						if(node.getVal() == "sb")
							break;
						bWriter.write(node.getVal());
						node = arvore;
						continue;
					}
				}
				
				bbReader.close();
				bWriter.close();
			
	}
	
	/**
	 * Gera uma arvore de altura "size"
	 * 
	 * @param size tamanho da arvore generica
	 * @return retorna a arvore com a altura definida pelo parametro size
	 */
	
	private static Node generateGenericTree(int size)
	{
		if(size == 0)
			return new Node("sb");
		return new Node(generateGenericTree(size - 1), generateGenericTree(size - 1));
	}
	
	/**
	 * Determinar o codigo maior na hashtable
	 * 
	 * @param vals	hashtable em que vai ser determinado o maior tamanho de codigo
	 * @return o maior tamanho de codigo
	 */
	
	private static int determineBiggestSizeofCode(Hashtable<String, String> vals){
		Enumeration keys = vals.keys();
		int biggestsizeofcode = 0;
		while(keys.hasMoreElements())
		{
			int tmp = vals.get(keys.nextElement()).length();
			if(biggestsizeofcode < tmp)
				biggestsizeofcode = tmp;
		}
		return biggestsizeofcode;
	}
	
	/**
	 * Função que apartir da arvore cria a codificação dos caracteres na hashtable
	 * 
	 * 
	 * @param node	arvore de codificação
	 * @param encoding	hashtable na qual vao ser inseridos os codigos
	 * @param code	codigo actual
	 */
	
	public static void encodingHashtable(Node node, Hashtable<String, String> encoding, String code)
	{
		if(node.getVal() != null)
		{
			String c = new String(node.getVal());
			encoding.put(c, code);
		}
		else
		{
			encodingHashtable(node.getLeftNode(), encoding, code + "0");
			encodingHashtable(node.getRightNode(), encoding, code + "1");
			
		}
			
	}
}




