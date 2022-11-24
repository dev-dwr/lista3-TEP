#include <iostream>
#include <vector>
#include <cstdlib>

//zadanie 1
class CNodeStatic {
public:
    void deleteChild(CNodeStatic *node) {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            if (&v_children[i] == node)
                v_children.erase(v_children.begin() + i);
        }
    }

    CNodeStatic() {
        i_val = 0;
        pc_parent_node = NULL;
    };

    ~CNodeStatic() { //zadanie 2
        //  std::cout << "\nUsuwam wezel statyczny: " << i_val << std::endl;
        while (!v_children.empty())
            v_children.pop_back();
    };

    CNodeStatic *getParent() {
        return pc_parent_node;
    }

    void vSetValue(int iNewVal) { i_val = iNewVal; };

    int iGetChildrenNumber() { return (v_children.size()); };

    //zadanie 1
    void vAddNewChild() {
        CNodeStatic node;
        node.pc_parent_node = this;
        v_children.push_back(node);
    };

    //zadanie 1
    CNodeStatic *pcGetChild(int iChildOffset) {
        if (iChildOffset < 0) {
            return NULL;
        } else if (iChildOffset > iGetChildrenNumber()) {
            return NULL;
        }
        return &(v_children.at(iChildOffset));
    }

    void vPrint() { std::cout << " " << i_val; };

    //zadanie 1
    void vPrintAllBelow() {
        for (int i = 0; i < v_children.size(); i++) {
            v_children[i].vPrint();
            v_children[i].vPrintAllBelow();
        }
    }

    //zadanie 3
    void vPrintUp() {
        vPrint();
        if (pc_parent_node != NULL)
            pc_parent_node->vPrintUp();
    }

    //zadanie 4
    void vSetNewChild(CNodeStatic *node) {
        CNodeStatic clone_node(*node);
        clone_node.pc_parent_node = this;
        v_children.push_back(clone_node);
    }


    //zadanie 2
    void v_tree_test1() {
        vAddNewChild();
        vAddNewChild();
        pcGetChild(0)->vSetValue(1);
        pcGetChild(1)->vSetValue(2);
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->pcGetChild(0)->vSetValue(11);
        pcGetChild(0)->pcGetChild(1)->vSetValue(12);
        pcGetChild(1)->vAddNewChild();
        pcGetChild(1)->vAddNewChild();
        pcGetChild(1)->pcGetChild(0)->vSetValue(21);
        pcGetChild(1)->pcGetChild(1)->vSetValue(22);
    }

    void v_tree_test2() {
        vAddNewChild();
        vAddNewChild();
        pcGetChild(0)->vSetValue(8);
        pcGetChild(1)->vSetValue(18);
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->pcGetChild(0)->vSetValue(9);
        pcGetChild(0)->pcGetChild(1)->vSetValue(10);
        pcGetChild(0)->pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(20);


    }

    void v_tree_test_static() {
        CNodeStatic c_root;
        c_root.vAddNewChild();
        c_root.vAddNewChild();
        c_root.pcGetChild(0)->vSetValue(1);
        c_root.pcGetChild(1)->vSetValue(2);
        c_root.pcGetChild(0)->vAddNewChild();
        c_root.pcGetChild(0)->vAddNewChild();
        c_root.pcGetChild(0)->pcGetChild(0)->vSetValue(11);
        c_root.pcGetChild(0)->pcGetChild(1)->vSetValue(12);
        c_root.pcGetChild(1)->vAddNewChild();
        c_root.pcGetChild(1)->vAddNewChild();
        c_root.pcGetChild(1)->pcGetChild(0)->vSetValue(21);
        c_root.pcGetChild(1)->pcGetChild(1)->vSetValue(22);
        c_root.vPrintAllBelow();
        std::cout << std::endl;
    }

private:
    std::vector<CNodeStatic> v_children;
    CNodeStatic *pc_parent_node;
    int i_val;
};

//zadanie 4
class CTreeStatic {
public:
    CTreeStatic() {

    }

    ~CTreeStatic() {
//        std::cout << "Usuwam drzewo statyczne: " << std::endl;
    }

    CNodeStatic *pcGetRoot() { return (&c_root); }

    void vPrintTree() {
        c_root.vPrint();
        c_root.vPrintAllBelow();
    }


    bool bMoveSubtree(CNodeStatic *pcParentNode, CNodeStatic *pcNewChildNode) {
        if (pcParentNode != NULL && pcNewChildNode != NULL) {

            pcParentNode->vSetNewChild(pcNewChildNode);
            pcNewChildNode->getParent()->deleteChild(pcNewChildNode);

            return true;
        } else return false;
    }


private:
    CNodeStatic c_root;
};

class CNodeDynamic {
public:
    CNodeDynamic() {
        i_val = 0;
        pc_parent_node = NULL;
    };

    ~CNodeDynamic() {
        std::cout << "Usuwam dynamiczny wezel: " << i_val << std::endl;
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            delete v_children[i];
        }
    }

    void vSetValue(int iNewVal) { i_val = iNewVal; };

    int getValue() {
        return i_val;
    }

    int iGetChildrenNumber() { return (v_children.size()); };

    void vAddNewChild() {
        CNodeDynamic *el;
        el = new CNodeDynamic;
        el->pc_parent_node = this;
        v_children.push_back(el);
    }

    void vAddNewChild(CNodeDynamic *pcOtherNode) {
        pcOtherNode->pc_parent_node = this;
        v_children.push_back(pcOtherNode);
    }

    CNodeDynamic *pcGetChild(int iChildOffset) {
        if (iChildOffset < 0) {
            return NULL;
        } else if (iChildOffset > iGetChildrenNumber()) {
            return NULL;
        }
        return v_children[iChildOffset];
    }

    void vPrint() { std::cout << " " << i_val; };

    void vPrintAllBelow() {
        for (int i = 0; i < v_children.size(); i++) {
            v_children[i]->vPrint();
            v_children[i]->vPrintAllBelow();
        }
    }

    void deleteChild(CNodeDynamic *node) {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            if (v_children[i] == node)
                v_children.erase(v_children.begin() + i);
        }

    }

    CNodeDynamic *getParent() {
        return pc_parent_node;
    }

    void vPrintUp() {
        vPrint();
        if (pc_parent_node != NULL)
            pc_parent_node->vPrintUp();
    }

    void v_tree_test1() {
        vAddNewChild();
        vAddNewChild();
        pcGetChild(0)->vSetValue(1);
        pcGetChild(1)->vSetValue(2);
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->pcGetChild(0)->vSetValue(11);
        pcGetChild(0)->pcGetChild(1)->vSetValue(12);
        pcGetChild(1)->vAddNewChild();
        pcGetChild(1)->vAddNewChild();
        pcGetChild(1)->pcGetChild(0)->vSetValue(21);
        pcGetChild(1)->pcGetChild(1)->vSetValue(22);
    }

    void v_tree_test2() {

        vAddNewChild();
        vAddNewChild();
        pcGetChild(0)->vSetValue(8);
        pcGetChild(1)->vSetValue(18);
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->pcGetChild(0)->vSetValue(9);
        pcGetChild(0)->pcGetChild(1)->vSetValue(10);
        pcGetChild(0)->pcGetChild(0)->vAddNewChild();
        pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(20);
    }

    void vSetNewChild(CNodeDynamic *node) {
        node->pc_parent_node = this;
        v_children.push_back(node);
    }

private:
    std::vector<CNodeDynamic *> v_children;
    CNodeDynamic *pc_parent_node;
    int i_val;
};

class CTreeDynamic {
public:
    CTreeDynamic() {
        pc_root = new CNodeDynamic();
    }

    ~CTreeDynamic() {
        std::cout << "Usuwam drzewo dynamiczne" << std::endl;
        delete pc_root;
    }

    CNodeDynamic *pcGetRoot() { return (pc_root); }

    bool bMoveSubtree(CNodeDynamic *pcParentNode, CNodeDynamic *pcNewChildNode) {
        if (pcParentNode != NULL && pcNewChildNode != NULL) {
            pcNewChildNode->getParent()->deleteChild(pcNewChildNode);
            pcParentNode->vSetNewChild(pcNewChildNode);
            return true;
        } else return false;
    }

    void vPrintTree() {
        pc_root->vPrint();
        pc_root->vPrintAllBelow();
    }


private:
    CNodeDynamic *pc_root;
};


int main() {

    CNodeStatic root;
    root.v_tree_test1();
    std::cout << "\nTASK2" << std::endl;
    std::cout << "Print all below" << std::endl;
    root.vPrintAllBelow();
    std::cout << "\n" << std::endl;

    std::cout << "\nTASK3" << std::endl;
    std::cout << "Print up: " << std::endl;
    root.pcGetChild(0)->pcGetChild(1)->vPrintUp();

    std::cout << "\n" << std::endl;
    CTreeStatic tree;
    CTreeStatic tree2;
    tree.pcGetRoot()->v_tree_test1();
    tree2.pcGetRoot()->v_tree_test2();
    std::cout << "\nStatyczne drzewa przed polaczeniem: " << std::endl;
    tree.vPrintTree();
    std::cout << std::endl;
    tree2.vPrintTree();
    std::cout << std::endl;
    tree.bMoveSubtree(tree.pcGetRoot()->pcGetChild(0), tree2.pcGetRoot()->pcGetChild(0));
    std::cout << std::endl;
    std::cout << "Statyczne drzewa po polaczeniu: " << std::endl;
    tree.vPrintTree();
    std::cout << std::endl;
    tree2.vPrintTree();
    std::cout << std::endl;


    std::cout << "CNodeDynamic printAllBelow " << std::endl;
    CNodeDynamic *root3;
    root3 = new CNodeDynamic();
    root3->v_tree_test1();
    root3->vPrintAllBelow();

    std::cout << "\n" << std::endl;
    CTreeDynamic tree3;
    CTreeDynamic tree4;
    std::cout << "Dynamiczne drzewa przed polaczeniem: " << std::endl;
    tree3.pcGetRoot()->v_tree_test1();
    tree4.pcGetRoot()->v_tree_test2();
    tree3.vPrintTree();
    std::cout << std::endl;
    tree4.vPrintTree();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Dynamiczne drzewa po polaczeniu: " << std::endl;
    tree3.bMoveSubtree(tree3.pcGetRoot()->pcGetChild(0), tree4.pcGetRoot()->pcGetChild(0));
    std::cout << "PrintUp " << std::endl;
//    dla dowolnego węzła wypisze wartości wszystkich jego rodziców, od wybranego węzła aż do korzenia
    tree3.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->pcGetChild(0)->vPrintUp();
    std::cout << std::endl;
    tree3.vPrintTree();
    std::cout << std::endl;
    tree4.vPrintTree();
    std::cout << std::endl;

    return 0;
}
