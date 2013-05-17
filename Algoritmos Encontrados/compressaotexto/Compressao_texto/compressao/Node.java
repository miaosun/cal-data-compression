package compressao;

/**
 * Classe corresponde aos n�s da �rvore de codifica��o, sendo que cada n� cont�m um valor, um n� esquerdo, um n� direito e um contador.
 * 
 * @author Rui Campos
 *
 *	
 */

public class Node implements Comparable{
	/**
	 * valor do n�
	 */
	String val;
	/**
	 * contador de frequ�ncia
	 */
	int counter = 0;
	Node leftnode = null;
	Node rightnode = null;
	
	/**
	 * Construtor
	 * @param val valor que o n� vai conter
	 */
	public Node(String val)
	{
		this.val = new String(val); 
		counter = 1;
		
	}
	
	/**
	 * Construtor
	 * @param val	valor que o n� vai conter
	 * @param counter	valor com que o contador vai ser inicializado
	 */
	public Node(String val, int counter)
	{
		this.val = new String(val);
		this.counter = counter;
	}
	
	/**
	 * Construtor
	 * Este construtor recebe dois n�s e determina qual vai ser o n� que vai ser o
	 * esquerdo e direito atraves da comparac�o do n�mero do contador de cada n�.
	 * Tamb�m determina o contador do novo n� com a soma dos dois n�s de entrada
	 * @param node1	
	 * @param node2
	 */
	public Node(Node node1, Node node2)
	{
		if(0 < node1.compareTo(node2))
		{
		leftnode = node2;
		rightnode = node1;
		}
		else{
			leftnode = node1;
			rightnode = node2;
		}
		this.counter = node1.getCounter() + node2.getCounter();
	}
	
	/**
	 * Incrementa o contador do n�
	 *
	 */
	public void incCounter(){
		++counter;
	}
	/**
	 * 
	 * @return Retorna o contador do n�
	 */
	public int getCounter()
	{
		return counter;
	}
	
	/**
	 * 
	 * @return Retorna o valor do n�
	 */
	public String getVal()
	{
		return val;
	}
	
	/**
	 * @return Retorna a diferen�a dos contadores entre o n� actual e o n� que � passado por argumento
	 */
	public int compareTo(Object arg0) {
		return this.counter - ((Node)arg0).counter;
	}
	/**
	 * 
	 * @return Retorna o n� esquerdo
	 */
	public Node getLeftNode()
	{
		return leftnode;
	}
	/**
	 * 
	 * @return Retorna o n� direito
	 */
	public Node getRightNode()
	{
		return rightnode;
	}
	/**
	 * 
	 * @param val Novo valor do n�
	 */
	private void setVal(String val)
	{
		this.val = val;
	}
	/**
	 * Este metodo coloca "val" no n� caso o codigo esteja vazio. Se o codigo
	 * n�o estiver vazio chama a fun��o recursivamente com o n� esquerdo ou direito
	 * (depende de o valor do primeiro char de "code" ser 0 ou 1) e corta o primeiro
	 * elemento de "code"
	 * @param val	Valor que vai ser colocado no n�
	 * @param code	C�digo para percorrer a arvore
	 * @return	true
	 */
	public boolean setValatCode(String val, String code)
	{
		if(code.length() == 0)
		{
			this.setVal( val);
			this.leftnode = null;
			this.rightnode = null;
			return true;
			}
		else{
		if(code.charAt(0) == '0')
		{
			
			return this.leftnode.setValatCode(val, code.substring(1));
		}
		else
		{			
			return this.rightnode.setValatCode(val, code.substring(1));
		}
		}
			
	}
	
	

}
