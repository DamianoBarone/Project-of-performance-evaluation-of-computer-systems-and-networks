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

#ifndef __BATCHSERVER_SERVER_H_
#define __BATCHSERVER_SERVER_H_

#include <job_m.h>
#include <omnetpp.h>
#include <cstdlib>
#include <queue>
#include <queue>

using namespace std;
/**
 * TODO - Generated class
 */
class Server : public cSimpleModule
{
    private:
        queue<job*> coda;
        bool idle;

        //strutture per gestire la fine dei batch
        simtime_t *tempicoda;
        double sommaST;
        int i;

        //statistics
        simsignal_t s_nPackets;
        simsignal_t s_nWorksArrived;
        simsignal_t s_nWorksServed;
        simsignal_t s_queueTime;
        simsignal_t s_batchWorkTime;
        simsignal_t s_batchWorkSize;
        simsignal_t s_responseTime;
        simsignal_t s_nidle;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void workBatch();
        virtual void finish();
};

#endif
