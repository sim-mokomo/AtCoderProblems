#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Node{
    int id;
    std::vector<int> relation;
};

struct Edge{
    int begin;
    int end;

    Edge(int begin, int end)
    : begin(begin)
    , end(end){

    }
};

int main(){
    int memberNum;
    int relationNum;

    std::cin >> memberNum >> relationNum;

    std::vector<Edge> edgeList;
    for(int i = 0; i < relationNum; i++){
        int begin,end;
        std::cin >> begin >> end;
        edgeList.push_back(Edge(begin, end));
    }

    // note: ノードごとの関係性をメモ
    std::vector<Node> nodeList;
    for(int i = 0; i < memberNum; i++){
        Node node;
        node.id = i;
        for (const auto edge: edgeList) {
            if(edge.begin == i){
                node.relation.push_back(edge.end);
            }

            if(edge.end == i){
                node.relation.push_back(edge.begin);
            }
        }
        nodeList.push_back(node);
    }

    int maxMemberNum = 0;
    for(int i = 0; i < std::pow(2, memberNum); i++){
        // note: bit化
        std::vector<int> bitArray;
        for(int j = 0; j < memberNum; j++){
            const int bit = (i >> j) & 1;
            bitArray.push_back(bit);
        }

        // note: ノードの組み合わせをvector化
        std::vector<int> nodeIdList;
        for(int j = 0; j < memberNum; j++){
            if(bitArray[j] > 0){
                nodeIdList.push_back(j + 1);
            }
        }

        // note: 各ノード、面識があるかどうかを確認
        bool allRelation = true;
        for (const int nodeId: nodeIdList) {
            const auto& node = std::find_if(
                    nodeList.cbegin(),
                    nodeList.cend(),
                    [nodeId](const Node& node){
                        return  node.id == nodeId;
                    });
            if(node == nodeList.cend()){
                continue;
            }

            for(const int otherNodeId: nodeIdList) {
                if (otherNodeId == nodeId) {
                    continue;
                }
                bool isRelation = std::any_of(
                        node->relation.cbegin(),
                        node->relation.cend(),
                        [otherNodeId](int nodeId) {
                            return otherNodeId == nodeId;
                        });
                if (!isRelation) {
                    allRelation = false;
                }
            }
        }

        if(allRelation){
            maxMemberNum = std::max(maxMemberNum, (int)nodeIdList.size());
        }
    }

    std::cout << maxMemberNum << std::endl;
    return 0;
}