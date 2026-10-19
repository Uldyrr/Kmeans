#include "Cluster_t.h"
#include <stdlib.h>
#include <stdio.h>


Cluster_t* CreateCluster(Vector2_t* initialCentroid) {
    Cluster_t* cluster = (Cluster_t*)malloc(sizeof(Cluster_t));

    if (cluster == NULL) {
        printf("Unable to allocate %zu bytes for cluster\n", sizeof(Cluster_t));
        return NULL;
    }

    cluster->Points = CreateList(LIST_DEFAULT_CAPACITY);
    cluster->Centroid = CopyVector2(initialCentroid);
    cluster->PreviousCentroid = CopyVector2(initialCentroid);

    return cluster;
}

void DestroyCluster(Cluster_t* cluster) {
    if (cluster == NULL) return;
    if (cluster->Points != NULL) DestroyList(cluster->Points, 1);
    if (cluster->Centroid != NULL) DestroyVector2(cluster->Centroid);
    if (cluster->PreviousCentroid != NULL) DestroyVector2(cluster->PreviousCentroid);

    free(cluster);
}