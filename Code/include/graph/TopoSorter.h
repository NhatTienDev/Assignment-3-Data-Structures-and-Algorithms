/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int) = 0)
    {
        //TODO
        this -> graph = graph;
        this -> hash_code = hash_code;
    }

    DLinkedList<T> sort(int mode = 0, bool sorted = true)
    {
        //TODO
        if(mode == BFS)
        {
            return bfsSort(sorted);
        }
        else
        {
            return dfsSort(sorted);
        }
    }

    DLinkedList<T> bfsSort(bool sorted = true)
    {
        //TODO
        DLinkedList<T> result;
        xMap<T, int> inDegreeMap = vertex2inDegree(hash_code);
        DLinkedList<T> zeroInDegreeList = listOfZeroInDegrees();

        if(sorted)
        {
            DLinkedListSE<T> sortedZeroInDegreeList(zeroInDegreeList);
            sortedZeroInDegreeList.sort();
            zeroInDegreeList = sortedZeroInDegreeList;
        }

        Queue<T> queue;

        for(typename DLinkedList<T>::Iterator it = zeroInDegreeList.begin(); it != zeroInDegreeList.end(); it++)
        {
            queue.push(*it);
        }

        while(!queue.empty())
        {
            T current = queue.pop();
            result.add(current);
            DLinkedList<T> outwardEdges = graph -> getOutwardEdges(current);

            for(typename DLinkedList<T>::Iterator it = outwardEdges.begin(); it != outwardEdges.end(); it++)
            {
                T neighbor = *it;
                int newInDegree = inDegreeMap.get(neighbor) - 1;
                inDegreeMap.put(neighbor, newInDegree);

                if(newInDegree == 0)
                {
                    queue.push(neighbor);
                }
            }
        }

        return result;
    }

    DLinkedList<T> dfsSort(bool sorted = true)
    {
        //TODO
        DLinkedList<T> solution;
        xMap<T, bool> visited(hash_code);
        Stack<T> dfs;
        DLinkedListSE<T> sortingList(graph -> vertices());

        if(sorted) sortingList.sort();

        typename DLinkedListSE<T>::Iterator it = sortingList.begin();

        while(it != sortingList.end())
        {
            visited.put((*it), false);
            it++;
        }

        it = sortingList.begin();

        while(it != sortingList.end())
        {
            T vertex = *it;

            if(!visited.get(vertex))
            {
                dfs.push(vertex);
                visited.put(vertex, true);
            }

            while(!dfs.empty())
            {
                T current = dfs.peek();
                DLinkedListSE<T> neighbors = graph -> getOutwardEdges(current);
                bool checked = false;
                typename DLinkedListSE<T>::Iterator iterator = neighbors.begin();

                while(iterator != neighbors.end())
                {
                    T neighbor = *iterator;

                    if(visited.get(neighbor) == false)
                    {
                        dfs.push(neighbor);
                        visited.put(neighbor, true);
                        checked = true;
                        break;
                    }

                    iterator++;
                }

                if(!checked)
                {
                    solution.add(0, dfs.pop());
                }
            }
            it++;
        }
        
        return solution;
    }
    
protected:
    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int))
    {
        xMap<T, int> inDegreeMap(hash);
        DLinkedList<T> vertices = graph -> vertices();

        for(typename DLinkedList<T>::Iterator it = vertices.begin(); it != vertices.end(); it++)
        {
            T vertex = *it;
            int inDegree = graph -> inDegree(vertex);
            inDegreeMap.put(vertex, inDegree);
        }

        return inDegreeMap;
    }

    xMap<T, int> vertex2outDegree(int (*hash)(T&, int))
    {
        xMap<T, int> outDegreeMap(hash);
        DLinkedList<T> vertices = graph -> vertices();

        for(typename DLinkedList<T>::Iterator it = vertices.begin(); it != vertices.end(); it++)
        {
            T vertex = *it;
            int outDegree = graph -> outDegree(vertex);
            outDegreeMap.put(vertex, outDegree);
        }   
        
        return outDegreeMap;
    }

    DLinkedList<T> listOfZeroInDegrees()
    {
        DLinkedList<T> zeroInDegreeList;
        DLinkedList<T> vertices = graph -> vertices();

        for(typename DLinkedList<T>::Iterator it = vertices.begin(); it != vertices.end(); it++)
        {
            T vertex = *it;
            if(graph -> inDegree(vertex) == 0)
            {
                zeroInDegreeList.add(vertex);
            }
        }

        return zeroInDegreeList;
    }

}; //TopoSorter

template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

