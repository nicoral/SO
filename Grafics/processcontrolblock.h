#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H
#include "Process.h"
#include <queue>
using namespace std;
class Compare
{
public:
    bool operator() (Process *A, Process *B)
    {
        return A->getPriority()<B->getPriority();
    }
};
class Compare2
{
public:
    bool operator() (Process *A, Process *B)
    {
        return A->getTime()<B->getTime();
    }
};

typedef std::priority_queue<Process*,vector<Process*>, Compare> minheap;
typedef std::priority_queue<Process*,vector<Process*>, Compare2> minheap2;
class ProcessControlBlock {
    public:
        string m_hora;
        Int64 m_executions;
        bool m_printer;
        minheap m_procesos;
        minheap2 m_blocks;
        queue<Process*> m_exits;
    public:
        ProcessControlBlock()
            :m_hora(""),m_executions(0){}
        void addprocess(Process* P)
        {
            m_procesos.push(P);
        }
        void prepare()
        {
            //cambio del estado de nuevo a listo
            if(!m_procesos.empty())
                m_procesos.top()->changestate(2);
        }
        void executeProcess()
        {
            //ofstream newFile("informe.txt",ios_base::app );
            while(!this->m_blocks.empty())
            {
                (this->m_blocks.top())->run(true);
                this->m_exits.push(this->m_blocks.top());
                this->m_blocks.pop();
            }
        }
        void inform()
        {
            ofstream newFile("ExecutionsPriorities.txt", std::ios_base::app);
            while(!m_exits.empty())
            {
                (m_exits.front())->print(newFile);
                m_exits.pop();
            }
//			newFile<<"Total executions:"<<end;
        }

};

#endif

