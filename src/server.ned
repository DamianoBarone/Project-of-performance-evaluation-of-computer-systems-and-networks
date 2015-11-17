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

package batchserver;

//
// TODO auto-generated module
//
simple Server
{
    parameters:
        //int sizeQueue;		//dimensione queue //da non usare in caso di coda infinita
        int sizeR;				//dimensione batch
        double  batchST;
        
        //statistics
        
        //number of packets in queue
      	@statistic[nPackets](source="nPackets"; record=stats, vector;);
      	//number of works arrived
        @statistic[nWorksArrived](source="nWorksArrived"; record=sum;);
        //number of works served
        @statistic[nWorksServed](source="nWorksServed"; record=sum;);
        //number of works dropped
        //@statistic[nWorksDropped](source="nWorksDropped"; record=sum;);
        //nidle
        @statistic[nidle](source="nidle"; record=sum,vector;);
        //queue time
        @statistic[queueTime](source="queueTime"; record=stats, vector,histogram;);
        //batch work time
        @statistic[batchWorkTime](source="batchWorkTime"; record=stats, vector,histogram;);
        //batch work size
        @statistic[batchWorkSize](source="batchWorkSize"; record=stats, vector;);
        //response time
        @statistic[responseTime](source="responseTime"; record=stats, vector,histogram;);
        
        
    gates:
        input inServer;
}
