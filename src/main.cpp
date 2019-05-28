#include "AirShuttle/AirShuttle.h"
#include "AirShuttle/ServicesPlanner.h"
#include "Graph/Graph.h"
#include "Utils/GraphLoader.h"
#include "Utils/MapDrawer.h"
#include "Utils/MapTag.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <iostream>
#include <ratio>

using namespace std;

int main() {
  vector<string> maps = {"Aveiro",   "Braga",  "Coimbra", "Ermesinde", "Fafe",
                         "Gondomar", "Lisboa", "Maia",    "Porto",     "Viseu"};
  vector<int> aeroports = {1074045106,    914277436, 711049847, 25452377,
                           26130602,      112624378, 582518618, 26058112,
                           PORTO_AIRPORT, 26023654};
  vector<string> reservations = {"reservations_100.txt", "reservations_500.txt",
                                 "reservations_1000.txt", "reservations_5000.txt",
                                 "reservations_10000.txt"};

  for (unsigned i = 2; i < 3; i++){
    for (unsigned j = 0; j < reservations.size(); j++) {
      Graph graph;
      GraphLoader::loadGraph(maps.at(i), &graph);

      ServicesPlanner planner(&graph, aeroports.at(i), 3);
      planner.addReservationsFromFile(maps.at(i), reservations.at(j));
      planner.preProcessEntryData();
      //graph.dijkstraShortestPath(aeroports.at(i));

       auto start_time = chrono::high_resolution_clock::now();

      planner.planSingleVanNotMixingPassengers();
      // planner.planSingleVanMixingPassengers();
      // planner.planVansFleetMixingPassengers();

      auto finish = chrono::high_resolution_clock::now();
      auto mili =chrono::duration_cast<chrono::milliseconds>(finish - start_time).count();
              
          
      
       cout  <<reservations.at(j)<<": " << mili <<"\n";
                 /*
                         int counter = 1;
                         for (const Van& v: planner.getVans()) {
                                 cout << "Van " << counter << ": \n";
                                 int sCounter = 1;
                                 for (Service& s: v.getServices()) {
                                         cout << "\tService " << sCounter <<
                    endl; cout << "\t\t" << s.getStart() << " -> " << s.getEnd()
                    << "\n"; cout << "\t\t" << s.getVacant() << "\n\n";

                                         for (const Reservation& r:
                    s.getReservations()) { cout << "\t\t" << r.getClientName()
                    << " - " << r.getArrival() << " -> " << r.getDeliver() <<
                    "\n";
                                         }
                                         sCounter++;
                                         cout << endl << endl;
                                 }
                                 counter++;
                         }
                         */

                     // graph.DFSConnectivity(graph.findVertex(PORTO_AIRPORT));
                     // graph.removeUnvisitedVertices();
                     // MapDrawer mapDrawer(2000, 2000);
                     // mapDrawer.drawMapFromGraph(&graph);
                     // mapDrawer.getViewer()->setVertexColor(474695389 , RED);
                     // mapDrawer.getViewer()->setVertexSize(474695389, 5);
                     // mapDrawer.getViewer()->setVertexColor(PORTO_AIRPORT ,
                     // RED); mapDrawer.getViewer()->rearrange();
                     // mapDrawer.drawMapFromPlannerSingleVan(&planner);
                         
      // getchar();

      // auto start_time = chrono::high_resolution_clock::now();
      // auto finish = chrono::high_resolution_clock::now();
      // auto mili = chrono::duration_cast<chrono::milliseconds>(finish -
      // start_time).count();
    }
}

return 0;
}
