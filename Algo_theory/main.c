#include<stdio.h>
#include<stdbool.h>

#define uint unsigned int
#define UNMATCHED 0xffffffff
#define MAX_INSTANCE_SIZE 500

// Global variables

// size_A -- no. of nodes in set A
// size_B -- no. of nodes in set B
// num_edges -- total no. of edges from set A to set B
uint size_A, size_B, num_edges;

// This is used to store the degre of every node in the Graph
uint adj_size[MAX_INSTANCE_SIZE];

// This stores the adjacency info about every node in the Graph
uint graph[MAX_INSTANCE_SIZE][MAX_INSTANCE_SIZE];

// This stores the info of the matching
// It stores UNMATCHED if the node is not matched to any other vertex
uint matched[MAX_INSTANCE_SIZE];

// This stores the info whether a node has been visited or not
bool visited[MAX_INSTANCE_SIZE];

// This struct stores the type of the set and the id of the node.
typedef struct _vertex {
  char type;
  uint id;
} vertex;


// The following two functions helps us to store the nodes of both sets
// in a single array

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
// This function adds edge between two nodes from set A and set B
void insert(uint index, uint val){

    graph[index][adj_size[index]] = val;

    adj_size[index]++;
}

// augmenting_path function...
bool augment_path(uint uid) {
  visited[uid] = true;

  for(int i=0;i<adj_size[uid];i++){
    uint nbr = graph[uid][i];

    if(visited[nbr]){
      continue;
    }

    if(matched[nbr] == UNMATCHED){
      matched[uid] = nbr;
      matched[nbr] = uid;
      return true;
    }

    else if(matched[nbr] != uid){
      // This is a simple DFS algorithm but we only apply DFS if there exists an augmenting path from the martched vertex of the neighbouring node.
      
      visited[nbr] = true;

      if(augment_path(matched[nbr])){
        matched[uid] = nbr;
        matched[nbr] = uid;
        return true;
      }
    }

  }
    return false;
}

int main(){
  
    
    // Initializing the matched array with every vertex as UNMATCHED...
    for(int i=0;i<MAX_INSTANCE_SIZE;i++){
        matched[i] = UNMATCHED;
    }
    
    // Initializing the adjacency size matrix with zero...
    // This stores the degree of each node
    for(int i=0;i<MAX_INSTANCE_SIZE;i++){
        adj_size[i] = 0;
    }
  
  // Reading input...
  scanf("%d %d %d\n", &size_A, &size_B, &num_edges);

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
  }
  
  // Initializing the size of matching...
  int size_matching = 0;

  
  // Checking for augmenting path from each node wrt current matching
  for(int i=0;i<size_A;i++){
    if(matched[i] == UNMATCHED){
      
      for(int i=0;i<MAX_INSTANCE_SIZE;i++){
        visited[i] = false;
      }

      if(augment_path(i)){
        size_matching++;
      }
    }
  }
  
  // Output
  printf("The size of the matching is: %d \n", size_matching);

  for(int i=0;i<size_A;i++){
    if(matched[i]!=UNMATCHED){
      vertex A = uid_to_vertex(i);
      vertex B = uid_to_vertex(matched[i]);
      printf("A%d B%d \n", A.id, B.id);
    }
  }

}

