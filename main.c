#include "src/Cluster_t.h"
#include "src/Vector2_t.h"
#include "src/List_t.h"
#include <stdio.h>
#include <float.h>


List_t* GetPoints(float* pointsValues, int pointsValuesSize) {
    List_t* points = CreateList(LIST_DEFAULT_CAPACITY);

    for (uint64_t i = 0; i < pointsValuesSize; i += 2) {
        ListAdd(points, CreateVector2(pointsValues[i], pointsValues[i+1]));
    }

    return points;
}

List_t* KMeansAlgorithm(List_t* points, uint16_t K) {
    // 1. Create K clusters with simple initial centroids
    List_t* clusters = CreateList(K);
    uint64_t countOfPoints = ListLength(points);

    for (int i = 0; i < K; i++) {
        ListAdd(clusters, CreateCluster((Vector2_t*)ListIndex(points, i)));
    }

    // 2. Repeatedly recalculate the center point of each cluster until no changes are made
    // Note: We will use euclidean distance
    Vector2_t* point;
    Cluster_t* cluster;
    int iterations = 1;
    register uint64_t i; 
    register uint16_t j;

    while (1) {
        iterations++;

        // 2.1. Clear all points of each cluster
        for (j = 0; j < K; j++) {
            ListClear(((Cluster_t*)ListIndex(clusters, j))->Points);
        }

        // 2.2. For each point, find closest cluster, and then assign it to that cluster
        Cluster_t* closestCluster = ListIndex(clusters, 0);
        register float dist;
        register float closestClusterDist;

        for (i = 0; i < countOfPoints; i++) {
            point = ListIndex(points, i);
            closestClusterDist = FLT_MAX;

            for (j = 0; j < K; j++) {
                cluster = ListIndex(clusters, j);

                if ((dist = Vector2DistanceBetween(point, cluster->Centroid)) < closestClusterDist) {
                    closestClusterDist = dist;
                    closestCluster = cluster;
                }
            }

            ListAdd(closestCluster->Points, point);
        }

        // 2.3. Recalculate centroids and check if any centroids have changed
        float xTotal, yTotal;
        uint64_t totalCount;
        uint8_t centroidsStable = 1;

        for (j = 0; j < K; j++) {
            cluster = ListIndex(clusters, j);
            xTotal = 0.0f;
            yTotal = 0.0f;
            totalCount = ListLength(cluster->Points);

            for (i = 0; i < totalCount; i++) {
                point = ListIndex(cluster->Points, i);
                xTotal += point->X;
                yTotal += point->Y;
            }

            xTotal /= (float)totalCount;
            yTotal /= (float)totalCount;
            cluster->Centroid->X = xTotal;
            cluster->Centroid->Y = yTotal;

            // 2.3.1 Check centroid change
            if (centroidsStable) centroidsStable = Vector2Equality(cluster->Centroid, cluster->PreviousCentroid);

            cluster->PreviousCentroid->X = xTotal;
            cluster->PreviousCentroid->Y = yTotal;
        }

        if (centroidsStable) break;
    }

    printf("Iterations: %i\n", iterations);

    return clusters;
}


int main() {
    const int K = 4;
    float pointsValues[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.1f, 0.1f,
        1.1f, 1.1f,
        0.1f, 1.1f,
        0.1f, 0.1f,

        1.2f, 0.2f,
        1.2f, 1.2f,
        0.2f, 1.2f,
        0.2f, 0.2f
    }; 
    List_t* points = GetPoints(pointsValues, sizeof(pointsValues) / sizeof(float));
    List_t* clusters = KMeansAlgorithm(points, K);

    printf("Clusters found:\n");

    for (int i = 0; i < K; i++) {
        Vector2_t* centroid = ((Cluster_t*)ListIndex(clusters, i))->PreviousCentroid;

        printf("Cluster %i: %f, %f\n", i + 1, centroid->X, centroid->Y);
    }

    return 0;
}

