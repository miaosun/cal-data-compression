// Huffman.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(__COMPRESS_H__)
#define __COMPRESS_H__

bool CompressHuffman(BYTE *pSrc, int nSrcLen, BYTE *&pDes, int &nDesLen);
bool DecompressHuffman(BYTE *pSrc, int nSrcLen, BYTE *&pDes, int &nDesLen);

#endif __COMPRESS_H__