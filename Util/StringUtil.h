/*
    open source routing machine
    Copyright (C) Dennis Luxen, 2010

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
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

// precision:  position after decimal point
// length: maximum number of digits including comma and decimals
template< int length, int precision >
inline char* printInt( char* buffer, int value )
{
    bool minus = false;
    if ( value < 0 ) {
        minus = true;
        value = -value;
    }
    buffer += length - 1;
    for ( int i = 0; i < precision; i++ ) {
        *buffer = '0' + ( value % 10 );
        value /= 10;
        buffer--;
    }
    *buffer = '.';
    buffer--;
    for ( int i = precision + 1; i < length; i++ ) {
        *buffer = '0' + ( value % 10 );
        value /= 10;
        if ( value == 0 ) break;
        buffer--;
    }
    if ( minus ) {
        buffer--;
        *buffer = '-';
    }
    return buffer;
}

inline void intToString(const int value, std::string & output) {
    // The largest 32-bit integer is 4294967295, that is 10 chars
    // On the safe side, add 1 for sign, and 1 for trailing zero
    char buffer[12] ;
    sprintf(buffer, "%i", value) ;
    output = buffer ;
}

inline void convertInternalLatLonToString(const int value, std::string & output)
{
    char buffer[100];
    buffer[10] = 0; // Nullterminierung
    char* string = printInt< 10, 5 >( buffer, value );
    output = string;
}

inline void convertInternalCoordinateToString(const _Coordinate & coord, std::string & output) {
    std::string tmp;
    convertInternalLatLonToString(coord.lon, tmp);
    output = tmp;
    output += ",";
    convertInternalLatLonToString(coord.lat, tmp);
    output += tmp;
    output += " ";
}
inline void convertInternalReversedCoordinateToString(const _Coordinate & coord, std::string & output) {
    std::string tmp;
    convertInternalLatLonToString(coord.lat, tmp);
    output = tmp;
    output += ",";
    convertInternalLatLonToString(coord.lon, tmp);
    output += tmp;
    output += " ";
}

inline void doubleToString(const double value, std::string & output){
    // The largest 32-bit integer is 4294967295, that is 10 chars
    // On the safe side, add 1 for sign, and 1 for trailing zero
    char buffer[12] ;
    sprintf(buffer, "%f", value) ;
    output = buffer ;
}

inline std::string & replaceAll(std::string &s, const std::string &sub, const std::string &other) {
    assert(!sub.empty());
    size_t b = 0;
    for (;;) {
        b = s.find(sub, b);
        if (b == s.npos) break;
        s.replace(b, sub.size(), other);
        b += other.size();
    }
    return s;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        if(item.size() > 0)
            elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}


std::string originals[] = {"&", "\"",  "<",  ">", "'", "[", "]", "\\"};
std::string entities[] = {"&amp;", "&quot;", "&lt;", "&gt;", "&#39;", "&91;", "&93;", " &#92;" };

std::string HTMLEntitize( std::string result) {
    for(unsigned i = 0; i < sizeof(originals)/sizeof(std::string); i++) {
        result = replaceAll(result, originals[i], entities[i]);
    }
    return result;
}

std::string HTMLDeEntitize( std::string result) {
    for(unsigned i = 0; i < sizeof(originals)/sizeof(std::string); i++) {
        result = replaceAll(result, entities[i], originals[i]);
    }
    return result;
}

bool StringStartsWith(string & input, string & prefix) {
    return (input.find(prefix) == 0);
}
#endif /* STRINGUTIL_H_ */
