//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <cmessage.h>
#include <cobjectfactory.h>
#include <cregistrationlist.h>
#include <onstartup.h>
#include <regmacros.h>
#include <server.h>
#include <simutil.h>
#include <iostream>
#include <queue>

using namespace std;

Define_Module(Server);

void Server::initialize()
{
    idle = true;

    tempicoda = new simtime_t[(int)par("sizeR")];

    //statistics
    s_nPackets = registerSignal("nPackets");
    s_nWorksArrived = registerSignal("nWorksArrived");
    s_nWorksServed = registerSignal("nWorksServed");
    //s_nWorksDropped = registerSignal("nWorksDropped");
    s_queueTime = registerSignal("queueTime");
    s_batchWorkTime = registerSignal("batchWorkTime");
    s_batchWorkSize = registerSignal("batchWorkSize");
    s_responseTime = registerSignal("responseTime");
    s_nidle=registerSignal("nidle");
}


void Server::handleMessage(cMessage *msg)
{
    ev <<"handler\n";

    if ( msg->isSelfMessage() )
    {
        ev<<"batch finito\n";

        delete msg;

        /**
         * gestione emit riferiti al batch appena terminato
         */

        for(int j=0 ; j<i ; j++){
            ev<<"emetto response time  "<<j<<"\n";
            emit(s_responseTime, tempicoda[j]+sommaST);
        }


        emit(s_nWorksServed, i);            //statistica globale di lavori serviti
        emit(s_batchWorkTime,sommaST);      //tempo di un batch
        emit(s_batchWorkSize,i);            //pachetti per batch



        if( !coda.empty() ){    //coda non vuota
            ev<<"coda non vuota chiamo il successivo batch\n";
            idle = false;
            workBatch();
        } else {
            ev<<"coda vuota vado in idle\n";
            idle = true;
            emit(s_nidle,1);
        }
    } else {
        ev<<"messaggio esterno\n";

        //saving number of packets in the queue
         emit(s_nPackets, (int)coda.size());
         emit(s_nWorksArrived, 1); //number of arrived jobs

         ev<<"push\n";
         dynamic_cast<job*>(msg)->setEnterQueue(simTime());
         coda.push(  dynamic_cast<job*>(msg) );

         if( idle ){
             idle = false;
             workBatch();
         }
    }
    ev <<"finehandler\n";
}


void Server::workBatch()
{
    sommaST = 0;

    ev <<"work\n";

    //inizializzazione
    int R=(int)par("sizeR");
    sommaST=exponential( (double)par("batchST") );

    ev<<"tempo di batch"<<sommaST <<"\n";

    for (i=0; i<R;i++)
    {
        ev<<"ciclo: "<<i<<endl;

        if ( coda.empty() ){
            ev<<"\tcoda svuotata\n";
            break;
        } else {
            ev<<"\tpop\n";

            job *support = coda.front();
            tempicoda[i] = simTime() - ( support->getEnterQueue() );
            emit(s_queueTime,tempicoda[i]); //tempo che va dalla coda al server
            coda.pop();
            delete support; //perche coda.pop() non chiama il distruttore
        }
    }
    scheduleAt(simTime()+sommaST, new cMessage);

    ev <<"endwork\n";
}


void Server::finish()
{
    while( !coda.empty() ){
        job *support = coda.front();
        coda.pop();
        delete support;
    }
    delete tempicoda;
}
