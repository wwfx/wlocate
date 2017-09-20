/* comparray4.c
   Copyright (C) 2005, K. Sadakane, all rights reserved.

   This file contains an implementation of CSA.
   For more information, see

   K. Sadakane. Compressed text databases with efficient query
     algorithms based on the compressed suffix array.
     In Proceedings 11th Annual International Symposium on Algorithms
     and Computation (ISAAC)}, LNCS v. 1969, pages 410--421, 2000.

   K. Sadakane. Succinct representations of lcp information and
     improvements in the compressed suffix arrays.
     In Proceedings 13th Annual ACM-SIAM Symposium on Discrete
     Algorithms (SODA), 2002.

   K. Sadakane. New text indexing functionalities of the compressed
     suffix arrays. Journal of Algorithms, 48(2):294--313, 2003.


   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef _COMPARRAY_H_
#define _COMPARRAY_H_

#define USE_MMAP

#ifdef USE_MMAP
#include "mman.h"
#endif

#define SIGMA 256

typedef struct csa {
  long n,m;
  long l,two,two2;
  long K[SIGMA+2],C[SIGMA+1],C2[SIGMA+1];
  long *SA,*ISA,*R;
  unsigned short *B; /* bit列 */
#ifdef USE_MMAP
  MMAP *mapp,*mapi;
#endif
} CSA;

long csa_psi(CSA *SA,long i);
long csa_T(CSA *SA,long i);
long csa_inverse(CSA *SA, long suf);
void csa_decode(unsigned char *p,CSA *SA,long suf,long len);
void csa_decode2(unsigned char *p,CSA *SA,long pos,long len);
long csa_write(CSA *SA,char *fname1,char *fname2);
void csa_new(long n, long *p, unsigned char *s, char *fname1, char *fname2, long rankb_w,long rankb_w2);
long csa_read(CSA *SA,char *fname1,char *fname2);
long initranktables(void);
void mkdecodetable(void);
long csa_lookup(CSA *SA, long i);
long *csa_batchlookup(CSA *SA,long l, long r);
unsigned long *csa_batchlookup2(CSA *SA,long l, long r);
long csa_bsearch(const unsigned char *key,long keylen,CSA *SA,long *li,long *ri);
void csa_decode1line(unsigned char *p,CSA *SA,long suf,long maxlen);
void csa_decodeall(unsigned char *p,CSA *SA);


#endif
