MPICC=/usr/local/mpich/bin/mpic++
NVCC=/usr/local/cuda-10.2/bin/nvcc

MPI_INCLUDE= -I /usr/local/mpich/include
CUDA_LIBS= -L /usr/local/mpich/lib

CUDA_INCLUDE= -I /usr/local/cuda-10.2/include
CUDA_LIBS= -L /usr/local/cuda-10.2/lib64 -lcudart 

CFILES=simpleMPI.c
CUFILES=simpleCu.cu
OBJECTS=simpleMPI.o simpleCu.o

all: 
	$(MPICC)  -c $(CFILES)  -o simpleMPI.o


	$(NVCC) $(CUDA_INCLUDE)  -c $(CUFILES) -o simpleCu.o 


	$(MPICC)  $(CUDA_LIBS) $(OBJECTS) -o simpleMPI 
run: 
	 mpirun -n  2 ./simpleMPI
clean:
	rm -f simpleMPI simpleCu.o simpleMPI.o

