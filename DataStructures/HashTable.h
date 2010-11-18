/*
    open source routing machine
    Copyright (C) Dennis Luxen, others 2010

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU AFFERO General Public License as published by
the Free Software Foundation; either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
or see http://www.gnu.org/licenses/agpl.txt.

  Created on: 18.11.2010
  Author: dennis
*/

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <google/sparse_hash_map>

template<typename keyT, typename valueT>
class HashTable {
	typedef google::sparse_hash_map<keyT, valueT> MyHashTable;
public:
	HashTable() { }
	HashTable(const unsigned size) {
		table.resize(size);
	}
	void Add(const keyT& key, const valueT& value){
		table[key] = value;
	}
	valueT Find(const keyT& key) {
		return table.find(key)->second;
	}
private:
	MyHashTable table;
};

#endif /* HASHTABLE_H_ */