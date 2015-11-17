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

#include <client.h>
#include <cobjectfactory.h>
#include <cregistrationlist.h>
#include <job_m.h>
#include <onstartup.h>
#include <regmacros.h>
#include <simutil.h>

Define_Module(Client);

void Client::initialize()
{
   scheduleNew();
}


void Client::handleMessage(cMessage *msg)
{
    send(msg, "outClient");
    scheduleNew();
}


void Client::scheduleNew()
{
    //initialize rv
    IATrv=exponential((double)par("meanIAT"));
    STrv=exponential((double)par("meanST"));

    //create job
    job *pkt=new job("pkt");
    pkt->setST( STrv);

    //schedule job
    scheduleAt(simTime()+IATrv, pkt);

}
