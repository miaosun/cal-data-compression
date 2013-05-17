package bitIO;

import java.io.IOException;
import java.io.OutputStream;

/**
 * 
 * Esta classe é utilizada para escrever bit a bit num ficheiro.
 * Esta escrita é feita através de um buffer intermedio em que
 * se vai escrevendo até 8 bits. Quando estes 8 bits sao atingidos
 * o byte é escrito no ficheiro e o buffer é apagado. 
 * @author Greg Travis http://archive.devx.com/java/free/articles/gt052002/gt052002p.asp  Com algumas alterações para se adaptar ao trabalho.
 *
 */

public class BitOutputStream
{
/**
 * stream de saida
 */
  private OutputStream out;
  private int buffer;
  /**
   * numero de bits já lidos.
   */
  private int bitCount;

  /**
   * Construtor 
   * @param out output stream
   */
  public BitOutputStream( OutputStream out ) {
    this.out = out;
  }

  /**
   * 
   * @param bit bit a escrever no ficheiro.
   * @throws IOException
   */
  synchronized public void writeBit( int bit ) throws IOException {
    if (out==null)
      throw new IOException( "Already closed" );

    if (bit != 0 && bit != 1) {
      throw new IOException( bit+" is not a bit" );
    }

    buffer |= bit<<bitCount;
    bitCount++;

    if (bitCount==8) {
      flush();
    }
  }

  /**
   * Escreve o buffer actual no ficheiro e reinicia o buffer
   * @throws IOException
   */
  private void flush() throws IOException {
    if (bitCount>0) {
      out.write( (byte)buffer );
      bitCount=0;
      buffer=0;
    }
  }
  /**
   * Termina a stream
   * @throws IOException
   */
  

  public void close() throws IOException {
    flush();
    out.close();
    out = null;
  }
}
