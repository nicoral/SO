#include "Process.h"
#include "dialog.h"

map<Int64,string> Process::m_states= {
    {0,"New"},
    {1,"Running"},
    {2,"Ready"},
    {3,"Blocked"},
    {4,"Exit"},
};

Process::Process()
    :m_state(0),m_priority(0),m_time(0),m_resources(false),m_finalcondition(false){
    m_identifier=new string("");

}
Process::Process(string* id,Int64 pri,Int64 t,bool r)
    :m_state(0),m_priority(pri),m_time(t),m_resources(r),m_timeElapsed(0),m_finalcondition(false)
{
    m_identifier=id;
    m_registro.push_back(0);
}
