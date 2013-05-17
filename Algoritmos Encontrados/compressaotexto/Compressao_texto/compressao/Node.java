package compressao;

/**
 * Classe corresponde aos nós da árvore de codificação, sendo que cada nó contém um valor, um nó esquerdo, um nó direito e um contador.
 * 
 * @author Rui Campos
 *
 *	
 */

public class Node implements Comparable{
	/**
	 * valor do nó
	 */
	String val;
	/**
	 * contador de frequência
	 */
	int counter = 0;
	Node leftnode = null;
	Node rightnode = null;
	
	/**
	 * Construtor
	 * @param val valor que o nó vai conter
	 */
	public Node(String val)
	{
		this.val = new String(val); 
		counter = 1;
		
	}
	
	/**
	 * Construtor
	 * @param val	valor que o nó vai conter
	 * @param counter	valor com que o contador vai ser inicializado
	 */
	public Node(String val, int counter)
	{
		this.val = new String(val);
		this.counter = counter;
	}
	
	/**
	 * Construtor
	 * Este construtor recebe dois nós e determina qual vai ser o nó que vai ser o
	 * esquerdo e direito atraves da comparacão do número do contador de cada nó.
	 * Também determina o contador do novo nó com a soma dos dois nós de entrada
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
	 * Incrementa o contador do nó
	 *
	 */
	public void incCounter(){
		++counter;
	}
	/**
	 * 
	 * @return Retorna o contador do nó
	 */
	public int getCounter()
	{
		return counter;
	}
	
	/**
	 * 
	 * @return Retorna o valor do nó
	 */
	public String getVal()
	{
		return val;
	}
	
	/**
	 * @return Retorna a diferença dos contadores entre o nó actual e o nó que é passado por argumento
	 */
	public int compareTo(Object arg0) {
		return this.counter - ((Node)arg0).counter;
	}
	/**
	 * 
	 * @return Retorna o nó esquerdo
	 */
	public Node getLeftNode()
	{
		return leftnode;
	}
	/**
	 * 
	 * @return Retorna o nó direito
	 */
	public Node getRightNode()
	{
		return rightnode;
	}
	/**
	 * 
	 * @param val Novo valor do nó
	 */
	private void setVal(String val)
	{
		this.val = val;
	}
	/**
	 * Este metodo coloca "val" no nó caso o codigo esteja vazio. Se o codigo
	 * não estiver vazio chama a função recursivamente com o nó esquerdo ou direito
	 * (depende de o valor do primeiro char de "code" ser 0 ou 1) e corta o primeiro
	 * elemento de "code"
	 * @param val	Valor que vai ser colocado no nó
	 * @param code	Código para percorrer a arvore
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
