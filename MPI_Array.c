#include <stdio.h>
#include <mpi.h>


void main(int argc,  char *argv[]) {
    MPI_Status status;
    int i, rank, size;
    int array_size;
    int tag=1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int array[array_size];
    if (rank == 0) {
        printf("Enter the size of the array.\n");
        scanf("%i", &array_size);
	for( i=0; i<array_size; i++){
	    array[i] = i+1;
        }
	MPI_Send(&array,array_size,MPI_INT,(size-1),tag,MPI_COMM_WORLD);
    }
    MPI_Bcast(&array_size,1,MPI_INT, 0, MPI_COMM_WORLD);
    if (rank != 0 && rank != size-1) {
	printf("process %d: After MPI_Bcast, the size of the array is %d\n", rank,array_size);
    }
    else {
	MPI_Recv(&array,array_size,MPI_INT,0,tag,MPI_COMM_WORLD, &status);
	printf("process %d: I am the last process! The array is: ", rank);
	for( i=0; i<array_size;i++){
	    printf("%d " , array[i]);
        }
	printf("\n");
        MPI_Finalize();
    }
}


