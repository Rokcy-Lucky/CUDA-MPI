#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpleMPI.h"

int main(int argc, char *argv[])
{
	int blockSize = 5;
	int gridSize = 2;
	int dataSizePerNode = gridSize * blockSize;

	MPI_Init(&argc, &argv);

	int commSize, commRank;
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);

	int dataSizeTotal = dataSizePerNode * commSize;
	float *dataRoot = NULL;

	if (commRank == 0)  
	{
		printf("Running on %d nodes\n", commSize);
		dataRoot = new float[dataSizeTotal];
		initData(dataRoot, dataSizeTotal);
		printData(dataRoot,dataSizeTotal);	
	}

	float *dataNode = new float[dataSizePerNode];
	MPI_Scatter(dataRoot,dataSizePerNode,MPI_FLOAT,dataNode,dataSizePerNode,MPI_FLOAT,0,MPI_COMM_WORLD);
	
	if (commRank == 0)
	{
		delete[] dataRoot;
	}

	printf("\n--------进程号：%d--------\n",commRank);
	printData(dataNode,dataSizePerNode);

	computeGPU(dataNode, blockSize, gridSize);

	MPI_Gather(dataNode, dataSizePerNode, MPI_FLOAT, dataRoot, dataSizePerNode,MPI_FLOAT,0, MPI_COMM_WORLD);

	if (commRank == 0)
	{
	printf("Pow Result:\n");
	printData(dataRoot,dataSizeTotal);	
	}

	delete[] dataNode;
	MPI_Finalize();

	if (commRank == 0)
	{
		printf("PASSED\n");
	}
	return 0;
}



