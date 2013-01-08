/* 
	filename:	nPatriciaTrie.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-02-15 오후 12:08:59
	title	:	

												10000개의 데이타에 대해 추가/검색/삭제가 약 5배이상 빠름
												-------------------------
												size = 8628 size = 0

												nPatriciaTrie = 4864

												-------------------------
												size = 8628 size = 0

												std::map = 25318



int main(int argc, char* argv[]) {

	uint s,e;
	int idx[10000];
	for(int i=0 ; i < 10000; i++)
	{
		idx[i]=rand();
	}
	fname_t buf;

	{
		printf("----------------------------\n");

		RDTSC(s);

		std::map<std::string,int> p;
		// insert some (first,second) pairs into the structure.

		for(int i=0 ; i < 10000; i++)
		{
			sprintf(buf, "%dassdlkfjweoidf%d",idx[i]);
			p[buf]=i;
		}

		for(int i=0 ; i < 10000; i++)
		{
			sprintf(buf, "%dassdlkfjweoidf%d",idx[i]);
			int asdf = p[buf];
			asdf++;
			int b= asdf+asdf;
		}
		printf(" size = %d",p.size());
		for(int i=0 ; i < 10000; i++)
		{
			sprintf(buf, "%dassdlkfjweoidf%d",idx[i]);
			p.erase(buf);
		}
		printf(" size = %d",p.size());

		RDTSC(e);

		printf("\n\nstd::map = %u\n\n", (e-s)/100000);
	}
	{
		printf("----------------------------\n");

		RDTSC(s);

		nPatriciaTrie<int> p;
		// insert some (first,second) pairs into the structure.

		for(int i=0 ; i < 10000; i++)
		{
			sprintf(buf, "%dassdlkfjweoidf%d",idx[i]);
			p[buf]=i;
		}

		for(int i=0 ; i < 10000; i++)
		{
			sprintf(buf, "%dassdlkfjweoidf%d",idx[i]);
			int asdf = p[buf];
			asdf++;
			int b= asdf+asdf;
		}
		printf(" size = %d",p.size());
		for(int i=0 ; i < 10000; i++)
		{
			sprintf(buf, "%dassdlkfjweoidf%d",idx[i]);
			p.erase(buf);
		}
		printf(" size = %d",p.size());

		RDTSC(e);

		printf("\n\nnPatriciaTrie = %u\n\n", (e-s)/100000);
	}


	return 0;
}

*/


//----------------------------------------------------------------------------
//
// PATRICIA Trie Template Class
//
// Released into the public domain on February 3, 2005 by:
//
//      Radu Gruian
//      web:   http://www.gruian.com
//      email: gruian@research.rutgers.edu
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to:
//
//      Free Software Foundation, Inc.
//      59 Temple Place, Suite 330
//      Boston, MA 02111-1307
//      USA
//
//----------------------------------------------------------------------------
//
// File:    nPatriciaTrie.h
// Date:    02/03/2005
// Purpose: Patricia trie ADT.
//
//----------------------------------------------------------------------------

#ifndef nPatriciaTrieH
#define nPatriciaTrieH

#include <tchar.h>
#include <stdlib.h>
#include <string.h>


namespace nMech
{
	namespace nDataStruct
	{
		typedef TCHAR* nPatriciaTrieKey_t;
		typedef const TCHAR* nPatriciaTrieKey_ct;


		//----------------------------------------------------------------------------
		//
		// Class:   nPatriciaTrieNode
		// Purpose: A node in a PATRICIA trie.
		//          Each node stores one first, and the second associated with that first.
		//
		//----------------------------------------------------------------------------
		template <class TTT> 
		class nPatriciaTrieNode 
			//----------------------------------------------------------------
		{
		public:
			int bit_index;
			nPatriciaTrieKey_t        first; // key
			TTT                       second; // data
			nPatriciaTrieNode<TTT>*   left;
			nPatriciaTrieNode<TTT>*   right;

			nPatriciaTrieNode() 
			{	
				Initialize(NULL, TTT() , -1, this, this);
			}
			//----------------------------------------------------------------------------

			void Initialize
				(
				nPatriciaTrieKey_ct k
				,const TTT &d
				, int bi
				,nPatriciaTrieNode<TTT>* l
				,nPatriciaTrieNode<TTT>* r
				) 
			{
				if (k)
					first = (nPatriciaTrieKey_t)jt_strdup(k);
				else
					first = const_cast<nPatriciaTrieKey_t>(k);
				second      = d;
				left      = l;
				right     = r;
				bit_index = bi;
			}

			//----------------------------------------------------------------------------

			~nPatriciaTrieNode() {
				if (first) {
					free(first);
					first = NULL;
				}
			}

			//----------------------------------------------------------------------------

			TTT GetData() {
				return second;
			}

			//----------------------------------------------------------------------------

			bool SetData(const TTT &d) {
				second = d;
				//memcpy(&second, &d, sizeof(TTT));
				return true;
			}

			//----------------------------------------------------------------------------

			nPatriciaTrieKey_ct GetKey() {
				return first;
			}

			//----------------------------------------------------------------------------

			nPatriciaTrieNode<TTT>* GetLeft() {
				return left;
			}

			//----------------------------------------------------------------------------

			nPatriciaTrieNode<TTT>* GetRight() {
				return right;
			}


		};

		//----------------------------------------------------------------------------
		//
		// Class:   nPatriciaTrie
		// Purpose: Implements a PATRICIA trie structure with keys of
		//          type nPatriciaTrieKey_t (currently char*, but can be changed, see
		//          the definition of nPatriciaTrieKey_t above).
		//
		//----------------------------------------------------------------------------
		template <class TTT > class nPatriciaTrie 
		{
		public:
			typedef nPatriciaTrieNode<TTT>* iterator;
			nPatriciaTrieNode<TTT>* head;
			size_t m_iSize;
		public:


			//----------------------------------------------------------------------------

			nPatriciaTrie() {
				// Create the head of the structure. The head is never moved
				// around in the trie (i.e. it always stays at the top of the structure).
				// This prevents further complications having to do with node removal.
				head = new nPatriciaTrieNode<TTT>();
#define ZEROTAB_SIZE 256
				head->first = (TCHAR*)calloc(ZEROTAB_SIZE, 1);
				m_iSize=0;

			}

			//----------------------------------------------------------------------------

			~nPatriciaTrie() {
				clear();
			}

			//----------------------------------------------------------------------------

			iterator insert(nPatriciaTrieKey_ct k, const TTT &d) {

				nPatriciaTrieNode<TTT> *p, *t, *x;

				// Start at the root
				p = head;
				t = (iterator)(p->right);

				// Navigate down the tree and look for the first
				while (p->bit_index < t->bit_index) {
					p = t;
					t = (iterator)(bit_get(k, t->bit_index) ? t->right : t->left);
				}

				// Is the first already in the tree?
				if (key_compare(k, t->first))
					return NULL; // Already in the tree!

				// Find the first bit that does not match.
				int i = bit_first_different(k, t->first);

				// Find the appropriate place in the tree where
				// the node has to be inserted
				p  = head;
				x  = (iterator)(p->right);
				while ( ( p->bit_index < x->bit_index ) &&
					( x->bit_index < i) ) {
						p = x;
						x = (iterator)(bit_get(k, x->bit_index) ? x->right : x->left);
					}

					// Allocate a new node and initialize it.
					t = new nPatriciaTrieNode<TTT>();
					++m_iSize;
					t->Initialize(k, d, i, (bit_get(k, i) ? x : t), (bit_get(k, i) ? t : x));

					// Rewire
					if (bit_get(k, p->bit_index))
						p->right = t;
					else
						p->left = t;

					// Return the newly created node
					return t;

			}

			//----------------------------------------------------------------------------

			TTT& Lookup(nPatriciaTrieKey_ct k) {

				// Lookup the node
				iterator node = find(k);

				// Failed?
				if (!node)
				{
					return insert(k,TTT())->second;
				}

				// Return the second stored in this node
				return node->second;

			}

			TTT& operator [](nPatriciaTrieKey_ct k)
			{
				return Lookup(k);
			}

			//----------------------------------------------------------------------------

			iterator find(nPatriciaTrieKey_ct k) {

				iterator p;
				iterator x;

				// Start at the root.
				p = head;
				x = (iterator)(head->right);

				// Go down the Patricia structure until an upward
				// link is encountered.
				while (p->bit_index < x->bit_index) {
					p = x;
					x = (iterator)(bit_get(k, x->bit_index) ? x->right : x->left);
				}

				// Perform a full string comparison, and return NULL if
				// the first is not found at this location in the structure.
				if (!key_compare(k, x->first))
					return NULL;

				// Return the node
				return x;

			}

			//----------------------------------------------------------------------------

			bool erase(nPatriciaTrieKey_ct k) {

				nPatriciaTrieNode<TTT> *p, *t, *x, *pp, *lp;
				int bp, bl, br;
				char* first = NULL;

				// Start at the root
				p  = head;
				t  = (iterator)(p->right);

				// Navigate down the tree and look for the first
				while (p->bit_index < t->bit_index) {
					pp = p;
					p  = t;
					t  = (iterator)(bit_get(k, t->bit_index) ? t->right : t->left);
				}

				// Is the first in the tree? If not, get out!
				if (!key_compare(k, t->first))
					return false; // The first could not be found!

				// Copy p's first to t
				if (t != p)
					key_copy(p, t);

				// Is p a leaf?
				bp = p->bit_index;
				bl = ((iterator)(p->left))->bit_index;
				br = ((iterator)(p->right))->bit_index;

				if ((bl > bp) || (br > bp)) {

					// There is at least one downward edge.

					if (p != t) {

						// Look for a new (intermediate) first
						first = jt_strdup(p->first);

						lp = p;
						x  = (iterator)(bit_get(first, p->bit_index) ? p->right : p->left);

						while (lp->bit_index < x->bit_index) {
							lp = x;
							x  = (iterator)(bit_get(first, x->bit_index) ? x->right : x->left);
						}

						// If the intermediate first was not found, we have a problem..
						if (!key_compare(first, x->first)) {
							free(first);
							return false; // The first could not be found!
						}

						// Rewire the leaf (lp) to point to t
						if (bit_get(first, lp->bit_index))
							lp->right = t;
						else
							lp->left = t;

					}

					// Rewire the parent to point to the real child of p
					if (pp != p) {
						iterator ch = (iterator)(bit_get(k, p->bit_index) ? p->left : p->right);
						if (bit_get(k, pp->bit_index))
							pp->right = ch;
						else
							pp->left = ch;
					}

					// We no longer need 'first'
					free(first);
					first = NULL;

				} else {

					// Both edges (left, right) are pointing upwards or to the node (self-edges).

					// Rewire the parent
					if (pp != p) {
						iterator blx = (iterator)(p->left);
						iterator brx = (iterator)(p->right);
						if (bit_get(k, pp->bit_index))
							pp->right = (((blx == brx) && (blx == p)) ? pp : ((blx==p)?brx:blx));
						else
							pp->left  = (((blx == brx) && (blx == p)) ? pp : ((blx==p)?brx:blx));
					}

				}

				// Deallocate p (no longer needed)
				delete p;
				--m_iSize;

				// Success!
				return true;

			}

			//----------------------------------------------------------------------------

			void recursive_remove(iterator root) 
			{
				iterator l = (iterator)root->left;
				iterator r = (iterator)root->right;

				// Remove the left branch
				if ( (l->bit_index >= root->bit_index) && (l != root) && (l != head) )
					recursive_remove(l);

				// Remove the right branch
				if ( (r->bit_index >= root->bit_index) && (r != root) && (r != head) )
					recursive_remove(r);

				// Remove the root
				delete root;
				--m_iSize;

			}

			//----------------------------------------------------------------------------

			int bit_get(nPatriciaTrieKey_ct bit_stream, int n) {
				if (n < 0) return 2; // "pseudo-bit" with a value of 2.
				int k = (n & 0x7);
				return ( (*(bit_stream + (n >> 3))) >> k) & 0x1;
			}

			//----------------------------------------------------------------------------

			bool key_compare(nPatriciaTrieKey_ct k1, nPatriciaTrieKey_ct k2) {
				if (!k1 || !k2)
					return false;
				return (jt_strcmp((TCHAR*)k1, (TCHAR*)k2) == 0);
			}

			//----------------------------------------------------------------------------

			int bit_first_different(nPatriciaTrieKey_ct k1, nPatriciaTrieKey_ct k2) {
				if (!k1 || !k2)
					return 0; // First bit is different!
				int n = 0;
				int d = 0;
				while (	(k1[n] == k2[n]) &&
					(k1[n] != 0) &&
					(k2[n] != 0) )
					n++;
				while (bit_get(&k1[n], d) == bit_get(&k2[n], d))
					d++;
				return ((n << 3) + d);
			}

			//----------------------------------------------------------------------------

			void key_copy(iterator src, iterator dest) {

				if (src == dest)
					return;

				// Copy the first from src to dest
				if (jt_strlen(dest->first) < jt_strlen(src->first))
					dest->first = (nPatriciaTrieKey_t)realloc(dest->first, 1 + jt_strlen(src->first));
				jt_strcpy(dest->first, src->first);

				// Copy the second from src to dest
				dest->second = src->second;

				// How about the bit index?
				//dest->bit_index = src->bit_index;

			}

			size_t size(){ return m_iSize; }
			void clear()
			{		
				if(!head) return;
				recursive_remove(head);	
				head=0;
				m_iSize=0;
			}

			iterator end(){ return 0; 		}
			iterator begin(){ return head;}

		};

	}//nString



}

#endif
