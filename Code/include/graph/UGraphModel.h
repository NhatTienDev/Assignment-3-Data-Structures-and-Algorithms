/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
// #include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this -> getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *toNode = this -> getVertexNode(to);

        if(!fromNode) throw VertexNotFoundException(this -> vertex2str(from));
        if(!toNode) throw VertexNotFoundException(this -> vertex2str(to));

        if(fromNode == toNode)
        {
            fromNode -> connect(toNode, weight);
        }
        else
        {
            fromNode -> connect(toNode, weight);
            toNode -> connect(fromNode, weight);
        }
    }

    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this -> getVertexNode(from);
        typename AbstractGraph<T>::VertexNode *toNode = this -> getVertexNode(to);

        if(!fromNode) throw VertexNotFoundException(this -> vertex2str(from));
        if(!toNode) throw VertexNotFoundException(this -> vertex2str(to));

        if(fromNode -> getEdge(toNode) == nullptr)
        {
            typename AbstractGraph<T>::Edge dummyEdge(fromNode, toNode);
            throw EdgeNotFoundException(this -> edge2Str(dummyEdge));
        }

        if(fromNode == toNode) fromNode -> removeTo(toNode);
        else
        {
            fromNode -> removeTo(toNode);
            toNode -> removeTo(fromNode);
        }
    }

    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *removedNode = this -> getVertexNode(vertex);

        if(removedNode == nullptr) throw VertexNotFoundException(this -> vertex2str(vertex));

        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this -> nodeList.begin();

        while(it != this -> nodeList.end())
        {
            typename AbstractGraph<T>::VertexNode *currentNode = *it;

            if(removedNode -> equals(currentNode) == false)
            {
                removedNode -> removeTo(currentNode);
                currentNode -> removeTo(removedNode);
            }
            else removedNode -> removeTo(currentNode);

            it++;
        }

        this -> nodeList.removeItem(removedNode);

        // if(this -> nodeList.removeItem(removedNode) == false)
        // {
        //     throw std::runtime_error("Failed to remove vertex from nodeList");
        // }

        delete removedNode;
    }

    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T> *graph = new UGraphModel<T>(vertexEQ, vertex2str);

        for(int i = 0; i < nvertices; i++)
        {
            graph -> add(vertices[i]);
        }

        for(int i = 0; i < nedges; i++)
        {
            graph -> connect(edges[i].from, edges[i].to, edges[i].weight);
        }

        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
