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

//g++ createHierarchy.cpp -fopenmp -Wno-deprecated -o createHierarchy -O3 -march=native -DNDEBUG

#define VERBOSE(x) x
#define VERBOSE2(x)

#ifdef NDEBUG
#undef VERBOSE
#undef VERBOSE2
#endif

#include <climits>
#include <fstream>
#include <istream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "typedefs.h"
#include "Contractor/Contractor.h"
#include "Contractor/ContractionCleanup.h"
#include "DataStructures/BinaryHeap.h"
#include "DataStructures/LevelInformation.h"
#include "DataStructures/NNGrid.h"
#include "Util/BaseConfiguration.h"
#include "Util/InputFileUtil.h"
#include "Util/GraphLoader.h"

using namespace std;

typedef DynamicGraph<EdgeData>::InputEdge InputEdge;
typedef StaticGraph<EdgeData>::InputEdge StaticEdge;
typedef BaseConfiguration ContractorConfiguration;

vector<NodeInfo> * int2ExtNodeMap = new vector<NodeInfo>();

int main (int argc, char *argv[]) {
    if(argc <= 1) {
        cerr << "usage: " << endl << argv[0] << " <osrm-data>" << endl;
        exit(-1);
    }

    unsigned numberOfThreads = omp_get_num_procs();
    if(testDataFile("contractor.ini")) {
        ContractorConfiguration contractorConfig("contractor.ini");
        if(atoi(contractorConfig.GetParameter("Threads").c_str()) != 0 && (unsigned)atoi(contractorConfig.GetParameter("Threads").c_str()) <= numberOfThreads)
            numberOfThreads = (unsigned)atoi( contractorConfig.GetParameter("Threads").c_str() );
    }
    omp_set_num_threads(numberOfThreads);

    cout << "preprocessing data from input file " << argv[1];
#ifdef _GLIBCXX_PARALLEL
    cout << " using STL parallel mode" << std::endl;
#else
    cout << " using STL serial mode" << std::endl;
#endif

    ifstream in;
    in.open (argv[1]);
    if (!in.is_open()) {
        cerr << "Cannot open " << argv[1] << endl; exit(-1);
    }
    vector<ImportEdge> edgeList;
    const NodeID n = readBinaryOSRMGraphFromStream(in, edgeList, int2ExtNodeMap);
    in.close();

    char nodeOut[1024];
    char edgeOut[1024];
    char ramIndexOut[1024];
    char fileIndexOut[1024];
    char levelInfoOut[1024];
    strcpy(nodeOut, argv[1]);
    strcpy(edgeOut, argv[1]);
    strcpy(ramIndexOut, argv[1]);
    strcpy(fileIndexOut, argv[1]);
    strcpy(levelInfoOut, argv[1]);

    strcat(nodeOut, ".nodes");
    strcat(edgeOut, ".hsgr");
    strcat(ramIndexOut, ".ramIndex");
    strcat(fileIndexOut, ".fileIndex");
    strcat(levelInfoOut, ".levels");

    cout << "initializing contractor ..." << flush;
    Contractor* contractor = new Contractor( n, edgeList );
    contractor->Run();

    LevelInformation * levelInfo = contractor->GetLevelInformation();
    std::cout << "sorting level info" << std::endl;
    for(unsigned currentLevel = levelInfo->GetNumberOfLevels(); currentLevel>0; currentLevel--) {
        std::vector<unsigned> & level = levelInfo->GetLevel(currentLevel-1);
        std::sort(level.begin(), level.end());
    }

    std::cout << "writing level info" << std::endl;
    ofstream levelOutFile(levelInfoOut, ios::binary);
    unsigned numberOfLevels = levelInfo->GetNumberOfLevels();
    levelOutFile.write((char *)&numberOfLevels, sizeof(unsigned));
    for(unsigned currentLevel = 0; currentLevel < levelInfo->GetNumberOfLevels(); currentLevel++ ) {
        std::vector<unsigned> & level = levelInfo->GetLevel(currentLevel);
        unsigned sizeOfLevel = level.size();
        levelOutFile.write((char *)&sizeOfLevel, sizeof(unsigned));
        for(unsigned currentLevelEntry = 0; currentLevelEntry < sizeOfLevel; currentLevelEntry++) {
            unsigned node = level[currentLevelEntry];
            levelOutFile.write((char *)&node, sizeof(unsigned));
            assert(node < n);
        }
    }
    levelOutFile.close();
    std::vector< ContractionCleanup::Edge > contractedEdges;
    contractor->GetEdges( contractedEdges );
    delete contractor;

    ContractionCleanup * cleanup = new ContractionCleanup(n, contractedEdges);
    contractedEdges.clear();
    cleanup->Run();

    std::vector< InputEdge> cleanedEdgeList;
    cleanup->GetData(cleanedEdgeList);
    delete cleanup;

    cout << "Serializing edges " << flush;
    ofstream edgeOutFile(edgeOut, ios::binary);
    Percent p(cleanedEdgeList.size());
    for(std::vector< InputEdge>::iterator it = cleanedEdgeList.begin(); it != cleanedEdgeList.end(); it++) {
        p.printIncrement();
        int distance= it->data.distance;
        assert(distance > 0);
        bool shortcut= it->data.shortcut;
        bool forward= it->data.forward;
        bool backward= it->data.backward;
        NodeID middle;
        if(shortcut)
            middle = it->data.middleName.middle;
        else {
            middle = it->data.middleName.nameID;
        }

        NodeID source = it->source;
        NodeID target = it->target;
        short type = it->data.type;

        edgeOutFile.write((char *)&(distance), sizeof(int));
        edgeOutFile.write((char *)&(shortcut), sizeof(bool));
        edgeOutFile.write((char *)&(forward), sizeof(bool));
        edgeOutFile.write((char *)&(backward), sizeof(bool));
        edgeOutFile.write((char *)&(middle), sizeof(NodeID));
        edgeOutFile.write((char *)&(type), sizeof(short));
        edgeOutFile.write((char *)&(source), sizeof(NodeID));
        edgeOutFile.write((char *)&(target), sizeof(NodeID));
    }
    edgeOutFile.close();
    cleanedEdgeList.clear();

    std::cout << "writing node map ..." << std::flush;
    ofstream mapOutFile(nodeOut, ios::binary);

    for(NodeID i = 0; i < int2ExtNodeMap->size(); i++) {
        mapOutFile.write((char *)&(int2ExtNodeMap->at(i)), sizeof(NodeInfo));
    }
    mapOutFile.close();
    std::cout << "ok" << std::endl;

    WritableGrid * writeableGrid = new WritableGrid();
    cout << "building grid ..." << flush;
    writeableGrid->ConstructGrid(edgeList, int2ExtNodeMap, ramIndexOut, fileIndexOut);
    delete writeableGrid;

    int2ExtNodeMap->clear();
    delete int2ExtNodeMap;

    cout << "finished" << endl;
    return 0;
}
