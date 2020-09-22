# transport-network
Building a public transportation network through object-oriented planning and providing a computational envelope of queries.

The transport network includes nodes representing stopping stations of different types, and a number of different transport vehicles connecting
Between the nodes.

Existing means of transportation: bus, tram, sprinter, rail.
Types of nodes: intercity, centraal, stad.

The program will answer questions such as: a query for finding the group of stations linked to a given point, a query for finding the group of stations from which there is a link to a given point, a query for calculating the shortest route between two stations and more.
We chose to work with a multi-graph that contains the entire transport network.
In addition we hold an inverse graph.
