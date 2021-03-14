#include<stdio.h>
#include<stdbool.h>

#define uint unsigned int
#define UNMATCHED 0xffffffff

#define MAX_INSTANCE_SIZE 500

// Global variables

uint size_A, size_B, num_edges;

uint adj_size[MAX_INSTANCE_SIZE];

uint graph[MAX_INSTANCE_SIZE][MAX_INSTANCE_SIZE];

uint matched[MAX_INSTANCE_SIZE];

bool visited[MAX_INSTANCE_SIZE];

typedef struct _vertex {
  char type;
  uint id;
} vertex;

// converts the vertex to uid...

uint vertex_to_uid(vertex v) {
  return ((v.type == 'A') ? 0 : size_A) + v.id;
}

// converts the uid to vertex...

vertex uid_to_vertex(uint uid) {
  vertex ret;
  if (uid < size_A) {
    ret = (vertex) { 'A', uid };
  } else {
    ret = (vertex) { 'B', uid - size_A };
  }
  ret.type = (uid < size_A) ? 'A' : 'B';
  ret.id = (uid < size_A) ? uid : uid - size_A;
  return ret;
}

// Insert Function...



void insert(uint index, uint val){
    // int i=0;
    // // while(graph[index][i]!=-1){
    // //     i++;
    // // 

    graph[index][adj_size[index]] = val;

    adj_size[index]++;
}

int main(){
    
    for(int i=0;i<MAX_INSTANCE_SIZE;i++){
        matched[i] = UNMATCHED;
    }
    
    // Initializing size matrix...
    for(int i=0;i<MAX_INSTANCE_SIZE;i++){
        adj_size[i] = 0;
    }

  // Standard competition practice of using cstdio instead of iostream
  scanf("%d %d %d\n", &size_A, &size_B, &num_edges);

  // Reading input
  vertex vertex_A, vertex_B;
  uint uid_A, uid_B;
  uint i;

  for(int i=0;i<MAX_INSTANCE_SIZE;i++){
      graph[i][0] = -1;
  }

  for (i = 0; i < num_edges; i++) {
    scanf("%c%d %c%d\n", &vertex_A.type, &vertex_A.id, &vertex_B.type, &vertex_B.id);
    uid_A = vertex_to_uid(vertex_A);
    uid_B = vertex_to_uid(vertex_B);

    insert(uid_A, uid_B);

    insert(uid_B, uid_A);
    // Build adjacency list
    // graph[uid_A][i] = (uid_B);
    // graph[uid_A][i+1] = -1;
    // graph[uid_B][i] = (uid_A);
    // graph[uid_B][i+1] = -1;
  }

  for(int i=0;i<(size_A+size_B);i++){
      for(int j=0;j<adj_size[i];j++){
          printf("%d ",graph[i][j]);
      }
      printf("\n");
  }

//   graph[uid_A][i] = -1;
//   graph[uid_B][i] = -1;


}

/*
Input :

5 5 10
A0 B0
A1 B0
A2 B0
A2 B1
A3 B1
B2 A3
A4 B2
B1 A4
B3 A4
B4 A4


Output : 

5 
5 
5 6 
6 7 
7 6 8 9 
0 1 2 
2 3 4 
3 4 
4 
4 

*/