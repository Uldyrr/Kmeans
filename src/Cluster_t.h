#ifndef CLUSTER_H_
#define CLUSTER_H_

#include "Vector2_t.h"
#include "List_t.h"

typedef struct {
    List_t* Points;
    Vector2_t* Centroid; 
    Vector2_t* PreviousCentroid;
} Cluster_t;

Cluster_t* CreateCluster(Vector2_t* initialCentroid); 
void DestroyCluster(Cluster_t* cluster);

#endif