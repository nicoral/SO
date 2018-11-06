#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <windows.h>
#include <stdio.h>
#include <tuple>
#include <fstream>
#include <string>

using namespace std;

//Tabla de estados posibles
typedef unsigned int Int64;
class Process {
    private:
        static  map<Int64,string> m_states;
        string* m_identifier;
        Int64 m_state;//se cambiará por un map de <code,state>
        Int64 m_priority;//nivel de prioridad
        Int64 m_time;//tiempo estimado de ejeccución
        Int64 m_timeElapsed;//tiempo transcurrido hasta la ejecuión del proceso
        bool m_resources;//en caso requiera disposividos de entrada o salida I/O
        bool m_finalcondition;//en caso el proceso haya sido abortado será true;
        vector<Int64> m_registro;//guardara el registro de cambios de estado
    public:
        Process();
        /*Un proceso siempre se creara como nuevo*/
        Process(string *id, Int64 pri, Int64 t, bool r);
        Int64 getPriority()
        {
            return m_priority;
        }
        Int64 getTime()
        {
            return m_time;
        }

        void changestate(Int64 nstate)
        {
            m_state=nstate;
            m_registro.push_back(nstate);
        }
        void print(ostream &os)
        {
            os<<"..."<<*m_identifier<<".."<<endl;
            os<<"State: "<<m_state<<endl;
            os<<"Priority: "<<m_priority<<endl;
            os<<"Time: "<<m_time<<endl;
            os<<"Resources: "<<m_resources<<endl;
            os<<"Registro de estados"<<endl;
            std::vector<Int64>::const_iterator iter= m_registro.begin();
            for(iter; iter != m_registro.end(); ++iter)
                os<<*iter<<":"<<m_states[*iter]<<endl;
            if(m_finalcondition)
                os<<"el proceso fué abortado"<<endl;
            else
                os<<"OK"<<endl;
            os<<"-----------------------"<<endl;
        }
        bool run(bool order)
        {
            //utilizar chrono para detener tiempo y poner en runninng 3 luego 4
            changestate(1);
            Sleep(m_time*1000);
            m_registro.push_back(1);
            std::cout<<m_time*1000<<std::endl;
            if(order)
                changestate(4);
            return true;
        }
};



#endif

