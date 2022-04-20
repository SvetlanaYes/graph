#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>

struct graph_element {
    int src, dest;
};

class Graph
{
private:
    std::vector<std::list<int>> arr;
    size_t capacity = 0;
    size_t size = 0;
    std::vector<bool> deleted_nodes;
public:
    Graph(){}
    ~Graph(){}
    Graph(int count_of_nodes,std::vector<graph_element> edges)
    {
        capacity = count_of_nodes;
        size = count_of_nodes;
        deleted_nodes.resize(size, true);
        arr.resize(capacity);
        for (int i = 0; i < edges.size(); ++i)
        {
            arr[edges[i].src - 1].push_back(edges[i].dest);
        }

    }
    void add_node()
    {
        ++size;
        ++capacity;
        arr.resize(capacity);
        deleted_nodes.resize(capacity, true);

    }
    void add_edge(graph_element el)
    {
        if (el.src > arr.size() || el.dest > arr.size())
            return;
        arr[el.src - 1].push_back(el.dest);
    }
    void add_edges(std::vector<graph_element> el)
    {
        for (size_t i = 0; i < el.size(); ++i)
            add_edge(el[i]);
    }

    
    void delete_node(int el)
    {
        if (el >= arr.size())
        {
            return;
        }
        for (size_t i = 0; i < arr.size(); ++i)
        {
            arr[i].remove(el);
        }
        
        deleted_nodes[el - 1] = false;

        std::cout << std::endl;
        --size;
    }

    void print()
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            if (deleted_nodes[i] == 0)
                continue;
            std::cout << i + 1 << " -->";
            for (auto j = arr[i].begin(); j != arr[i].end(); ++j)
                std::cout << *j << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void print_bfs()
    {
        if (arr.size() == 0)
            return;
        std::vector<bool> visited(arr.size(), true);
        std::queue<int> q;
        for (size_t i = 0; i < deleted_nodes.size(); ++i)
        {
            if (deleted_nodes[i] == 1)
            {
                q.push(i + 1);
                break;
            }
        }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            visited[u - 1] = false;
            
            std::cout << u << " ";
            for (auto i = arr[u - 1].begin(); i != arr[u - 1].end(); ++i)
            {
                if (visited[*i - 1] == 1 && deleted_nodes[*i - 1] == 1)
                {
                    q.push(*i);
                }
            }
            //checking if we have disconnected graph
            if (q.empty()) {
                for (size_t i = 0; i < visited.size(); ++i)
                {
                    if (visited[i] == 1 && deleted_nodes[i] == 1)
                    {
                        q.push(i + 1);
                        break;
                    }
                }
            }
        }
        std::cout << std::endl;
    }
};

int main()
{
    std::vector<graph_element> edges(3);
    edges[0].src = 1;
    edges[0].dest = 2;
    edges[1].src = 1;
    edges[1].dest = 3;
    edges[2].src = 2;
    edges[2].dest = 1;
    Graph graph(3, edges);
    std::cout << "Graph" << std::endl;
    graph.print();
    graph.add_node();
    std::cout << "Graph after adding one node" << std::endl;
    graph.print();
    graph_element e;
    e.src = 4;
    e.dest = 1;
    graph.add_edge(e);
    std::cout << "Graph after adding egde {4, 1}" << std::endl;
    graph.print();
    std::cout << "BFS" << std::endl;
    graph.print_bfs();
    graph.delete_node(2);
    std::cout << "Graph after deleting node - 2" << std::endl;
    graph.print();
    std::cout << "BFS" << std::endl;
    graph.print_bfs();

    return 0;
}

