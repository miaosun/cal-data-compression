package bitIO;

import java.io.IOException;
import java.io.InputStream;
/**
 *  
 * Esta classe lê ficheiros bit a bit. Para o efectuar é utilizado 
 * um buffer de 8 bits que vai sendo lido bit a bit. Quando sao 
 * lidos 8 bits o buffer é preenchido com um novo byte do ficheiro.
 * @author Greg Travis http://archive.devx.com/java/free/articles/gt052002/gt052002p.asp  Com algumas alteraçõees para se adaptar ao trabalho.
 *
 *
 */

public class BitInputStream
{
	
  /**
   *  stream de escrita
   * 
   */
  private InputStream in;
  private int buffer;
  /**
   * proximo bit a ser lido
   */
  private int nextBit = 8;
  /**
   * estado da stream
   */
  private boolean ready;

  /**
   * Construtor
   * @param in stream de escrita
   */
  public BitInputStream( InputStream in ) {
    this.in = in;
    ready = true;
  }
  
  /**
   * 
   * @return Retorna o bit lido.
   * @throws IOException
   */

  synchronized public int readBit() throws IOException {
    if (in == null)
      throw new IOException( "Already closed" );

    if (nextBit==8) {
      buffer = in.read();

      if (buffer==-1)
        ready = false;

      nextBit = 0;
    }

    int bit = buffer & (1<<nextBit);
    nextBit++;

    bit = bit == 0 ? 0 : 1;

    return bit;
  }
  
  /**
   * 
   * @return retorna true se a leitura ainda é possivel.
   */
  
  public boolean ready()
  {
	  return ready;
  }
  
  /**
   * Termina a stream.
   * @throws IOException
   */

  public void close() throws IOException {
    in.close();
    in = null;
  }
}