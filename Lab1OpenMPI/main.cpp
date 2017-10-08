//
//  main.cpp
//  Lab1OpenMPI
//
//  Created by Алексей Лазарев on 10/8/17.
//  Copyright © 2017 Алексей Лазарев. All rights reserved.
//

#include <iostream>
#include <mpi.h>

using namespace std;

void sendMessageFrom(int sender, int numberOfProcesses) {
    for (int i = sender + 1; i < numberOfProcesses; i++) {
        cout << "Procees " << sender << " send message to process: " << i << endl;
        MPI_Send(&sender, 1, MPI_INT, i ,0, MPI_COMM_WORLD );
    }
}

void reciveMessageFrom(int sender, int numberOfProcces, MPI_Status status) {
    for (int i = sender + 1; i < numberOfProcces; i++) {
        int senderNumber;
        MPI_Recv(&senderNumber, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        cout << "Process " << i << " recived message from process " << senderNumber << endl;
    }
}

int main(int argc, const char * argv[]) {
    int rank, n;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    
    for (int i = rank; i < n; i++) {
        sendMessageFrom(i, n);
        reciveMessageFrom(i, n, status);
        
    }
    
    MPI_Finalize( );
    return 0;
}
