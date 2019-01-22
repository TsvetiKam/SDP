#include "stdafx.h"
#include <iostream>
#include "BinTree.h"
#include "Graph.h"
#include "GraphElement.h"

using namespace std;

//some additional functions


template<typename T>
void deleteLast(LList<T>& lst) {
	if (lst.isEmpty()) return;
	lst.iterStart();
	Node<T>* p = lst.iterNext();
	while (p->next) {
		p = lst.iterNext();
	}
	T x;
	lst.deleteElem(p, x);
}
template<typename T>
void deleteFirst(LList<T>& lst) {
	if (lst.isEmpty()) return;
	lst.iterStart();
	Node<T>* p = lst.iterNext();
	T x;
	lst.deleteElem(p,x);
}

template<typename T>
bool member(LList<T>& lst, T& x) {
	lst.iterStart();
	Node<T>* p = lst.iterNext();
	while (p) {
		if (p->data == x) return true;
		p = lst.iterNext();
	}
	return false;
}

void print(LList< LList<char> > lst) {
	if (lst.isEmpty()) return;
	lst.iterStart();
	Node< LList<char> >* p = lst.iterNext();
	while (p) {
		p->data.print();
		std::cout << std::endl;
		p = p->next;
	}
}

BinTree<char> getTree() {
	BinTree<char> empty;
	BinTree<char> a, b, c, d, e, f, g, h, n;
	//leaves
	n.createWithData('n', empty, empty);
	h.createWithData('h', empty, empty);
	c.createWithData('c', empty, empty);
	g.createWithData('g', empty, empty);
	//other
	f.createWithData('f', n, empty);
	d.createWithData('d', h, empty);
	b.createWithData('b', c, f);
	e.createWithData('e', d, g);
	//root
	a.createWithData('a', b, e);

	return a;
}

Graph<GraphElement<char> > getGraph() {
	Graph<GraphElement<char> > graph;
	GraphElement<char> i('i');
	GraphElement<char> a1('a');
	GraphElement<char> b('b');
	GraphElement<char> e('e');
	GraphElement<char> n('n');
	GraphElement<char> a2('a');
	GraphElement<char> f('f');
	GraphElement<char> c('c');
	GraphElement<char> g('g');
	graph.addVertex(i);
	graph.addVertex(a1);
	graph.addVertex(b);
	graph.addVertex(e);
	graph.addVertex(n);
	graph.addVertex(a2);
	graph.addVertex(f);
	graph.addVertex(c);
	graph.addVertex(g);
	graph.addEdge(i, a1);
	graph.addEdge(a1, b);
	graph.addEdge(n, a2);
	graph.addEdge(a2, e);
	graph.addEdge(e, b);
	graph.addEdge(b, f);
	graph.addEdge(b, c);
	graph.addEdge(e, g);
	graph.addEdge(f, g);

	return graph;
}

/*Plan:
1.Function that finds all paths in a tree from the root to all leaves and puts them into a list of lists of characters
2.Function that checks if a path from a list of characters exists in a graph
3.Function that prints all possible paths
*/


//step 1
void findAllPathsInTree(BinTree<char> tree, LList< LList<char> > &paths, LList<char> currentPath) {

	//case: empty tree 
	if (tree.isEmpty()) {
		return;
	}
	//case: we found a leave aka. a path
	if (tree.getLeftTree().isEmpty() && tree.getRightTree().isEmpty()) {
		//insert the last elem
		currentPath.insertToEnd(tree.getRootData());
		//put the finnished list in the collection
		paths.insertToEnd(currentPath);
		return;
	}
	//case: we havent found a path yet
	currentPath.insertToEnd(tree.getRootData());
	findAllPathsInTree(tree.getLeftTree(), paths, currentPath);
	findAllPathsInTree(tree.getRightTree(), paths, currentPath);
}

//step 2 Function that checks if a path from a list of characters exists in a graph

bool same(LList<char> lst, LList<GraphElement<char>> glst) {
	if (lst.isEmpty() && glst.isEmpty()) {
		return true;
	}
	if (glst.isEmpty() || lst.isEmpty()) {
		return false;
	}
	lst.iterStart();
	glst.iterStart();
	Node <char>* l = lst.iterNext();
	Node <GraphElement<char>>* g = glst.iterNext();
	while (l && g) {
		if (l->data == g->data.getData()) {
			l = lst.iterNext();
			g = glst.iterNext();
		}
		else {
			return false;
		}
	}
	return l == NULL && g == NULL;
}


bool hasWay(Graph<GraphElement<char> > graph, LList<char> potential, Node<char>* curr, GraphElement<char> start, LList<GraphElement<char>> &actual) {
	if (graph.isEmpty()) {
		return false;
	}
	if (same(potential, actual)) {
		return true;
	}
	actual.insertToEnd(start);
	cout << start << endl;
	Node<GraphElement<char> >* elem = graph.getVertexPointer(start);
	elem = elem->next;

	while (elem) {
		if (!member(actual, elem->data)) {
			if (hasWay(graph, potential, curr->next, elem->data, actual)) {
				return true;
			}
		}
		elem = elem->next;
	}
	deleteLast(actual);
	return false;
	
}

void getAllPathsInGraph(Graph<GraphElement<char>> graph, GraphElement<char> start, LList<GraphElement<char>> path, LList<char> potential) {
	path.insertToEnd(start);

	if (same(potential, path)) {
		potential.print();
	}

	Node<GraphElement<char>>* p = graph.getVertexPointer(start);
	p = p->next;
	while (p) {
		if (!member(path, p->data)) {
			getAllPathsInGraph(graph, p->data, path, potential);
		}
		p = p->next;
	}
}



int main() {
	BinTree<char> test = getTree();
	test.print();
	cout << endl;
	LList < LList<char> > paths;
	LList<char> lst;
	findAllPathsInTree(test, paths, lst);
	print(paths);
	cout << endl;

	Graph<GraphElement<char> > graph = getGraph();

	paths.iterStart();
	Node<LList<char> >* p = paths.iterNext();

	p->data.iterStart();
	Node<char>* curr = p->data.iterNext();

	LList<GraphElement<char> > elements = graph.getVertices();
	elements.iterStart();
	Node<GraphElement<char> >* elem = elements.iterNext();
	elem = elements.iterNext();

	LList<GraphElement<char>> actualPath;

	graph.print();

	//cout << hasWay(graph, p->data, curr, elem->data, actualPath);


//	LList<char> l;
//	GraphElement<char> c('c');
//	LList<GraphElement<char> > g;
//	l.insertToEnd('c');
//	g.insertToEnd(c);
//	cout << same(l, g);
//	Graph<GraphElement<char> > graph = getGraph();
//	graph.print();


    return 0;
}

